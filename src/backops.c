#include "backops.h"

void backward(tensor_t *self)
{
    if (self->backward == NULL)
    {
        log_debug("Node %p has no backward.", (void*) self);
        return;
    }

    self->backward(self);
}

void init_grad(tensor_t *self)
{   
    if (! self->requires_grad || self->grad) return;
    self->grad = smalloc(.size = self->size, .nmemb = sizeof(float), .kind = SHARED);
    tensor_zero_grad(self);
}

// UPDATE OPS
void update_grad_add(tensor_t *self, tensor_t *child)
{
    if (!child->requires_grad)
        return;
    
    for (int i = 0; i < self->size; i++)
    {
        child->grad[i] += self->grad[i];
    }
}

void update_grad_relu(tensor_t *self, tensor_t *child)
{
    if (!child->requires_grad)
        return;
    for (int i = 0; i < self->size; i++)
    {
        child->grad[i] += self->grad[i] * (self->data[i] > 0);
    }
}

void update_grad_mul(tensor_t *self, tensor_t *child, tensor_t *other)
{
    if (!child->requires_grad)
        return;

    int k;
    for (int i = 0; i < self->size; i++)
    {
        k = (other->size == 1) ? 0 : i;
        child->grad[i] += self->grad[i] * other->data[k];
    }
}

void update_grad_pow(tensor_t *self, tensor_t *child, tensor_t *other)
{
    if (!child->requires_grad)
        return;

    int k;
    for (int i = 0; i < self->size; i++)
    {
        k = (other->size == 1) ? 0 : i;
        child->grad[i] += self->grad[i] * other->data[k] * powf(child->data[i], other->data[k] - 1);
    }
}

void update_grad_exp(tensor_t *self, tensor_t *child, tensor_t *other)
{
    if (!child->requires_grad)
        return;

    int k;
    for (int i = 0; i < self->size; i++)
    {
        k = (other->size == 1) ? 0 : i;
        child->grad[i] += self->grad[i] * self->data[i] * logf(other->data[k]);
    }
}

void update_grad_sum(tensor_t *self, tensor_t *child)
{
    if (!child->requires_grad)
        return;
    for (int i = 0; i < child->size; i++)
    {
        child->grad[i] += self->grad[0];
    }
}

// UNARY OPS
void backward_relu(tensor_t *self)
{
    if (self->child1 == NULL)
    {
        log_debug("Child of tensor %p is NULL. Reached end of tree.", (void *)self);
        return;
    }
    init_grad(self->child1);
    update_grad_relu(self, self->child1);
    backward(self->child1);
}

// BINARY OPS
void backward_add(tensor_t *self)
{
    if (self->child1 == NULL || self->child2 == NULL)
    {
        log_debug("Child of tensor %p is NULL. Reached end of tree.", (void *)self);
        return;
    }
    init_grad(self->child1);
    init_grad(self->child2);

    update_grad_add(self, self->child1);
    update_grad_add(self, self->child2);

    backward(self->child1);
    backward(self->child2);
}

void backward_mul(tensor_t *self)
{
    if (self->child1 == NULL || self->child2 == NULL)
    {
        log_debug("Child of tensor %p is NULL. Reached end of tree.", (void *)self);
        return;
    }
    init_grad(self->child1);
    init_grad(self->child2);

    update_grad_mul(self, self->child1, self->child2);
    update_grad_mul(self, self->child2, self->child1);

    backward(self->child1);
    backward(self->child2);
}

void backward_pow(tensor_t *self)
{
    if (self->child1 == NULL)
    {
        log_debug("Child of tensor %p is NULL. Reached end of tree.", (void *)self);
        return;
    }
    init_grad(self->child1);
    init_grad(self->child2);
    
    update_grad_pow(self, self->child1, self->child2);
    update_grad_exp(self, self->child2, self->child1);

    backward(self->child1);
    backward(self->child2);
}

// REDUCE OPS
void backward_sum(tensor_t *self)
{
    if (self->child1 == NULL)
    {
        log_debug("Child of tensor %p is NULL. Reached end of tree.", (void *)self);
        return;
    }
    init_grad(self->child1);
    update_grad_sum(self, self->child1);
    backward(self->child1);
}
#include "ops.h"

// TODO:
// before any operation, check if full range is used
// if so, iterate over data contiguous memory
// if not, use iterator to iterate over data

float *addt(tensor_t *a, tensor_t *b)
{   
    int k;
    float *data = smalloc(.size = a->size, .nmemb = sizeof(float), .kind = SHARED);
    for (int i = 0; i < a->size; i++)
    {   
        k = (b->size == 1) ? 0 : i;
        data[i] = a->data[i] + b->data[k];
    }
    return data;
}

float *mult(tensor_t *a, tensor_t *b)
{   
    int k;
    float *data = smalloc(.size = a->size, .nmemb = sizeof(float), .kind = SHARED);
    for (int i = 0; i < a->size; i++)
    {   
        k = (b->size == 1) ? 0 : i;
        data[i] = a->data[i] * b->data[k];
    }
    return data;
}

float *powt(tensor_t *a, tensor_t *b)
{   
    int j, k;
    int size = (a->size > b->size) ? a->size : b->size;
    float *data = smalloc(.size = size, .nmemb = sizeof(float), .kind = SHARED);
    for (int i = 0; i < a->size; i++)
    {   
        j = (a->size == 1) ? 0 : i;
        k = (b->size == 1) ? 0 : i;
        data[i] = powf(a->data[j], b->data[k]);
    }
    return data;
}

// tensor_t *tensor_mul_tf(tensor_t *a, float b)
// {
//     tensor_t *out = tensor_init(a->shape, a->ndim, a->requires_grad);
//     for (int i = 0; i < a->size; i++)
//     {
//         out->data[i] = a->data[i] * b;
//     }
//     out->child1 = a;
//     out->child2 = tensor((float[]){b}, (int[]){1}, 1, false);
//     if (out->requires_grad)
//         out->backward = backward_mul;

//     return out;
// }

// tensor_t *tensor_pow_tf(tensor_t *a, float b)
// {
//     tensor_t *out = tensor_init(a->shape, a->ndim, a->requires_grad);
//     for (int i = 0; i < a->size; i++)
//     {
//         out->data[i] = powf(a->data[i], b);
//     }
//     out->child1 = a;
//     out->child2 = tensor((float[]){b}, (int[]){1}, 1, false);
//     if (out->requires_grad)
//         out->backward = backward_pow;

//     return out;
// }

// tensor_t *tensor_pow_ft(float a, tensor_t *b)
// {
//     tensor_t *out = tensor_init(b->shape, b->ndim, b->requires_grad);
//     for (int i = 0; i < b->size; i++)
//     {
//         out->data[i] = powf(a, b->data[i]);
//     }
//     out->child1 = tensor((float[]){a}, (int[]){1}, 1, false);
//     out->child2 = b;
//     if (out->requires_grad)
//         out->backward = backward_pow;

//     return out;
// }

// tensor_t *tensor_sum(tensor_t *a)
// {
//     tensor_t *out = tensor_init((int[]){1}, 1, a->requires_grad);
//     for (int i = 0; i < a->size; i++)
//     {
//         out->data[0] += a->data[i];
//     }
//     out->child1 = a;
//     if (out->requires_grad)
//         out->backward = backward_sum;

//     return out;
// }

// tensor_t *tensor_relu(tensor_t *a)
// {
//     tensor_t *out = tensor_init(a->shape, a->ndim, a->requires_grad);
//     for (int i = 0; i < a->size; i++)
//     {
//         out->data[i] = (a->data[i] > 0.0) ? a->data[i] : 0.0;
//     }
//     out->child1 = a;
//     if (out->requires_grad)
//         out->backward = backward_relu;

//     return out;
// }

// tensor_t *tensor_add_ft(float a, tensor_t *b)
// {
//     return tensor_add_tf(b, a);
// }

// tensor_t *tensor_mul_ft(float a, tensor_t *b)
// {
//     return tensor_mul_tf(b, a);
// }

// tensor_t *tensor_pow(tensor_t *a, tensor_t *b)
// {
//     return tensor_pow_tt(a, b);
// }

// tensor_t *tensor_exp(tensor_t *a)
// {
//     return tensor_pow_ft(expf(1.0), a);
// }

// tensor_t *tensor_neg(tensor_t *a)
// {
//     return tensor_mul_tf(a, -1.0);
// }

// tensor_t *tensor_sub(tensor_t *a, tensor_t *b)
// {
//     return tensor_sub_tt(a, b);
// }

// tensor_t *tensor_sub_tt(tensor_t *a, tensor_t *b)
// {
//     return tensor_add(a, tensor_neg(b));
// }

// tensor_t *tensor_sub_tf(tensor_t *a, float b)
// {
//     return tensor_add_tf(a, -b);
// }

// tensor_t *tensor_sub_ft(float a, tensor_t *b)
// {
//     return tensor_add_ft(a, tensor_neg(b));
// }

// tensor_t *tensor_div(tensor_t *a, tensor_t *b)
// {
//     return tensor_div_tt(a, b);
// }

// tensor_t *tensor_div_tt(tensor_t *a, tensor_t *b)
// {
//     return tensor_mul(a, tensor_pow_tf(b, -1.0));
// }

// tensor_t *tensor_div_tf(tensor_t *a, float b)
// {
//     return tensor_mul_tf(a, 1.0 / b);
// }

// tensor_t *tensor_div_ft(float a, tensor_t *b)
// {
//     return tensor_mul_ft(a, tensor_pow_tf(b, -1.0));
// }
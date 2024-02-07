#include "tensor.h"
#include "ops.h"
#include "log.h"

int main()
{
    log_set_level(LOG_INFO);

    tensor_t *a = tensor_rand((int[]){3, 5, 10}, 3, false);
    tensor_t *b = tensor_rand((int[]){3, 1, 10}, 3, false);
    tensor_t *c = tensor_cat((tensor_t *[]){a, b}, 2, 1);
    tensor_print(a, PRINT_DATA);
    tensor_print(b, PRINT_DATA);
    tensor_print(c, PRINT_DATA);

    tensor_free(a, true);
    tensor_free(b, true);
    tensor_free(c, true);

    return 0;
}
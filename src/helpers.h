#include "log.h"
#include "tensor.h"
#include <math.h>
#include <stdbool.h>

#define EPSILON 1e-6
#define MAX_PRINT_SIZE 10

#define ASSERT(condition, format, ...)        \
    do                                        \
    {                                         \
        if (!(condition))                     \
        {                                     \
            log_error(format, ##__VA_ARGS__); \
            exit(EXIT_FAILURE);               \
        }                                     \
    } while (0)

// tensor helpers
int get_size(int shape[], int ndim);
int get_index(int coords[], int shape[], int ndim);

void swap_int(int *array, int index1, int index2);
void swap_slice(slice_t *array, int index1, int index2);

void set_data(float *data, float value, int size);
void normalize_range(slice_t range[], int shape[], int ndim);

void print_metadata(int data[], int ndim);
void print_data(float *data, slice_t shape[], int stride[], int ndim);
void copy_from_range(float *dst, float *src, slice_t range[], int stride[], int ndim);
void copy_to_range(float *dst, float *src, slice_t range[], int stride[], int ndim);

bool is_equal_data(float *data_a, float *data_b, int size);
bool is_same_shape(int shape_a[], int shape_b[], int ndim_a, int ndim_b);

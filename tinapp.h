#ifndef TINAPP_H
#define TINAPP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TINAPP_FEATURE_SELF 0
#define TINAPP_FEATURE_QUERY 1

#define TINAPP_DATA_MAX_SIZE 8

// All parameters  values are exchanged as strings of upto 8 characters
// Data types are inferred from format 1.20 (float), 12 (integer),
// 12:00:01 or 12:01 (time), 23-09-17 (date), text (enumeration)
typedef enum tinapp_attribute {
    TINAPP_ATTRIBUTE_NAME = 0,
    TINAPP_ATTRIBUTE_VALUE,
    TINAPP_ATTRIBUTE_UNITS,
    TINAPP_ATTRIBUTE_MINIMUM,
    TINAPP_ATTRIBUTE_MAXIMUM,
    TINAPP_ATTRIBUTE_STEP,
    TINAPP_ATTRIBUTE_ENUMERATE,
} tinapp_attribute;

typedef struct tinapp_data {
    char size;
    char data[TINAPP_DATA_MAX_SIZE];
} tinapp_data_t;

typedef struct tinapp_message_t {
    char node_id;
    char feature_id;
    char attribute_id;
    tinapp_data_t data;
} tinapp_message_t;

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* TINAPP_H */
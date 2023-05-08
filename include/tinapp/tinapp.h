#ifndef TINAPP_H
#define TINAPP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TINAPP_MAX_DATA_SIZE (8)


typedef enum tinapp_node{
    TINAPP_NONE = 0,
    TINAPP_NAME,
};

typedef enum tinapp_feature{
    TINAPP_NONE = 0,
    TINAPP_NAME,
};

typedef enum tinapp_access {
    TINAPP_ACCESS_NONE = 0,
    TINAPP_ACCESS_READ_ONLY,
    TINAPP_ACCESS_WRITE_ONLY,
    TINAPP_ACCESS_READ_WRITE,
};

typedef enum tinapp_type {
    TINAPP_TYPE_BOOL = 0,
    TINAPP_TYPE_U8,
    TINAPP_TYPE_S8,
    TINAPP_TYPE_U16,
    TINAPP_TYPE_S16,
    TINAPP_TYPE_U32,
    TINAPP_TYPE_S32,
    TINAPP_TYPE_F32,
};

typedef enum tinapp_units {
    TINAPP_UNITS_NONE = 0,
    TINAPP_UNITS_VOLT,
    TINAPP_UNITS_AMP,
    TINAPP_UNITS_CELCIUS,
    TINAPP_UNITS_PASCAL,
    TINAPP_UNITS_SECOND,
    TINAPP_UNITS_METER,
    TINAPP_UNITS_TIME,
};

typedef enum tinapp_scale {
    TINAPP_SCALE_NONE = 0,
    TINAPP_SCALE_MICRO,
    TINAPP_SCALE_MILLI,
    TINAPP_SCALE_CENTI,
    TINAPP_SCALE_DECI,
    TINAPP_SCALE_UNIT,
    TINAPP_SCALE_DECA,
    TINAPP_SCALE_HECTO,
    TINAPP_SCALE_KILO,
    TINAPP_SCALE_MEGA,
};


typedef enum tinapp_parameter{
    TINAPP_NONE = 0,
    TINAPP_NAME,
    TINAPP_VALUE,

    TINAPP_RANGE,

    

    TINAPP_TYPE,
    TINAPP_UNITS,

    TINAPP_ACCESS,
    TINAPP_STEP,



    

};

typedef struct tinapp_msg_t {
    uint8_t node_id;
    uint8_t feature_id;
    uint8_t parameter_id;
    uint8_t size;
    uint8_t data[TINAPP_MAX_DATA_SIZE];
} tinapp_msg_t;


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* TINAPP_H */
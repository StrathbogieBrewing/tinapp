#include<stdio.h>

#define TINAPP_FEATURE_SELF 0
#define TINAPP_DATA_MAX_SIZE 8

// All parameters  values are exchanged as strings of upto 8 characters
// Data types are inferred from format 1.20 (float), 12 (integer), 
// 12:00:01 or 12:01 (time), 23-09-17 (date), text (enumeration) 
typedef enum tinapp_const_attribute {
        TINAPP_ATTRIBUTE_NAME = 0,
	TINAPP_ATTRIBUTE_UNITS,
	TINAPP_ATTRIBUTE_MINIMUM,
	TINAPP_ATTRIBUTE_MAXIMUM,
	TINAPP_ATTRIBUTE_STEP,
	TINAPP_CONST_ATTRIBUTE_COUNT 
} tinapp_const_attribute;

typedef enum tinapp_attribute {
	TINAPP_ATTRIBUTE_VALUE = TINAPP_CONST_ATTRIBUTE_COUNT,
	TINAPP_ATTRIBUTE_ENUMERATE,
	TINAPP_ATTRIBUTE_COUNT,
} tinapp_attribute;	

typedef struct tinapp_data {
	char size;
	char data[TINAPP_DATA_MAX_SIZE];
} tinapp_data_t;

typedef struct tinapp_message {
	char node_id;
	char feature_id;
	char parameter_id;
	tinapp_data_t data;
} tinapp_message_t;

typedef tinapp_data_t (*tinapp_get_func)();
typedef void (*tinapp_set_func)(tinapp_data_t value);

typedef struct tinapp_feature {
	char* attributess[TINAPP_CONST_ATTRIBUTE_COUNT];
	tinapp_get_func get_func;
	tinapp_set_func set_func;
} tinapp_feature_t;

typedef enum {
	FEATURE_SELF = TINAPP_FEATURE_SELF,
	FEATURE_CELL_1_VOLTAGE,
	FEATURE_CELL_2_VOLTAGE,
	FEATURE_PACK_CURRENT,
	FEATURE_COUNT
} features;

const char* feature_names[FEATURE_COUNT] = {
	[FEATURE_SELF] = "BMS", 
	[FEATURE_CELL_1_VOLTAGE] = "Cell 1", 
	[FEATURE_CELL_2_VOLTAGE] = "Cell 2",
	[FEATURE_PACK_CURRENT] = "Pack",
};	

const char* feature_units[FEATURE_COUNT] = {
	[FEATURE_SELF] = "", 
	[FEATURE_CELL_1_VOLTAGE] = "mV", 
	[FEATURE_CELL_2_VOLTAGE] = "mV",
	[FEATURE_PACK_CURRENT] = "mA",
};

int main(int argc, char* argv[]){
	for (int i = 0 ; i < FEATURE_COUNT ; i++){
		printf("%s\n", feature_names[i]);
	}

	return 0;
}





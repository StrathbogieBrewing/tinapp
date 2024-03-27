#include<stdio.h>

#include "tinapp.h"



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





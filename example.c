#include<stdio.h>

#define TINAPP_FEATURE_SELF 0


// All parameters and values are exchanged as strings of upto 8 characters
// Data types are inferred from format 1.20, 12, 12:00:01 or 12:01 (time), 23-09-17 (date)
typedef enum tinapp_parameter{
        TINAPP_PARAMETER_NAME = 0,
	TINAPP_PARAMETER_VALUE,
	TINAPP_PARAMETER_UNITS,
	TINAPP_PARAMETER_MAXIMUM,
	TINAPP_PARAMETER_MINIMUM,
	TINAPP_PARAMETER_STEP,
	TINAPP_PARAMETER_COUNT,	
} tinapp_parameter;

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





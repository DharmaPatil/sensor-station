#include "tgs4161.h"

extern ADC_HandleTypeDef hadc1;

char TGS4161_Conversion( float *emf ) {

	int sum = 0;
	
	for (int i = 0; i < 10; i++) {
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 3000);
		sum += HAL_ADC_GetValue(&hadc1);
		HAL_Delay(2);
	}
	
	*emf = ((float)sum)/10 * 3.3f/4096;
	return 0;
}



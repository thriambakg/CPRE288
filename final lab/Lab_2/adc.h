//code added on 10/6/20, need to verify accuracy -- if correct, then done?
#ifndef ADC_H_
#define ADC_H_

void adc_init();

int ir_read(void);

double ir_readCM(double max_dist);

double ir_read_avgCM(double max_dist, int avg_times);

void ir_init(void);

void ir_setAvg(int avg_rate);



#endif

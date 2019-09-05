/*
* program_functions.h
*
* Created: 1/10/2019 2:26:33 PM
*  Author: ENG_3
*/


#ifndef PROGRAM_FUNCTIONS_H_
#define PROGRAM_FUNCTIONS_H_

void blink_red();
void blink_yellow();
void blink_green();
void blink_led();
void load_values_from_eeprom();
void clear_all_errors();
void handle_over_temperature(OutputState* output);
void check_voltage_drift(OutputState* output);
void handle_encoder_clicks();
uint8_t get_ambient_brightness();
void increase_target_current(OutputState* output);
void decrease_target_current(OutputState* output);
void check_save_voltage(OutputState* output);
void read_pson();
void calibrate_unit(OutputState* output);

#endif /* PROGRAM_FUNCTIONS_H_ */
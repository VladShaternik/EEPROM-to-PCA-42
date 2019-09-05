/*
* setting_current_functions.h
*
* Created: 11/19/2018 11:14:01 AM
*  Author: ENG_3
*/


#ifndef SETTING_CURRENT_FUNCTIONS_H_
#define SETTING_CURRENT_FUNCTIONS_H_

void write_pwm_to_41ec(uint16_t output_one_pwm, uint16_t output_two_pwm, bool pwm1_enable, bool pwm2_enable, bool pwm3_enable, bool pwm4_enable, uint8_t slave_addr);
void write_to_dac101c085(uint16_t data, uint8_t slave_addr);
uint16_t read_from_dac101c085(uint8_t slave_addr);
void clear_pwms(uint8_t slave_addr);
void clear_dummy_dacs(uint8_t output1_dac_slave_addr, uint8_t output2_dac_slave_addr);
void set_current(OutputState *output);
void set_current_calibrate(OutputState *output, bool using_formula);
int get_dummy_current(uint8_t port);
uint16_t read_external_eeprom(TWI_Master_t *twi, uint8_t eepromAddress, uint16_t dataAddress);
void write_external_eeprom(TWI_Master_t *twi, uint8_t eepromAddress, uint16_t dataAddress, uint16_t data);

#endif /* SETTING_CURRENT_FUNCTIONS_H_ */
/*
* setting_current_functions.c
*
* Created: 11/19/2018 11:13:39 AM
*  Author: ENG_3
*/

#include "main.h"


void write_pwm_to_41ec(uint16_t output_one_pwm, uint16_t output_two_pwm, bool pwm1_enable, bool pwm2_enable, bool pwm3_enable, bool pwm4_enable, uint8_t slave_addr)
{
	uint8_t message_type = 0x15; //this is to let the 41ec board know that you're trying to set the pwms
	uint8_t pwm_enables = (pwm1_enable << 0) | (pwm2_enable << 1) | (pwm3_enable << 2) | (pwm4_enable << 3);
	uint8_t message[6] = {message_type, output_one_pwm, (output_one_pwm >> 8), output_two_pwm, (output_two_pwm >> 8), pwm_enables};
	TWI_MasterWrite(&twiMaster, slave_addr, (uint8_t *) message, 6);
}

/*
I have channel and operating_mode as parameters so that the OutputState struct can be initialized with either this function or the write_to_dac6574() function above
*/
void write_to_dac101c085(uint16_t data, uint8_t slave_addr)
{
	uint8_t msb = data >> 8;
	uint8_t lsb = data;
	uint8_t message[2] = {msb, lsb};
	TWI_MasterWrite(&twiMaster, slave_addr, (uint8_t *) message, 2);
}


uint16_t read_from_dac101c085(uint8_t slave_addr)
{
	TWI_MasterRead(&twiMaster, slave_addr, 2);
	_delay_ms(5);
	int val = ((twiMaster.readData[0] << 8) + (twiMaster.readData[1]));
	return val;
}

/**********************************
* Zeros all the pwms on the 41ec board
***********************************/
void clear_pwms(uint8_t slave_addr)
{
	write_pwm_to_41ec(0, 0, TRUE, TRUE, TRUE, TRUE, slave_addr);
}

/*
Zeros both dummy dacs
*/
void clear_dummy_dacs(uint8_t output1_dac_slave_addr, uint8_t output2_dac_slave_addr)
{
	write_to_dac101c085(0, output1_dac_slave_addr);
	if (program_state.program != THIRTY_EIGHT)
	{
		write_to_dac101c085(0, output2_dac_slave_addr);
	}
	
}

void set_current_thirty_eight(OutputState *output) {
	output_one.isChanelused1 = TRUE;
	output_one.isChanelused2 = FALSE;
	output_two.isChanelused1 = FALSE;
	output_two.isChanelused2 = FALSE;
}

void set_current_fourty_two_1(OutputState *output, int desired_current) {
	if (desired_current < 250)
	{
		output_one.isChanelused1 = TRUE;
		output_one.isChanelused2 = FALSE;
		output_two.isChanelused1 = FALSE;
		output_two.isChanelused2 = FALSE;
	}
	else if (desired_current < 500)
	{
		output_one.isChanelused1 = TRUE;
		output_one.isChanelused2 = TRUE;
		output_two.isChanelused1 = FALSE;
		output_two.isChanelused2 = FALSE;
	}
	else if (desired_current < 750)
	{
		output_one.isChanelused1 = TRUE;
		output_one.isChanelused2 = TRUE;
		output_two.isChanelused1 = TRUE;
		output_two.isChanelused2 = FALSE;
	}
	else
	{
		output_one.isChanelused1 = TRUE;
		output_one.isChanelused2 = TRUE;
		output_two.isChanelused1 = TRUE;
		output_two.isChanelused2 = TRUE;
	}
}

void set_current_fourty_two_2(OutputState *output, int desired_current) 
{
	if (desired_current < 500)
	{
		output->isChanelused1 = TRUE;
		output->isChanelused2 = FALSE;
	}
	else
	{
		output->isChanelused2 = TRUE;
		output->isChanelused1 = TRUE;
	}
}

void set_current(OutputState *output) 
{
	//read_current_and_voltage(output);
	
	int volatile desired_current = MIN(output->target_current * output->reduced_current_fraction, output->max_current);
	
	uint16_t present_voltage = output->voltage;
	
	int volatile present_current = output->current;
	
	int dac_start_value = 0;
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	/* max current has been hit */
	if(present_current > output->max_current-10 && desired_current > present_current)
	{
		output->hit_max_current = TRUE;
		return;
	}
	else
	{
		output->hit_max_current = FALSE;
	}
	
	/* min current has been hit */
	if(desired_current <= present_current - 10 && present_voltage < 30 && !(output->voltage < 700))
	{
		output->hit_min_current = TRUE;
		//return;
	}
	else
	{
		output->hit_min_current = FALSE;
	}
	
	/* max voltage has been hit */
	if(desired_current > present_current && present_voltage > output->max_voltage - 300 && present_current > 1)
	{
		output->hit_max_voltage = TRUE;
		return;
	}
	else
	{
		output->hit_max_voltage = FALSE;
	}
	
	if (desired_current == 0)
	{
		output->pwm_value = 0;
		output->dac_value = 0;
		return;
	}
	
	if (abs(desired_current - present_current) <= MIN_ACCURACY)
	{
		return;
	}
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	uint16_t pwm_eeprom_start_address;
	
	if (program_state.program == THIRTY_EIGHT)
	{
		set_current_thirty_eight(output);
		pwm_eeprom_start_address = 0;
		
		dac_start_value = 120;
	}
	else if (program_state.program == FOURTY_ONE_DUAL)
	{
		set_current_fourty_two_2(output, desired_current);
		if (output->id == output_one.id)
		{
			pwm_eeprom_start_address = 420;
		}
		else
		{
			pwm_eeprom_start_address = 940;
		}
		
		dac_start_value = 100;
	}
	else if (program_state.program == FOURTY_ONE)
	{
		set_current_fourty_two_1(output, desired_current);
		pwm_eeprom_start_address = 1460;
		
		dac_start_value = 100;
	}
	
	uint16_t pwm_eeprom_address = pwm_eeprom_start_address + desired_current / 5;
	uint16_t value_to_assemble = 0;
	
	value_to_assemble = read_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, pwm_eeprom_address);
	
	if (desired_current < dac_start_value)
	{
		uint16_t pwm_eeprom_address2 = pwm_eeprom_start_address + dac_start_value / 5;
		
		output->pwm_value = read_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, pwm_eeprom_address2);
		
		//---------------------------------------------------------setting current to 1A ^
		
		//---------------------------------------------------------setting dac
		if (output->voltage < 700 && !(desired_current <= present_current - 10 && present_voltage < 30))
		{
			output->hit_min_current = FALSE;
			output->dac_value = value_to_assemble;
		}
		else
		{
			output->hit_min_current = TRUE;
			if (!(desired_current <= present_current - 10 && present_voltage < 30))
			{
				output->dac_value = 0;
			}
		}
	}
	else
	{
		output->dac_value = 0;
		output->pwm_value = value_to_assemble;
	}
}

void set_current_calibrate(OutputState *output, bool using_formula) 
{
	read_current_and_voltage(output);
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	_delay_ms(100);
	
	int dac_start_value = 0;
	
	int volatile desired_current = MIN(output->target_current * output->reduced_current_fraction, output->max_current);
	
	int volatile present_current = output->current;
	
	if (abs(desired_current - present_current) < MIN_ACCURACY)
	{
		for (int i = 0; i < 3; i++)
		{
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
			
			read_current_and_voltage(output);
			_delay_ms(100);
		}
		
		if (abs(desired_current - present_current) < MIN_ACCURACY)
		{
			return;
		}
	}
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	if (program_state.program == THIRTY_EIGHT)
	{
		output_one.isChanelused1 = TRUE;
		output_one.isChanelused2 = FALSE;
		output_two.isChanelused1 = FALSE;
		output_two.isChanelused2 = FALSE;
		
		dac_start_value = 120;
	}
	else if (program_state.program == FOURTY_ONE)
	{
		if (desired_current < 250)
		{
			if (output_one.isChanelused1 && output_one.isChanelused2 && !output_two.isChanelused1 && !output_two.isChanelused2)
			{
				output->pwm_value = 0;
			}
			else if (output_one.isChanelused1 && output_one.isChanelused2 && output_two.isChanelused1 && !output_two.isChanelused2)
			{
				output->pwm_value = 0;
			}
			else if (output_one.isChanelused1 && output_one.isChanelused2 && output_two.isChanelused1 && output_two.isChanelused2)
			{
				output->pwm_value = 0;
			}
			output_one.isChanelused1 = TRUE;
			output_one.isChanelused2 = FALSE;
			output_two.isChanelused1 = FALSE;
			output_two.isChanelused2 = FALSE;
		}
		else if (desired_current < 500)
		{
			if (output_one.isChanelused1 && output_one.isChanelused2 && output_two.isChanelused1 && !output_two.isChanelused2)
			{
				output->pwm_value = 0;
			}
			else if (output_one.isChanelused1 && !output_one.isChanelused2 && !output_two.isChanelused1 && !output_two.isChanelused2)
			{
				output->pwm_value = 0;
			}
			else if (output_one.isChanelused1 && output_one.isChanelused2 && output_two.isChanelused1 && output_two.isChanelused2)
			{
				output->pwm_value = 0;
			}
			output_one.isChanelused1 = TRUE;
			output_one.isChanelused2 = TRUE;
			output_two.isChanelused1 = FALSE;
			output_two.isChanelused2 = FALSE;
		}
		else if (desired_current < 750)
		{
			if (output_one.isChanelused1 && output_one.isChanelused2 && output_two.isChanelused1 && output_two.isChanelused2)
			{
				output->pwm_value = 0;
			}
			else if (output_one.isChanelused1 && output_one.isChanelused2 && !output_two.isChanelused1 && !output_two.isChanelused2)
			{
				output->pwm_value = 0;
			}
			else if (output_one.isChanelused1 && !output_one.isChanelused2 && !output_two.isChanelused1 && !output_two.isChanelused2)
			{
				output->pwm_value = 0;
			}
			output_one.isChanelused1 = TRUE;
			output_one.isChanelused2 = TRUE;
			output_two.isChanelused1 = TRUE;
			output_two.isChanelused2 = FALSE;
		}
		else
		{
			if (output_one.isChanelused1 && output_one.isChanelused2 && output_two.isChanelused1 && !output_two.isChanelused2)
			{
				output->pwm_value = 0;
			}
			else if (output_one.isChanelused1 && output_one.isChanelused2 && !output_two.isChanelused1 && !output_two.isChanelused2)
			{
				output->pwm_value = 0;
			}
			else if (output_one.isChanelused1 && !output_one.isChanelused2 && !output_two.isChanelused1 && !output_two.isChanelused2)
			{
				output->pwm_value = 0;
			}
			output_one.isChanelused1 = TRUE;
			output_one.isChanelused2 = TRUE;
			output_two.isChanelused1 = TRUE;
			output_two.isChanelused2 = TRUE;
		}
		
		dac_start_value = 100;
	}
	else if (program_state.program == FOURTY_ONE_DUAL)
	{
		if (desired_current < 500)
		{
			if (output->isChanelused2)
			{
				output->pwm_value = 0;
			}
			output->isChanelused1 = TRUE;
			output->isChanelused2 = FALSE;
		}
		else
		{
			if (!output->isChanelused2)
			{
				output->pwm_value = 0;
			}
			output->isChanelused2 = TRUE;
			output->isChanelused1 = TRUE;
		}
		
		dac_start_value = 100;
	}
	
	if (desired_current == 0)
	{
		output->dac_value = 0;
		output->pwm_value = 0;
	}
	else if (desired_current < dac_start_value)
	{
		uint16_t pwm_eeprom_start_address;
		
		if (program_state.program == THIRTY_EIGHT)
		{
			pwm_eeprom_start_address = 0;
		}
		else if (program_state.program == FOURTY_ONE_DUAL)
		{
			if (output->id == output_one.id)
			{
				pwm_eeprom_start_address = 420;
			}
			else
			{
				pwm_eeprom_start_address = 940;
			}
		}
		else if (program_state.program == FOURTY_ONE)
		{
			pwm_eeprom_start_address = 1460;
		}
		
		uint16_t pwm_eeprom_address = pwm_eeprom_start_address + dac_start_value / 5;
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		
		output->pwm_value = read_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, pwm_eeprom_address);
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		
		//---------------------------------------------------------setting current to 1A ^
		
		//---------------------------------------------------------setting dac
		if (desired_current > present_current)
		{
			if (output->dac_value >= 50)
			{
				output->dac_value -= 50;
			}
		}
		else
		{
			if (output->dac_value < 4000)
			{
				output->dac_value += 50;
			}
		}
	}
	else
	{
		if (desired_current > present_current)
		{
			if (output->pwm_value < output->power_supply_pwm_max)
			{
				if (present_current == 0)
				{
					output->pwm_value += 10;
				}
				else if (using_formula && !output->over_temp_error1 && !output->over_temp_error2 && !output->over_temp_error_uncleared1 && !output->over_temp_error_uncleared2)
				{
					uint16_t volatile desired_pwm = ((float)output->pwm_value * (float)desired_current) / (float)present_current;
					output->pwm_value += ((int)desired_pwm - (int)output->pwm_value) * 1;
					if (output->pwm_value > 1023)
					{
						output->pwm_value = 1023;
					}
					if (output->pwm_value < 0)
					{
						output->pwm_value = 0;
					}
				}
				else if (!output->over_temp_error1 && !output->over_temp_error2 && !output->over_temp_error_uncleared1 && !output->over_temp_error_uncleared2)
				{
					output->pwm_value++;
				}
			}
			output->dac_value = 0;
		}
		else
		{
			if (output->pwm_value > 0)
			{
				if (present_current == 0)
				{
					output->pwm_value += 10;
				}
				else if (using_formula && !output->over_temp_error1 && !output->over_temp_error2 && !output->over_temp_error_uncleared1 && !output->over_temp_error_uncleared2)
				{
					uint16_t volatile desired_pwm = ((float)output->pwm_value * (float)desired_current) / (float)present_current;
					output->pwm_value += ((int)desired_pwm - (int)output->pwm_value) * 1;
					if (output->pwm_value > 1023)
					{
						output->pwm_value = 1023;
					}
					if (output->pwm_value < 0)
					{
						output->pwm_value = 0;
					}
				}
				else if (!output->over_temp_error1 && !output->over_temp_error2 && !output->over_temp_error_uncleared1 && !output->over_temp_error_uncleared2)
				{
					output->pwm_value--;
				}
			}
			output->dac_value = 0;
		}
	}
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	output->write_to_dummy_dac(output->dac_value, output->dummy_dac_address);
	_delay_ms(5);
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	if (program_state.program == FOURTY_ONE)
	{
		output->set_pwm(output_one.pwm_value, output_one.pwm_value, output_one.isChanelused1, output_two.isChanelused2, output_two.isChanelused1, output_one.isChanelused2, BOARD_41EC_ADDR);
	}
	else
	{
		output->set_pwm(output_one.pwm_value, output_two.pwm_value, output_one.isChanelused1, output_two.isChanelused2, output_two.isChanelused1, output_one.isChanelused2, BOARD_41EC_ADDR);
	}
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	_delay_ms(5);
}

uint16_t read_external_eeprom(TWI_Master_t *twi, uint8_t eepromAddress, uint16_t dataAddress)
{
	uint16_t received_data = 0;
	
	char message[8];
	message[0] = (uint8_t)(dataAddress >> 8);
	message[1] = (uint8_t)(dataAddress);
	TWI_MasterWrite(&twiMasterForEEPROM, eepromAddress, (uint8_t *) message, 2);
	_delay_ms(20);
	
	while(twi->status != TWIM_STATUS_READY)
	{
		if (counters.i2c_error_counter > 20)
		{
			break;
		}
		counters.i2c_error_counter++;
	}
	
	_delay_ms(5);
	
	counters.i2c_error_counter = 0;
	
	TWI_MasterRead(&twiMasterForEEPROM, eepromAddress, 1);
	_delay_ms(20);
	
	while(twi->status != TWIM_STATUS_READY)
	{
		if (counters.i2c_error_counter > 20)
		{
			break;
		}
		counters.i2c_error_counter++;
	}
	
	_delay_ms(5);
	
	counters.i2c_error_counter = 0;
	
	dataAddress++;
	received_data = twi->readData[0] << 8;
	
	message[0] = (uint8_t)(dataAddress >> 8);
	message[1] = (uint8_t)(dataAddress);
	TWI_MasterWrite(&twiMasterForEEPROM, eepromAddress, (uint8_t *) message, 2);
	_delay_ms(20);
	
	while(twi->status != TWIM_STATUS_READY)
	{
		if (counters.i2c_error_counter > 20)
		{
			break;
		}
		counters.i2c_error_counter++;
	}
	
	_delay_ms(5);
	
	counters.i2c_error_counter = 0;
	
	TWI_MasterRead(&twiMasterForEEPROM, eepromAddress, 1);
	_delay_ms(20);
	
	while(twi->status != TWIM_STATUS_READY)
	{
		if (counters.i2c_error_counter > 20)
		{
			break;
		}
		counters.i2c_error_counter++;
	}
	
	_delay_ms(5);
	
	counters.i2c_error_counter = 0;
	
	received_data |= twi->readData[0];
	
	return received_data;
}

void write_external_eeprom(TWI_Master_t *twi, uint8_t eepromAddress, uint16_t dataAddress, uint16_t data)
{
	uint16_t current_value = read_external_eeprom(twi, eepromAddress, dataAddress);
	
	// If the current value in EEPROM is the same as the value that needs to be written then do not write it.
	// This saves some amount of writes used, since reads are free of charge, writes we only have about 100,000.
	// So, it is good to save as many writes as possible.
	if (current_value == data)
	{
		return;
	}
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	char message[8];
	message[0] = (uint8_t)(dataAddress >> 8);
	message[1] = (uint8_t)(dataAddress);
	message[2] = (uint8_t)(data >> 8);
	TWI_MasterWrite(&twiMasterForEEPROM, eepromAddress, (uint8_t *) message, 3);
	_delay_ms(20);

	while(twi->status != TWIM_STATUS_READY)
	{
		if (counters.i2c_error_counter > 20)
		{
			break;
		}
		counters.i2c_error_counter++;
	}
	
	_delay_ms(5);
	
	counters.i2c_error_counter = 0;
	
	dataAddress++;
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	message[0] = (uint8_t)(dataAddress >> 8);
	message[1] = (uint8_t)(dataAddress);
	message[2] = (uint8_t)(data);
	TWI_MasterWrite(&twiMasterForEEPROM, eepromAddress, (uint8_t *) message, 3);
	_delay_ms(20);

	while(twi->status != TWIM_STATUS_READY)
	{
		if (counters.i2c_error_counter > 20)
		{
			break;
		}
		counters.i2c_error_counter++;
	}
	
	_delay_ms(5);
	
	counters.i2c_error_counter = 0;
}

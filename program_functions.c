/*
* program_functions.c
*
* Created: 1/10/2019 2:26:52 PM
*  Author: ENG_3
*/

#include "main.h"
#include "setting_current_functions.h"

/*************************************************************************
Decreases the target current variably depending on the speed of the turn
**************************************************************************/
void decrease_target_current(OutputState* output)
{
	int new_target_current = output->target_current;
	if(output->target_current >= 10)
	{
		program_state.changing_settings = CHANGING_SETTINGS_TIME;
		if(counters.periodic_int_count < 15)
		{
			int current_to_remove = 200/counters.periodic_int_count;
			current_to_remove -= current_to_remove%10;
			new_target_current -= current_to_remove;
		}
		new_target_current -= 10;
		
		if(new_target_current < 0)
		{
			new_target_current = 0;
		}
		output->target_current = new_target_current;
	}
}

/***********************************************************************
Increases the target current variably depending on the speed of the turn
************************************************************************/
void increase_target_current(OutputState* output)
{
	int new_target_current = output->target_current;
	if(output->target_current <= output->max_current-10)//if it hasn't hit max resistance or max userset current of 20 A
	{ 
		program_state.changing_settings = CHANGING_SETTINGS_TIME;
		if(counters.periodic_int_count < 15)
		{
			int current_to_add = 200/counters.periodic_int_count;
			current_to_add -= current_to_add%10;
			new_target_current += current_to_add;
		}
		new_target_current += 10;
		
		if(new_target_current > output->max_current)
		{
			new_target_current = output->max_current;
		}
		output->target_current = new_target_current;
	}
	else if(output->target_current == output->max_current)
	{
		output->hit_max_current = TRUE;
	}
}


uint8_t get_ambient_brightness()
{
	ADCA_CH0_CTRL |= 0b10000000;				//Start conversion
	while(!(ADCA_CH0_INTFLAGS & 0b00000001));	//Wait for conversion to be complete
	volatile float x = ADCA_CH0_RES;
	
	return (uint8_t) (ADCA_CH0_RES/30);
}

/*******************************************************************************
This function handles what happens when a user clicks the encoder and holds it
********************************************************************************/
void handle_encoder_clicks()
{
	if(encoder_state.holding_click && (!(PORTA_IN & (1 << ENCDR_SW))))//if still holding click
	{ 
		if(counters.periodic_int_count >= SETTINGS_HOLD_TIME)//5 seconds have passed
		{ 
			program_state.mode = SETTINGS_MODE;
		}
		else if(counters.periodic_int_count >= EXIT_SETTINGS_HOLD_TIME)//2 seconds have passed
		{ 
			if(program_state.mode == SETTINGS_MODE)
			{
				program_state.mode = NORMAL_MODE;
				
				if (program_state.program == FOURTY_ONE || program_state.program == FOURTY_ONE_DUAL)
				{
					if (program_state.num_outputs == DOUBLE)
					{
						output_one.max_current = 2500;
						output_one.max_voltage = 5000;
						output_one.ina226_addr = OUTPUT1_INA226_ADDR; // 0x45 - THRIRTY_EIGTH, 0x41 - FOURTY_ONE
						output_two.max_current = 2500;
						output_two.max_voltage = 5000;
						output_two.ina226_addr = OUTPUT2_INA226_ADDR;
						program_state.program = FOURTY_ONE_DUAL;
						
					}
					else if (program_state.num_outputs == SINGLE)
					{
						output_one.max_current = 5000;
						output_one.max_voltage = 5000;
						output_one.ina226_addr = OUTPUT1_INA226_ADDR; // 0x45 - THRIRTY_EIGTH, 0x41 - FOURTY_ONE
						output_two.max_current = 5000;
						output_two.max_voltage = 5000;
						output_two.ina226_addr = OUTPUT2_INA226_ADDR;
						program_state.program = FOURTY_ONE;
					}
				}
				else if (program_state.program == THIRTY_EIGHT)
				{
					output_one.max_current = 2000;
					output_one.max_voltage = 3000;
					output_one.ina226_addr = OUTPUT1_INA226_ADDR; // 0x45 - THRIRTY_EIGTH, 0x41 - FOURTY_ONE
					output_two.max_current = 2000;
					output_two.max_voltage = 3000;
					output_two.ina226_addr = OUTPUT2_INA226_ADDR;
				}
				
				if (output_one.target_current > output_one.max_current)
				{
					output_one.target_current = output_one.max_current;
				}
				
				if (output_two.target_current > output_two.max_current)
				{
					output_two.target_current = output_two.max_current;
				}
				program_state.output->isCurrentAdjusted = FALSE;
				program_state.output->needsAdjusting = FALSE;
			}
		}
		
	}
	else if(encoder_state.holding_click && (PORTA_IN & (1 << ENCDR_SW)))//no longer holding click
	{ 
		if(program_state.mode == SETTINGS_MODE && counters.periodic_int_count < EXIT_SETTINGS_HOLD_TIME) 
		{
			if (program_state.testing_mode)
			{
				if (program_state.settings_row_num == 0)
				{
					program_state.settings_row_num = 1;
				}
				else if (program_state.settings_row_num == 1)
				{
					program_state.settings_row_num = 2;
				}
				else if (program_state.settings_row_num == 2)
				{
					program_state.mode = NORMAL_MODE;
					program_state.settings_row_num = 0;
					program_state.testing_mode = FALSE;
					program_state.debug_mode = FALSE;
					program_state.calibrating_mode = FALSE;
				}
			}
			else if(program_state.settings_row_num == 0 && program_state.program != THIRTY_EIGHT)
			{
				if(program_state.num_outputs == SINGLE)
				{
					program_state.num_outputs = DOUBLE;
				}
				else if(program_state.num_outputs == DOUBLE)
				{
					program_state.num_outputs = SINGLE;
					program_state.output = &output_one;
				}
				write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_CHANELS_AMT_ADDR, program_state.num_outputs);
			}
			else if (program_state.settings_row_num == 1 && program_state.debug_mode)
			{
				write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_COM_ERROR1_AMT_ADDR, 0);
				write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_COM_ERROR2_AMT_ADDR, 0);
				write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_COM_ERROR3_AMT_ADDR, 0);
				write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_COM_ERROR4_AMT_ADDR, 0);
				write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_COM_ERROR5_AMT_ADDR, 0);
				write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_COM_ERROR6_AMT_ADDR, 0);
			}
			else if (program_state.settings_row_num == 2 && program_state.debug_mode)
			{
				program_state.settings_row_num = 0;
				TIME_TO_CHECK_TEMP = 30000; // 30 sec default
				program_state.testing_mode = TRUE;
			}
			else if (program_state.settings_row_num == 1 && program_state.calibrating_mode)
			{
				program_state.calibrating_mode_clicked = TRUE;
				program_state.mode = NORMAL_MODE;
				program_state.settings_row_num = 0;
			}
		}
		else if(program_state.mode == NORMAL_MODE && counters.periodic_int_count < EXIT_SETTINGS_HOLD_TIME)
		{
			if(program_state.num_outputs == SINGLE)
			{
				program_state.output = &output_one;
				output_two.set_current_state = VISIBLE_LOCKED;
				output_one.set_current_state = VISIBLE;
			}
			else if(program_state.num_outputs == DOUBLE)
			{
				if((program_state.output)->id == output_one.id && program_state.output->set_current_state == VISIBLE_LOCKED)
				{
					program_state.output = &output_two;
					output_one.set_current_state = VISIBLE_LOCKED;
					output_two.set_current_state = VISIBLE;
				}
				else if(program_state.output->id == output_two.id && program_state.output->set_current_state == VISIBLE_LOCKED)
				{
					program_state.output = &output_one;
					output_two.set_current_state = VISIBLE_LOCKED;
					output_one.set_current_state = VISIBLE;
				}
			}
			
			if(program_state.output->set_current_state == VISIBLE_LOCKED)
			{
				program_state.output->set_current_state = VISIBLE;
			}
			
			if (program_state.uncleared_error)
			{
				program_state.output->set_current_state = VISIBLE_LOCKED;
				clear_all_errors();
			}
		}
		
		encoder_state.holding_click = FALSE;
		counters.periodic_int_count = 0;
	}
}

void blink_red()
{
	GRN_LED_OFF;
	RED_LED_TGL;
}

void blink_yellow()
{
	if((PORTA_OUT & (1 << GRN_LED)) == (PORTA_OUT & (1 << RED_LED)))
	{
		GRN_LED_TGL;
		RED_LED_TGL;
	}
	else
	{
		GRN_LED_ON;
		RED_LED_ON;
	}
}

void blink_green()
{
	GRN_LED_TGL;
	RED_LED_OFF;
}

/********************************************************************************
This program always requires a blinking LED. This function determines which color
should be blinked at the moment
*********************************************************************************/
void blink_led(){
	if (counters.real_time_counter < 5000) // Do not blick at the start of the program
	{
		RED_LED_OFF;
		GRN_LED_OFF;
		return;
	}
	else if(program_state.pson_low || output_one.current < 5 || (program_state.program == FOURTY_ONE_DUAL && output_two.current < 5))//current is zero or DC is off
	{ 
		blink_red();
	}
	else if(program_state.uncleared_error)//if there's an uncleared error
	{ 
		blink_yellow();
	}
	else
	{
		blink_green(); //if everything is fine
	}
}

/************************************************************************************
This functions checks that the two values "target current" and "error offset" loaded
from the EEPROM are legitimate values. If not, they are set to some default values.
This function is necessary for new boards that have not loaded the proper values into
the EEPROM yet
*************************************************************************************/
void load_values_from_eeprom()
{
	output_one.target_current = read_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_OUT1_CURRENT_VALUE_ADDR); //load last set target current
	output_two.target_current = read_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_OUT2_CURRENT_VALUE_ADDR); //load last set target current
	program_state.num_outputs = read_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_CHANELS_AMT_ADDR); //load last set target current
	
	if(output_one.target_current > 5000)//if the previously loaded target current is somehow above 50 A, set it to 1 A. This is primarily to account for new IC's that have a random EEPROM value
	{
		program_state.comm_error6++;
		output_one.target_current = 0;
		write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_OUT1_CURRENT_VALUE_ADDR, output_one.target_current);
	}
	if(output_two.target_current > 5000) //if the previously loaded target current is somehow above 50 A, set it to 1 A. This is primarily to account for new IC's that have a random EEPROM value
	{
		program_state.comm_error6++;
		output_two.target_current = 0;
		write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_OUT2_CURRENT_VALUE_ADDR, output_one.target_current);
	}
	if(program_state.num_outputs != SINGLE && program_state.num_outputs != DOUBLE) //if the number of outputs is neither 1 or 2, set it to 1. This is primarily to account for new IC's that have a random EEPROM value
	{
		program_state.comm_error6++;
		program_state.num_outputs = SINGLE;
		write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_CHANELS_AMT_ADDR, program_state.num_outputs);
	}
	if (program_state.program == THIRTY_EIGHT)
	{
		program_state.num_outputs = SINGLE;
		write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_CHANELS_AMT_ADDR, program_state.num_outputs);
	}
	
	if (program_state.program == FOURTY_ONE || program_state.program == FOURTY_ONE_DUAL)
	{
		if (program_state.num_outputs == DOUBLE)
		{
			output_one.max_current = 2500;
			output_one.max_voltage = 5000;
			output_one.ina226_addr = OUTPUT1_INA226_ADDR; // 0x45 - THRIRTY_EIGTH, 0x41 - FOURTY_ONE
			output_two.max_current = 2500;
			output_two.max_voltage = 5000;
			output_two.ina226_addr = OUTPUT2_INA226_ADDR;
			program_state.program = FOURTY_ONE_DUAL;
		}
		else if (program_state.num_outputs == SINGLE)
		{
			output_one.max_current = 5000;
			output_one.max_voltage = 5000;
			output_one.ina226_addr = OUTPUT1_INA226_ADDR; // 0x45 - THRIRTY_EIGTH, 0x41 - FOURTY_ONE
			output_two.max_current = 5000;
			output_two.max_voltage = 5000;
			output_two.ina226_addr = OUTPUT2_INA226_ADDR;
			program_state.program = FOURTY_ONE;
		}
	}
	else if (program_state.program == THIRTY_EIGHT)
	{
		output_one.max_current = 2000;
		output_one.max_voltage = 3000;
		output_one.ina226_addr = OUTPUT1_INA226_ADDR; // 0x45 - THRIRTY_EIGTH, 0x41 - FOURTY_ONE
		output_two.max_current = 2000;
		output_two.max_voltage = 3000;
		output_two.ina226_addr = OUTPUT2_INA226_ADDR;
	}
}

void clear_all_errors()
{
	program_state.uncleared_error = FALSE;
	output_one.voltage_drift_error = FALSE;
	output_one.over_temp_error1 = FALSE;
	output_one.over_temp_error_uncleared1 = FALSE;
	output_one.over_temp_error2 = FALSE;
	output_one.over_temp_error_uncleared2 = FALSE;
	output_one.current_voltage_pair[0] = 0;
	
	output_two.voltage_drift_error = FALSE;
	output_two.over_temp_error1 = FALSE;
	output_two.over_temp_error_uncleared1 = FALSE;
	output_two.over_temp_error2 = FALSE;
	output_two.over_temp_error_uncleared2 = FALSE;
	output_two.current_voltage_pair[0] = 0;
	
	output_one.current_voltage_pair[0] = output_one.current;
	output_one.current_voltage_pair[1] = output_one.voltage;
	output_two.current_voltage_pair[0] = output_two.current;
	output_two.current_voltage_pair[1] = output_two.voltage;
	output_one.need_to_set_current_voltage_pair = FALSE;
	output_two.need_to_set_current_voltage_pair = FALSE;
}

/**********************************************************************************************
Handles the state of the program if the temperature error has occurred and not been cleared yet
***********************************************************************************************/
void handle_over_temperature(OutputState* output)
{
	if (counters.check_temp_counter >= TIME_TO_CHECK_TEMP)
	{
		counters.check_temp_counter = 0;
		
		char message[1];
		message[0] = 0x16;
		TWI_MasterWrite(&twiMaster, BOARD_41EC_ADDR, (uint8_t *) message, 1);
		
		TWI_MasterRead(&twiMaster, BOARD_41EC_ADDR, 8);
		_delay_ms(10);
		
		uint16_t volatile t1 = ((uint16_t)twiMaster.readData[0] << 8) + twiMaster.readData[1];
		uint16_t volatile t2 = ((uint16_t)twiMaster.readData[2] << 8) + twiMaster.readData[3];
		uint16_t volatile t3 = ((uint16_t)twiMaster.readData[4] << 8) + twiMaster.readData[5];
		uint16_t volatile t4 = ((uint16_t)twiMaster.readData[6] << 8) + twiMaster.readData[7];
		
		if (t1 < OVER_TEMP_VALUE)
		{
			output_one.over_temp_error1 = TRUE;
		}
		if (t1 > OVER_TEMP_VALUE + 10)
		{
			output_one.over_temp_error1 = FALSE;
		}
		
		if (program_state.program == FOURTY_ONE || program_state.program == FOURTY_ONE_DUAL)
		{
			if (t2 < OVER_TEMP_VALUE)
			{
				output_one.over_temp_error2 = TRUE;
			}
			if (t2 > OVER_TEMP_VALUE + 10)
			{
				output_one.over_temp_error2 = FALSE;
			}
			
			if (t3 < OVER_TEMP_VALUE)
			{
				output_two.over_temp_error1 = TRUE;
			}
			if (t3 > OVER_TEMP_VALUE + 10)
			{
				output_two.over_temp_error1 = FALSE;
			}
			
			if (t4 < OVER_TEMP_VALUE)
			{
				output_two.over_temp_error2 = TRUE;
			}
			if (t4 > OVER_TEMP_VALUE + 10)
			{
				output_two.over_temp_error2 = FALSE;
			}
		}
	}
	
	if(output->over_temp_error1 || output->over_temp_error2)
	{
		//wr8(REG_VOL_SOUND,0xFF); //set the volume to maximum
		//wr16(REG_SOUND, 0x08);
		//wr8(REG_PLAY, 1); // play the sound
		++(output->over_temp_half_second_count);
		if(output->over_temp_half_second_count > 90)
		{
			output->over_temp_half_second_count = 90;
		}
	}
	else if(output->over_temp_half_second_count > 0)
	{
		--(output->over_temp_half_second_count);
	}
	
	
	if(output->over_temp_error1 || output->over_temp_half_second_count)
	{
		program_state.uncleared_error = TRUE;
		output->over_temp_error_uncleared1 = TRUE;
		output->reduced_current_fraction = (float)((9 - output->over_temp_half_second_count/10)/10.0);
		if (output->reduced_current_fraction < 0.4)
		{
			output->reduced_current_fraction = 0;
		}
	}
	else if(output->over_temp_error2 || output->over_temp_half_second_count)
	{
		program_state.uncleared_error = TRUE;
		output->over_temp_error_uncleared2 = TRUE;
		output->reduced_current_fraction = (float)((9 - output->over_temp_half_second_count/10)/10.0);
		if (output->reduced_current_fraction < 0.4)
		{
			output->reduced_current_fraction = 0;
		}
	}
	else
	{
		output->reduced_current_fraction = 1.00;
	}
}

/**********************************************************************
This function sets the voltage-current pair and also checks whether the
voltage has strayed by more than a certain percentage
***********************************************************************/
void check_voltage_drift(OutputState* output)
{
		//if >15% in voltage
		if(!output_one.over_temp_error1 && !output_one.over_temp_error2 && !output_one.over_temp_half_second_count && output_one.current_voltage_pair[0] && 
			(output_one.voltage > output_one.current_voltage_pair[1] * 1.15 || output_one.voltage < output_one.current_voltage_pair[1] * 0.85))
		{ 
			output_one.voltage_drift_counter++;
		}
		else
		{
			output_one.voltage_drift_counter = 0;
		}
		
		if (output_one.voltage_drift_counter > 120)
		{
			output_one.voltage_drift_error = TRUE;
			program_state.uncleared_error = TRUE;
		}
		
		//if >15% in voltage
		if(output->id != output_one.id && !output_two.over_temp_error1 && !output_two.over_temp_error2 && !output_two.over_temp_half_second_count && output_two.current_voltage_pair[0] && 
			(output_two.voltage > output_two.current_voltage_pair[1] * 1.15 || output_two.voltage < output_two.current_voltage_pair[1] * 0.85))
		{ 
			output_two.voltage_drift_counter++;
		}
		else
		{
			output_two.voltage_drift_counter = 0;
		}
		
		if (output_two.voltage_drift_counter > 120)
		{
			output_two.voltage_drift_error = TRUE;
			program_state.uncleared_error = TRUE;
		}
		
}

/*
This function sets the saving_voltage state for a couple seconds, and then saves the voltage afterwards
*/
void check_save_voltage(OutputState* output)
{
	if(counters.real_time_counter - counters.idle_time_counter >= 5000 && output->need_to_set_current_voltage_pair)
	{
		output_one.current_voltage_pair[0] = output_one.current;
		output_one.current_voltage_pair[1] = output_one.voltage;
		output_two.current_voltage_pair[0] = output_two.current;
		output_two.current_voltage_pair[1] = output_two.voltage;
		output_one.need_to_set_current_voltage_pair = FALSE;
		output_two.need_to_set_current_voltage_pair = FALSE;
	}
}

void read_pson()
{
	bool temp = program_state.pson_low;
	program_state.pson_low = !(PORTA_IN & (1 << PSON));
	if (temp != program_state.pson_low)
	{
		counters.clear_errors_pson_counter = 1000;
	}
	if (program_state.pson_low)
	{
		output_one.set_current_state = VISIBLE_LOCKED;
		output_two.set_current_state = VISIBLE_LOCKED;
	}
}

void calibrate_unit(OutputState* output) {
	output->pwm_value = 0;
	output->dac_value = 0;
	
	int dac_start_value = 0;
	uint16_t pwm_eeprom_start_address;
	
	if (program_state.program == THIRTY_EIGHT)
	{
		pwm_eeprom_start_address = 0;
		dac_start_value = 120;
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
		
		dac_start_value = 100;
	}
	else if (program_state.program == FOURTY_ONE)
	{
		pwm_eeprom_start_address = 1460;
		dac_start_value = 100;
	}
	
	for (int i = dac_start_value; i <= output->max_current; i += 10)
	{
		output->target_current = i;
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		
		int tries = 0;
		
		while(abs(MIN(output->target_current * output->reduced_current_fraction, output->max_current) - output->current) > MIN_ACCURACY)
		{
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
		
			set_current_calibrate(output, FALSE);
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
			
			tries++;
			
			if (tries > 100)
			{
				break;
			}
		}
		
			
		_delay_ms(100);
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		
		read_current_and_voltage(output);
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		
		_delay_ms(100);
		
		tries = 0;
		
		while(abs(MIN(output->target_current * output->reduced_current_fraction, output->max_current) - output->current) > MIN_ACCURACY)
		{
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
		
			set_current_calibrate(output, FALSE);
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
			
			tries++;
			
			if (tries > 100)
			{
				break;
			}
		}
		
		uint16_t pwm_eeprom_address = pwm_eeprom_start_address + i / 5;
		
		write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, pwm_eeprom_address, output->pwm_value);
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
	}
	for (int i = dac_start_value - 10; i >= 0; i -= 10)
	{
		output->target_current = i;
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		
		int tries = 0;
		
		while(abs(MIN(output->target_current * output->reduced_current_fraction, output->max_current) - output->current) > MIN_ACCURACY)
		{
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
		
			set_current_calibrate(output, FALSE);
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
			output->write_to_dummy_dac(output->dac_value, output->dummy_dac_address);
			_delay_ms(5);
			
			tries++;
			
			if (tries > 100)
			{
				break;
			}
		}
			
		_delay_ms(100);
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		
		read_current_and_voltage(output);
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		
		tries = 0;
		
		_delay_ms(100);
		
		while(abs(MIN(output->target_current * output->reduced_current_fraction, output->max_current) - output->current) > MIN_ACCURACY)
		{
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
		
			set_current_calibrate(output, FALSE);
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
			output->write_to_dummy_dac(output->dac_value, output->dummy_dac_address);
			_delay_ms(5);
			
			tries++;
			
			if (tries > 100)
			{
				break;
			}
		}
		uint16_t pwm_eeprom_address = pwm_eeprom_start_address + i / 5;
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		
		write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, pwm_eeprom_address, output->dac_value);
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
	}
}


void calibrate_value(OutputState *output)
{
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	uint16_t pwm_eeprom_start_address = 0;
	int dac_start_value = 0;
	int volatile desired_current = MIN(output->target_current * output->reduced_current_fraction, output->max_current);
	
	if (program_state.program == THIRTY_EIGHT)
	{
		pwm_eeprom_start_address = 0;
		dac_start_value = 120;
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
		dac_start_value = 100;
	}
	else if (program_state.program == FOURTY_ONE)
	{
		pwm_eeprom_start_address = 1460;
		dac_start_value = 100;
	}
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	if (desired_current >= dac_start_value)
	{
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		if (abs(output->current - desired_current) <= 10)
		{
			set_current_calibrate(output, FALSE);
		}
		else
		{
			set_current_calibrate(output, TRUE);
		}
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		
		uint16_t pwm_eeprom_address = pwm_eeprom_start_address + desired_current / 5;
		
		if (output->over_temp_error1 == FALSE && output->over_temp_error2 == FALSE)
		{
			write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, pwm_eeprom_address, output->pwm_value);
		}
	}
	else
	{
		if (output->voltage < 700)
		{
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
		
			set_current_calibrate(output, FALSE);
		
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
		
			output->write_to_dummy_dac(output->dac_value, output->dummy_dac_address);
			_delay_ms(5);
		
		
			uint16_t pwm_eeprom_address = pwm_eeprom_start_address + desired_current / 5;
		
			if (output->over_temp_error1 == FALSE && output->over_temp_error2 == FALSE)
			{
				write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, pwm_eeprom_address, output->dac_value);
			}
		}
	}
}
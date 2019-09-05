/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! 
	\mainpage 

	\section summary_sec Main Operation Summary

	\subsection fsma5050_subsec FSMA 50-50 

	User sets desired current between 0 - 50 A (0 - 25 A on each channel 
	if in dual mode) and the controller will set it to that current.


	\subsection fsma3020_subsec FSMA 30-20 

	User sets desired current between 0 - 20 A and the controller will 
	set it to that current.

	\section knob_sec Knob Functions

	\subsection b_hold_subsec Button Hold
	
	<ol>
		<li type="a">If unit is on 'Select Desired Current' page, 
			\ref b_hold_subsec "button hold" opens 'Settings' 
			page where you can select the unit to operate in 
			dual or single mode.</li>
		<li type="a">If unit is on 'Settings' page, 
		    \ref b_hold_subsec "button hold" closes 'Settings' page 
			and opens 'Select Desired Current' page. </li>
	</ol>
	
	\note 
	<ol>
		<li type="disc">'Settings' page also closes automatically 
			after 2 seconds of inactivity.</li>
		<li type="disc">If the FSMA 30-20 is used, then the 
			button for selecting \ref dual_mode_sec "dual" or 
			single mode will be disabled, since this unit 
			can only operate in single mode.</li>
	</ol>

	\subsection b_click_subsec Button Click
	
	<ol>
		<li type="a">If unit is on 'Select Desired Current' page, 
			after \ref b_click_subsec "button click" the "SET CURRENT:" 
			will start blinking. If unit is in \ref dual_mode_sec "dual mode", 
			every \ref b_click_subsec "button click" will switch the selected 
			channel and the "SET CURRENT:" will be blinking on the 
			selected channel.</li>
		<li type="a">If unit is on 'Settings' page, 
			\ref b_click_subsec "button click" will switch setting 
			to "MODE: DUAL" or "MODE: SINGLE".</li>
	</ol>
	
	\note
	<ol>
		<li type="disc">"SET CURRENT:" will be blinking until 
			backlight turns off.</li>
	</ol>

	\subsection b_rotate_clockwise_subsec Rotate Clockwise
	
	<ol>
		<li type="a">Increases target current (if "SET CURRENT:" 
			is blinking).</li>
		<li type="a" style="color:red">IF ON 'SETTINGS' PAGE AND 
			\ref b_rotate_clockwise_subsec "ROTATE CLOCKWISE" FOR LONG ENOUGH, 
			THE ERROR LOGS WILL APPEAR, AND WILL GIVE ABILITY TO CLEAR THEM. 
			IF YOU WANT TO EXIT TO 'SELECT DESIRED CURRENT' PAGE THEN SELECT 
			MODE SETTING AND WAIT FOR TWO SECOND OR 
			\ref b_hold_subsec "HOLD BUTTON". THE ERROR LOGS WILL NOT APEAR 
			NEXT TIME WHEN USER ENTERS 'SETTINGS' PAGE, USER WOULD NEED AGAIN 
			\ref b_rotate_clockwise_subsec "ROTATE CLOCKWISE" FOR SOME 
			PERIOD OF TIME (THIS IS DONE ONLY FOR DEVELOPMENT PURPUSES, 
			AND IS NOT NEEDED FOR REGULAR USAGE).</li>
	</ol>

	\subsection b_rotate_counter_clockwise_subsec Rotate Counter-Clockwise
	
	<ol>
		<li type="a">Decreases target current (if "SET CURRENT:"
			is blinking).</li>
		<li type="a" style="color:red">IF ON 'SETTINGS' PAGE AND 
			\ref b_rotate_counter_clockwise_subsec "ROTATE COUNTER-CLOCKWISE" 
			FOR LONG ENOUGH, THE "CALIBRATE UNIT" OPTION WILL APPEAR, 
			AND IF \ref b_click_subsec "CLICKED" WILL START UNIT CALIBRATION 
			WHICH TAKES 5 MINUTES FOR 30-20 UNIT, 15 MINUTES FOR 50-50 UNIT IN DUAL 
			MODE AND 20 MINUTES FOR 50-50 UNIT IN SINGLE MODE. YOU WANT 
			TO EXIT TO 'SELECT DESIRED CURRENT' PAGE THEN SELECT MODE 
			SETTING AND WAIT FOR TWO SECOND OR \ref b_hold_subsec "HOLD BUTTON". 
			THE CALIBRATION SETTING WILL NOT APEAR NEXT TIME WHEN 
			USER ENTERS 'SETTINGS' PAGE, USER WOULD NEED AGAIN 
			\ref b_rotate_counter_clockwise_subsec "ROTATE COUNTER-CLOCKWISE" 
			FOR SOME PERIOD OF TIME (THIS OPTION SHOULD BE USED ONLY ONCE BEFORE 
			SHIPPING THE UNIT TO THE CUSTOMER, AND IS NOT NEEDED 
			FOR REGULAR USAGE).</li>
	</ol>
	
	\note
	<ol>
		<li type="disc">Any of the above functions will first turn 
			on the LCD backlight if not already on (LCD backlight 
			stays on for 10 minutes before turning back off).</li>
		<li type="disc">Any of the above functions will first 
			clear any outstanding errors (if the backlight is 
			already on).</li>
	</ol>
	
	\section led_lights_sec LED Light Codes

	\subsection led_green_subsec Flashing Green
	<ol>
		<li type="disc">Working properly.</li>
	</ol>

	\subsection led_orange_subsec Flashing Orange
	<ol>
		<li type="disc">An \ref errors_sec "error" or other 
			\ref lcd_messages_sec "message" has occurred, 
			check LCD display.</li>
	</ol>

	\subsection led_red_subsec Flashing Red
	<ol>
		<li type="disc">Power supply has been turned off 
			(or open load).</li>
	</ol>
	
	\section errors_sec Errors
	
	\subsection volt_drift_err_subsec Voltage Drift Error
	<ol>
		<li type="disc">If \ref volt_drift_err_subsec 
			"voltage drifts" more than 15% 
			from the set current-voltage pair
			for more than 1 minute. (See
			\ref vol_drift_msg_subsec 
			"voltage drift message")</li>
	</ol>
	
	\subsection temp_err_subsec Temperature Error
	<ol>
		<li type="disc">When temperature surpasses the 
			temperature threshold of 75&deg; C, current 
			drops 10% every 30 minutes as long as 
			temperature is above the threshold until 
			hits 40% of the current, after this point 
			unit turn off. If the temperature has 
			fallen back below the threshold, the 
			current will increase 10% every 30 
			minutes until it is back to the desired 
			current. (See \ref ovr_tmp_red_msg_subsec
			"over temp. message" and 
			\ref ovr_tmp_norm_msg_subsec
			"over temp. normalized message")</li>
	</ol>
	
	\section dual_mode_sec Dual Output Mode
	<ol>
		<li type="disc">In \ref dual_mode_sec "double output mode", 
			there will be two gauges. Each output can be 
			adjusted individually. A blinking 
			"SET CURRENT:" indicates which output 
			is currently selected.</li>
	</ol>
	
	\section lcd_messages_sec LCD Messages
	
	\note 
	<ol>
		<li type="disc">If the unit is in \ref dual_mode_sec 
			"dual-output mode", then there will be a "STR. 1: " 
			or "STR. 2: " preceding each \ref lcd_messages_sec 
			"message", to indicate which one is being referred.</li>
	</ol>
	
	\subsection sys_norm_msg_subsec "SYSTEM NORMAL"
	<ol>
		<li type="disc">This message is displayed when 
			device is operational and error-free.</li>
	</ol>
	
	\subsection max_cur_msg_subsec "MAX. CURRENT"
	<ol>
		<li type="disc">This message is displayed when the 
			output has reached the maximum current.</li>
	</ol>
	
	\subsection max_vol_msg_subsec "MAX. VOLTAGE"
	<ol>
		<li type="disc">This message is displayed when 
			the output has reached the maximum voltage.</li>
	</ol>
	
	\subsection min_cur_msg_subsec "MIN. CURRENT"
	<ol>
		<li type="disc">This message is displayed when 
			the output has reached the minimum current. 
			It occurs when the voltage is too low 
			(< 0.2 V) or too high (>7.0V) to operate.</li>
	</ol>
	
	\subsection ovr_tmp_red_msg_subsec "PS. #1-4: OVER TEMP. REDUCED CURRENT"
	<ol>
		<li type="disc">This message is displayed if the 
			unit is at over-temperature condition. Current 
			is reduced 10% every 30 minutes as long as 
			the condition remains. "PS. #" shows which 
			Power Supply is overheating (one through 
			four from the left).</li>
	</ol>
	
	\subsection ovr_tmp_norm_msg_subsec "PS. #1-4: OVER TEMP. OCCURRED - NORMAL NOW"
	<ol>
		<li type="disc">This message is displayed if the 
			over-temperature condition occurred previously, 
			but it is stable now and the current is back 
			to normal. "PS. #" shows which Power Supply 
			was overheating, one through four from the left.</li>
	</ol>
	
	\subsection vol_drift_msg_subsec "VOLTAGE DRIFT > 15%"
	<ol>
		<li type="disc">This message is displayed if the 
			voltage has drifted more than 15% for more 
			than 1 minute.</li>
	</ol>
	
	\subsection interrupt_msg_subsec "INTERRUPT MODE"
	<ol>
		<li type="disc">DC ON/OFF switch is in the off state.</li>
	</ol>
	
	\subsection zero_cur_msg_subsec "ZERO CURRENT OUTPUT"
	<ol>
		<li type="disc">This message is displayed if there 
			is zero current but DC is ON.</li>
	</ol>
	
	\subsection com_err_msg_subsec "COMM. ERROR"
	<ol>
		<li type="disc">This message is displayed if there 
			is an internal communication error. To clear this 
			error the unit needs to be restarted. If the 
			restart did not help, then the unit needs to 
			be sent to the manufacturer for repair.</li>
		<li type="disc" style="color:red">If this happens 
			all I2C communications need to be checked, the 
			addresses that follow this message might give 
			hints where to look at but they are not 100% 
			accurate.</li>
	</ol>
	
	\note
	<ol>
		<li type="disc">If multiple messages need to be shown 
			at once, each message will take turns for 2 seconds 
			each.</li>
	</ol>
*/

/*! \file 

    \brief This is the main file with the main loop and interrupts
		that controls the whole program.

    \author
           Vladyslav Shaternik\n
           Email: vladik.shaternik32@gmail.com

    $Date: 2019-07-16 16:43:33 -0700 (tu, 16 jul 2019) $
*/

#include "main.h"


#define LCD_BCKLGHT_OFF (wr8(REG_PWM_DUTY, 0))
#define LCD_BCKLGHT_ON (wr8(REG_PWM_DUTY, get_ambient_brightness()))

/*
Initializes all ports to output/low. This is needed for safety
*/
void init_ports_out_low()
{
	//PORTA_DIR = (unsigned char)0x11111110; PORTA_OUT = (unsigned char)0x00110000;
	PORTB_DIR = (unsigned char)0x11111111; PORTB_OUT = (unsigned char)0x00000000;
	PORTC_DIR = (unsigned char)0x11111111; PORTC_OUT = (unsigned char)0x00000000;
	PORTD_DIR = (unsigned char)0x11101101; PORTD_OUT = (unsigned char)0x00000000;
	PORTE_DIR = (unsigned char)0x11111111; PORTE_OUT = (unsigned char)0x00000000;
	PORTR_DIR = (unsigned char)0x11111111; PORTR_OUT = (unsigned char)0x00000000;
}

/*
Initializes clock, pins, and various peripherals for an ATxmegaA4U
*/
void initialize(void)
{
	init_ports_out_low();
	//Clock initialization
	OSC_CTRL |= OSC_RC32MEN_bm; //enable 32MHz Internal Oscillator
	_delay_ms(1); //time needed for 32MHz to stabilize
	CCP = CCP_IOREG_gc; // allow change to protected IO registers
	CLK_CTRL = CLK_SCLKSEL_RC32M_gc; //select 32MHz internal oscillator
	
	//Port A initialization
	PORTA_PIN1CTRL = PORT_OPC_PULLUP_gc; PORTA_PIN2CTRL = PORT_OPC_PULLUP_gc; PORTA_PIN3CTRL = PORT_OPC_PULLUP_gc; //pullups on encdr-A, encdr-B and encdr-SW
	PORTA_PIN1CTRL |= PORT_ISC_BOTHEDGES_gc; PORTA_PIN2CTRL |= PORT_ISC_BOTHEDGES_gc; //both edges interrupts on encdr-A and encdr-B
	PORTA_PIN3CTRL |= PORT_ISC_FALLING_gc; //falling edge interrupt on encdr-SW
	PORTA_INT0MASK = (0x7 << 1); //enables interrupts on encdr-A,encdr-B,encdr-SW
	PORTA_INTCTRL = PORT_INT0LVL_LO_gc; //enable port A interrupts
	
	PORTA_DIRSET = (1 << GRN_LED); //set grn led to output
	PORTA_DIRSET = (1 << RED_LED); //set red led to output
	GRN_LED_OFF;
	RED_LED_OFF;
	
	//Port B initialization
	
	
	//Port C initialization
	PORTC_DIRSET = (1 << SCL_C); PORTC_OUTSET = (1 << SCL_C); //output/high on SCL
	PORTC_PIN0CTRL = PORT_OPC_PULLUP_gc; //pullup on SDA
	
	//Port D initialization
	
	//Port E initialization
	PORTE_DIRSET = (1 << SCL_E); PORTE_OUTSET = (1 << SCL_E); //output/high on SCL
	PORTE_PIN0CTRL = PORT_OPC_PULLUP_gc; //pullup on SDA
	
	//Port R initialization
	
	//SPI initialization
	PORTD_DIRSET = (1 << SS_D) | (1 << MOSI_D) | (1 << SCK_D); //output on SS, MOSI, and SCK
	SPID_CTRL = (1 << SPI_ENABLE_bp) | (1 << SPI_MASTER_bp); //enable SPI, Master, set clock rate fck/4 (8 MHz), MSB first
	
	
	//I2C initialization
	PMIC_CTRL = PMIC_LOLVLEN_bm; //enable low-lvl interrupts
	TWI_MasterInit(&twiMaster, &TWIC, TWI_MASTER_INTLVL_LO_gc, TWI_BAUDSETTING);
	
	//I2C initialization for external EEPROM
	TWI_MasterInit(&twiMasterForEEPROM, &TWIE, TWI_MASTER_INTLVL_LO_gc, TWI_BAUDSETTING);
	
	//RTC initialization
	CLK_RTCCTRL = (CLK_RTCSRC_RCOSC32_gc | CLK_RTCEN_bm); //choose 32kHz clock and enable RTC clock
	RTC_PER = 33;
	RTC_INTCTRL = (1 << 0); //enable overflow interrupt
	RTC_CTRL = 1; //no prescaling
	
	
	
	//ADC initialization
	ADCA_REFCTRL = ADC_REFSEL_AREFA_gc; //select AREFA as reference
	ADCA_CH0_CTRL = ADC_CH_START_bm | ADC_CH_INPUTMODE0_bm;
	ADCA_CH0_MUXCTRL = ADC_CH_MUXPOS_PIN6_gc; //choose PA6 as ADC input
	ADCA_CTRLA = ADC_ENABLE_bm; //enable ADC
}

/* Output is either FOURTY_ONE, THIRTY_EIGHT, or FOURTY_ONE_DUAL */
uint8_t figure_out_which_program()
{
	//int dac_val = 0;
	//int iteration_count = 0;
	//
	//int volatile voltage_if_thirty_eight = get_voltage(&twiMaster, FALSE, 0x45);
	//if(voltage_if_thirty_eight > 0){
	//output_one.max_current = 2000;
	//return THIRTY_EIGHT;
	//}
	//
	//int volatile first_voltage = get_voltage(&twiMaster, FALSE, OUTPUT1_INA226_ADDR);
	//twiMaster.readData[0] = 0;
	//twiMaster.readData[1] = 0;
	//int volatile second_voltage = get_voltage(&twiMaster, FALSE, OUTPUT2_INA226_ADDR);
	//
	//
	//if(second_voltage == 0){
	//output_one.max_current = 5000;
	//return FOURTY_ONE;
	//}
	//
	//while(first_voltage > second_voltage*0.98 && first_voltage < second_voltage*1.02){ //if both voltages are roughly the same
	//if(iteration_count > 3){
	//output_one.max_current = 5000;
	//return FOURTY_ONE;
	//}
	//
	//dac_val += 20;
	//write_pwm_to_41ec(dac_val, dac_val, TRUE, TRUE, TRUE, TRUE, BOARD_41EC_ADDR);
	//_delay_ms(500);
	//first_voltage = get_voltage(&twiMaster, FALSE, OUTPUT1_INA226_ADDR);
	//second_voltage = get_voltage(&twiMaster, FALSE, OUTPUT2_INA226_ADDR);
	//
	//++iteration_count;
	//}
	output_one.max_current = 2500;
	output_one.max_voltage = 5000;
	output_one.ina226_addr = OUTPUT1_INA226_ADDR; // 0x45 - THIRTY_EIGHT, 0x41 - FOURTY_ONE and new THIRY_EIGHT
	output_two.max_current = 2500;
	output_two.max_voltage = 5000;
	output_two.ina226_addr = OUTPUT2_INA226_ADDR;
	return FOURTY_ONE;
}

void initialize_variables()
{
	program_state.program = figure_out_which_program();
	program_state.mode = STARTUP_MODE;
	program_state.pson_low = TRUE;
	program_state.output = &output_two;
	program_state.comm_error1 = 0;
	program_state.comm_error2 = 0;
	program_state.comm_error3 = 0;
	program_state.comm_error4 = 0;
	program_state.comm_error5 = 0;
	program_state.comm_error6 = 0;
	program_state.testing_mode = FALSE;
	program_state.debug_mode = FALSE;
	program_state.need_to_save_target_current = FALSE;
	
	counters.backlight_timer = BCKLGHT_DFLT_TIME;
	counters.start_up_screen_timeout = STARTUP_SCREEN_TIME;
	counters.settings_to_turn_off_counter = SETTINGS_TO_TURN_OFF_AUTOMATICALLY_TIME;
	counters.check_temp_counter = 0;
	counters.screen_refresh_counter = 0;
	counters.clear_errors_pson_counter = 0;
	counters.voltage_drift_error_counter = 0;
	counters.i2c_error_counter = 0;
	counters.dc_off_time = 0;
	counters.debug_clicks_counter = 0;
	
	
	/* Output One Initialization */
	output_one.id = 1;
	output_one.target_current = 300;
	output_one.power_supply_max_current = 1250;
	output_one.power_supply_pwm_max = 1023;
	output_one.pwm_multiplier = 2.00;
	output_one.reduced_current_fraction = 1.00;
	//output_one.ina226_addr = OUTPUT1_INA226_ADDR;
	output_one.pwm_board_addr = BOARD_41EC_ADDR;
	output_one.dummy_dac_address = OUTPUT1_DAC101C085_ADDR;
	output_one.set_pwm = &write_pwm_to_41ec;
	output_one.write_to_dummy_dac = &write_to_dac101c085;
	output_one.need_to_set_current_voltage_pair = TRUE;
	output_one.set_current_state = VISIBLE_LOCKED;
	output_one.isCurrentAdjusted = FALSE;
	output_one.needsAdjusting = FALSE;
	output_one.isChanelused1 = FALSE;
	output_one.isChanelused2 = FALSE;
	output_one.dac_value = 0;
	output_one.dac_flag = FALSE;
	output_one.set_current_tries = 0;
	output_one.cur_adj = FALSE;
	
	/* Output Two Initialization */
	output_two.id = 2;
	output_two.target_current = 300;
	output_two.power_supply_max_current = 1250;
	output_two.power_supply_pwm_max = 1023;
	output_two.pwm_multiplier = 2.00;
	output_two.reduced_current_fraction = 1.00;
	//output_two.ina226_addr = OUTPUT2_INA226_ADDR;
	output_two.pwm_board_addr = BOARD_41EC_ADDR;
	output_two.dummy_dac_address = OUTPUT2_DAC101C085_ADDR;
	output_two.set_pwm = &write_pwm_to_41ec;
	output_two.write_to_dummy_dac = &write_to_dac101c085;
	output_two.need_to_set_current_voltage_pair = TRUE;
	output_two.set_current_state = VISIBLE_LOCKED;
	output_two.isCurrentAdjusted = FALSE;
	output_two.needsAdjusting = FALSE;
	output_two.isChanelused1 = FALSE;
	output_two.isChanelused2 = FALSE;
	output_two.dac_value = 0;
	output_two.dac_flag = FALSE;
	output_two.set_current_tries = 0;
	output_two.cur_adj = FALSE;
	
	
	/* Messages Initialization */
	messages.system_normal = "SYSTEM NORMAL";
	messages.dc_interrupted = "INTERRUPT MODE";
	messages.voltage_drift = "VOLTAGE DRIFT > 15%";
	messages.zero_current = "ZERO CURRENT OUTPUT";
	messages.max_current = "MAX. CURRENT";
	messages.min_current = "MIN. CURRENT";
	messages.max_voltage = "MAX. VOLTAGE";
	
	messages.over_temperature_output_one1 = "PS. #1:  OVER TEMP. REDUCED CURRENT";
	messages.over_temperature_normal_now_output_one1 = "PS. #1: OVER TEMP. OCCURRED - NORMAL NOW";
	messages.over_temperature_output_one2 = "PS. #2:  OVER TEMP. REDUCED CURRENT";
	messages.over_temperature_normal_now_output_one2 = "PS. #2: OVER TEMP. OCCURRED - NORMAL NOW";
	messages.voltage_drift_output_one = "STR. #1: VOLTAGE DRIFT > 15%";
	messages.zero_current_output_one = "STR. #1: ZERO CURRENT OUTPUT";
	messages.max_current_output_one = "STR. #1: MAX. CURRENT";
	messages.min_current_output_one = "STR. #1: MIN. CURRENT";
	messages.max_voltage_output_one = "STR. #1: MAX. VOLTAGE";
	
	messages.over_temperature_output_two1 = "PS. #3:  OVER TEMP. REDUCED CURRENT";
	messages.over_temperature_normal_now_output_two1 = "PS. #3: OVER TEMP. OCCURRED - NORMAL NOW";
	messages.over_temperature_output_two2 = "PS. #4:  OVER TEMP. REDUCED CURRENT";
	messages.over_temperature_normal_now_output_two2 = "PS. #4: OVER TEMP. OCCURRED - NORMAL NOW";
	messages.voltage_drift_output_two = "STR. #2: VOLTAGE DRIFT > 15%";
	messages.zero_current_output_two = "STR. #2: ZERO CURRENT OUTPUT";
	messages.max_current_output_two = "STR. #2: MAX. CURRENT";
	messages.min_current_output_two = "STR. #2: MIN. CURRENT";
	messages.max_voltage_output_two = "STR. #2: MAX. VOLTAGE";
	
	messages.communication_error = "COMM. ERROR:";
	messages.calibrating_notification = "CALIBRATING";
	

	gauge_x = 15;
	gauge_y = 4;
	gauge_width = 290;
	
	dummy_current_one = 0;
	dummy_current_two = 0;
	
	
	output_one.dac_value = 0;
	output_two.dac_value = 0;
	
	output_one.write_to_dummy_dac(output_one.dac_value, output_one.dummy_dac_address);
	
	if (program_state.program != THIRTY_EIGHT)
	{
		output_two.write_to_dummy_dac(output_two.dac_value, output_two.dummy_dac_address);
	}
	
	
	TIME_TO_CHECK_TEMP = 1800000;
	OVER_TEMP_VALUE = 50;
}

void execute_maintenance_functions(OutputState* output)
{
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	// If voltage or current is higher then its maximum + 10% for more that 2 seconds then turn off unit
	if (counters.over_current_counter > 2000 || counters.over_voltage_counter > 2000)
	{
		char message[8];
		message[0] = (uint8_t)(0x17);
		TWI_MasterWrite(&twiMaster, BOARD_41EC_ADDR, (uint8_t *) message, 1);
	}
	
	if (program_state.need_to_save_target_current)
	{
		write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_OUT1_CURRENT_VALUE_ADDR, output_one.target_current);
		write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_OUT2_CURRENT_VALUE_ADDR, output_two.target_current);
		program_state.need_to_save_target_current = FALSE;
	}
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_COM_ERROR1_AMT_ADDR, program_state.comm_error1);
	write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_COM_ERROR2_AMT_ADDR, program_state.comm_error2);
	write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_COM_ERROR3_AMT_ADDR, program_state.comm_error3);
	write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_COM_ERROR4_AMT_ADDR, program_state.comm_error4);
	write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_COM_ERROR5_AMT_ADDR, program_state.comm_error5);
	write_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, EEPROM_COM_ERROR6_AMT_ADDR, program_state.comm_error6);
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	check_save_voltage(output);
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	if (program_state.calibrating_mode_clicked)
	{
		output_one.set_current_state = VISIBLE_LOCKED;
		output_two.set_current_state = VISIBLE_LOCKED;
		if (program_state.program == FOURTY_ONE || program_state.program == THIRTY_EIGHT)
		{
			calibrate_unit(&output_one);
			
			output_one.target_current = 100;
		}
		else if (program_state.program == FOURTY_ONE_DUAL)
		{
			calibrate_unit(&output_one);
			
			output_one.target_current = 100;
			
			calibrate_unit(&output_two);
			
			output_two.target_current = 100;
		}
		
		program_state.calibrating_mode_clicked = FALSE;
	}
	else
	{
		handle_over_temperature(output);
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
	
		if(output->over_temp_error1 == FALSE && output->over_temp_error2 == FALSE && output->over_temp_half_second_count == 0)//should only check for voltage drift when there is no over-temperature error
		{ 
			check_voltage_drift(output);
		}
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
	
		// Stop blinking the "Set current:" if 1 minutes passed or error occured
		if (((counters.real_time_counter - counters.idle_time_counter) >= (36000000)) || program_state.uncleared_error)
		{
			output->set_current_state = VISIBLE_LOCKED;
			program_state.output = &output_two;
		}
	
		if(!program_state.changing_settings && !(output->voltage > 4000 && output->current < 4) && // set current only if on "Set CUrrent" page and if the load is not open
		!(program_state.comm_error1_to_display || program_state.comm_error2_to_display ||          // (voltage is not max && current is not zero) and if no comm errors and if unit is
		program_state.comm_error3_to_display || program_state.comm_error4_to_display ||            // not powering down (which happens when the current and voltage are zero and
		program_state.comm_error5_to_display || program_state.comm_error6_to_display) &&           // PWM with desired current are not zero).
		!(output->pwm_value > 30 && output->voltage < 4 && output->current < 4 && 
		MIN(output->target_current * output->reduced_current_fraction, output->max_current) > 0))
		{
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
			set_current(output);
			
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
		
			output->write_to_dummy_dac(output->dac_value, output->dummy_dac_address);
			if (program_state.program == FOURTY_ONE)
			{
				output->set_pwm(output_one.pwm_value, output_one.pwm_value, output_one.isChanelused1, output_two.isChanelused2, output_two.isChanelused1, output_one.isChanelused2, BOARD_41EC_ADDR);
			}
			else
			{
				output->set_pwm(output_one.pwm_value, output_two.pwm_value, output_one.isChanelused1, output_two.isChanelused2, output_two.isChanelused1, output_one.isChanelused2, BOARD_41EC_ADDR);
			}
			_delay_ms(100);
			if(output->over_temp_error1 == FALSE && output->over_temp_error2 == FALSE && output->over_temp_half_second_count == 0)//should only check for voltage drift when there is no over-temperature error
			{
				if (abs(MIN(output->target_current * output->reduced_current_fraction, output->max_current) - output->current) > MIN_ACCURACY && (counters.real_time_counter - counters.idle_time_counter) > 4000 && !output->hit_min_current && !output->hit_max_voltage && !output->hit_max_current)
				{
					calibrate_value(output);
				}
			}
		}
		else
		{
			if (program_state.comm_error1_to_display || program_state.comm_error2_to_display ||
			program_state.comm_error3_to_display || program_state.comm_error4_to_display ||
			program_state.comm_error5_to_display || program_state.comm_error6_to_display)
			{
				char message[1] = {0};
				
				if (program_state.comm_error1_to_display)
				{
					if(!TWI_MasterWrite(&twiMaster, OUTPUT1_INA226_ADDR, (uint8_t *) message, 1))
					{
						counters.i2c_error_counter++;
					}
				}
				if (program_state.comm_error2_to_display)
				{
					if(!TWI_MasterWrite(&twiMaster, OUTPUT2_INA226_ADDR, (uint8_t *) message, 1))
					{
						counters.i2c_error_counter++;
					}
				}
				if (program_state.comm_error3_to_display)
				{
					if(!TWI_MasterWrite(&twiMaster, OUTPUT1_DAC101C085_ADDR, (uint8_t *) message, 1))
					{
						counters.i2c_error_counter++;
					}
				}
				if (program_state.comm_error4_to_display)
				{
					if(!TWI_MasterWrite(&twiMaster, OUTPUT2_DAC101C085_ADDR, (uint8_t *) message, 1))
					{
						counters.i2c_error_counter++;
					}
				}
				if (program_state.comm_error5_to_display)
				{
					if(!TWI_MasterWrite(&twiMaster, BOARD_41EC_ADDR, (uint8_t *) message, 1))
					{
						counters.i2c_error_counter++;
					}
				}
				if (program_state.comm_error6_to_display)
				{
					if(!TWI_MasterWrite(&twiMaster, EXTERNAL_EEPROM_ADDR, (uint8_t *) message, 1))
					{
						counters.i2c_error_counter++;
					}
				}
			
			}
		}
	}
}

void read_current_and_voltage(OutputState* output)
{
	if (!output->high_averaging) //set to high averaging before taking current/voltage reading
	{ 
		output->high_averaging = TRUE;
		
		high_INA_averaging(&twiMaster, output->ina226_addr);
		_delay_ms(5);
	}
	
	int volatile desired_current = MIN(output->target_current * output->reduced_current_fraction, output->max_current);
	
	int volatile present_current = get_current(&twiMaster, FALSE, output->ina226_addr);//round_to_tens(get_dummy_current(output->id));  //round_to_tens(get_current(&twiMaster, FALSE, output->ina226_addr));
	
	if(program_state.program == FOURTY_ONE)
	{
		if(output->id == output_one.id)
		{
			present_current += get_current(&twiMaster, FALSE, output_two.ina226_addr);//get_dummy_current(output_two.id); //round_to_tens(get_current(&twiMaster, FALSE, output_two.ina226_addr));
		}
		else if(output->id == output_two.id)
		{
			present_current += get_current(&twiMaster, FALSE, output_one.ina226_addr);//get_dummy_current(output_one.id); //round_to_tens(get_current(&twiMaster, FALSE, output_one.ina226_addr));
		}
	}
	
	output->current = round_to_tens(present_current);
	
	if (abs(present_current - desired_current) < MIN_ACCURACY)
	{
		output->current = desired_current;
	}
	
	output->voltage = round_to_tens(get_voltage(&twiMaster, FALSE, output->ina226_addr));
	
	if (output->voltage >= output->max_voltage)
	{
		output->hit_max_voltage = TRUE;
	}
}

static bool powerGood = FALSE;

int main(void)
{
	while(!(PORTA_IN & (1 << 0)))
	{
		powerGood = FALSE;
	}
	
	powerGood = TRUE;
	
	// BROWN-OUT RESET INITIALIZATION
	FUSE_FUSEBYTE5 = BODLVL_3V0_gc;
	FUSE_FUSEBYTE5 = BODACT_CONTINUOUS_gc;
	FUSE_FUSEBYTE4 = OSC_XOSCSEL_32KHz_gc;
	
	wdt_disable();
	_delay_ms(100);
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	initialize(); //initializes clocks and pin settings

	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	FT813_init(); //initializes display
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	sei();
	
	
	wr8(REG_PWM_DUTY, 0); //keeps screen off during drawing gauge/snapshot phase
	wdt_reset();
	
	initialize_variables(); //sets initial values to global variables
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	draw_gauge_and_partial_snapshot(gauge_x, gauge_y, gauge_width); //draws gauge and takes snapshot
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	load_values_from_eeprom();
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	clear_pwms(BOARD_41EC_ADDR);
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	clear_dummy_dacs(OUTPUT1_DAC101C085_ADDR, OUTPUT2_DAC101C085_ADDR);
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	write_screen(); //refreshes screen with newest data
	
	//_delay_ms(1500);
	
	for(int i = 0; i < 25; ++i)
	{
		wr8(REG_PWM_DUTY, i); //turns screen back on
		_delay_ms(35);
	}
	
	
	wdt_reset();
	//Watch dog (or dead man) timer initialization
	wdt_enable(CCP_IOREG_gc);
	wdt_enable(WDT_CEN_bm);
	wdt_enable(WDT_ENABLE_bm);
	wdt_enable(WDTO_2S);
	
	while (1)
	{
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		
		while(!(PORTA_IN & (1 << 0)))
		{
			powerGood = FALSE;
			set_sleep_mode(SLEEP_MODE_PWR_DOWN);
			sleep_mode();
		}
		
		read_pson();
		
		if(program_state.pson_low){ //if DC OFF
			program_state.output->need_to_set_current_voltage_pair = TRUE;
			clear_all_errors();
			output_one.pson_was_low = TRUE;
			output_two.pson_was_low = TRUE;
		}
		else { //if DC ON
			handle_encoder_clicks(); //this checks how long you have been holding a click, changes program state accordingly
		}
		
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		
		if (counters.check_program_state_counter >= 500) //every 500 ms this if-block is executed
		{ 
			
			if(counters.backlight_timer)
			{
				LCD_BCKLGHT_ON;
			}
			else
			{
				LCD_BCKLGHT_OFF;
			}
			
			if (program_state.output->set_current_state == VISIBLE_LOCKED)
			{
				
				program_state.output = &output_two;
			}
			
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
			read_current_and_voltage(&output_one);
			
			if(program_state.program == FOURTY_ONE_DUAL || program_state.program == FOURTY_ONE)
			{
				read_current_and_voltage(&output_two);
			}
			
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************
			
			if(!program_state.pson_low) //if DC ON
			{ 
				execute_maintenance_functions(&output_one);
				
				if(program_state.program == FOURTY_ONE_DUAL)
				{
					execute_maintenance_functions(&output_two);
				}

			}
			
			counters.check_program_state_counter = 0;
		}
	}
}

ISR(RTC_OVF_vect)//interrupts every 1ms
{
	if (powerGood)
	{
		++counters.check_program_state_counter;
		++counters.real_time_counter;
		++counters.rtc_int_count;
		++counters.periodic_int_count;
		++counters.update_message_box_counter;
		++counters.check_temp_counter;
		
		if (output_one.current > output_one.max_current * 1.2 || output_two.current > output_two.max_current * 1.2)
		{
			counters.over_current_counter++;
		}
		else
		{
			counters.over_current_counter = 0;
		}
		
		if (output_one.voltage > output_one.max_voltage * 1.2 || output_two.voltage > output_two.max_voltage * 1.2)
		{
			counters.over_voltage_counter++;
		}
		else
		{
			counters.over_voltage_counter = 0;
		}
		
		if (counters.clear_errors_pson_counter > 0)
		{
			--counters.clear_errors_pson_counter;
			clear_all_errors();
		}
		if (twiMaster.status == TWIM_STATUS_BUSY || twiMasterForEEPROM.status == TWIM_STATUS_BUSY)
		{
			counters.i2c_busy_time++;
		
			if (counters.i2c_busy_time > 100)
			{
				PMIC_CTRL = PMIC_LOLVLEN_bm; //enable low-lvl interrupts
				TWI_MasterInit(&twiMaster, &TWIC, TWI_MASTER_INTLVL_LO_gc, TWI_BAUDSETTING);
				TWI_MasterInit(&twiMasterForEEPROM, &TWIE, TWI_MASTER_INTLVL_LO_gc, TWI_BAUDSETTING);
				//**************************************************
				wdt_reset(); // WATCH DOG TIMER RESET
				//**************************************************
			}
		}
		else
		{
			counters.i2c_busy_time = 0;
		}
		if (counters.real_time_counter > 5000)
		{
			if (counters.i2c_error_counter > 50)
			{
				PMIC_CTRL = PMIC_LOLVLEN_bm; //enable low-lvl interrupts
				TWI_MasterInit(&twiMaster, &TWIC, TWI_MASTER_INTLVL_LO_gc, TWI_BAUDSETTING);
				TWI_MasterInit(&twiMasterForEEPROM, &TWIE, TWI_MASTER_INTLVL_LO_gc, TWI_BAUDSETTING);
				//**************************************************
				wdt_reset(); // WATCH DOG TIMER RESET
				//**************************************************
			}
		}
		else
		{
			counters.i2c_error_counter = 0;
		}
	
		counters.screen_refresh_counter++;
		if (counters.screen_refresh_counter > 100 && counters.real_time_counter > 5000)
		{
			write_screen();
		
			counters.screen_refresh_counter = 0;
		}
		if(counters.start_up_screen_timeout > 0)
		{
			counters.start_up_screen_timeout -= 1;
			if(counters.start_up_screen_timeout == 0)
			{
				program_state.mode = NORMAL_MODE;
			}
		}
		if (program_state.mode == SETTINGS_MODE && (counters.real_time_counter - counters.idle_time_counter) > 10)
		{
			clear_all_errors();
			counters.settings_to_turn_off_counter--;
		
			if (counters.settings_to_turn_off_counter == 0 && program_state.settings_row_num != 1 && program_state.settings_row_num != 2 && !program_state.testing_mode)
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
					output_two.max_current = 3000;
					output_two.max_voltage = 5000;
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
				output_one.isCurrentAdjusted = FALSE;
				output_one.needsAdjusting = FALSE;
				output_two.isCurrentAdjusted = FALSE;
				output_two.needsAdjusting = FALSE;
			}
		}
		else
		{
			counters.settings_to_turn_off_counter = SETTINGS_TO_TURN_OFF_AUTOMATICALLY_TIME;
		}
	
		if(counters.rtc_int_count >= 500){ //if half a second has passed
		
		
			if(program_state.output->set_current_state == INVISIBLE || program_state.output->set_current_state == VISIBLE)
			{
				program_state.output->set_current_state ^= 1; //flips value
			}
		
			blink_led();
		
			if(counters.backlight_timer > 0)
			{
				--counters.backlight_timer;
				if(counters.backlight_timer == 0)
				{
					program_state.mode = STARTUP_MODE;
					LCD_BCKLGHT_OFF;
				}
			}
		
			if(program_state.changing_settings > 0)
			{
				--program_state.changing_settings;
				program_state.need_to_save_target_current = TRUE;
			}
		
			counters.rtc_int_count = 0;
		}
	}
	
	RTC_INTFLAGS = 1; //clear OVF interrupt flag
}


ISR(TWIC_TWIM_vect)
{
	if (powerGood)
	{
		TWI_MasterInterruptHandler(&twiMaster);
	}
}
ISR(TWIE_TWIM_vect)
{
	if (powerGood)
	{
		TWI_MasterInterruptHandler(&twiMasterForEEPROM);
	}
}

/************************************************************************/
/* FUNCTION - debounce                                                  */
/* This function debounces switches, encoders, buttons...               */
/* It counts amount of highs and lows until one of them hits            */
/* @precision times in a row                                            */
/*                                                                      */
/************************WARNING!!!**************************************/
/*         USE CAREFULL THIS FUNCTION INSIDE INTERRAPT!                 */
/*               (IT COULD TAKE TOO MUCH TIME)                          */
/************************WARNING!!!**************************************/
/*                                                                      */
/* ASSUMPTIONS: This function assumes that you have TRUE and FALSE      */
/*              declared as macros (#define)                            */
/*                                                                      */
/* @port - address of port where located pin that needs to be debounced */
/*         (example - &PORTA_IN)                                        */
/* @pin - pin in the port that needs to be debounced                    */
/*        (example - 3)                                                 */
/* @precisionUs - how many times in a row should highs or lows hit. It  */
/*                is also equals to the time in ms of the delay that    */
/*                this function causes                                  */
/*                (example - 20)                                        */
/* @maxUs - max amt of microseconds to last for this function (usually  */
/*          6 times more than @precisionUs)                             */
/* @return - whether the function debounced pin correctly (If running   */
/*           time of the function reached @maxUs returns false(0))      */
/************************************************************************/
uint8_t debounce(volatile unsigned char *port, uint8_t pin, uint8_t precisionUs, uint8_t maxUs)
{
	uint8_t counter = 0;
	uint8_t counterUs = 0;
	uint8_t isHigh = FALSE;
	
	while(counter != precisionUs && counterUs != maxUs)
	{
		// *(volatile uint8_t *)(port) - is a dereference of a port's address, therefore, we read directly from memory
		if(*(volatile uint8_t *)(port) & (1 << pin))
		{
			counter = isHigh ? counter + 1 : 0;
			isHigh = TRUE;
		}
		else
		{
			counter = isHigh ? 0 : counter + 1;
			isHigh = FALSE;
		}
		_delay_us(1);
		counterUs++;
	}
	
	return counterUs != maxUs;
}

ISR(PORTA_INT0_vect)//interrupts from an encoder turn or push
{
	if (powerGood)
	{
	
		output_one.pson_was_low = FALSE;
		output_two.pson_was_low = FALSE;
		output_one.set_current_tries = 0;
		output_two.set_current_tries = 0;
		if (program_state.mode == NORMAL_MODE)
		{
			output_one.set_current_tries = 0;
			output_two.set_current_tries = 0;
		}
		
		bool is_debounce_successful = TRUE;
		is_debounce_successful &= debounce(&PORTA_IN, ENCDR_SW, 10, 60);
		is_debounce_successful &= debounce(&PORTA_IN, ENCDR_A, 10, 60);
		is_debounce_successful &= debounce(&PORTA_IN, ENCDR_B, 10, 60);
		
		if (is_debounce_successful)
		{
			if(!(PORTA_IN & (1 << ENCDR_SW)))//if switch pin is low
			{ 
				if(counters.backlight_timer > 0)
				{
					program_state.output->set_current_state = VISIBLE_LOCKED;
				}
				else
				{
					counters.start_up_screen_timeout = STARTUP_SCREEN_TIME;
					program_state.output->set_current_state = VISIBLE_LOCKED;
				}
		
		
				if(!encoder_state.holding_click)
				{
					counters.periodic_int_count = 0;
					encoder_state.holding_click = TRUE;
				}
				counters.backlight_timer = BCKLGHT_DFLT_TIME;
			}
			else if(encoder_state.both_low)
			{
				if(counters.backlight_timer > 0)
				{
					if((PORTA_IN & (1 << ENCDR_B)))//left turn
					{ 
						if(program_state.mode == NORMAL_MODE && program_state.output->set_current_state != VISIBLE_LOCKED)
						{
							decrease_target_current(program_state.output);
					
							counters.debug_clicks_counter = 0;
							counters.calibrate_clicks_counter = 0;
						}
				
						if (program_state.mode == SETTINGS_MODE)
						{
							if (program_state.testing_mode)
							{
								if (program_state.settings_row_num == 0)
								{
									OVER_TEMP_VALUE--;
								}
								else if (program_state.settings_row_num == 1)
								{
									TIME_TO_CHECK_TEMP -= 1000;
								}
							}
							else
							{
								counters.debug_clicks_counter = 0;
								counters.calibrate_clicks_counter++;
								
								if (counters.calibrate_clicks_counter > 30)
								{
									program_state.calibrating_mode = TRUE;
									program_state.debug_mode = FALSE;
								}
								
								if (program_state.calibrating_mode)
								{
									program_state.settings_row_num = 0;
								}
								
								if (program_state.debug_mode)
								{
									if (program_state.settings_row_num > 0)
									{
										program_state.settings_row_num--;
									}
								}
							}
						}
					}
					else if((PORTA_IN & (1 << ENCDR_A))) //right turn
					{
						if(program_state.mode == NORMAL_MODE && program_state.output->set_current_state != VISIBLE_LOCKED)
						{
							increase_target_current(program_state.output);
					
							counters.debug_clicks_counter = 0;
							counters.calibrate_clicks_counter = 0;
						}
				
						if (program_state.mode == SETTINGS_MODE)
						{
							if (program_state.testing_mode)
							{
								if (program_state.settings_row_num == 0)
								{
									OVER_TEMP_VALUE++;
								}
								else if (program_state.settings_row_num == 1)
								{
									TIME_TO_CHECK_TEMP += 1000;
								}
							}
							else
							{
								counters.debug_clicks_counter++;
								counters.calibrate_clicks_counter = 0;
								
								if (counters.debug_clicks_counter > 30)
								{
									program_state.debug_mode = TRUE;
									program_state.calibrating_mode = FALSE;
								}
								
								if (program_state.calibrating_mode)
								{
									program_state.settings_row_num = 1;
								}
								
								if (program_state.debug_mode)
								{
									if (program_state.settings_row_num < 2)
									{
										program_state.settings_row_num++;
									}
								}
							}
						}
					}
				}
				else
				{
					counters.start_up_screen_timeout = STARTUP_SCREEN_TIME;
					program_state.output->set_current_state = VISIBLE_LOCKED;
				}
		
				if (counters.start_up_screen_timeout == 0)
				{
					clear_all_errors();
				}
		
				counters.backlight_timer = BCKLGHT_DFLT_TIME;
		
				counters.periodic_int_count = 0;
				encoder_state.both_low = FALSE;
				encoder_state.b_low = FALSE;
				encoder_state.a_low = FALSE;
				_delay_ms(2);
			}
			else if(!(PORTA_IN & (1 << ENCDR_B)) && !encoder_state.b_low)
			{
				encoder_state.b_low = TRUE;
				if(encoder_state.a_low)
				{
					encoder_state.both_low = TRUE;
					_delay_ms(1);
					encoder_state.b_low = FALSE;
					encoder_state.a_low = FALSE;
				}
			}
			else if(!(PORTA_IN & (1 << ENCDR_A)) && !encoder_state.a_low)
			{
				encoder_state.a_low = TRUE;
				if(encoder_state.b_low)
				{
					encoder_state.both_low = TRUE;
					_delay_ms(1);
					encoder_state.b_low = FALSE;
					encoder_state.a_low = FALSE;
				}
			}
			else if(encoder_state.b_low && PORTA_IN & (1 << ENCDR_A))//if B is low and A is high
			{ 
				encoder_state.a_low = FALSE;
				encoder_state.b_low = FALSE;
				encoder_state.both_low = FALSE;
			}
			else if(encoder_state.a_low && PORTA_IN & (1 << ENCDR_B)) //if A is low and B is high
			{
				encoder_state.a_low = FALSE;
				encoder_state.b_low = FALSE;
				encoder_state.both_low = FALSE;
			}
	
			program_state.output->need_to_set_current_voltage_pair = TRUE;
			counters.idle_time_counter = counters.real_time_counter;
		}
	}
	PORTA_INTFLAGS = 0xFF; //clear port interrupt flags
}



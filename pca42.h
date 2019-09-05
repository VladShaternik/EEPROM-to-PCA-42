/*
* pca42.h
*
* Created: 10/30/2018 9:24:35 AM
*  Author: ENG_3

This file defines pins and other general variables for the PCA-42 xMega
*/


#ifndef PCA42_H_
#define PCA42_H_

#define F_CPU 20000000

#define OUTPUT1_INA226_ADDR 0x41 // 0x45 for THIRTY_EIGHT / 0x41 - FOURTY_TWO and new THIRY_EIGHT
#define OUTPUT2_INA226_ADDR 0x40
#define OUTPUT1_DAC101C085_ADDR 0x0A // 0x09 for THIRTY_EIGHT / 0x0A - FOURTY_TWO / 4D - new Boards
#define OUTPUT2_DAC101C085_ADDR 0x09 // 0x09 for FOURTY_TWO / 0x0A - THIRTY_EIGHT / 4E - new Boards
#define BOARD_41EC_ADDR 0x4C
#define EXTERNAL_EEPROM_ADDR 0x51
#define EEPROM_OUT1_CURRENT_VALUE_ADDR 2600
#define EEPROM_OUT2_CURRENT_VALUE_ADDR 2602
#define EEPROM_CHANELS_AMT_ADDR 2604
#define EEPROM_COM_ERROR1_AMT_ADDR 2606
#define EEPROM_COM_ERROR2_AMT_ADDR 2608
#define EEPROM_COM_ERROR3_AMT_ADDR 2610
#define EEPROM_COM_ERROR4_AMT_ADDR 2612
#define EEPROM_COM_ERROR5_AMT_ADDR 2614
#define EEPROM_COM_ERROR6_AMT_ADDR 2616

#define TRUE 1
#define FALSE 0
#define HIGH 1
#define LOW 0

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/eeprom.h>
#include <stdbool.h>
#include <stdlib.h>


/* I2C Baudrate Settings (BAUDRATE 100kHz and Baudrate Register Settings) */
#define TWI_BAUDRATE 100000
#define TWI_BAUDSETTING TWI_BAUD(F_CPU, TWI_BAUDRATE)


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define GRN_LED_ON (PORTA_OUTCLR = (1 << GRN_LED))
#define GRN_LED_OFF (PORTA_OUTSET = (1 << GRN_LED))
#define GRN_LED_TGL (PORTA_OUTTGL = (1 << GRN_LED))

#define RED_LED_ON (PORTA_OUTCLR = (1 << RED_LED))
#define RED_LED_OFF (PORTA_OUTSET = (1 << RED_LED))
#define RED_LED_TGL (PORTA_OUTTGL = (1 << RED_LED))


enum DAC6574_CHANNELS {A, B, C, D};
enum PORTA_PINS {AREF, ENCDR_A, ENCDR_B, ENCDR_SW, RED_LED, GRN_LED, AMBIENTLS, PSON};
enum PORTC_PINS {SDA_C, SCL_C, RX_C, TX_C, SS_C, MOSI_C, MISO_C, SCK_C};
enum PORTR_PINS {XTL2, XTL1};
enum PORTE_PINS {SDA_E, SCL_E, RX_E, TX_E};
enum PORTD_PINS {PD_N, INT_N, RX_D, TX_D, SS_D, MOSI_D, MISO_D, SCK_D};
enum CURRENT_SETTING_ERRORS {CURRENT_OK, HIT_MIN, hit_max_current, CANNOT_INCREASE};

typedef struct 
{
	char* system_normal;
	char* dc_interrupted;
	
	/* Single Mode */
	char* voltage_drift;
	char* zero_current;
	char* max_current;
	char* min_current;
	char* max_voltage;
	
	/* Dual Mode */
	
	// Output One
	char* over_temperature_output_one1;
	char* over_temperature_normal_now_output_one1;
	char* over_temperature_output_one2;
	char* over_temperature_normal_now_output_one2;
	char* voltage_drift_output_one;
	char* zero_current_output_one;
	char* max_current_output_one;
	char* min_current_output_one;
	char* max_voltage_output_one;
	
	// Output Two
	char* over_temperature_output_two1;
	char* over_temperature_normal_now_output_two1;
	char* over_temperature_output_two2;
	char* over_temperature_normal_now_output_two2;
	char* voltage_drift_output_two;
	char* zero_current_output_two;
	char* max_current_output_two;
	char* min_current_output_two;
	char* max_voltage_output_two;
	
	char* communication_error;
	char* calibrating_notification;
	
} LCDMessages;


typedef struct 
{
	uint8_t id;
	uint16_t power_supply_max_current;
	uint16_t power_supply_pwm_max;
	
	//Flags
	bool hit_max_current;
	bool hit_min_current;
	bool hit_max_voltage;
	bool voltage_drift_error;
	bool over_temp_error1;
	bool over_temp_error2;
	bool over_temp_error_uncleared1;
	bool over_temp_error_uncleared2;
	bool need_to_set_current_voltage_pair;
	bool high_averaging;
	uint8_t set_current_state; //0 = INVISIBLE, 1 = VISIBLE, 2 = VISIBLE BUT LOCKED
	
	//Setting Current Variables
	uint16_t target_current;
	uint16_t max_current;
	uint16_t max_voltage;
	uint16_t current;
	uint16_t voltage;
	uint16_t pwm_value; // 10-bit pwm value
	uint16_t dac_value; // 10-bit dac value
	uint8_t  set_current_tries;
	float pwm_multiplier; // this fraction is used to adjust pwm if calculated pwm is not correct
	float reduced_current_fraction;
	//int total_current_dac_val;
	int resistor_error_offset;
	uint8_t isCurrentAdjusted;
	uint8_t needsAdjusting;
	bool isChanelused1;
	bool isChanelused2;
	bool dac_flag;
	bool pson_was_low;
	bool cur_adj;
	uint16_t voltage_drift_counter;
	
	//Setting Current Functions
	void (*set_pwm)(uint16_t, uint16_t, bool, bool, bool, bool, uint8_t);
	void (*write_to_dummy_dac)(uint16_t, uint8_t);
	
	//State variables
	uint16_t current_voltage_pair[2];
	
	//Counters
	uint16_t over_temp_half_second_count;
	
	//Addresses
	volatile uint8_t ina226_addr;
	uint8_t pwm_board_addr;
	uint8_t dummy_dac_address;
	
} OutputState;

enum I2C_ERROR_DEVICES {INA1, INA2, DAC1, DAC2, PWM};

typedef struct 
{
	uint16_t backlight_timer;
	uint32_t periodic_int_count; //keeps track of the # of PIT interrupts
	uint32_t rtc_int_count; //keeps track of the # of RTC interrupts
	uint16_t check_program_state_counter;
	uint64_t idle_time_counter;
	uint64_t real_time_counter;
	uint16_t update_message_box_counter;
	uint16_t start_up_screen_timeout;
	uint16_t settings_to_turn_off_counter;
	uint16_t check_temp_counter;
	uint16_t screen_refresh_counter;
	uint16_t clear_errors_pson_counter;
	uint16_t voltage_drift_error_counter;
	uint16_t i2c_error_counter;
	uint16_t i2c_busy_time;
	uint16_t dc_off_time;
	uint16_t debug_clicks_counter;
	uint16_t calibrate_clicks_counter;
	uint16_t over_current_counter;
	uint16_t over_voltage_counter;
} TimerCount;

typedef struct 
{
	uint16_t num_outputs;
	uint8_t changing_settings;
	uint8_t mode; //NORMAL MODE, SETTINGS MODE, STARTUP MODE
	uint8_t program;
	bool pson_low;
	bool uncleared_error;
	uint16_t program_settings[10];
	uint8_t settings_row_num;
	uint16_t comm_error1;
	uint16_t comm_error2;
	uint16_t comm_error3;
	uint16_t comm_error4;
	uint16_t comm_error5;
	uint16_t comm_error6;
	bool comm_error1_to_display;
	bool comm_error2_to_display;
	bool comm_error3_to_display;
	bool comm_error4_to_display;
	bool comm_error5_to_display;
	bool comm_error6_to_display;
	bool testing_mode;
	bool debug_mode;
	bool calibrating_mode;
	bool calibrating_mode_clicked;
	bool need_to_save_target_current;
	OutputState* output;
	
} ProgramState;

typedef struct 
{
	uint8_t a_low;
	uint8_t b_low;
	uint8_t both_low;
	uint8_t holding_click;
} EncoderState;



#endif /* PCA42_H_ */
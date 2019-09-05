/*
* main.h
*
* Created: 12/20/2018 12:19:05 PM
*  Author: ENG_3
*/

#include "pca42.h"
#include "twi_master_driver.h"
#include "ina226.h"
#include "ft800_functions.h"
#include "setting_current_functions.h"
#include "program_functions.h"
#include <avr/wdt.h>
#include <avr/sleep.h>

#ifndef MAIN_H_
#define MAIN_H_

enum PROGRAMS {THIRTY_EIGHT, FOURTY_ONE, FOURTY_ONE_DUAL};
enum MODES {NORMAL_MODE, SETTINGS_MODE, STARTUP_MODE};
enum OUTPUT_TYPE {SINGLE, DOUBLE};
enum SET_CURRENT_STATES {INVISIBLE, VISIBLE, VISIBLE_LOCKED};

#define SETTINGS_HOLD_TIME 2000
#define EXIT_SETTINGS_HOLD_TIME 1000
#define STARTUP_SCREEN_TIME 3000
#define BCKLGHT_DFLT_TIME 72000 //value * 500ms
#define CHANGING_SETTINGS_TIME 2 // value * 500ms.
#define SETTINGS_TO_TURN_OFF_AUTOMATICALLY_TIME 1500
#define VOLTAGE_DROP_COEFICIENT 0.989689926
long TIME_TO_CHECK_TEMP; //1800000 // 30 min
uint16_t OVER_TEMP_VALUE; //50 - 75 degrees C 

#define NUM_POWER_SUPPLIES 4

#define MIN_ACCURACY 1

int gauge_x;
int gauge_y;
int gauge_width;

TWI_Master_t twiMaster;    /*!< TWI master module. */
TWI_Master_t twiMasterForEEPROM;    /*!< TWI master module. */

EncoderState encoder_state;
OutputState output_one;
OutputState output_two;
ProgramState program_state;
TimerCount counters;
LCDMessages messages;

void write_screen();
void read_current_and_voltage(OutputState* output);

int dummy_current_one;
int dummy_current_two;

#endif /* MAIN_H_ */
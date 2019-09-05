/*
 * basic_vars_macros.h
 *
 * Created: 11/19/2018 11:28:52 AM
 *  Author: ENG_3
 */ 


#ifndef BASIC_VARS_MACROS_H_
#define BASIC_VARS_MACROS_H_

#include "twi_master_driver.h"

TWI_Master_t twiMaster;    /*!< TWI master module. */
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define TRUE 1
#define FALSE 0
#define HIGH 1
#define LOW 0

enum DAC6574_CHANNELS {A, B, C, D};
enum PORTA_PINS {AREF, ENCDR_A, ENCDR_B, ENCDR_SW, RED_LED, GRN_LED, AMBIENTLS, ALRT_5050};
enum PORTC_PINS {SDA_C, SCL_C, RX_C, TX_C, SS_C, MOSI_C, MISO_C, SCK_C};
enum PORTR_PINS {XTL2, XTL1};
enum PORTE_PINS {SDA_E, SCL_E, RX_E, TX_E};
enum PORTD_PINS {PD_N, INT_N, RX_D, TX_D, SS_D, MOSI_D, MISO_D, SCK_D};
enum PORTEXPANDER_PINS {LD5050, ENOP, NC2, NC3, ALRT, NC5, PSON, PD};
enum CURRENT_SETTING_ERRORS {CURRENT_OK, HIT_MIN, HIT_MAX, CANNOT_INCREASE};



#endif /* BASIC_VARS_MACROS_H_ */
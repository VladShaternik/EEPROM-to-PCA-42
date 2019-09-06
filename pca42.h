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

typedef struct 
{
	uint8_t a_low;
	uint8_t b_low;
	uint8_t both_low;
	uint8_t holding_click;
} EncoderState;

#endif /* PCA42_H_ */
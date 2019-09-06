/*
* main.h
*
* Created: 12/20/2018 12:19:05 PM
*  Author: ENG_3
*/

#include "pca42.h"
#include "twi_master_driver.h"
#include <avr/wdt.h>
#include <avr/sleep.h>

#ifndef MAIN_H_
#define MAIN_H_

TWI_Master_t twiMaster;    /*!< TWI master module. */
TWI_Master_t twiMasterForEEPROM;    /*!< TWI master module. */

#endif /* MAIN_H_ */
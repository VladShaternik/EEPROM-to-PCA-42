/*! \file 

    \brief This is the main file with the main loop and interrupts
		that controls the whole program.

    \author
           Vladyslav Shaternik\n
           Email: vladik.shaternik32@gmail.com

    $Date: 2019-09-05 16:43:33 -0700 (tu, 16 jul 2019) $
*/

#include "main.h"

uint16_t read_external_eeprom(TWI_Master_t *twi, uint8_t eepromAddress, uint16_t dataAddress);
void write_external_eeprom(TWI_Master_t *twi, uint8_t eepromAddress, uint16_t dataAddress, uint16_t data);

/*
Initializes clock, pins, and various peripherals for an ATxmegaA4U
*/
void initialize(void)
{
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
}

bool isLoading = FALSE;

int main(void)
{
	initialize(); //initializes clocks and pin settings

	sei();
	
	while (1)
	{
		RED_LED_OFF;
		GRN_LED_ON;
		
		if (isLoading)
		{
			RED_LED_ON;
			GRN_LED_OFF;
			
			for (int i = 0; i < 2700; i += 2)//2700
			{
				uint16_t data = read_external_eeprom(&twiMasterForEEPROM, EXTERNAL_EEPROM_ADDR, i);
				write_external_eeprom(&twiMaster, EXTERNAL_EEPROM_ADDR, i, data);
			}
			
			isLoading = FALSE;
		}
	}
}

uint16_t read_external_eeprom(TWI_Master_t *twi, uint8_t eepromAddress, uint16_t dataAddress)
{
	uint16_t received_data = 0;
	
	char message[8];
	message[0] = (uint8_t)(dataAddress >> 8);
	message[1] = (uint8_t)(dataAddress);
	TWI_MasterWrite(twi, eepromAddress, (uint8_t *) message, 2);
	_delay_ms(20);
	
	TWI_MasterRead(twi, eepromAddress, 1);
	_delay_ms(20);
	
	dataAddress++;
	received_data = twi->readData[0] << 8;
	
	message[0] = (uint8_t)(dataAddress >> 8);
	message[1] = (uint8_t)(dataAddress);
	TWI_MasterWrite(twi, eepromAddress, (uint8_t *) message, 2);
	_delay_ms(20);
	
	TWI_MasterRead(twi, eepromAddress, 1);
	_delay_ms(20);
	
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
	
	char message[8];
	message[0] = (uint8_t)(dataAddress >> 8);
	message[1] = (uint8_t)(dataAddress);
	message[2] = (uint8_t)(data >> 8);
	TWI_MasterWrite(twi, eepromAddress, (uint8_t *) message, 3);
	_delay_ms(20);

	dataAddress++;
	
	message[0] = (uint8_t)(dataAddress >> 8);
	message[1] = (uint8_t)(dataAddress);
	message[2] = (uint8_t)(data);
	TWI_MasterWrite(twi, eepromAddress, (uint8_t *) message, 3);
	_delay_ms(20);
}


ISR(TWIC_TWIM_vect)
{
	TWI_MasterInterruptHandler(&twiMaster);
}
ISR(TWIE_TWIM_vect)
{
	TWI_MasterInterruptHandler(&twiMasterForEEPROM);
}

ISR(PORTA_INT0_vect)//interrupts from an encoder turn or push
{
	if (!isLoading)
	{
		if(!(PORTA_IN & (1 << ENCDR_SW)))//if switch pin is low
		{
			isLoading = TRUE;
		}
	}
	
	PORTA_INTFLAGS = 0xFF; //clear port interrupt flags
}
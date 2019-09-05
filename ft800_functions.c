/*
* tft_display_functions.c
*
* Created: 10/15/2018 1:28:52 PM
*  Author: ENG_3
*/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void wr32(uint32_t addr, uint32_t data)
{
	PORTD_OUTCLR = (1 << SS_D); //set FT800 CS low

	SPID_DATA = ((addr >> 16) | 0x80);
	
	while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	
	for(int i = 8; i >= 0; i -= 8)
	{
		SPID_DATA = addr >> i;
		
		while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	}
	
	for(int i = 0; i <= 24; i += 8)
	{
		SPID_DATA = data >> i;
		
		while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	}
	
	PORTD_OUTSET = (1 << SS_D); //set FT800 CS high
}

void wr16(uint32_t addr, uint16_t data)
{
	PORTD_OUTCLR = (1 << SS_D); //set FT800 CS low

	SPID_DATA = ((addr >> 16) | 0x80);
	
	while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	
	for(int i = 8; i >= 0; i -= 8)
	{
		SPID_DATA = addr >> i;
		
		while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	}
	
	for(int i = 0; i <= 8; i += 8)
	{
		SPID_DATA = data >> i;
		
		while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	}
	
	PORTD_OUTSET = (1 << SS_D); //set FT800 CS high
}

void wr8(uint32_t addr, uint8_t data)
{
	PORTD_OUTCLR = (1 << SS_D); //set FT800 CS low

	SPID_DATA = ((addr >> 16) | 0x80);
	
	while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	
	for(int i = 8; i >= 0; i -= 8)
	{
		SPID_DATA = addr >> i;
		
		while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	}
	
	SPID_DATA = data;
	
	while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	
	PORTD_OUTSET = (1 << SS_D); //set FT800 CS high
}

void host_command(uint8_t* command){	PORTD_OUTCLR = (1 << SS_D); //set FT800 CS low
	int num_bytes = 3;
	
	for(int i = 0; i < num_bytes; ++i)
	{
		/* Start transmission */
		SPID_DATA = command[i];
		/* Wait for transmission complete */
		while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	}
	
	PORTD_OUTSET = (1 << SS_D); //set FT800 CS high}

uint8_t rd8(uint32_t addr)
{
	uint8_t result;
	PORTD_OUTCLR = (1 << SS_D); //set FT800 CS low
	
	SPID_DATA = ((addr >> 16));
	while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	SPID_DATA = addr >> 8;
	while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	SPID_DATA = addr;
	while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	
	SPID_DATA = 0xFF; /* Start transmission (Dummy Byte) */
	while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	SPID_DATA = 0xFF; /* Start transmission */
	while(!(SPID_STATUS & (1<<SPI_IF_bp)));
	result = SPID_DATA;
	PORTD_OUTSET = (1 << SS_D); //set FT800 CS high
	
	return result;
}

void FT813_init()
{
	static uint8_t ACTIVE[3] = {0x00, 0x00, 0x00};
	static uint8_t CLKEXT[3] = {0x44, 0x00, 0x00};
	
	PORTD_DIRSET = (1 << PD_N); //set PD_N as output
	PORTD_OUTCLR = (1 << PD_N); //drive PD_N low
	_delay_ms(20);
	PORTD_OUTSET = (1 << PD_N);; //drive PD_N high
	_delay_ms(20);
	
	host_command(CLKEXT);//send command to "CLKEXT" to FT800
	host_command(ACTIVE);//send host command "ACTIVE" to FT800
	while(rd8(REG_ID) != 0x7C);
	/* Configure display registers - demonstration for WQVGA resolution */
	wr16(REG_HCYCLE, 420);
	wr16(REG_HOFFSET, 69);
	wr16(REG_HSYNC0, 0);
	wr16(REG_HSYNC1, 41);
	wr16(REG_VCYCLE, 292);
	wr16(REG_VOFFSET, 13);
	wr16(REG_VSYNC0, 0);
	wr16(REG_VSYNC1, 10);
	wr8(REG_SWIZZLE, 0);
	wr8(REG_PCLK_POL, 1);
	wr8(REG_CSPREAD, 1);
	wr16(REG_HSIZE, 320);
	wr16(REG_VSIZE, 240);
	
	wr32(FT8_RAM_DL+0, CLEAR_COLOR_RGB(200,255,255));
	wr32(FT8_RAM_DL+4, CLEAR(1,1,1));
	wr32(FT8_RAM_DL+8, DISPLAY());
	
	wr8(REG_DLSWAP, DLSWAP_FRAME);
	
	wr8(REG_GPIO_DIR, 0x80); //display bit as output
	wr8(REG_GPIO, 0x80); //enables display bit
	
	wr8(REG_PCLK, 2);
}void cmd(uint32_t command)
{
	wr32(FT8_RAM_CMD + cmd_offset, command);
	cmd_offset = (cmd_offset + 4) % 4096;
	
	if(command == CMD_SWAP)
	{
		cmd_exec();
	}
}void cmd_2(uint16_t command)
{
	wr16(FT8_RAM_CMD + cmd_offset, command);
	cmd_offset=(cmd_offset+2)%4096;
}void cmd_1(uint8_t command){	wr8(FT8_RAM_CMD + cmd_offset, command);
	cmd_offset=(cmd_offset+1)%4096;}void cmd_text(uint16_t x, uint16_t y, uint16_t font, uint16_t options, const char* text){	cmd(CMD_TEXT);	cmd_2(x);	cmd_2(y);	cmd_2(font);	cmd_2(options);	int text_idx = 0;		while(text[text_idx] != '\0')	{		cmd_1((uint8_t) text[text_idx]);		++text_idx;	}		int padding = cmd_offset%4;	padding = 4-padding;		while(padding > 0)	{		cmd_1(0);		--padding;	}}uint32_t BEGIN(uint8_t primitive){	uint32_t command = ((uint32_t)0x1F << 24) + primitive;	return command;}uint32_t END(){	uint32_t command = ((uint32_t) 0x21 << 24);	return command;}uint32_t COLOR_RGB(uint8_t red, uint8_t green, uint8_t blue)
{
	uint32_t command = (((uint32_t)0x04 << 24) | ((uint32_t)blue << 16) | ((uint32_t)green << 8) | red);
	return command;
}uint32_t POINT_SIZE(uint16_t size){	uint32_t command = (((uint32_t) 0x0D << 24) | size);	return command;}uint32_t VERTEX2F(uint16_t x, uint16_t y){	x &= 0x7FFF;	y &= 0x7FFF;	uint32_t command = (((uint32_t) 0x01 << 30) | (uint32_t) x << 15 | (uint32_t) y);	return command;}uint32_t VERTEX2II(uint16_t x, uint16_t y, uint8_t handle, uint8_t cell){	x &= 0x01FF;	y &= 0x01FF;	uint32_t command = (((uint32_t) 0x02 << 30) | (uint32_t) x << 21 | (uint32_t) y << 12 | (uint32_t) handle << 7 | cell);	return command;}uint32_t LINE_WIDTH(uint16_t width){	width &= 0b0000111111111111;	uint32_t command = (((uint32_t) 0x0E << 24) | width);	return command;}
uint32_t CLEAR_COLOR_RGB(uint8_t red, uint8_t green, uint8_t blue)
{
	uint32_t command = (((uint32_t)0x02 << 24) | ((uint32_t)blue << 16) | ((uint32_t)green << 8) | red);
	return command;
}

uint32_t CLEAR(uint8_t C, uint8_t S, uint8_t T)
{
	uint32_t command = (((uint32_t)0x26 << 24) | (C << 2) | (S << 1) | T);
	return command;
}

uint32_t DISPLAY()
{
	uint32_t command = 0;
	return command;
}

uint32_t SAVE_CONTEXT(){	uint32_t command = (((uint32_t) 0x22 << 24));	return command;
}

uint32_t RESTORE_CONTEXT(){	uint32_t command = (((uint32_t) 0x23 << 24));	return command;
}

uint32_t SNAPSHOT()
{
	return (uint32_t) 0xFFFFFF1F;
}

uint32_t SNAPSHOT2()
{
	return (uint32_t) 0xFFFFFF37;
}

uint32_t SETBITMAP()
{
	return (uint32_t) 0xFFFFFF43;
}

uint32_t BITMAP_SOURCE(uint32_t addr)
{
	addr &= 0x00071111;
	uint32_t command = (((uint32_t) 0x01 << 24) | (addr));
	return command;
}

uint32_t BITMAP_LAYOUT(uint8_t f, uint16_t linestride, uint16_t height)
{
	uint32_t command = (((uint32_t) 0x07 << 24) | ((uint32_t) f << 19) | ((uint32_t) linestride << 9)| height);
	return command;
}

uint32_t BITMAP_SIZE(uint8_t filter, uint8_t wrapx, uint8_t wrapy, uint16_t width, uint16_t height)
{
	uint32_t command = (((uint32_t) 0x08 << 24) | ((uint32_t) wrapx << 19) | ((uint32_t) wrapy << 18) | ((uint32_t) width << 9) | height);
	return command;
}

void draw_rectangle(uint16_t width, int height, uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue)
{
	/*
	Coordinates x and y are the points at the bottom of the midcmde of the line if height  > 0.
	They are the top of the midcmde of the line if height < 0
	*/
	cmd( COLOR_RGB(red, green, blue) );
	cmd( BEGIN(RECTS) );
	if(height > 0)
	{
		cmd( VERTEX2F((x-(width/2))*8,(y-height) * 16) ); //top left
		cmd( VERTEX2F((x+(width/2))*8, y * 16) ); //bottom right
	}
	else
	{
		height = (uint16_t) (height*-1);
		cmd( VERTEX2F((x-(width/2))*8,y * 16) ); //top left
		cmd( VERTEX2F((x+(width/2))*8,(y+height) * 16) ); //bottom right
	}
	cmd(END());
}

void draw_text(char* text, uint8_t text_array_size, uint8_t font_size, uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue)
{
	cmd( COLOR_RGB(255, green, blue));
	cmd(BEGIN(BITMAPS)); // start drawing bitmaps
	for(int i = 0; i < text_array_size; ++i)
	{
		draw_character(text[i], font_size, x + (font_size*i*0.5), y, 0, 0, 0);
	}
	cmd(END());
}

void draw_character(char character, uint8_t font_size, uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue)
{
	cmd( COLOR_RGB(red, green, blue));
	cmd(BEGIN(BITMAPS)); // start drawing bitmaps
	cmd(VERTEX2II(x, y, font_size, character));
	cmd(END());
}

void draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t red, uint8_t green, uint8_t blue)
{
	cmd( COLOR_RGB(red, green, blue));
	cmd( BEGIN(LINE_STRIP));
	cmd( VERTEX2F(x1 * 16,y1 * 16) );
	cmd( VERTEX2F(x2 * 16,y2 * 16) );
	cmd(END());
}

void draw_line_with_width(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t width, uint8_t red, uint8_t green, uint8_t blue)
{
	cmd( COLOR_RGB(red, green, blue));
	cmd( BEGIN(LINES));
	cmd(LINE_WIDTH(width));
	cmd( VERTEX2F(x1 * 16,y1 * 16) );
	cmd( VERTEX2F(x2 * 16,y2 * 16) );
	cmd(END());
}


char * int_to_char_array(int val)
{
	int temp = val;
	int num_chars = 0;
	char char_arr[13];
	
	while(temp != 0)
	{
		char_arr[num_chars] = (temp % 10) + 48;
		++num_chars;
		temp /= 10;
	}
	
	if(val == 0)
	{
		char* final_arr = malloc(sizeof(char)*1);
		final_arr[0] = 48;
		return final_arr;
	}
	
	char* final_arr = malloc(sizeof(char)*(num_chars+1));
	int j = 0;
	
	for(int i = num_chars-1; i >=0 ; --i, ++j)
	{
		final_arr[j] = char_arr[i];
	}
	
	final_arr[j] = '\0';
	
	return final_arr;
}

int number_of_digits(int val)
{
	return log10(val) + 1;
}

void display_digital_reading(uint16_t value, int top_left_x, int top_left_y, int font_size, uint8_t is_voltage){
	value /= 10;
	char digits[5] = {'0', '0', '.', '0', '\0'};
	
	for(int i = 3; i >= 0 && value > 0; --i)
	{
		if(i == 2)
		{
			continue;
		}
		
		digits[i] = value%10 + '0';
		value /= 10;
	}
	
	cmd_text(top_left_x, top_left_y, font_size, 0, digits);
	
	char c[2];
	if(is_voltage)
	{
		c[0] = 'V';
	}
	else
	{
		c[0] = 'A';
	}
	
	c[1] = '\0';
	
	cmd_text(top_left_x+38, top_left_y, font_size, 0, c);

}

void draw_one_pixel_line(uint16_t x, uint16_t y, uint8_t font_size, uint8_t r, uint8_t g, uint8_t b)
{
	char text[1] = "|";
	draw_text(text, 1, font_size, x, y, r, g, b);
}

void draw_simple_rectangle(uint16_t top_left_x, uint16_t top_left_y, uint16_t bottom_right_x, uint16_t bottom_right_y, uint8_t r, uint8_t g, uint8_t b)
{
	cmd( COLOR_RGB(r, g, b) );
	cmd( BEGIN(RECTS) );
	cmd( VERTEX2F(top_left_x * 16,top_left_y * 16) );
	cmd( VERTEX2F(bottom_right_x * 16,bottom_right_y * 16) );
}


/*
Draws the part of the gauge with all the repetitive graduation lines
*/

void draw_gauge(int start_x, int y, int width) 
{
	int start = 35;
	int cnt = 0;
	for(int i = start; i <= 325-start; i += 5)
	{
		if((i-start) % 25 == 0)
		{
			draw_one_pixel_line(i+cnt-1, y-1, 23, 0, 0, 0); //draws larger graduation line
			++cnt;
			if((i-start)%50 == 0)
			{
				char* text = int_to_char_array((i-start)/5);
				int numDigits = number_of_digits((i-start)/5);
				
				if(numDigits < 2)//for single digits
				{ 
					cmd_text(i-3, y+18, 21, 0, text);
				}
				else if(i-start < 300)//for double digits
				{ 
					cmd_text(i-9+cnt, y+18, 21, 0, text);
					
				}
				free(text);
			}
			continue;
		}
		draw_one_pixel_line(i+cnt-1, y, 20, 0, 0, 0); //draws small graduation line
	}
	
	start = 35;
	cnt = 0;
	y+= 15;
	
	for(int i = start; i <= 325-start; i += 5)
	{
		if((i-start) % 25 == 0)
		{
			draw_one_pixel_line(i+cnt-1, y+16, 23, 0, 0, 0); //draws larger graduation line
			++cnt;
			continue;
		}
		draw_one_pixel_line(i+cnt-1, y+25, 20, 0, 0, 0); //draws small graduation line
	}
}

/*
Draws the part of the gauge with all the repetitive graduation lines, then takes a snapshot of that gauge and stores in RAM_G. This can then be called as a bitmap.
This way, we don't have to keep re-writing the whole gauge every single time
*/
void draw_gauge_and_partial_snapshot(int start_x, int y, int width)
{
	for(int i = 0; i < 5; ++i)
	{
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		_delay_ms(40);
		cmd(CMD_DLSTART);
		cmd(CLEAR_COLOR_RGB(220, 230, 230));
		cmd(CLEAR(1, 1, 1)); // clear screen
		
		
		draw_gauge(start_x, y, width);
		
		cmd(DISPLAY()); // display the image		cmd(CMD_SWAP);				_delay_ms(50);				cmd(SNAPSHOT2());
		cmd(6); //format
		cmd(0); //RAM_G ptr
		cmd_2(30); //top left x
		cmd_2(5); //top left y
		cmd_2(280); //width
		cmd_2(80); //height
		
	}
}



void draw_settings_page(ProgramState *program_state, OutputState *output_one) 
{
	if (program_state->testing_mode)
	{
		cmd( BEGIN(RECTS) );
		cmd(COLOR_RGB(0, 0, 255)); //draw outer boundary
		cmd( LINE_WIDTH(200) );
		cmd( VERTEX2F(16 * 15, 16 * (15)) );
		cmd( VERTEX2F(16 * 305, 16 * (27)) );

		if(program_state->settings_row_num == 0)
		{
			cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
			cmd( VERTEX2F(16 * 17, 16 * (17)) );
			cmd( VERTEX2F(16 * 303, 16 * (25)) );
			
			cmd(COLOR_RGB(0, 0, 255));
		}
		else
		{
			cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
			cmd( VERTEX2F(16 * 15, 16 * (15)) );
			cmd( VERTEX2F(16 * 305, 16 * (27)) );
			
			cmd(COLOR_RGB(0, 0, 0));
		}
		cmd_text(80, 10, 26, 0, "TEMPERATURE VALUE:");
		cmd_text(35, 20, 22, 0, "lower value - higher temperature cap"); 
		cmd_text(235, 10, 26, 0, int_to_char_array(OVER_TEMP_VALUE)); 
		
		cmd( BEGIN(RECTS) );
		cmd(COLOR_RGB(0, 0, 255)); //draw outer boundary
		cmd( LINE_WIDTH(200) );
		cmd( VERTEX2F(16 * 15, 16 * (55)) );
		cmd( VERTEX2F(16 * 305, 16 * (67)) );

		if(program_state->settings_row_num == 1)
		{
			cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
			cmd( VERTEX2F(16 * 17, 16 * (57)) );
			cmd( VERTEX2F(16 * 303, 16 * (65)) );
			
			cmd(COLOR_RGB(0, 0, 255));
		}
		else
		{
			cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
			cmd( VERTEX2F(16 * 15, 16 * (55)) );
			cmd( VERTEX2F(16 * 305, 16 * (67)) );
			
			cmd(COLOR_RGB(0, 0, 0));
		}
		cmd_text(75, 55, 26, 0, "TIME TO CHECK TEMP:");
		cmd_text(235, 55, 26, 0, int_to_char_array(TIME_TO_CHECK_TEMP / 1000));
		cmd_text(270, 55, 26, 0, "sec");
		
		cmd( BEGIN(RECTS) );
		cmd(COLOR_RGB(0, 0, 255)); //draw outer boundary
		cmd( LINE_WIDTH(200) );
		cmd( VERTEX2F(16 * 15, 16 * (95)) );
		cmd( VERTEX2F(16 * 305, 16 * (107)) );

		if(program_state->settings_row_num == 2)
		{
			cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
			cmd( VERTEX2F(16 * 17, 16 * (97)) );
			cmd( VERTEX2F(16 * 303, 16 * (105)) );
			
			cmd(COLOR_RGB(0, 0, 255));
		}
		else
		{
			cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
			cmd( VERTEX2F(16 * 15, 16 * (95)) );
			cmd( VERTEX2F(16 * 305, 16 * (107)) );
			
			cmd(COLOR_RGB(0, 0, 0));
		}
		cmd_text(130, 95, 26, 0, "APPLY");
	}
	else
	{
		if (program_state->program == FOURTY_ONE || program_state->program == FOURTY_ONE_DUAL)
		{
			cmd( BEGIN(RECTS) );
			cmd(COLOR_RGB(0, 0, 255)); //draw outer boundary
			cmd( LINE_WIDTH(200) );
			cmd( VERTEX2F(16 * 15, 16 * (15)) );
			cmd( VERTEX2F(16 * 305, 16 * (27)) );
	
			if(program_state->settings_row_num == 0) 
			{
				cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
				cmd( VERTEX2F(16 * 17, 16 * (17)) );
				cmd( VERTEX2F(16 * 303, 16 * (25)) );
		
				cmd(COLOR_RGB(0, 0, 255));
			}
			else 
			{
				cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
				cmd( VERTEX2F(16 * 15, 16 * (15)) );
				cmd( VERTEX2F(16 * 305, 16 * (27)) );
		
				cmd(COLOR_RGB(0, 0, 0));
			}
	
			cmd_text(120, 15, 26, 0, "MODE : ");
			if (program_state->num_outputs == SINGLE) 
			{
				cmd_text(170, 15, 26, 0, "SINGLE");
			}
			else 
			{
				cmd_text(170, 15, 26, 0, "DUAL");
			}
		}
		else
		{
			cmd( BEGIN(RECTS) );
			cmd(COLOR_RGB(100, 100, 255)); //draw outer boundary
			cmd( LINE_WIDTH(200) );
			cmd( VERTEX2F(16 * 15, 16 * (15)) );
			cmd( VERTEX2F(16 * 305, 16 * (27)) );
		
			if(program_state->settings_row_num == 0)
			{
				cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
				cmd( VERTEX2F(16 * 17, 16 * (17)) );
				cmd( VERTEX2F(16 * 303, 16 * (25)) );
			
				cmd(COLOR_RGB(80, 80, 255));
			}
			else
			{
				cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
				cmd( VERTEX2F(16 * 15, 16 * (15)) );
				cmd( VERTEX2F(16 * 305, 16 * (27)) );
			
				cmd(COLOR_RGB(80, 80, 80));
			}
		
			cmd_text(120, 15, 26, 0, "MODE : ");
			cmd_text(170, 15, 26, 0, "SINGLE");
		}
		
		if (program_state->debug_mode)
		{
			cmd( BEGIN(RECTS) );
			cmd(COLOR_RGB(0, 0, 255)); //draw outer boundary
			cmd( LINE_WIDTH(200) );
			cmd( VERTEX2F(16 * 15, 16 * (55)) );
			cmd( VERTEX2F(16 * 305, 16 * (67)) );

			if(program_state->settings_row_num == 1)
			{
				cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
				cmd( VERTEX2F(16 * 17, 16 * (57)) );
				cmd( VERTEX2F(16 * 303, 16 * (65)) );
			
				cmd(COLOR_RGB(0, 0, 255));
			}
			else
			{
				cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
				cmd( VERTEX2F(16 * 15, 16 * (55)) );
				cmd( VERTEX2F(16 * 305, 16 * (67)) );
			
				cmd(COLOR_RGB(0, 0, 0));
			}
			cmd_text(100, 55, 26, 0, "CLEAR ERROR LOGS");
		
			cmd( BEGIN(RECTS) );
			cmd(COLOR_RGB(0, 0, 255)); //draw outer boundary
			cmd( LINE_WIDTH(200) );
			cmd( VERTEX2F(16 * 15, 16 * (95)) );
			cmd( VERTEX2F(16 * 305, 16 * (107)) );

			if(program_state->settings_row_num == 2)
			{
				cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
				cmd( VERTEX2F(16 * 17, 16 * (97)) );
				cmd( VERTEX2F(16 * 303, 16 * (105)) );
			
				cmd(COLOR_RGB(0, 0, 255));
			}
			else
			{
				cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
				cmd( VERTEX2F(16 * 15, 16 * (95)) );
				cmd( VERTEX2F(16 * 305, 16 * (107)) );
			
				cmd(COLOR_RGB(0, 0, 0));
			}
			cmd_text(130, 95, 26, 0, "TEST MODE");
		
			char com_err1_amt[10] = "\0";
			char com_err2_amt[10] = "\0";
			char com_err3_amt[10] = "\0";
			char com_err4_amt[10] = "\0";
			char com_err5_amt[10] = "\0";
			char com_err6_amt[10] = "\0";
		
			sprintf(com_err1_amt, "%u", program_state->comm_error1);
			sprintf(com_err2_amt, "%u", program_state->comm_error2);
			sprintf(com_err3_amt, "%u", program_state->comm_error3);
			sprintf(com_err4_amt, "%u", program_state->comm_error4);
			sprintf(com_err5_amt, "%u", program_state->comm_error5);
			sprintf(com_err6_amt, "%u", program_state->comm_error6);
		
			// Error logs
			cmd(COLOR_RGB(51, 255, 51));
			cmd_text(10, 130, 16, 0, "0X41 :"); cmd_text(60, 130, 16, 0, com_err1_amt);
			cmd_text(10, 150, 16, 0, "0X40 :"); cmd_text(60, 150, 16, 0, com_err2_amt);
			cmd_text(10, 170, 16, 0, "0X4D :"); cmd_text(60, 170, 16, 0, com_err3_amt);
			cmd_text(10, 190, 16, 0, "0X4E :"); cmd_text(60, 190, 16, 0, com_err4_amt);
			cmd_text(10, 210, 16, 0, "0X4C :"); cmd_text(60, 210, 16, 0, com_err5_amt);
			cmd_text(10, 230, 16, 0, "EEP  :"); cmd_text(60, 230, 16, 0, com_err6_amt);
		}
		else if (program_state->calibrating_mode)
		{
			cmd( BEGIN(RECTS) );
			cmd(COLOR_RGB(0, 0, 255)); //draw outer boundary
			cmd( LINE_WIDTH(200) );
			cmd( VERTEX2F(16 * 15, 16 * (55)) );
			cmd( VERTEX2F(16 * 305, 16 * (67)) );

			if(program_state->settings_row_num == 1)
			{
				cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
				cmd( VERTEX2F(16 * 17, 16 * (57)) );
				cmd( VERTEX2F(16 * 303, 16 * (65)) );
			
				cmd(COLOR_RGB(0, 0, 255));
			}
			else
			{
				cmd(COLOR_RGB(255, 255, 255)); //draw inner boundary
				cmd( VERTEX2F(16 * 15, 16 * (55)) );
				cmd( VERTEX2F(16 * 305, 16 * (67)) );
			
				cmd(COLOR_RGB(0, 0, 0));
			}
			cmd_text(100, 55, 26, 0, "CALIBRATE UNIT");
		}
	}
}

void draw_current_and_voltage(ProgramState *program_state, OutputState *output, int gauge_x, int gauge_y, int width, uint16_t max_voltage, uint16_t max_current)
{
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	cmd( BEGIN(RECTS) );
	
	/* draws outer rectangle (black) */
	cmd(COLOR_RGB(0, 0, 0));
	cmd( LINE_WIDTH(200) );
	cmd( VERTEX2F(16 * 15, 16 * (gauge_y+10)) );
	cmd( VERTEX2F(16 * 305, 16 * (gauge_y+82)) );

	/*draws inner rectangle (white) */
	cmd(COLOR_RGB(255, 255, 255));
	cmd( VERTEX2F(16 * 17, 16 * (gauge_y+12)) );
	cmd( VERTEX2F(16 * 303, 16 * (gauge_y+80)) );
	

	/* draws red bar for voltage */
	cmd( LINE_WIDTH(16) );
	cmd(COLOR_RGB(255, 0, 0));
	if (program_state->num_outputs == 0)
	{
		double startMaxVoltage = (((float) ((float)output->max_voltage/100)) + 3.677326)/0.0119958;
		cmd( VERTEX2F(startMaxVoltage + (16*16), 16 * (gauge_y+3)) );
		double endMaxVoltage = (((float) ((float)5100/100)) + 3.677326)/0.0119958;
		cmd( VERTEX2F(endMaxVoltage + (16*16), 16 * (gauge_y+8)) );
	}
	else
	{
		double startMaxVoltage = (((float) ((float)output->max_voltage/100)) + 3.677326)/0.0119958;
		cmd( VERTEX2F(startMaxVoltage + (16*16), 16 * (gauge_y+3)) );
		double endMaxVoltage = (((float) ((float)5100/100)) + 3.677326)/0.0119958;
		cmd( VERTEX2F(endMaxVoltage + (16*16), 16 * (gauge_y+8)) );
	}
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	/* draws red bar for current */
	cmd( LINE_WIDTH(16) );
	cmd(COLOR_RGB(255, 0, 0));

	if (program_state->num_outputs == 0)
	{
		double startMaxCurrent = (((float) ((float)output->max_current/100)) + 3.677326)/0.0119958;
		cmd( VERTEX2F(startMaxCurrent + (16*16), 16 * (gauge_y+45)) );
		double endMaxCurrent = (((float) ((float)5100/100)) + 3.677326)/0.0119958;
		cmd( VERTEX2F(endMaxCurrent + (16*16), 16 * (gauge_y+50)) );
	}
	else
	{
		double startMaxCurrent = (((float) ((float)output->max_current/100)) + 3.677326)/0.0119958;
		cmd( VERTEX2F(startMaxCurrent + (16*16), 16 * (gauge_y+45)) );
		double endMaxCurrent = (((float) ((float)5100/100)) + 3.677326)/0.0119958;
		cmd( VERTEX2F(endMaxCurrent + (16*16), 16 * (gauge_y+50)) );
	}
	
	/* selects color of voltage bar */
	if((uint16_t)(round(output->voltage * VOLTAGE_DROP_COEFICIENT)) >= 5000)
	{
		cmd(COLOR_RGB(255, 10, 15)); //choose reddish color
	}
	else
	{
		cmd(COLOR_RGB(0, 100, 200)); //choose blueish color
	}
	
	/* draws voltage bar */
	cmd( LINE_WIDTH(16) );
	if((uint16_t)(round(output->voltage * VOLTAGE_DROP_COEFICIENT)) > 5)
	{
		cmd( VERTEX2F(16 * (gauge_x+22), 16 * (gauge_y+3)) );
		double shouldBeValVoltage = (((float) ((float) MAX(round_to_tens((uint16_t)(round(output->voltage * VOLTAGE_DROP_COEFICIENT))), 15)/100)) + 3.677326)/0.0119958;
		cmd( VERTEX2F(shouldBeValVoltage + (16*16), 16 * (gauge_y+10)) );
	}
	
	/* selects color of current bar */
	if(output->current > 5050)
	{
		cmd(COLOR_RGB(255, 10, 15));
	}
	else
	{
		cmd(COLOR_RGB(40, 190, 40));
	}
	
	/* draws current bar */
	if(output->current > 5)
	{
		cmd( LINE_WIDTH(16) );
		cmd( VERTEX2F(16 * (gauge_x+22), 16 * (gauge_y+43)) );
		double shouldBeValCurrent = (((float) ((float) MAX(round_to_tens(output->current), 15)/100)) + 3.677326)/0.0119958;
		cmd( VERTEX2F(shouldBeValCurrent + (16*16), 16 * (gauge_y+50)) );
	}

	cmd(END());
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	/* gets gauge screenshot from memory and pastes it on screen at desired location */
	cmd(BITMAP_SOURCE(0));
	cmd(BITMAP_LAYOUT(6, 2*280, 80));
	cmd(BITMAP_SIZE(0, 0, 0, 280, 80));
	cmd(BEGIN(BITMAPS));
	cmd(VERTEX2II(gauge_x+15, gauge_y, 0, 0));
			cmd( LINE_WIDTH(16) );	cmd(COLOR_RGB(0, 0, 0)); // chooses black color		if(program_state->program == FOURTY_ONE_DUAL)	{		if(output->id == output_one.id)		{			cmd_text(gauge_x+15, gauge_y+73, 27, 0, "STR. #1");		}		else if(output->id == output_two.id)		{			cmd_text(gauge_x+15, gauge_y+73, 27, 0, "STR. #2");		}	}	cmd_text(gauge_x+40, gauge_y+55, 27, 0, "OUTPUT: "); // writes "OUTPUT: "	display_digital_reading((uint16_t)(round(output->voltage * VOLTAGE_DROP_COEFICIENT)), gauge_x+140, gauge_y+55, 27, TRUE); //writes voltage reading
	display_digital_reading(output->current, gauge_x+225, gauge_y+55, 27, FALSE); //writes current reading		if(output->set_current_state >= 1)	{		cmd_text(gauge_x+98, gauge_y+74, 27, 0, "SET CURRENT:");	}		display_digital_reading(output->target_current, gauge_x+225, gauge_y+74, 27, FALSE); // writes target current			draw_character('V', 27, gauge_x+5, gauge_y, 0, 0, 0); // draws 'V' next to voltage gauge	draw_character('A', 27, gauge_x+5, gauge_y+36, 0, 0, 0); //draws 'A' next to current gauge
}

void draw_message_box(ProgramState *program_state, OutputState *output_one, OutputState *output_two, TimerCount *counters)
{
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	static int message_idx = -1;
	
	cmd( BEGIN(RECTS) ); //draws black outer circle for bottom rectangle
	cmd(COLOR_RGB(0, 0, 0));
	cmd( LINE_WIDTH(200) );
	cmd( VERTEX2F(16 * 15, 16 * 114) );
	cmd( VERTEX2F(16 * 305, 16 * 125) );		cmd( BEGIN(RECTS) ); //draws white inner rectangle for bottom rectangle
	cmd(COLOR_RGB(255, 255, 255));
	cmd( LINE_WIDTH(200) );
	cmd( VERTEX2F(16 * 17, 16 * 116) );
	cmd( VERTEX2F(16 * 303, 16 * 123) );
	
	cmd(COLOR_RGB(0,0,0));
	
	volatile bool found = TRUE;
	bool output_one_zero_current = FALSE;
	bool output_two_zero_current = FALSE;
	
	if(output_one->current < 5)
	{
		output_one_zero_current = TRUE;
	}
	if(output_two->current < 5 && program_state->program == FOURTY_ONE_DUAL)
	{
		output_two_zero_current = TRUE;
	}
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	if(counters->update_message_box_counter >= 2000)
	{
		bool message_prompters[16] = {
			program_state->pson_low, output_one->over_temp_error_uncleared1, output_one->over_temp_error_uncleared2, 
			output_two->over_temp_error_uncleared1, output_two->over_temp_error_uncleared2, output_one->voltage_drift_error, 
			output_two->voltage_drift_error, output_one_zero_current, output_two_zero_current, program_state->calibrating_mode_clicked,
			output_one->hit_max_current && !program_state->pson_low, output_two->hit_max_current && !program_state->pson_low, 
			output_one->hit_max_voltage && !program_state->pson_low, output_two->hit_max_voltage && !program_state->pson_low,
			output_one->hit_min_current && !program_state->pson_low && !(output_one_zero_current), 
			output_two->hit_min_current && !program_state->pson_low && !(output_two_zero_current),
			};
		found = FALSE;
		for(int i = message_idx + 1; i < 16; ++i) //looks for next active message from the idx towards the last idx
		{ 
			if(message_prompters[i] > 0)
			{
				message_idx = i;
				found = TRUE;
				break;
			}
		}
		if(found == FALSE) //looks for next active message from the first idx towards the current idx
		{ 
			for(int i = 0; i <= message_idx; ++i)
			{
				if(message_prompters[i] > 0) 
				{
					message_idx = i;
					found = TRUE;
					break;
				}
			}
		}
		
		counters->update_message_box_counter = 0;
	}	if (!found)
	{
		message_idx = -1;
	}	char str_com_addres_failed1[3] = "41\0";	char str_com_addres_failed2[3] = "40\0";	char str_com_addres_failed3[3] = "4D\0";	char str_com_addres_failed4[3] = "4E\0";	char str_com_addres_failed5[3] = "4C\0";	char str_com_addres_failed6[4] = "EEP\0";
		
	if (counters->real_time_counter % 1000 < 500)
	{
		if (program_state->comm_error1_to_display || program_state->comm_error2_to_display || program_state->comm_error3_to_display || 
		program_state->comm_error4_to_display || program_state->comm_error5_to_display || program_state->comm_error6_to_display)
		{
			//**************************************************
			wdt_reset(); // WATCH DOG TIMER RESET
			//**************************************************						char addresses_to_display[19] = "\0";
			if (program_state->comm_error1_to_display)
			{
				strcat(addresses_to_display, " ");
				strcat(addresses_to_display, str_com_addres_failed1);
			}
			if (program_state->comm_error2_to_display)
			{
				strcat(addresses_to_display, " ");
				strcat(addresses_to_display, str_com_addres_failed2);
			}
			if (program_state->comm_error3_to_display)
			{
				strcat(addresses_to_display, " ");
				strcat(addresses_to_display, str_com_addres_failed3);
			}
			if (program_state->comm_error4_to_display)
			{
				strcat(addresses_to_display, " ");
				strcat(addresses_to_display, str_com_addres_failed4);
			}
			if (program_state->comm_error5_to_display)
			{
				strcat(addresses_to_display, " ");
				strcat(addresses_to_display, str_com_addres_failed5);
			}
			if (program_state->comm_error6_to_display)
			{
				strcat(addresses_to_display, " ");
				strcat(addresses_to_display, str_com_addres_failed6);
			}
			
			
			cmd(COLOR_RGB(255, 0, 0));
			cmd_text(90, 112, 26, 0, messages.communication_error);
			cmd_text(190, 112, 26, 0, addresses_to_display);
			
		}
		else
		{
			cmd(COLOR_RGB(255,0,0));
			switch(message_idx)
			{
				case -1:
				{
					cmd(COLOR_RGB(0,0,0));
					cmd_text(107, 112, 26, 0, messages.system_normal);
					break;
				}
				
				case 0:
				{
					cmd_text(105, 112, 26, 0, messages.dc_interrupted);
					break;
				}
				
				case 1:
				{
					if(output_one->over_temp_error1 || output_one->over_temp_half_second_count)
					{
						cmd_text(50, 112, 26, 0, messages.over_temperature_output_one1);
					}
					else
					{
						cmd_text(5, 112, 26, 0, messages.over_temperature_normal_now_output_one1);
					}
					break;
				}
				
				case 2:
				{
					if(output_one->over_temp_error2 || output_one->over_temp_half_second_count)
					{
						cmd_text(50, 112, 26, 0, messages.over_temperature_output_one2);
					}
					else
					{
						cmd_text(5, 112, 26, 0, messages.over_temperature_normal_now_output_one2);
					}
					break;
				}
				
				case 3:
				{
					if(output_two->over_temp_error1 || output_two->over_temp_half_second_count)
					{
						cmd_text(20, 112, 26, 0, messages.over_temperature_output_two1);
					}
					else
					{
						cmd_text(6, 112, 26, 0, messages.over_temperature_normal_now_output_two1);
					}
					break;
				}
				
				case 4:
				{
					if(output_two->over_temp_error2 || output_two->over_temp_half_second_count)
					{
						cmd_text(20, 112, 26, 0, messages.over_temperature_output_two2);
					}
					else
					{
						cmd_text(6, 112, 26, 0, messages.over_temperature_normal_now_output_two2);
					}
					break;
				}
				
				case 5:
				{
					if(program_state->num_outputs == SINGLE)
					{
						cmd_text(85, 112, 26, 0, messages.voltage_drift);
					}
					else
					{
						cmd_text(68, 112, 26, 0, messages.voltage_drift_output_one);
					}
					break;
				}
				
				case 6:
				{
					cmd_text(69, 112, 26, 0, messages.voltage_drift_output_two);
					break;
				}
				
				case 7:
				{
					if (!program_state->pson_low)
					{
						if(program_state->num_outputs == SINGLE)
						{
							cmd_text(90, 112, 26, 0, messages.zero_current);
						}
						else
						{
							cmd_text(61, 112, 26, 0, messages.zero_current_output_one);
						}
					}
					else
					{
						cmd_text(105, 112, 26, 0, messages.dc_interrupted);
					}
					
					break;
				}
				
				case 8:
				{
					if (!program_state->pson_low)
					{
						cmd_text(62, 112, 26, 0, messages.zero_current_output_two);
					}
					else
					{
						cmd_text(105, 112, 26, 0, messages.dc_interrupted);
					}
					break;
				}
				
				case 9:
				{
					cmd(COLOR_RGB(0, 155, 0));
					cmd_text(120, 112, 26, 0, messages.calibrating_notification);
					break;
				}
				
				case 10:
				{
					cmd(COLOR_RGB(255,0,0));
					if(program_state->num_outputs == SINGLE)
					{
						cmd_text(115, 112, 26, 0, messages.max_current);
					}
					else
					{
						cmd_text(85, 112, 26, 0, messages.max_current_output_one);
					}
					break;
				}
				
				case 11:
				{
					cmd(COLOR_RGB(255,0,0));
					if(program_state->num_outputs == SINGLE)
					{
						cmd_text(115, 112, 26, 0, messages.max_current);
					}
					else
					{
						cmd_text(85, 112, 26, 0, messages.max_current_output_two);
					}
					break;
				}
				
				case 12:
				{
					cmd(COLOR_RGB(255,0,0));
					if(program_state->num_outputs == SINGLE)
					{
						cmd_text(115, 112, 26, 0, messages.max_voltage);
					}
					else
					{
						cmd_text(85, 112, 26, 0, messages.max_voltage_output_one);
					}
					break;
				}
				
				case 13:
				{
					cmd(COLOR_RGB(255,0,0));
					if(program_state->num_outputs == SINGLE)
					{
						cmd_text(115, 112, 26, 0, messages.max_voltage);
					}
					else
					{
						cmd_text(85, 112, 26, 0, messages.max_voltage_output_two);
					}
					break;
				}
				
				case 14:
				{
					cmd(COLOR_RGB(255,0,0));
					if(program_state->num_outputs == SINGLE)
					{
						cmd_text(115, 112, 26, 0, messages.min_current);
					}
					else
					{
						cmd_text(85, 112, 26, 0, messages.min_current_output_one);
					}
					break;
				}
				
				case 15:
				{
					cmd(COLOR_RGB(255,0,0));
					if(program_state->num_outputs == SINGLE)
					{
						cmd_text(85, 112, 26, 0, messages.min_current);
					}
					else
					{
						cmd_text(85, 112, 26, 0, messages.min_current_output_two);
					}
					break;
				}
			}
		}
	}
	else if (message_idx == -1)
	{
		cmd(COLOR_RGB(0,0,0));
		cmd_text(107, 112, 26, 0, messages.system_normal);
	}
}

void draw_startup_screen(){
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	cmd( BEGIN(RECTS) );
	cmd( LINE_WIDTH(200) );
	
	/* draws outer rectangle (black) */
	cmd(COLOR_RGB(0, 0, 0));
	cmd( LINE_WIDTH(200) );
	cmd( VERTEX2F(16 * 15, 16 * (gauge_y+10)) );
	cmd( VERTEX2F(16 * 305, 16 * (gauge_y+82)) );

	/*draws inner rectangle (white) */
	cmd(COLOR_RGB(255, 255, 255));
	cmd( VERTEX2F(16 * 17, 16 * (gauge_y+12)) );
	cmd( VERTEX2F(16 * 303, 16 * (gauge_y+80)) );
	
	//---------------------------------------------------------------------------
	
	/* draws outer rectangle (black) */
	cmd(COLOR_RGB(0, 0, 0));
	cmd( LINE_WIDTH(200) );
	cmd( VERTEX2F(16 * 15, 16 * (gauge_y+149)) );
	cmd( VERTEX2F(16 * 305, 16 * (gauge_y+222)) );

	/*draws inner rectangle (white) */
	cmd(COLOR_RGB(255, 255, 255));
	cmd( VERTEX2F(16 * 17, 16 * (gauge_y+151)) );
	cmd( VERTEX2F(16 * 303, 16 * (gauge_y+219)) );
	
	//---------------------------------------------------------------------------
	
	cmd( BEGIN(RECTS) ); //draws black outer circle for bottom rectangle
	cmd(COLOR_RGB(0, 0, 0));
	cmd( LINE_WIDTH(200) );
	cmd( VERTEX2F(16 * 15, 16 * 114) );
	cmd( VERTEX2F(16 * 305, 16 * 125) );		cmd( BEGIN(RECTS) ); //draws white inner rectangle for bottom rectangle
	cmd(COLOR_RGB(255, 255, 255));
	cmd( LINE_WIDTH(200) );
	cmd( VERTEX2F(16 * 17, 16 * 116) );
	cmd( VERTEX2F(16 * 303, 16 * 123) );
	
	cmd(COLOR_RGB(49,74,137));
	
	cmd_text(40, 25, 29, 0, "FARWEST");
	cmd_text(157, 25, 29, 0, "CORROSION");
	cmd_text(50, 50, 29, 0, "CONTROL");
	cmd_text(167, 50, 29, 0, "COMPANY");
	
	// draw same text shifted one pixel to the left and down to make text bolder
	cmd_text(41, 25, 29, 0, "FARWEST");
	cmd_text(158, 25, 29, 0, "CORROSION");
	cmd_text(51, 50, 29, 0, "CONTROL");
	cmd_text(168, 50, 29, 0, "COMPANY");
	
	cmd_text(40, 26, 29, 0, "FARWEST");
	cmd_text(157, 26, 29, 0, "CORROSION");
	cmd_text(50, 51, 29, 0, "CONTROL");
	cmd_text(167, 51, 29, 0, "COMPANY");
	
	cmd_text(15, 110, 27, 0, "HW Rev A");
	cmd_text(220, 110, 27, 0, "SW Rev 1.0");
	
	cmd(COLOR_RGB(0,0,0));
	if (program_state.program == THIRTY_EIGHT)
	{
		cmd_text(50, 170, 29, 0, "D     ro   FSMA 30-20");
	}
	else
	{
		cmd_text(50, 170, 29, 0, "D     ro   FSMA 50-50");
	}
	cmd(COLOR_RGB(49,74,137));
	cmd_text(49, 170, 29, 0, "   CP");
}

void write_screen(){
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	cmd(CMD_DLSTART);
	
	if (program_state.mode == NORMAL_MODE) 
	{
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		program_state.debug_mode = FALSE;
		counters.debug_clicks_counter = 0;
		program_state.calibrating_mode = FALSE;
		counters.calibrate_clicks_counter = 0;
		cmd(CLEAR_COLOR_RGB(0, 0, 0));
		cmd(CLEAR(1, 1, 1)); // clear screen
		draw_current_and_voltage(&program_state, &output_one, gauge_x, gauge_y, gauge_width, 5000, program_state.output->max_current);
		draw_message_box(&program_state, &output_one, &output_two, &counters);
		if(program_state.num_outputs == DOUBLE)
		{
			draw_current_and_voltage(&program_state, &output_two, gauge_x, gauge_y+139, gauge_width, 5000,  program_state.output->max_current); //draws second gauge
		}
	}
	else if (program_state.mode == SETTINGS_MODE) 
	{
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		program_state.output = &output_two;
		cmd(CLEAR_COLOR_RGB(0, 0, 0));
		cmd(CLEAR(1, 1, 1)); // clear screen
		draw_settings_page(&program_state, &output_one);
	}
	else if (program_state.mode == STARTUP_MODE) 
	{
		//**************************************************
		wdt_reset(); // WATCH DOG TIMER RESET
		//**************************************************
		program_state.output = &output_two;
		cmd(CLEAR_COLOR_RGB(0, 0, 0));
		cmd(CLEAR(1, 1, 1)); // clear screen
		draw_startup_screen();
	}
	
	//**************************************************
	wdt_reset(); // WATCH DOG TIMER RESET
	//**************************************************
	
	_delay_ms(20); //this delay is necessary to maintain a maximum refresh rate, otherwise the screen may tear and glitch out if writing to screen too often
	cmd(DISPLAY()); // display the image	cmd(CMD_SWAP);
	
}

/*************************************************
Rounds any 16-bit number to the closest tens place.
So 1564 -> 1560, 1785 -> 1790, etc.
**************************************************/
uint16_t round_to_tens(uint16_t number)
{
	return (uint16_t)((number / 10) + 0.5) * 10;
}
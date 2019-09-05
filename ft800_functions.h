/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file 

    \brief This header file defines all functions for FT800 chip that controls 
           display.

    \author
           Vladyslav Shaternik\n
           Email: vladik.shaternik32@gmail.com

    $Date: 2019-07-15 11:05:02 -0700 (mo, 15 jul 2019) $  \n

    \note See documentation for extra description of functions described here
          https://brtchip.com/wp-content/uploads/Support/Documentation/Programming_Guides/ICs/EVE/FT800_Series_Programmer_Guide.pdf
*/
#include <stdint.h>
#include <avr/io.h>

#define LOW_FREQ_BOUND      58800000L /*!< 98% of 60Mhz */

#define DLSWAP_FRAME        2

/*! \addtogroup mem_defs FT800 Memory definitions
	@{
*/
#define FT8_RAM_G			0x000000UL
#define FT8_ROM_CHIPID		0x0C0000UL
#define FT8_ROM_FONT		0x1E0000UL
#define FT8_ROM_FONT_ADDR	0x2FFFFCUL
#define FT8_RAM_DL			0x300000UL
#define FT8_RAM_REG			0x302000UL
#define FT8_RAM_CMD			0x308000UL
#define FT8_RAM_IMG         0x00000000 /*!< start-address of logo-img */
/*! @} */

/*! \addtogroup mem_size_defs FT800 Memory sizes
	@{
*/
#define FT8_RAM_G_SIZE		1024*1024L
#define FT8_CMDFIFO_SIZE	4*1024L
#define FT8_RAM_DL_SIZE		8*1024L
/*! @} */

/*! \addtogroup mem_additional_defs FT800 Additional defines
	@{
*/
#define FT8_ADC_DIFFERENTIAL     1UL
#define FT8_ADC_SINGLE_ENDED     0UL

#define FT8_INT_G8               18UL
#define FT8_INT_L8C              12UL
#define FT8_INT_VGA              13UL

#define FT8_OPT_MEDIAFIFO        16UL
#define FT8_OPT_FULLSCREEN       8UL
#define FT8_OPT_NOTEAR           4UL
#define FT8_OPT_SOUND            32UL

#define FT8_PALETTED4444         15UL
#define FT8_PALETTED565          14UL
#define FT8_PALETTED8            16UL
#define FT8_L2                   17UL
/*! @} */

/*! \addtogroup commands_defs FT800 Commands
	@{
*/
#define CMD_TEXT				0xFFFFFF0CUL
#define CMD_DLSTART             0xFFFFFF00UL
#define CMD_SWAP				0xFFFFFF01UL
#define CMD_MEDIAFIFO			0xFFFFFF39UL
#define CMD_PLAYVIDEO			0xFFFFFF3AUL
#define CMD_ROMFONT				0xFFFFFF3FU
#define CMD_SETBASE				0xFFFFFF38UL
#define CMD_SETBITMAP			0xFFFFFF43UL
#define CMD_SETFONT2			0xFFFFFF3BUL
#define CMD_SETROTATE			0xFFFFFF36UL
#define CMD_SETSCRATCH			0xFFFFFF3CUL
#define CMD_SNAPSHOT2			0xFFFFFF37UL
#define CMD_VIDEOFRAME			0xFFFFFF41UL
#define CMD_VIDEOSTART			0xFFFFFF40UL
#define CMD_LOADIMAGE			0xFFFFFF24
/*! @} */

/* EVE Memory Commands - used with EVE_memWritexx and EVE_memReadxx */

/*! \addtogroup eve_mem_commands_defs FT800 EVE Memory Commands

	Used with EVE_memWritexx and EVE_memReadxx
	
	@{
*/
#define MEM_WRITE	0x80	/*!< EVE Host Memory Write */
#define MEM_READ	0x00	/*!< EVE Host Memory Read */
/*! @} */

/*! \addtogroup reg_defs FT800 Register definitions
	@{
*/
#define REG_ANA_COMP          0x302184UL /*!< only listed in datasheet */
#define REG_BIST_EN           0x302174UL /*!< only listed in datasheet */
#define REG_CLOCK             0x302008UL
#define REG_CMDB_SPACE        0x302574UL
#define REG_CMDB_WRITE        0x302578UL
#define REG_CMD_DL            0x302100UL
#define REG_CMD_READ          0x3020f8UL
#define REG_CMD_WRITE         0x3020fcUL
#define REG_CPURESET          0x302020UL
#define REG_CSPREAD           0x302068UL
#define REG_CTOUCH_EXTENDED   0x302108UL
#define REG_CTOUCH_TOUCH0_XY  0x302124UL /*!< only listed in datasheet */
#define REG_CTOUCH_TOUCH4_X   0x30216cUL
#define REG_CTOUCH_TOUCH4_Y   0x302120UL
#define REG_CTOUCH_TOUCH1_XY  0x30211cUL
#define REG_CTOUCH_TOUCH2_XY  0x30218cUL
#define REG_CTOUCH_TOUCH3_XY  0x302190UL
#define REG_TOUCH_CONFIG      0x302168UL
#define REG_DATESTAMP         0x302564UL /* only listed in datasheet */
#define REG_DITHER            0x302060UL
#define REG_DLSWAP            0x302054UL
#define REG_FRAMES            0x302004UL
#define REG_FREQUENCY         0x30200cUL
#define REG_GPIO              0x302094UL
#define REG_GPIOX             0x30209cUL
#define REG_GPIOX_DIR         0x302098UL
#define REG_GPIO_DIR          0x302090UL
#define REG_HCYCLE            0x30202cUL
#define REG_HOFFSET           0x302030UL
#define REG_HSIZE             0x302034UL
#define REG_HSYNC0            0x302038UL
#define REG_HSYNC1            0x30203cUL
#define REG_ID                0x302000UL
#define REG_INT_EN            0x3020acUL
#define REG_INT_FLAGS         0x3020a8UL
#define REG_INT_MASK          0x3020b0UL
#define REG_MACRO_0           0x3020d8UL
#define REG_MACRO_1           0x3020dcUL
#define REG_MEDIAFIFO_READ    0x309014UL /*!< only listed in programmers guide */
#define REG_MEDIAFIFO_WRITE   0x309018UL /*!< only listed in programmers guide */
#define REG_OUTBITS           0x30205cUL
#define REG_PCLK              0x302070UL
#define REG_PCLK_POL          0x30206cUL
#define REG_PLAY              0x30208cUL
#define REG_PLAYBACK_FORMAT   0x3020c4UL
#define REG_PLAYBACK_FREQ     0x3020c0UL
#define REG_PLAYBACK_LENGTH   0x3020b8UL
#define REG_PLAYBACK_LOOP     0x3020c8UL
#define REG_PLAYBACK_PLAY     0x3020ccUL
#define REG_PLAYBACK_READPTR  0x3020bcUL
#define REG_PLAYBACK_START    0x3020b4UL
#define REG_PWM_DUTY          0x3020d4UL
#define REG_PWM_HZ            0x3020d0UL
#define REG_RENDERMODE        0x302010UL /*!< only listed in datasheet */
#define REG_ROTATE            0x302058UL
#define REG_SNAPFORMAT        0x30201cUL /*!< only listed in datasheet */
#define REG_SNAPSHOT          0x302018UL /*!< only listed in datasheet */
#define REG_SNAPY             0x302014UL /*!< only listed in datasheet */
#define REG_SOUND             0x302088UL
#define REG_SPI_WIDTH         0x302188UL /*!< listed with false offset in programmers guide V1.1 */
#define REG_SWIZZLE           0x302064UL
#define REG_TAG               0x30207cUL
#define REG_TAG_X             0x302074UL
#define REG_TAG_Y             0x302078UL
#define REG_TAP_CRC           0x302024UL /*!< only listed in datasheet */
#define REG_TAP_MASK          0x302028UL /*!< only listed in datasheet */
#define REG_TOUCH_ADC_MODE    0x302108UL
#define REG_TOUCH_CHARGE      0x30210cUL
#define REG_TOUCH_DIRECT_XY   0x30218cUL
#define REG_TOUCH_DIRECT_Z1Z2 0x302190UL
#define REG_TOUCH_MODE        0x302104UL
#define REG_TOUCH_OVERSAMPLE  0x302114UL
#define REG_TOUCH_RAW_XY      0x30211cUL
#define REG_TOUCH_RZ          0x302120UL
#define REG_TOUCH_RZTHRESH    0x302118UL
#define REG_TOUCH_SCREEN_XY   0x302124UL
#define REG_TOUCH_SETTLE      0x302110UL
#define REG_TOUCH_TAG         0x30212cUL
#define REG_TOUCH_TAG1        0x302134UL /*!< only listed in datasheet */
#define REG_TOUCH_TAG1_XY     0x302130UL /*!< only listed in datasheet */
#define REG_TOUCH_TAG2        0x30213cUL /*!< only listed in datasheet */
#define REG_TOUCH_TAG2_XY     0x302138UL /*!< only listed in datasheet */
#define REG_TOUCH_TAG3        0x302144UL /*!< only listed in datasheet */
#define REG_TOUCH_TAG3_XY     0x302140UL /*!< only listed in datasheet */
#define REG_TOUCH_TAG4        0x30214cUL /*!< only listed in datasheet */
#define REG_TOUCH_TAG4_XY     0x302148UL /*!< only listed in datasheet */
#define REG_TOUCH_TAG_XY      0x302128UL
#define REG_TOUCH_TRANSFORM_A 0x302150UL
#define REG_TOUCH_TRANSFORM_B 0x302154UL
#define REG_TOUCH_TRANSFORM_C 0x302158UL
#define REG_TOUCH_TRANSFORM_D 0x30215cUL
#define REG_TOUCH_TRANSFORM_E 0x302160UL
#define REG_TOUCH_TRANSFORM_F 0x302164UL
#define REG_TRACKER           0x309000UL /*!< only listed in programmers guide */
#define REG_TRACKER_1         0x309004UL /*!< only listed in programmers guide */
#define REG_TRACKER_2         0x309008UL /*!< only listed in programmers guide */
#define REG_TRACKER_3         0x30900cUL /*!< only listed in programmers guide */
#define REG_TRACKER_4         0x309010UL /*!< only listed in programmers guide */
#define REG_TRIM              0x302180UL
#define REG_VCYCLE            0x302040UL
#define REG_VOFFSET           0x302044UL
#define REG_VOL_PB            0x302080UL
#define REG_VOL_SOUND         0x302084UL
#define REG_VSIZE             0x302048UL
#define REG_VSYNC0            0x30204cUL
#define REG_VSYNC1            0x302050UL
#define RAM_CMD			      0x308000UL
/*! @} */

/*! \addtogroup bitmap_formats_defs FT800 Bitmap formats
	@{
*/
#define ARGB1555             0UL
#define L1                   1UL
#define L4                   2UL
#define L8                   3UL
#define RGB332               4UL
#define ARGB2                5UL
#define ARGB4                6UL
#define RGB565               7UL
#define PALETTED             8UL
#define TEXT8X8              9UL
#define TEXTVGA              10UL
#define BARGRAPH             11UL
/*! @} */

/*! \addtogroup bitmap_filters_defs FT800 Bitmap filter types
	@{
*/
#define NEAREST              0UL
#define BILINEAR             1UL
/*! @} */

/*! \addtogroup bitmap_wraps_defs FT800 Bitmap wrap types
	@{
*/
#define BORDER               0UL
#define REPEAT               1UL
/*! @} */

#if 0
/*! \addtogroup reserved_defs FT800 Reserved
	@{
*/
#define REG_BUSYBITS         0x3020e8UL /*!< only listed as "reserved" in datasheet */
#define REG_CRC              0x302178UL /*!< only listed as "reserved" in datasheet */
#define REG_SPI_EARLY_TX     0x30217cUL /*!< only listed as "reserved" in datasheet */
#define REG_ROMSUB_SEL       0x3020f0UL /*!< only listed as "reserved" in datasheet */
#define REG_TOUCH_FAULT      0x302170UL /*!< only listed as "reserved" in datasheet */
/*! @} */
#endif

/*! \enum primitive_operations

    \brief List of primitives.
	
	<ul>
		<li>BITMAPS - rectangular pixel arrays, in various color formats</li>
		<li>POINTS - anti-aliased points, point radius is 1-256 pixels</li>
		<li>LINES - anti-aliased lines, with width from 0 to 4095 1/16th of pixel units.
		    (width is from center of the line to boundary)</li>
		<li>LINE_STRIP - anti-aliased lines, connected head-to-tail</li>
		<li>EDGE_STRIP_A/B/L/R - edge strips</li>
		<li>RECTS - round-cornered rectangles, curvature of the corners can be adjusted
		    using LINE_WIDTH.</li>
	</ul>
*/
enum primitive_operations
{
	BITMAPS       = 1, /*!< Rectangular pixel arrays, in various color formats. */
	POINTS        = 2, /*!< Anti-aliased points, point radius is 1-256 pixels. */
	LINES         = 3, /*!< anti-aliased lines, with width from 0 to 4095 1/16th of pixel units.
	                      (width is from center of the line to boundary). */
	LINE_STRIP    = 4, /*!< Anti-aliased lines, connected head-to-tail. */
	EDGE_STRIP_R  = 5, /*!< Edge strip. */
	EDGE_STRIP_LR = 6, /*!< Edge strip. */
	EDGE_STRIP_A  = 7, /*!< Edge strip. */
	EDGE_STRIP_B  = 8, /*!< Edge strip. */
	RECTS         = 9  /*!< Round-cornered rectangles, curvature of the corners can be adjusted
	                      using LINE_WIDTH. */
};

static uint16_t cmd_offset = 0; /*!< CMD Offset. */

#define cmd_exec() wr16(REG_CMD_WRITE, cmd_offset) /*!< Execute CMD command. */

/*! \fn void FT813_init()

    \brief Initialize the FT800 chip.
*/
void FT813_init();

/*! \fn void wr32(uint32_t addr, uint32_t data)

    \brief Write 32bit long data to FT800 at specified address.
	
    \param addr Address where to write.
    \param data 32bit data to write.
*/
void wr32(uint32_t addr, uint32_t data);

/*! \fn void wr16(uint32_t addr, uint16_t data)

    \brief Write 16bit long data to FT800 at specified address.
	
    \param addr Address where to write.
    \param data 16bit data to write.
*/
void wr16(uint32_t addr, uint16_t data);

/*! \fn void wr8(uint32_t addr, uint8_t data)

    \brief Write 8bit long data to FT800 at specified address.
	
    \param addr Address where to write.
    \param data 8bit data to write.
*/
void wr8(uint32_t addr, uint8_t data);

/*! \fn void host_command(uint8_t* command)

    \brief Write a host \p command to the FT800.
	
    \param command Host command. For full list of commands refer to the
                   FT800 documentation 
				   https://www.ftdichip.com/Support/Documents/AppNotes/AN_240_FT800_From_the_Ground_Up.pdf
	
	\return 8bit long string received from FT800 at specified address.
*/
void host_command(uint8_t* command);

/*! \fn uint8_t rd8(uint32_t addr)

    \brief Read 8bit long string from the specified \p address of FT800.
	
    \param addr Address from where to read.
	
	\return 8bit long string received from FT800 at specified \p address.
*/
uint8_t rd8(uint32_t addr);

/*! \fn uint32_t BEGIN(uint8_t primitive)

    \brief Generates a \p command that needs to be executed for starting
           drawing specified \p primitive.
	
    \param primitive Primitive to draw. For full list of primitives refer
                     to the FT800 documentation
                     https://www.ftdichip.com/Support/Documents/AppNotes/AN_240_FT800_From_the_Ground_Up.pdf
	
	\return BEGIN \p command for specified \p primitive.
*/
uint32_t BEGIN(uint8_t primitive);

/*! \fn uint32_t END()

    \brief Generates a \p command that needs to be executed when finished
           drawing \p primitive.
		   
	\return END \p command for drawing \p primitive.
*/
uint32_t END();

/*! \fn uint32_t COLOR_RGB(uint8_t red, uint8_t green, uint8_t blue)

    \brief Generates a \p command that sets RGB color for the next 
	       \p primitive.
	
	\param red   Red RGB value.
	\param green Green RGB value.
	\param blue  Blue RGB value.
		   
	\return \p command that sets RGB color for the next \p primitive.
*/
uint32_t COLOR_RGB(uint8_t red, uint8_t green, uint8_t blue);

/*! \fn uint32_t POINT_SIZE(uint16_t size)

    \brief Generates a \p command that sets point size for the next 
	       \p primitive.
	
	\param size Point size.
		   
	\return \p command that sets point size for the next \p primitive.
*/
uint32_t POINT_SIZE(uint16_t size);

/*! \fn uint32_t VERTEX2II(uint16_t x, uint16_t y, uint8_t handle, uint8_t cell)

    \brief Generates a \p command that sets coordinates of the next 
	       \p primitive or its defining points. Allows only positive 
		   coordinates unlike VERTEX2F().
	
	\param x      x-coordinate in pixels.
	\param y      y-coordinate in pixels.
	\param handle Bitmap handle. 
	
	\note         The valid range is from 0 to 31. 
	              From 16 to 31, the bitmap handle is dedicated to 
				  the FT800 built-in font.
	\param cell   Cell number. 
	
	\note         Cell number is the index of bitmap 
	              with same bitmap layout and format. For example, 
				  for handle 31, the cell 65 means the character 
				  "A" in the largest built in font.
		   
	\return \p command that sets coordinates for the next \p primitive.
*/
uint32_t VERTEX2II(uint16_t x, uint16_t y, uint8_t handle, uint8_t cell);

/*! \fn uint32_t VERTEX2F(uint16_t x, uint16_t y)

    \brief Generates a \p command that sets coordinates of the next 
	       \p primitive or its defining points. Allows positive and
		   negative coordinates unlike VERTEX2II().
	
	\param x      x-coordinate in 1/16 pixel precision (Integer).
	\param y      y-coordinate in 1/16 pixel precision (Integer).
	
	\return \p command that sets coordinates for the next \p primitive.
*/
uint32_t VERTEX2F(uint16_t x, uint16_t y);

/*! \fn uint32_t LINE_WIDTH(uint16_t width)

    \brief Generates a \p command that sets line width for the next 
	       \p primitive.
	
	\param width Line width.
		   
	\return \p command that sets line width for the next \p primitive.
*/
uint32_t LINE_WIDTH(uint16_t width);

/*! \fn uint32_t CLEAR_COLOR_RGB(uint8_t red, uint8_t green, uint8_t blue)

    \brief Generates a \p command that sets a color that will be 
	       displayed when the buffer is cleared.
	
	\param red   Red RGB value.
	\param green Green RGB value.
	\param blue  Blue RGB value.
		   
	\return \p command that sets color if the buffer is cleared.
*/
uint32_t CLEAR_COLOR_RGB(uint8_t red, uint8_t green, uint8_t blue);

/*! \fn uint32_t CLEAR(uint8_t C, uint8_t S, uint8_t T)

    \brief Generates a \p command that clears buffers to preset 
	       values.
	
	\param C Clear color buffer. 
	
	\note    Setting this bit to 1 will 
	         clear the color buffer of the FT800 to the preset 
			 value. Setting this bit to 0 will maintain the color 
			 buffer of the FT800 with an unchanged value. 
			 The preset value is defined in \p command 
			 CLEAR_COLOR_RGB for RGB channel and CLEAR_COLOR_A 
			 for alpha channel.
			 
	\param S Clear stencil buffer. 
	
	\note    Setting this bit to 1 will 
	         clear the stencil buffer of the FT800 to the preset 
			 value. Setting this bit to 0 will maintain the stencil
	         buffer of the FT800 with an unchanged value. 
			 The preset value is defined in \p command CLEAR_STENCIL.
			 
	\param T Clear tag buffer. 
	
	\note    Setting this bit to 1 will clear 
	         the tag buffer of the FT800 to the preset value. 
			 Setting this bit to 0 will maintain the tag buffer 
			 of the FT800 with an unchanged value. The preset 
			 value is defined in \p command CLEAR_TAG.
		   
	\return \p command that clears buffers to preset values.
*/
uint32_t CLEAR(uint8_t C, uint8_t S, uint8_t T);

/*! \fn uint32_t DISPLAY()

    \brief Generates a \p command that ends the display list. 
	       FT800 will ignore all the \p commands following 
		   this \p command.
		   
	\return \p command that ends the display list.
*/
uint32_t DISPLAY();

/*! \fn uint32_t SAVE_CONTEXT()

    \brief Generates a \p command that pushes the current 
	       graphics context on the context stack.
		   
	\return \p command that pushes the current
	        graphics context on the context stack.
*/
uint32_t SAVE_CONTEXT();

/*! \fn uint32_t RESTORE_CONTEXT()

    \brief Generates a \p command that restores the 
	       current graphics context from the context 
		   stack.
		   
	\return \p command that restores the
	        current graphics context from the context 
			stack.
*/
uint32_t RESTORE_CONTEXT();

/*! \fn uint32_t SNAPSHOT()

    \brief Generates a \p command that causes the co-processor 
	       engine to take a snapshot of the current 
		   screen, and write the result into RAM_G 
		   as a ARGB4 bitmap. The size of the bitmap 
		   is the size of the screen, given by the 
		   REG_HSIZE and REG_VSIZE registers.
		   
	\note  During the snapshot process, the display 
		   should be disabled by setting REG_PCLK to 
		   0 to avoid display glitch.
		   
	\note  Because co-processor engine needs to write 
		   the result into the destination address, 		   the destination address must be never 		   used or referenced by graphics engine.
		   
	\return \p command that takes a snapshot of the 
	        current screen.
*/
uint32_t SNAPSHOT();

/*! \fn uint32_t BITMAP_SOURCE(uint32_t addr)

    \brief Generates a \p command that sets the 
	       bitmap source address, which is normally 
		   the address in main memory where the
           bitmap graphic data is loaded.
		   
	\param addr Bitmap address in graphics SRAM FT800, 
	            aligned with respect to the bitmap format.
				
	\note       For example, if the bitmap format is 
				RGB565/ARGB4/ARGB1555, the bitmap
	            source shall be aligned to 2 bytes.
		   
	\return \p command that takes a snapshot of the 
	        current screen.
*/
uint32_t BITMAP_SOURCE(uint32_t addr);

/*! \fn uint32_t BITMAP_LAYOUT(uint8_t f, uint16_t linestride, uint16_t height)

    \brief Generates a \p command that specifies the source 
	       bitmap memory format and layout for the current handle.
		   
	\param f          Bitmap pixel format. The valid range is 
	                  from 0 to 11 and defined as per the table below.
	
	<table>
		<caption>BITMAP_LAYOUT format list</caption>
		<tr><th>NAME<th>VALUE
		<tr><th>ARGB1555<th>0
		<tr><th>L1<th>1
		<tr><th>L4<th>2
		<tr><th>L8<th>3
		<tr><th>RGB332<th>4
		<tr><th>ARGB2<th>5
		<tr><th>ARGB4<th>6
		<tr><th>RGB565<th>7
		<tr><th>PALETTED<th>8
		<tr><th>TEXT8X8<th>9
		<tr><th>TEXTVGA<th>10
		<tr><th>BARGRAPH<th>11
	</table>
	
	\note \b BARGRAPH - render data as a bar graph. Looks up the x coordinate in a byte array, then
	      gives an opaque pixel if the byte value is less than y, otherwise a transparent pixel. The
	      result is a bar graph of the bitmap data. A maximum of 256x256 size bitmap can be
	      drawn using the BARGRAPH format. Orientation, width and height of the graph can be
	      altered using the bitmap transform matrix.
		  \n\n
	      \b TEXT8X8 - lookup in a fixed 8x8 font. The bitmap is a byte array present in the graphics
	      ram and each byte indexes into an internal 8x8 CP437 [2] font (inbuilt font bitmap
	      handles 16 & 17 are used for drawing TEXT8X8 format). The result is that the bitmap
	      acts like a character grid. A single bitmap can be drawn which covers all or part of the
	      display; each byte in the bitmap data corresponds to one 8x8 pixel character cell.
		  \n\n
	      \b TEXTVGA - lookup in a fixed 8x16 font with TEXTVGA syntax. The bitmap is a TEXTVGA
	      array present in the graphics ram, each element indexes into an internal 8x16 CP437 [2]
	      font (inbuilt font bitmap handles 18 & 19 are used for drawing TEXTVGA format with
	      control information such as background color, foreground color and cursor etc). The
	      result is that the bitmap acts like a TEXTVGA grid. A single bitmap can be drawn which
	      covers all or part of the display; each TEXTVGA data type in the bitmap corresponds to
	      one 8x16 pixel character cell.
		  \n\n
	      \b PALETTED - bitmap bytes are indices into a palette table. By using a palette table -
	      which contains 32-bit RGBA colors - a significant amount of memory can be saved. The
	      256 color palette is stored in a dedicated 1K (256x4) byte RAM_PAL.
	
	\param linestride Bitmap linestride, in bytes. Please note the alignment requirement which is
	                  described below.
	\param height     Bitmap height, in lines.
				
	\note The bitmap formats supported are L1, L4, L8, RGB332, ARGB2, ARGB4, ARGB1555,
	      RGB565 and Palette.
		  \n\n
	      For L1 format, the line stride must be a multiple of 8 bits; For L4 format the line
	      stride must be multiple of 2 nibbles (Aligned to byte).
		  \n\n
	      For more details about alignment, please refer to the tables below:
		  
	<table>
		<tr><th colspan="2">L1 format layout<th>Byte Order
		<tr><th>Pixel 0<th>Bit 7<th rowspan="4">Byte 0
		<tr><th>Pixel 1<th>Bit 6
		<tr><th colspan="2">...
		<tr><th>Pixel 7<th>Bit 0
	</table>
	<p></p>
	<table>
		<tr><th colspan="2">L4 format layout<th>Byte Order
		<tr><th>Pixel 0<th>Bit 7-4<th rowspan="2">Byte 0
		<tr><th>Pixel 1<th>Bit 3-0
	</table>
	<p></p>
	<table>
		<tr><th colspan="2">L8 format layout<th>Byte Order
		<tr><th>Pixel 0<th>Bit 7-0<th>Byte 0
		<tr><th>Pixel 1<th>Bit 15-8<th>Byte 1
		<tr><th>Pixel 2<th>Bit 23-16<th>Byte 2
	</table>
	<p></p>
	<table>
		<tr><th colspan="2">ARGB2 format layout<th>Byte Order
		<tr><th>A<th>Bit 7-6<th rowspan="4">Byte 1 \n Byte 0
		<tr><th>R<th>Bit 5-4
		<tr><th>G<th>Bit 3-2
		<tr><th>B<th>Bit 1-0
	</table>
	<p></p>
	<table>
		<tr><th colspan="2">ARGB1555 format layout<th>Byte Order
		<tr><th>A<th>Bit 15<th rowspan="4">Byte 1 \n Byte 0
		<tr><th>R<th>Bit 14-10
		<tr><th>G<th>Bit 9-5
		<tr><th>B<th>Bit 4-0
	</table>
	<p></p>
	<table>
		<tr><th colspan="2">ARGB4 format layout<th>Byte Order
		<tr><th>A<th>Bit 15-12<th rowspan="4">Byte 1 \n Byte 0
		<tr><th>R<th>Bit 11-8
		<tr><th>G<th>Bit 7-4
		<tr><th>B<th>Bit 3-0
	</table>
	<p></p>
	<table>
		<tr><th colspan="2">RGB332 pixel layout<th>Byte Order
		<tr><th>R<th>Bit 7-5<th rowspan="4">Byte 0
		<tr><th>G<th>Bit 4-2
		<tr><th>B<th>Bit 1-0
	</table>
	<p></p>
	<table>
		<tr><th colspan="2">RGB565 format layout<th>Byte Order
		<tr><th>R<th>Bit 15-11<th rowspan="4">Byte 1 \n Byte 0
		<tr><th>G<th>Bit 10-5
		<tr><th>B<th>Bit 4-0
	</table>
	<p></p>
	<table>
		<tr><th colspan="2">Palette format layout<th>Byte Order
		<tr><th>A<th>Bit 31-24<th>Byte 3
		<tr><th>R<th>Bit 23-16<th>Byte 2
		<tr><th>G<th>Bit 15-8<th>Byte 1
		<tr><th>B<th>Bit 7-0<th>Byte 0
	</table>
		   
	\return \p command that takes a snapshot of the 
	        current screen.
*/
uint32_t BITMAP_LAYOUT(uint8_t f, uint16_t linestride, uint16_t height);

/*! \fn uint32_t BITMAP_SIZE(uint8_t filter, uint8_t wrapx, uint8_t wrapy, uint16_t width, uint16_t height)

    \brief Generates a \p command that specifies the 
	       screen drawing of bitmaps for the current handle.
		   
	\param filter Bitmap filtering mode, one of NEAREST or BILINEAR
	              The value of NEAREST is 0 and the value of BILINEAR is 1.
	\param wrapx  Bitmap x wrap mode, one of REPEAT or BORDER
	              The value of BORDER is 0 and the value of REPEAT is 1.
	\param wrapy  Bitmap y wrap mode, one of REPEAT or BORDER.
	\param width  Drawn bitmap width, in pixels.
	\param height Drawn bitmap height, in pixels.
				
	\note This \p command controls the drawing of bitmaps: the on-screen size of the bitmap,
		  the behavior for wrapping, and the filtering function. Please note that if wrapx or
		  wrapy is REPEAT then the corresponding memory layout dimension
		  (BITMAP_LAYOUT line stride or height) must be power of two, otherwise the result is
		  undefined.
		  \n\n
		  For parameter width and height, the value from 1 to 511 means the bitmap width
		  and height in pixel. The value of zero means the 512 pixels in width or height.
		   
	\return \p command that specifies the
	         screen drawing of bitmaps for the current handle.
*/
uint32_t BITMAP_SIZE(uint8_t filter, uint8_t wrapx, uint8_t wrapy, uint16_t width, uint16_t height);

/*! \addtogroup transformations_defs FT800 Transformations

	To achieve the bitmap transformation, the bitmap transform matrix below is specified in
	the FT800 and denoted as \p m
	
	       |  ????????????_??????????????????_??  ????????????_??????????????????_??  ????????????_??????????????????_??  |
	\p m = |                                                                        |
	       |  ????????????_??????????????????_??  ????????????_??????????????????_??  ????????????_??????????????????_??  |
	
	
	                  |  1.0  0.0  0.0  |
	By default \p m = |                 |, it is named as identity matrix. 
	                  |  0.0  1.0  0.0  |					      The coordinates ??', ??' after transforming is calculated in following equation:    
	                  |x'|       |x|
					  |y'| = m x |y|
					  |1 |       |1|
					  
	i.e.:
	
	                  x' = x * A + y * B + C
					  y' = x * D + y * E + F
					  
	Where A,B,C,E,D,E,F stands for the values assigned by commands
					  BITMAP_TRANSFORM_A-F.
	@{
*/
#define BITMAP_TRANSFORM_A(a) ((21UL<<24)|(((a)&131071UL)<<0))
#define BITMAP_TRANSFORM_B(b) ((22UL<<24)|(((b)&131071UL)<<0))
#define BITMAP_TRANSFORM_C(c) ((23UL<<24)|(((c)&16777215UL)<<0))
#define BITMAP_TRANSFORM_D(d) ((24UL<<24)|(((d)&131071UL)<<0))
#define BITMAP_TRANSFORM_E(e) ((25UL<<24)|(((e)&131071UL)<<0))
#define BITMAP_TRANSFORM_F(f) ((26UL<<24)|(((f)&16777215UL)<<0))
/*! @} */

/*! \fn void cmd(uint32_t command)

    \brief Write 32 bits \p command to co-processor engine FIFO RAM_CMD.
		   
	\param Command 32 bits \p command.
*/
void cmd(uint32_t command);

/*! \addtogroup draw_shapes FT800 Set of Functions for Simplified Shapes Drawing

	This is a set of functions that make it easier to draw some commonly used 
	(especially in this project) shapes.
	@{
*/

/*! \fn void draw_rectangle(uint16_t width, int height, uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue)

    \brief Draws rectangle with rounded corners.
		   
	\param width Width of the rectangle.
	\param height Height of the rectangle.
	\param x X-coordinate of the left top corner of the rectangle.
	\param y Y-coordinate of the left top corner of the rectangle.
	\param red Red color from RGB.
	\param green Green color from RGB.
	\param blue Blue color from RGB.
*/
void draw_rectangle(uint16_t width, int height, uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue);

/*! \fn void draw_oval(uint16_t width, int height, uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue)

    \brief NOT IMPLEMENTED!!! Draws oval.
		   
	\param width Width of the oval.
	\param height Height of the oval.
	\param x X-coordinate of the left top corner of the oval.
	\param y Y-coordinate of the left top corner of the oval.
	\param red Red color from RGB.
	\param green Green color from RGB.
	\param blue Blue color from RGB.
*/
void draw_oval(uint16_t width, int height, uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue);

/*! \fn void draw_text(char* text, uint8_t text_array_size, uint8_t font_size, uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue)

    \brief Draws specified text.
		   
	\param text Text to be displayed.
	\param text_array_size Size of the array that holds text (don't forget null terminator '\0').
	\param font_size Font Size.
	\param x X-coordinate of the left top corner of the text.
	\param y Y-coordinate of the left top corner of the text.
	\param red Red color from RGB.
	\param green Green color from RGB.
	\param blue Blue color from RGB.
*/
void draw_text(char* text, uint8_t text_array_size, uint8_t font_size, uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue);

/*! \fn void draw_character(char character, uint8_t font_size, uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue)

    \brief Draws specified character.
		   
	\param character Character to be displayed.
	\param font_size Font Size.
	\param x X-coordinate of the left top corner of the character.
	\param y Y-coordinate of the left top corner of the character.
	\param red Red color from RGB.
	\param green Green color from RGB.
	\param blue Blue color from RGB.
*/
void draw_character(char character, uint8_t font_size, uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue);

/*! \fn void draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t red, uint8_t green, uint8_t blue)

    \brief Draws line.
		   
	\param x1 X-coordinate of the starting point.
	\param y1 Y-coordinate of the starting point.
	\param x2 X-coordinate of the ending point.
	\param y2 Y-coordinate of the ending point.
	\param red Red color from RGB.
	\param green Green color from RGB.
	\param blue Blue color from RGB.
*/
void draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t red, uint8_t green, uint8_t blue);

/*! \fn void draw_line_with_width(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t width, uint8_t red, uint8_t green, uint8_t blue)

    \brief Draws line with specified width.
		   
	\param x1 X-coordinate of the starting point.
	\param y1 Y-coordinate of the starting point.
	\param x2 X-coordinate of the ending point.
	\param y2 Y-coordinate of the ending point.
	\param width Line width.
	\param red Red color from RGB.
	\param green Green color from RGB.
	\param blue Blue color from RGB.
*/
void draw_line_with_width(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t width, uint8_t red, uint8_t green, uint8_t blue);

/*! \fn void draw_one_pixel_line(uint16_t x, uint16_t y, uint8_t font_size, uint8_t r, uint8_t g, uint8_t b)

    \brief Draws 1-pixel width line.
		   
	\param x X-coordinate of the top left corner.
	\param y Y-coordinate of the top left corner.
	\param font_size Font size.
	\param r Red color from RGB.
	\param g Green color from RGB.
	\param b Blue color from RGB.
*/
void draw_one_pixel_line(uint16_t x, uint16_t y, uint8_t font_size, uint8_t r, uint8_t g, uint8_t b);

/*! \fn void display_digital_reading(uint16_t value, int top_left_x, int top_left_y, int font_size, uint8_t is_voltage)

    \brief Displays voltage or current in format NN.N (ex. 13.2).
		   
	\param value Value to be displayed.
	\param top_left_x X-coordinate of the top left corner.
	\param top_left_y Y-coordinate of the top left corner.
	\param font_size Font size.
	\param is_voltage Voltage = TRUE, Current = FALSE.
*/
void display_digital_reading(uint16_t value, int top_left_x, int top_left_y, int font_size, uint8_t is_voltage);

/*! \fn void draw_simple_rectangle(uint16_t top_left_x, uint16_t top_left_y, uint16_t bottom_right_x, uint16_t bottom_right_y, uint8_t r, uint8_t g, uint8_t b)

    \brief Draws 1-pixel width line.
		   
	\param top_left_x X-coordinate of the top left corner.
	\param top_left_y Y-coordinate of the top left corner.
	\param bottom_right_x X-coordinate of the bottom right corner.
	\param bottom_right_y Y-coordinate of the bottom right corner.
	\param r Red color from RGB.
	\param g Green color from RGB.
	\param b Blue color from RGB.
*/
void draw_simple_rectangle(uint16_t top_left_x, uint16_t top_left_y, uint16_t bottom_right_x, uint16_t bottom_right_y, uint8_t r, uint8_t g, uint8_t b);

/*! \fn void draw_gauge(int start_x, int y, int width)

    \brief Draws the part of the gauge with all the repetitive graduation lines.
		   
	\param start_x X-coordinate of the top left corner.
	\param y Y-coordinate of the top left corner.
	\param width Width of the gauge.
*/
void draw_gauge(int start_x, int y, int width);

/*! \fn void draw_gauge_and_partial_snapshot(int start_x, int y, int width)

    \brief Draws the part of the gauge with all the repetitive graduation lines, 
	then takes a snapshot of that gauge and stores in RAM_G. 
	This can then be called as a bitmap.
    This way, we don't have to keep re-writing the whole gauge every single time.
		   
	\param start_x X-coordinate of the top left corner.
	\param y Y-coordinate of the top left corner.
	\param width Width of the gauge.
*/
void draw_gauge_and_partial_snapshot(int start_x, int y, int width);

/*! \fn void draw_current_and_voltage(ProgramState *program_state, OutputState *output, int start_x, int y, int width, uint16_t max_voltage, uint16_t max_current)

    \brief Draws on the gauge voltage as a blue line, current as a green 
	line and the maximum current and voltage as red lines.
		   
	\param program_state Program state that holds important up to date 
		information about whole system.
	\param output Which output to draw the current and voltage lines on (Since we have two outputs).
	\param start_x X-coordinate of the top left corner.
	\param y Y-coordinate of the top left corner.
	\param width Width of the lines.
	\param max_voltage Maximum voltage.
	\param max_current Maximum current.
*/
void draw_current_and_voltage(ProgramState *program_state, OutputState *output, int start_x, int y, int width, uint16_t max_voltage, uint16_t max_current);
/*! @} */

/*! \fn void draw_message_box(ProgramState *program_state, OutputState *output_one, OutputState *output_two, TimerCount *counters)

    \brief Draws message box with appropriate messages which will show up
		depending on the program state and outputs.
		   
	\param program_state Program state that holds important up to date 
		information about whole system.
	\param output_one Reference to the first output.
	\param output_two Reference to the second output.
	\param counters Reference to the counters that contains all counters for all events.
*/
void draw_message_box(ProgramState *program_state, OutputState *output_one, OutputState *output_two, TimerCount *counters);

/*! \fn void draw_settings_page(ProgramState *program_state, OutputState *output_one)

    \brief Draws "Settings Page" where the user is able to change unit 
		mode to single and double. Also, the developers are able to 
		calibrate the unit and see error logs.
		   
	\param program_state Program state that holds important up to date 
		information about whole system.
	\param output_one Reference to the first output.
*/
void draw_settings_page(ProgramState *program_state, OutputState *output_one);

/*! \fn char * int_to_char_array(int val)

    \brief Converts integer number to the character array number 
		that then can be displayed.
		   
	\param val Integer value that needs to be converted.
	
	\return character array with the specified converted number.
*/
char * int_to_char_array(int val);

/*! \fn int number_of_digits(int val)

    \brief Gets amount of digits in a number.
		   
	\param val Integer value whose digits need to be counted.
	
	\return Amount of digits in a number.
*/
int number_of_digits(int val);

/*! \fn uint16_t round_to_tens(uint16_t number)

    \brief Rounds to tens a specified number.
		   
	\param number Number to round.
	
	\return Rounded number.
*/
uint16_t round_to_tens(uint16_t number);

/*! \fn void write_screen()

    \brief Updates screen.
*/
void write_screen();
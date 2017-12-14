/*!
******************************************************************************
@file   : /home/jenkins/builds/workspace/ISP_PKG/build/CI/felix/regdefs/regdefs//registers/ext_data_generator.h

@brief  

@Author <Autogenerated>

		<b>Copyright 2005 by Imagination Technologies Limited.</b>
		All rights reserved.  No part of this software, either
		material or conceptual may be copied or distributed,
		transmitted, transcribed, stored in a retrieval system
		or translated into any human or computer language in any
		form by any means, electronic, mechanical, manual or
		other-wise, or disclosed to third parties without the
		express written permission of Imagination Technologies
		Limited, Unit 8, HomePark Industrial Estate,
		King's Langley, Hertfordshire, WD4 8LZ, U.K.

<b>Description:</b>\n
		This file contains the EXT_DATA_GENERATOR_H Defintions.


 Register Attributes meaning:
 @li <REG>_OFFSET <int> offset in bytes from the register bank
 @li <REG>_STRIDE <int> [table register only] distance in bytes between table entries
 @li <REG>_NO_ENTRIES <int> [table register only] number of entries in the table
 @li <REG>_TRUSTED <bool> [only if register is trusted] if the register can only be written by trusted source

 Fields Attributes meaning:
 @li <FIELD>_MASK <int> in register
 @li <FIELD>_LSBMASK <int> when field is shifted to LSBs
 @li <FIELD>_SHIFT <int> in bits from LSB
 @li <FIELD>_LENGTH <int> in bits
 @li <FIELD>_DEFAULT <int>
 @li <FIELD>_SIGNED_FIELD <bool>
 @li <FIELD>_NO_REPS <int> [repeated field only] number of time the field is repeated
 @li <FIELD>_SIZE <int> [repeated field only] size of repeated field (same than LENGTH)

 If the register bank is a structure <BANK>_BYTE_SIZE <int> is defined as the size in memory.
******************************************************************************/

#if !defined (__EXT_DATA_GENERATOR_H__)
#define __EXT_DATA_GENERATOR_H__

#ifdef __cplusplus
extern "C" {
#endif


#define FELIX_TEST_DG_DG_CONFIG_OFFSET		(0x0000)

/* FELIX_TEST_DG, DG_CONFIG, DG_ENABLE_STATUS
*/
#define FELIX_TEST_DG_DG_CONFIG_DG_ENABLE_STATUS_MASK		(0x00000001)
#define FELIX_TEST_DG_DG_CONFIG_DG_ENABLE_STATUS_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_CONFIG_DG_ENABLE_STATUS_SHIFT		(0)
#define FELIX_TEST_DG_DG_CONFIG_DG_ENABLE_STATUS_LENGTH		(1)
#define FELIX_TEST_DG_DG_CONFIG_DG_ENABLE_STATUS_DEFAULT		(0)
#define FELIX_TEST_DG_DG_CONFIG_DG_ENABLE_STATUS_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_STATUS_OFFSET		(0x0004)

/* FELIX_TEST_DG, DG_STATUS, DG_STATE
*/
#define FELIX_TEST_DG_DG_STATUS_DG_STATE_MASK		(0x02000000)
#define FELIX_TEST_DG_DG_STATUS_DG_STATE_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_STATUS_DG_STATE_SHIFT		(25)
#define FELIX_TEST_DG_DG_STATUS_DG_STATE_LENGTH		(1)
#define FELIX_TEST_DG_DG_STATUS_DG_STATE_DEFAULT		(0)
#define FELIX_TEST_DG_DG_STATUS_DG_STATE_SIGNED_FIELD	(IMG_FALSE)

enum FELIX_TEST_DG_DG_STATUS_DG_STATE_ENUM {
	/**
	 * @brief The data Generator is active transmitting data or waiting for a new linked list structure
	 */
	FELIX_TEST_DG_DG_STATE_DG_ACTIVE = 0x1,
	/**
	 * @brief The data Generator is idle. No data being transmitted or pending linked list request
	 */
	FELIX_TEST_DG_DG_STATE_DG_IDLE = 0x0,
};

/* FELIX_TEST_DG, DG_STATUS, DG_PIXEL_REF_CLK
10.3 representation of the pixel clock frequency in MHz used to generate the Pixel clock (parallel) or byte clock frequency (MIPI)
*/
#define FELIX_TEST_DG_DG_STATUS_DG_PIXEL_REF_CLK_MASK		(0x01FFF000)
#define FELIX_TEST_DG_DG_STATUS_DG_PIXEL_REF_CLK_LSBMASK		(0x00001FFF)
#define FELIX_TEST_DG_DG_STATUS_DG_PIXEL_REF_CLK_SHIFT		(12)
#define FELIX_TEST_DG_DG_STATUS_DG_PIXEL_REF_CLK_LENGTH		(13)
#define FELIX_TEST_DG_DG_STATUS_DG_PIXEL_REF_CLK_DEFAULT		(0)
#define FELIX_TEST_DG_DG_STATUS_DG_PIXEL_REF_CLK_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_STATUS, DG_FRAMES_SENT
Number of frames transmitted since last enabled. The register will wrap around.
*/
#define FELIX_TEST_DG_DG_STATUS_DG_FRAMES_SENT_MASK		(0x00000FFF)
#define FELIX_TEST_DG_DG_STATUS_DG_FRAMES_SENT_LSBMASK		(0x00000FFF)
#define FELIX_TEST_DG_DG_STATUS_DG_FRAMES_SENT_SHIFT		(0)
#define FELIX_TEST_DG_DG_STATUS_DG_FRAMES_SENT_LENGTH		(12)
#define FELIX_TEST_DG_DG_STATUS_DG_FRAMES_SENT_DEFAULT		(0)
#define FELIX_TEST_DG_DG_STATUS_DG_FRAMES_SENT_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_CTRL_OFFSET		(0x0008)

/* FELIX_TEST_DG, DG_CTRL, DG_GROUP_OVERRIDE
This register is used to define which group overide a data generator should use.
*/
#define FELIX_TEST_DG_DG_CTRL_DG_GROUP_OVERRIDE_MASK		(0x00000180)
#define FELIX_TEST_DG_DG_CTRL_DG_GROUP_OVERRIDE_LSBMASK		(0x00000003)
#define FELIX_TEST_DG_DG_CTRL_DG_GROUP_OVERRIDE_SHIFT		(7)
#define FELIX_TEST_DG_DG_CTRL_DG_GROUP_OVERRIDE_LENGTH		(2)
#define FELIX_TEST_DG_DG_CTRL_DG_GROUP_OVERRIDE_DEFAULT		(0)
#define FELIX_TEST_DG_DG_CTRL_DG_GROUP_OVERRIDE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_CTRL, DG_CRC_CLEAR
Initialise all CRCs in the Datagenerator and gaskets. Auto-clears
*/
#define FELIX_TEST_DG_DG_CTRL_DG_CRC_CLEAR_MASK		(0x00000040)
#define FELIX_TEST_DG_DG_CTRL_DG_CRC_CLEAR_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_CTRL_DG_CRC_CLEAR_SHIFT		(6)
#define FELIX_TEST_DG_DG_CTRL_DG_CRC_CLEAR_LENGTH		(1)
#define FELIX_TEST_DG_DG_CTRL_DG_CRC_CLEAR_DEFAULT		(0)
#define FELIX_TEST_DG_DG_CTRL_DG_CRC_CLEAR_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_CTRL, DG_PRELOAD
Pre-fetch the next row address at the start of each row. 1 - enabled, 0 - disabled
*/
#define FELIX_TEST_DG_DG_CTRL_DG_PRELOAD_MASK		(0x00000020)
#define FELIX_TEST_DG_DG_CTRL_DG_PRELOAD_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_CTRL_DG_PRELOAD_SHIFT		(5)
#define FELIX_TEST_DG_DG_CTRL_DG_PRELOAD_LENGTH		(1)
#define FELIX_TEST_DG_DG_CTRL_DG_PRELOAD_DEFAULT		(0)
#define FELIX_TEST_DG_DG_CTRL_DG_PRELOAD_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_CTRL, DG_PIXEL_FORMAT

*/
#define FELIX_TEST_DG_DG_CTRL_DG_PIXEL_FORMAT_MASK		(0x00000010)
#define FELIX_TEST_DG_DG_CTRL_DG_PIXEL_FORMAT_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_CTRL_DG_PIXEL_FORMAT_SHIFT		(4)
#define FELIX_TEST_DG_DG_CTRL_DG_PIXEL_FORMAT_LENGTH		(1)
#define FELIX_TEST_DG_DG_CTRL_DG_PIXEL_FORMAT_DEFAULT		(0)
#define FELIX_TEST_DG_DG_CTRL_DG_PIXEL_FORMAT_SIGNED_FIELD	(IMG_FALSE)

enum FELIX_TEST_DG_DG_CTRL_DG_PIXEL_FORMAT_ENUM {
	FELIX_TEST_DG_DG_PIXEL_FORMAT_DG_12BIT_FORMAT = 0x1,
	FELIX_TEST_DG_DG_PIXEL_FORMAT_DG_10BIT_FORMAT = 0x0,
};

/* FELIX_TEST_DG, DG_CTRL, RESERVED
Reserved
*/
#define FELIX_TEST_DG_DG_CTRL_RESERVED_MASK		(0x00000008)
#define FELIX_TEST_DG_DG_CTRL_RESERVED_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_CTRL_RESERVED_SHIFT		(3)
#define FELIX_TEST_DG_DG_CTRL_RESERVED_LENGTH		(1)
#define FELIX_TEST_DG_DG_CTRL_RESERVED_DEFAULT		(0)
#define FELIX_TEST_DG_DG_CTRL_RESERVED_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_CTRL, DG_IF_MODE

*/
#define FELIX_TEST_DG_DG_CTRL_DG_IF_MODE_MASK		(0x00000004)
#define FELIX_TEST_DG_DG_CTRL_DG_IF_MODE_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_CTRL_DG_IF_MODE_SHIFT		(2)
#define FELIX_TEST_DG_DG_CTRL_DG_IF_MODE_LENGTH		(1)
#define FELIX_TEST_DG_DG_CTRL_DG_IF_MODE_DEFAULT		(0)
#define FELIX_TEST_DG_DG_CTRL_DG_IF_MODE_SIGNED_FIELD	(IMG_FALSE)

enum FELIX_TEST_DG_DG_CTRL_DG_IF_MODE_ENUM {
	/**
	 * @brief Select MIPI mode
	 */
	FELIX_TEST_DG_DG_IF_MODE_DG_MIPI = 0x1,
	/**
	 * @brief Select parallel mode
	 */
	FELIX_TEST_DG_DG_IF_MODE_DG_PARALLEL = 0x0,
};

/* FELIX_TEST_DG, DG_CTRL, DG_MIPI_LS_EN
Configuration for MIPI data generation
0: No short packets containing line start or line end are present 
1: Short packets containing line information are enabled
*/
#define FELIX_TEST_DG_DG_CTRL_DG_MIPI_LS_EN_MASK		(0x00000002)
#define FELIX_TEST_DG_DG_CTRL_DG_MIPI_LS_EN_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_CTRL_DG_MIPI_LS_EN_SHIFT		(1)
#define FELIX_TEST_DG_DG_CTRL_DG_MIPI_LS_EN_LENGTH		(1)
#define FELIX_TEST_DG_DG_CTRL_DG_MIPI_LS_EN_DEFAULT		(0)
#define FELIX_TEST_DG_DG_CTRL_DG_MIPI_LS_EN_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_CTRL, DG_ENABLE
*/
#define FELIX_TEST_DG_DG_CTRL_DG_ENABLE_MASK		(0x00000001)
#define FELIX_TEST_DG_DG_CTRL_DG_ENABLE_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_CTRL_DG_ENABLE_SHIFT		(0)
#define FELIX_TEST_DG_DG_CTRL_DG_ENABLE_LENGTH		(1)
#define FELIX_TEST_DG_DG_CTRL_DG_ENABLE_DEFAULT		(0)
#define FELIX_TEST_DG_DG_CTRL_DG_ENABLE_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_MODE_OFFSET		(0x000C)

/* FELIX_TEST_DG, DG_MODE, DG_MODE
Selects the capture mode.
*/
#define FELIX_TEST_DG_DG_MODE_DG_MODE_MASK		(0x00000003)
#define FELIX_TEST_DG_DG_MODE_DG_MODE_LSBMASK		(0x00000003)
#define FELIX_TEST_DG_DG_MODE_DG_MODE_SHIFT		(0)
#define FELIX_TEST_DG_DG_MODE_DG_MODE_LENGTH		(2)
#define FELIX_TEST_DG_DG_MODE_DG_MODE_DEFAULT		(0)
#define FELIX_TEST_DG_DG_MODE_DG_MODE_SIGNED_FIELD	(IMG_FALSE)

enum FELIX_TEST_DG_DG_MODE_DG_MODE_ENUM {
	/**
	 * @brief Not supported.
	 */
	FELIX_TEST_DG_DG_MODE_DG_UNUSED = 0x3,
	/**
	 * @brief Automatically capture frames using a linked list to store the results for each frame
	 */
	FELIX_TEST_DG_DG_MODE_DG_LINKED_LIST = 0x2,
	/**
	 * @brief When set only one frame is captured. Returns to CAP_DISABLE after the capture has finish.
	 */
	FELIX_TEST_DG_DG_MODE_DG_MANUAL = 0x1,
	/**
	 * @brief Capture of video is disabled
	 */
	FELIX_TEST_DG_DG_MODE_DG_DISABLE = 0x0,
};

#define FELIX_TEST_DG_DG_RESET_OFFSET		(0x0010)

/* FELIX_TEST_DG, DG_RESET, DG_RESET
*/
#define FELIX_TEST_DG_DG_RESET_DG_RESET_MASK		(0x00000001)
#define FELIX_TEST_DG_DG_RESET_DG_RESET_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_RESET_DG_RESET_SHIFT		(0)
#define FELIX_TEST_DG_DG_RESET_DG_RESET_LENGTH		(1)
#define FELIX_TEST_DG_DG_RESET_DG_RESET_DEFAULT		(0)
#define FELIX_TEST_DG_DG_RESET_DG_RESET_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_LINK_ADDR_OFFSET		(0x0014)

/* FELIX_TEST_DG, DG_LINK_ADDR, DG_LINK_ADDR
*/
#define FELIX_TEST_DG_DG_LINK_ADDR_DG_LINK_ADDR_MASK		(0xFFFFFFC0)
#define FELIX_TEST_DG_DG_LINK_ADDR_DG_LINK_ADDR_LSBMASK		(0x03FFFFFF)
#define FELIX_TEST_DG_DG_LINK_ADDR_DG_LINK_ADDR_SHIFT		(6)
#define FELIX_TEST_DG_DG_LINK_ADDR_DG_LINK_ADDR_LENGTH		(26)
#define FELIX_TEST_DG_DG_LINK_ADDR_DG_LINK_ADDR_DEFAULT		(0)
#define FELIX_TEST_DG_DG_LINK_ADDR_DG_LINK_ADDR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_TAG_OFFSET		(0x0018)

/* FELIX_TEST_DG, DG_TAG, DG_TAG
TAG field that can be used by the SW to identify the LINKED LIST. Not relevant for HW.
*/
#define FELIX_TEST_DG_DG_TAG_DG_TAG_MASK		(0xFFFFFFFF)
#define FELIX_TEST_DG_DG_TAG_DG_TAG_LSBMASK		(0xFFFFFFFF)
#define FELIX_TEST_DG_DG_TAG_DG_TAG_SHIFT		(0)
#define FELIX_TEST_DG_DG_TAG_DG_TAG_LENGTH		(32)
#define FELIX_TEST_DG_DG_TAG_DG_TAG_DEFAULT		(0)
#define FELIX_TEST_DG_DG_TAG_DG_TAG_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_ADDR_DATA_OFFSET		(0x001C)

/* FELIX_TEST_DG, DG_ADDR_DATA, DG_ADDR_DATA
*/
#define FELIX_TEST_DG_DG_ADDR_DATA_DG_ADDR_DATA_MASK		(0xFFFFFFC0)
#define FELIX_TEST_DG_DG_ADDR_DATA_DG_ADDR_DATA_LSBMASK		(0x03FFFFFF)
#define FELIX_TEST_DG_DG_ADDR_DATA_DG_ADDR_DATA_SHIFT		(6)
#define FELIX_TEST_DG_DG_ADDR_DATA_DG_ADDR_DATA_LENGTH		(26)
#define FELIX_TEST_DG_DG_ADDR_DATA_DG_ADDR_DATA_DEFAULT		(0)
#define FELIX_TEST_DG_DG_ADDR_DATA_DG_ADDR_DATA_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_DATA_STRIDE_OFFSET		(0x0020)

/* FELIX_TEST_DG, DG_DATA_STRIDE, DG_DATA_STRIDE
*/
#define FELIX_TEST_DG_DG_DATA_STRIDE_DG_DATA_STRIDE_MASK		(0xFFFFFFC0)
#define FELIX_TEST_DG_DG_DATA_STRIDE_DG_DATA_STRIDE_LSBMASK		(0x03FFFFFF)
#define FELIX_TEST_DG_DG_DATA_STRIDE_DG_DATA_STRIDE_SHIFT		(6)
#define FELIX_TEST_DG_DG_DATA_STRIDE_DG_DATA_STRIDE_LENGTH		(26)
#define FELIX_TEST_DG_DG_DATA_STRIDE_DG_DATA_STRIDE_DEFAULT		(0)
#define FELIX_TEST_DG_DG_DATA_STRIDE_DG_DATA_STRIDE_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_FRAME_SIZE_OFFSET		(0x0024)

/* FELIX_TEST_DG, DG_FRAME_SIZE, DG_FRAME_WIDTH
*/
#define FELIX_TEST_DG_DG_FRAME_SIZE_DG_FRAME_WIDTH_MASK		(0x0000FFFF)
#define FELIX_TEST_DG_DG_FRAME_SIZE_DG_FRAME_WIDTH_LSBMASK		(0x0000FFFF)
#define FELIX_TEST_DG_DG_FRAME_SIZE_DG_FRAME_WIDTH_SHIFT		(0)
#define FELIX_TEST_DG_DG_FRAME_SIZE_DG_FRAME_WIDTH_LENGTH		(16)
#define FELIX_TEST_DG_DG_FRAME_SIZE_DG_FRAME_WIDTH_DEFAULT		(0)
#define FELIX_TEST_DG_DG_FRAME_SIZE_DG_FRAME_WIDTH_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_FRAME_SIZE, DG_FRAME_HEIGHT
*/
#define FELIX_TEST_DG_DG_FRAME_SIZE_DG_FRAME_HEIGHT_MASK		(0xFFFF0000)
#define FELIX_TEST_DG_DG_FRAME_SIZE_DG_FRAME_HEIGHT_LSBMASK		(0x0000FFFF)
#define FELIX_TEST_DG_DG_FRAME_SIZE_DG_FRAME_HEIGHT_SHIFT		(16)
#define FELIX_TEST_DG_DG_FRAME_SIZE_DG_FRAME_HEIGHT_LENGTH		(16)
#define FELIX_TEST_DG_DG_FRAME_SIZE_DG_FRAME_HEIGHT_DEFAULT		(0)
#define FELIX_TEST_DG_DG_FRAME_SIZE_DG_FRAME_HEIGHT_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_FRAME_BLANKING_OFFSET		(0x0028)

/* FELIX_TEST_DG, DG_FRAME_BLANKING, DG_VERTICAL_BLANKING
*/
#define FELIX_TEST_DG_DG_FRAME_BLANKING_DG_VERTICAL_BLANKING_MASK		(0x00001FFF)
#define FELIX_TEST_DG_DG_FRAME_BLANKING_DG_VERTICAL_BLANKING_LSBMASK		(0x00001FFF)
#define FELIX_TEST_DG_DG_FRAME_BLANKING_DG_VERTICAL_BLANKING_SHIFT		(0)
#define FELIX_TEST_DG_DG_FRAME_BLANKING_DG_VERTICAL_BLANKING_LENGTH		(13)
#define FELIX_TEST_DG_DG_FRAME_BLANKING_DG_VERTICAL_BLANKING_DEFAULT		(0)
#define FELIX_TEST_DG_DG_FRAME_BLANKING_DG_VERTICAL_BLANKING_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_FRAME_BLANKING, DG_HORIZONTAL_BLANKING
*/
#define FELIX_TEST_DG_DG_FRAME_BLANKING_DG_HORIZONTAL_BLANKING_MASK		(0x1FFF0000)
#define FELIX_TEST_DG_DG_FRAME_BLANKING_DG_HORIZONTAL_BLANKING_LSBMASK		(0x00001FFF)
#define FELIX_TEST_DG_DG_FRAME_BLANKING_DG_HORIZONTAL_BLANKING_SHIFT		(16)
#define FELIX_TEST_DG_DG_FRAME_BLANKING_DG_HORIZONTAL_BLANKING_LENGTH		(13)
#define FELIX_TEST_DG_DG_FRAME_BLANKING_DG_HORIZONTAL_BLANKING_DEFAULT		(0)
#define FELIX_TEST_DG_DG_FRAME_BLANKING_DG_HORIZONTAL_BLANKING_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_PIXEL_RATE_OFFSET		(0x002C)

/* FELIX_TEST_DG, DG_PIXEL_RATE, DG_PIXEL_CLK_DIV
*/
#define FELIX_TEST_DG_DG_PIXEL_RATE_DG_PIXEL_CLK_DIV_MASK		(0x00007F80)
#define FELIX_TEST_DG_DG_PIXEL_RATE_DG_PIXEL_CLK_DIV_LSBMASK		(0x000000FF)
#define FELIX_TEST_DG_DG_PIXEL_RATE_DG_PIXEL_CLK_DIV_SHIFT		(7)
#define FELIX_TEST_DG_DG_PIXEL_RATE_DG_PIXEL_CLK_DIV_LENGTH		(8)
#define FELIX_TEST_DG_DG_PIXEL_RATE_DG_PIXEL_CLK_DIV_DEFAULT		(0)
#define FELIX_TEST_DG_DG_PIXEL_RATE_DG_PIXEL_CLK_DIV_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_PIXEL_RATE, DG_PIXEL_CLK_MULT
*/
#define FELIX_TEST_DG_DG_PIXEL_RATE_DG_PIXEL_CLK_MULT_MASK		(0x0000007F)
#define FELIX_TEST_DG_DG_PIXEL_RATE_DG_PIXEL_CLK_MULT_LSBMASK		(0x0000007F)
#define FELIX_TEST_DG_DG_PIXEL_RATE_DG_PIXEL_CLK_MULT_SHIFT		(0)
#define FELIX_TEST_DG_DG_PIXEL_RATE_DG_PIXEL_CLK_MULT_LENGTH		(7)
#define FELIX_TEST_DG_DG_PIXEL_RATE_DG_PIXEL_CLK_MULT_DEFAULT		(0)
#define FELIX_TEST_DG_DG_PIXEL_RATE_DG_PIXEL_CLK_MULT_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_INTER_STATUS_OFFSET		(0x0030)

/* FELIX_TEST_DG, DG_INTER_STATUS, DG_INT_ERROR
When set indicates that a the frame could not be properly transmitted because not enough data could be read from MEMORY. A DG_RESET is required.
*/
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_ERROR_MASK		(0x00000004)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_ERROR_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_ERROR_SHIFT		(2)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_ERROR_LENGTH		(1)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_ERROR_DEFAULT		(0)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_ERROR_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_INTER_STATUS, DG_INT_END_OF_FRAME
When set indicates that a new frame has FINISHED to be transmitted.
*/
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_END_OF_FRAME_MASK		(0x00000002)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_END_OF_FRAME_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_END_OF_FRAME_SHIFT		(1)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_END_OF_FRAME_LENGTH		(1)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_END_OF_FRAME_DEFAULT		(0)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_END_OF_FRAME_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_INTER_STATUS, DG_INT_START_OF_FRAME
*/
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_START_OF_FRAME_MASK		(0x00000001)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_START_OF_FRAME_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_START_OF_FRAME_SHIFT		(0)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_START_OF_FRAME_LENGTH		(1)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_START_OF_FRAME_DEFAULT		(0)
#define FELIX_TEST_DG_DG_INTER_STATUS_DG_INT_START_OF_FRAME_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_INTER_ENABLE_OFFSET		(0x0034)

/* FELIX_TEST_DG, DG_INTER_ENABLE, DG_INT_ERROR_EN
*/
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_ERROR_EN_MASK		(0x00000004)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_ERROR_EN_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_ERROR_EN_SHIFT		(2)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_ERROR_EN_LENGTH		(1)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_ERROR_EN_DEFAULT		(0)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_ERROR_EN_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_INTER_ENABLE, DG_INT_END_OF_FRAME_EN
*/
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_END_OF_FRAME_EN_MASK		(0x00000002)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_END_OF_FRAME_EN_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_END_OF_FRAME_EN_SHIFT		(1)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_END_OF_FRAME_EN_LENGTH		(1)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_END_OF_FRAME_EN_DEFAULT		(0)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_END_OF_FRAME_EN_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_INTER_ENABLE, DG_INT_START_OF_FRAME_EN
*/
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_START_OF_FRAME_EN_MASK		(0x00000001)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_START_OF_FRAME_EN_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_START_OF_FRAME_EN_SHIFT		(0)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_START_OF_FRAME_EN_LENGTH		(1)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_START_OF_FRAME_EN_DEFAULT		(0)
#define FELIX_TEST_DG_DG_INTER_ENABLE_DG_INT_START_OF_FRAME_EN_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_INTER_CLEAR_OFFSET		(0x0038)

/* FELIX_TEST_DG, DG_INTER_CLEAR, DG_INT_ERROR_CL
*/
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_ERROR_CL_MASK		(0x00000004)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_ERROR_CL_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_ERROR_CL_SHIFT		(2)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_ERROR_CL_LENGTH		(1)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_ERROR_CL_DEFAULT		(0)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_ERROR_CL_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_INTER_CLEAR, DG_INT_END_OF_FRAME_CL
*/
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_END_OF_FRAME_CL_MASK		(0x00000002)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_END_OF_FRAME_CL_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_END_OF_FRAME_CL_SHIFT		(1)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_END_OF_FRAME_CL_LENGTH		(1)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_END_OF_FRAME_CL_DEFAULT		(0)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_END_OF_FRAME_CL_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_INTER_CLEAR, DG_INT_START_OF_FRAME_CL
*/
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_START_OF_FRAME_CL_MASK		(0x00000001)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_START_OF_FRAME_CL_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_START_OF_FRAME_CL_SHIFT		(0)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_START_OF_FRAME_CL_LENGTH		(1)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_START_OF_FRAME_CL_DEFAULT		(0)
#define FELIX_TEST_DG_DG_INTER_CLEAR_DG_INT_START_OF_FRAME_CL_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_OFFSET		(0x003C)

/* FELIX_TEST_DG, DG_MIPI_START_OF_DATA_TRANSMISSION, DG_TLPX
*/
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_TLPX_MASK		(0x000003FF)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_TLPX_LSBMASK		(0x000003FF)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_TLPX_SHIFT		(0)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_TLPX_LENGTH		(10)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_TLPX_DEFAULT		(31)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_TLPX_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_MIPI_START_OF_DATA_TRANSMISSION, DG_THS_PREPARE
*/
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_THS_PREPARE_MASK		(0x001FF800)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_THS_PREPARE_LSBMASK		(0x000003FF)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_THS_PREPARE_SHIFT		(11)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_THS_PREPARE_LENGTH		(10)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_THS_PREPARE_DEFAULT		(31)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_THS_PREPARE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_MIPI_START_OF_DATA_TRANSMISSION, DG_THS_ZERO
*/
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_THS_ZERO_MASK		(0xFFC00000)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_THS_ZERO_LSBMASK		(0x000003FF)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_THS_ZERO_SHIFT		(22)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_THS_ZERO_LENGTH		(10)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_THS_ZERO_DEFAULT		(63)
#define FELIX_TEST_DG_DG_MIPI_START_OF_DATA_TRANSMISSION_DG_THS_ZERO_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_MIPI_END_OF_DATA_TRANSMISSION_OFFSET		(0x0040)

/* FELIX_TEST_DG, DG_MIPI_END_OF_DATA_TRANSMISSION, DG_THS_TRAIL
*/
#define FELIX_TEST_DG_DG_MIPI_END_OF_DATA_TRANSMISSION_DG_THS_TRAIL_MASK		(0x000003FF)
#define FELIX_TEST_DG_DG_MIPI_END_OF_DATA_TRANSMISSION_DG_THS_TRAIL_LSBMASK		(0x000003FF)
#define FELIX_TEST_DG_DG_MIPI_END_OF_DATA_TRANSMISSION_DG_THS_TRAIL_SHIFT		(0)
#define FELIX_TEST_DG_DG_MIPI_END_OF_DATA_TRANSMISSION_DG_THS_TRAIL_LENGTH		(10)
#define FELIX_TEST_DG_DG_MIPI_END_OF_DATA_TRANSMISSION_DG_THS_TRAIL_DEFAULT		(47)
#define FELIX_TEST_DG_DG_MIPI_END_OF_DATA_TRANSMISSION_DG_THS_TRAIL_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_MIPI_END_OF_DATA_TRANSMISSION, DG_THS_EXIT
*/
#define FELIX_TEST_DG_DG_MIPI_END_OF_DATA_TRANSMISSION_DG_THS_EXIT_MASK		(0x03FF0000)
#define FELIX_TEST_DG_DG_MIPI_END_OF_DATA_TRANSMISSION_DG_THS_EXIT_LSBMASK		(0x000003FF)
#define FELIX_TEST_DG_DG_MIPI_END_OF_DATA_TRANSMISSION_DG_THS_EXIT_SHIFT		(16)
#define FELIX_TEST_DG_DG_MIPI_END_OF_DATA_TRANSMISSION_DG_THS_EXIT_LENGTH		(10)
#define FELIX_TEST_DG_DG_MIPI_END_OF_DATA_TRANSMISSION_DG_THS_EXIT_DEFAULT		(63)
#define FELIX_TEST_DG_DG_MIPI_END_OF_DATA_TRANSMISSION_DG_THS_EXIT_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_MIPI_START_OF_CLOCK_TRANSMISSION_OFFSET		(0x0044)

/* FELIX_TEST_DG, DG_MIPI_START_OF_CLOCK_TRANSMISSION, DG_TCLK_PREPARE
*/
#define FELIX_TEST_DG_DG_MIPI_START_OF_CLOCK_TRANSMISSION_DG_TCLK_PREPARE_MASK		(0x000003FF)
#define FELIX_TEST_DG_DG_MIPI_START_OF_CLOCK_TRANSMISSION_DG_TCLK_PREPARE_LSBMASK		(0x000003FF)
#define FELIX_TEST_DG_DG_MIPI_START_OF_CLOCK_TRANSMISSION_DG_TCLK_PREPARE_SHIFT		(0)
#define FELIX_TEST_DG_DG_MIPI_START_OF_CLOCK_TRANSMISSION_DG_TCLK_PREPARE_LENGTH		(10)
#define FELIX_TEST_DG_DG_MIPI_START_OF_CLOCK_TRANSMISSION_DG_TCLK_PREPARE_DEFAULT		(63)
#define FELIX_TEST_DG_DG_MIPI_START_OF_CLOCK_TRANSMISSION_DG_TCLK_PREPARE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_MIPI_START_OF_CLOCK_TRANSMISSION, DG_TCLK_ZERO
*/
#define FELIX_TEST_DG_DG_MIPI_START_OF_CLOCK_TRANSMISSION_DG_TCLK_ZERO_MASK		(0x03FF0000)
#define FELIX_TEST_DG_DG_MIPI_START_OF_CLOCK_TRANSMISSION_DG_TCLK_ZERO_LSBMASK		(0x000003FF)
#define FELIX_TEST_DG_DG_MIPI_START_OF_CLOCK_TRANSMISSION_DG_TCLK_ZERO_SHIFT		(16)
#define FELIX_TEST_DG_DG_MIPI_START_OF_CLOCK_TRANSMISSION_DG_TCLK_ZERO_LENGTH		(10)
#define FELIX_TEST_DG_DG_MIPI_START_OF_CLOCK_TRANSMISSION_DG_TCLK_ZERO_DEFAULT		(191)
#define FELIX_TEST_DG_DG_MIPI_START_OF_CLOCK_TRANSMISSION_DG_TCLK_ZERO_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_MIPI_END_OF_CLOCK_TRANSMISSION_OFFSET		(0x0048)

/* FELIX_TEST_DG, DG_MIPI_END_OF_CLOCK_TRANSMISSION, DG_TCLK_POST
*/
#define FELIX_TEST_DG_DG_MIPI_END_OF_CLOCK_TRANSMISSION_DG_TCLK_POST_MASK		(0x000003FF)
#define FELIX_TEST_DG_DG_MIPI_END_OF_CLOCK_TRANSMISSION_DG_TCLK_POST_LSBMASK		(0x000003FF)
#define FELIX_TEST_DG_DG_MIPI_END_OF_CLOCK_TRANSMISSION_DG_TCLK_POST_SHIFT		(0)
#define FELIX_TEST_DG_DG_MIPI_END_OF_CLOCK_TRANSMISSION_DG_TCLK_POST_LENGTH		(10)
#define FELIX_TEST_DG_DG_MIPI_END_OF_CLOCK_TRANSMISSION_DG_TCLK_POST_DEFAULT		(127)
#define FELIX_TEST_DG_DG_MIPI_END_OF_CLOCK_TRANSMISSION_DG_TCLK_POST_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, DG_MIPI_END_OF_CLOCK_TRANSMISSION, DG_TCLK_TRAIL
*/
#define FELIX_TEST_DG_DG_MIPI_END_OF_CLOCK_TRANSMISSION_DG_TCLK_TRAIL_MASK		(0x03FF0000)
#define FELIX_TEST_DG_DG_MIPI_END_OF_CLOCK_TRANSMISSION_DG_TCLK_TRAIL_LSBMASK		(0x000003FF)
#define FELIX_TEST_DG_DG_MIPI_END_OF_CLOCK_TRANSMISSION_DG_TCLK_TRAIL_SHIFT		(16)
#define FELIX_TEST_DG_DG_MIPI_END_OF_CLOCK_TRANSMISSION_DG_TCLK_TRAIL_LENGTH		(10)
#define FELIX_TEST_DG_DG_MIPI_END_OF_CLOCK_TRANSMISSION_DG_TCLK_TRAIL_DEFAULT		(47)
#define FELIX_TEST_DG_DG_MIPI_END_OF_CLOCK_TRANSMISSION_DG_TCLK_TRAIL_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_PARALLEL_CTRL_OFFSET		(0x004C)

/* FELIX_TEST_DG, PARALLEL_CTRL, PARALLEL_V_SYNC_POLARITY
*/
#define FELIX_TEST_DG_PARALLEL_CTRL_PARALLEL_V_SYNC_POLARITY_MASK		(0x00000002)
#define FELIX_TEST_DG_PARALLEL_CTRL_PARALLEL_V_SYNC_POLARITY_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_PARALLEL_CTRL_PARALLEL_V_SYNC_POLARITY_SHIFT		(1)
#define FELIX_TEST_DG_PARALLEL_CTRL_PARALLEL_V_SYNC_POLARITY_LENGTH		(1)
#define FELIX_TEST_DG_PARALLEL_CTRL_PARALLEL_V_SYNC_POLARITY_DEFAULT		(0)
#define FELIX_TEST_DG_PARALLEL_CTRL_PARALLEL_V_SYNC_POLARITY_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_TEST_DG, PARALLEL_CTRL, PARALLEL_H_SYNC_POLARITY
*/
#define FELIX_TEST_DG_PARALLEL_CTRL_PARALLEL_H_SYNC_POLARITY_MASK		(0x00000001)
#define FELIX_TEST_DG_PARALLEL_CTRL_PARALLEL_H_SYNC_POLARITY_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_PARALLEL_CTRL_PARALLEL_H_SYNC_POLARITY_SHIFT		(0)
#define FELIX_TEST_DG_PARALLEL_CTRL_PARALLEL_H_SYNC_POLARITY_LENGTH		(1)
#define FELIX_TEST_DG_PARALLEL_CTRL_PARALLEL_H_SYNC_POLARITY_DEFAULT		(0)
#define FELIX_TEST_DG_PARALLEL_CTRL_PARALLEL_H_SYNC_POLARITY_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_MIPI_CTRL_OFFSET		(0x0050)

/* FELIX_TEST_DG, MIPI_CTRL, DG_MIPI_LANES
Indicates how many mipi lanes -1 are active.
*/
#define FELIX_TEST_DG_MIPI_CTRL_DG_MIPI_LANES_MASK		(0x00000003)
#define FELIX_TEST_DG_MIPI_CTRL_DG_MIPI_LANES_LSBMASK		(0x00000003)
#define FELIX_TEST_DG_MIPI_CTRL_DG_MIPI_LANES_SHIFT		(0)
#define FELIX_TEST_DG_MIPI_CTRL_DG_MIPI_LANES_LENGTH		(2)
#define FELIX_TEST_DG_MIPI_CTRL_DG_MIPI_LANES_DEFAULT		(0)
#define FELIX_TEST_DG_MIPI_CTRL_DG_MIPI_LANES_SIGNED_FIELD	(IMG_FALSE)

enum FELIX_TEST_DG_MIPI_CTRL_DG_MIPI_LANES_ENUM {
	/**
	 * @brief 4 Lanes transmitting data
	 */
	FELIX_TEST_DG_DG_MIPI_LANES_FOUR_ACTIVE = 0x3,
	/**
	 * @brief Not Supported
	 */
	FELIX_TEST_DG_DG_MIPI_LANES_RESERVED = 0x2,
	/**
	 * @brief 2 Lanes transmitting data
	 */
	FELIX_TEST_DG_DG_MIPI_LANES_TWO_ACTIVE = 0x1,
	/**
	 * @brief 1 Lane transmitting data
	 */
	FELIX_TEST_DG_DG_MIPI_LANES_ONE_ACTIVE = 0x0,
};

#define FELIX_TEST_DG_DG_READ_REQ_CRC_OFFSET		(0x0054)

/* FELIX_TEST_DG, DG_READ_REQ_CRC, DG_READ_REQ_CRC
CRC of the read requests to memory. (req_addr)
*/
#define FELIX_TEST_DG_DG_READ_REQ_CRC_DG_READ_REQ_CRC_MASK		(0xFFFFFFFF)
#define FELIX_TEST_DG_DG_READ_REQ_CRC_DG_READ_REQ_CRC_LSBMASK		(0xFFFFFFFF)
#define FELIX_TEST_DG_DG_READ_REQ_CRC_DG_READ_REQ_CRC_SHIFT		(0)
#define FELIX_TEST_DG_DG_READ_REQ_CRC_DG_READ_REQ_CRC_LENGTH		(32)
#define FELIX_TEST_DG_DG_READ_REQ_CRC_DG_READ_REQ_CRC_DEFAULT		(0)
#define FELIX_TEST_DG_DG_READ_REQ_CRC_DG_READ_REQ_CRC_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_READ_RESPONSE_CRC_OFFSET		(0x0058)

/* FELIX_TEST_DG, DG_READ_RESPONSE_CRC, DG_READ_RESPONSE_CRC
CRC of the read response from memory. (read_data)
*/
#define FELIX_TEST_DG_DG_READ_RESPONSE_CRC_DG_READ_RESPONSE_CRC_MASK		(0xFFFFFFFF)
#define FELIX_TEST_DG_DG_READ_RESPONSE_CRC_DG_READ_RESPONSE_CRC_LSBMASK		(0xFFFFFFFF)
#define FELIX_TEST_DG_DG_READ_RESPONSE_CRC_DG_READ_RESPONSE_CRC_SHIFT		(0)
#define FELIX_TEST_DG_DG_READ_RESPONSE_CRC_DG_READ_RESPONSE_CRC_LENGTH		(32)
#define FELIX_TEST_DG_DG_READ_RESPONSE_CRC_DG_READ_RESPONSE_CRC_DEFAULT		(0)
#define FELIX_TEST_DG_DG_READ_RESPONSE_CRC_DG_READ_RESPONSE_CRC_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_PWR_CTRL_OFFSET		(0x0060)

/* FELIX_TEST_DG, DG_PWR_CTRL, CLOCK_GATECTRL_DG
*/
#define FELIX_TEST_DG_DG_PWR_CTRL_CLOCK_GATECTRL_DG_MASK		(0x00000003)
#define FELIX_TEST_DG_DG_PWR_CTRL_CLOCK_GATECTRL_DG_LSBMASK		(0x00000003)
#define FELIX_TEST_DG_DG_PWR_CTRL_CLOCK_GATECTRL_DG_SHIFT		(0)
#define FELIX_TEST_DG_DG_PWR_CTRL_CLOCK_GATECTRL_DG_LENGTH		(2)
#define FELIX_TEST_DG_DG_PWR_CTRL_CLOCK_GATECTRL_DG_DEFAULT		(2)
#define FELIX_TEST_DG_DG_PWR_CTRL_CLOCK_GATECTRL_DG_SIGNED_FIELD	(IMG_FALSE)

enum FELIX_TEST_DG_DG_PWR_CTRL_CLOCK_GATECTRL_DG_ENUM {
	/**
	 * @brief Auto clock gating (Clocks controlled by HW)
	 */
	FELIX_TEST_DG_CLOCK_GATECTRL_DG_AUTO_CLOCK_GATING = 0x2,
	/**
	 * @brief Clock Forced Enabled
	 */
	FELIX_TEST_DG_CLOCK_GATECTRL_DG_FORCE_CLOCK_ENABLE = 0x1,
	/**
	 * @brief clock gated (Clocks disabled)
	 */
	FELIX_TEST_DG_CLOCK_GATECTRL_DG_FORCE_CLOCK_GATE = 0x0,
};

#define FELIX_TEST_DG_DG_PWR_STATUS_OFFSET		(0x0064)

/* FELIX_TEST_DG, DG_PWR_STATUS, CLOCK_GATESTATUS_DG
*/
#define FELIX_TEST_DG_DG_PWR_STATUS_CLOCK_GATESTATUS_DG_MASK		(0x00000001)
#define FELIX_TEST_DG_DG_PWR_STATUS_CLOCK_GATESTATUS_DG_LSBMASK		(0x00000001)
#define FELIX_TEST_DG_DG_PWR_STATUS_CLOCK_GATESTATUS_DG_SHIFT		(0)
#define FELIX_TEST_DG_DG_PWR_STATUS_CLOCK_GATESTATUS_DG_LENGTH		(1)
#define FELIX_TEST_DG_DG_PWR_STATUS_CLOCK_GATESTATUS_DG_DEFAULT		(0)
#define FELIX_TEST_DG_DG_PWR_STATUS_CLOCK_GATESTATUS_DG_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_TEST_DG_DG_STALLING_OFFSET		(0x0068)

/* FELIX_TEST_DG, DG_STALLING, DG_STALLING
Setting this greater than 0 will add 2^(VALUE) clock cycles between requests from the data generator to the MMU. The default value is external memory bus divided by requestor bus width.
*/
#define FELIX_TEST_DG_DG_STALLING_DG_STALLING_MASK		(0x0000000F)
#define FELIX_TEST_DG_DG_STALLING_DG_STALLING_LSBMASK		(0x0000000F)
#define FELIX_TEST_DG_DG_STALLING_DG_STALLING_SHIFT		(0)
#define FELIX_TEST_DG_DG_STALLING_DG_STALLING_LENGTH		(4)
#define FELIX_TEST_DG_DG_STALLING_DG_STALLING_DEFAULT		(0)
#define FELIX_TEST_DG_DG_STALLING_DG_STALLING_SIGNED_FIELD	(IMG_FALSE)

/*
 * size of the memory structure FELIX_TEST_DG
 * Computed from DG_STALLING offset and size
 */
#define FELIX_TEST_DG_BYTE_SIZE		(0x006C)


#ifdef __cplusplus
}
#endif

#endif /* __EXT_DATA_GENERATOR_H__ */
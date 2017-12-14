/*
 * A V4L2 driver for Gcore GC0308 cameras.
 *
 * Copyright 2006 One Laptop Per Child Association, Inc.  Written
 * by Jonathan Corbet with substantial inspiration from Mark
 * McClelland's ovcamchip code.
 *
 * Copyright 2006-7 Jonathan Corbet <corbet@lwn.net>
 *
 * This file may be distributed under the terms of the GNU General
 * Public License, version 2.
 */


 #include <linux/init.h>
 #include <linux/module.h>
 #include <linux/slab.h>
 #include <linux/i2c.h>
 #include <linux/delay.h>
 #include <linux/videodev2.h>
 #include <media/v4l2-device.h>
 #include <media/v4l2-chip-ident.h>
 #include <media/v4l2-ctrls.h>
 #include <media/v4l2-mediabus.h>

#define SENSOR_MAX_HEIGHT   1600
#define SENSOR_MAX_WIDTH    1200

#define SENSOR_MIN_WIDTH    640
#define SENSOR_MIN_HEIGHT   480

struct reginfo {
	unsigned char reg;
	unsigned char val;
};

struct gc2035_win_size {
	int width;
	int height;
	struct reginfo *regs;
};

struct gc2035_info {
	struct v4l2_subdev sd;
	struct media_pad pad;
	struct v4l2_ctrl_handler ctrls;
	struct i2c_client *client;
	enum v4l2_mbus_type bus_type;
	struct mutex		lock;

};



static struct reginfo sensor_init[] = {
	{0xfe, 0x80},
	{0xfe, 0x80},
	{0xfe, 0x80},
	{0xfe, 0x80},
	{0xfc, 0x06},
	{0xf2, 0x00},
	{0xf3, 0x00},
	{0xf4, 0x00},
	{0xf5, 0x00},
	{0xf9, 0xfe}, //[0] pll enable
	{0xfa, 0x00},
	{0xf6, 0x00},
	{0xf7, 0x15}, //pll enable
	{0xf8, 0x85},
	{0xfe, 0x00},
	{0x82, 0x00},
	{0xb3, 0x60},
	{0xb4, 0x40},
	{0xb5, 0x60},
	{0x03, 0x02},
	{0x04, 0xa8},

      //measure window
	{0xfe, 0x00},
	{0xec, 0x06},//04
	{0xed, 0x06},//04
	{0xee, 0x62},//60
	{0xef, 0x92},//90

	{0x0a, 0x00}, //row start
	{0x0c, 0x00}, //col start

	{0x0d, 0x04},
	{0x0e, 0xc0},
	{0x0f, 0x06}, //Window setting
	{0x10, 0x58},//

	{0x17, 0x14}, //[0]mirror [1]flip
	{0x18, 0x0e}, //0a 2012.10.26
	{0x19, 0x0c}, //AD pipe number

	{0x1a, 0x01}, //CISCTL mode4
	{0x1b, 0x8b},
	{0x1c, 0x05},//add by lanking 20130403
	{0x1e, 0x88}, //analog mode1 [7] tx-high en
	{0x1f, 0x08}, //[3] tx-low en//

	{0x20, 0x05}, //[0]adclk mode  [1]rowclk_MODE [2]rsthigh_en
	{0x21, 0x0f}, //[3]txlow_en
	{0x22, 0xf0}, //[3:0]vref
	{0x23, 0xc3}, //f3//ADC_r
	{0x24, 0x1f}, //pad drive

	//AWB_gray
	{0xfe, 0x01},
	{0x4f, 0x00},
	{0x4d, 0x32}, // 30
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4d, 0x42}, // 40
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4d, 0x52}, // 50
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4d, 0x62}, // 60
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4d, 0x72}, // 70
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4d, 0x82}, // 80
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4d, 0x92}, // 90
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4e, 0x04},
	{0x4f, 0x01},
	{0x50, 0x88},
	{0xfe, 0x00},
	{0x82, 0xfe},

	///////awb start ////////////////
	{0xfe, 0x01},
	{0x50, 0x88},//c0//[6]green mode
	{0x52, 0x40},
	{0x54, 0x60},
	{0x56, 0x06},
	{0x57, 0x20},//pre adjust
	{0x58, 0x01},
	{0x5b, 0x02},//AWB_gain_delta
	{0x61, 0xaa},//R/G stand
	{0x62, 0xaa},//R/G stand
	{0x71, 0x00},
	{0x74, 0x10},//AWB_C_max
	{0x77, 0x08},//AWB_p2_x
	{0x78, 0xfd},//AWB_p2_y
	{0x86, 0x30},
	{0x87, 0x00},
	{0x88, 0x04},//[1]dark mode
	{0x8a, 0xc0},//awb move mode
	{0x89, 0x75},
	{0x84, 0x08},//auto_window
	{0x8b, 0x00},//awb compare luma
	{0x8d, 0x70},//awb gain limit R
	{0x8e, 0x70},//G
	{0x8f, 0xf4},//B
  /////////awb end /////////////

	//AEC
	{0xfe, 0x01},
	{0x11, 0x20},//AEC_out_slope, 0x
	{0x1f, 0xc0},//max_post_gain
	{0x20, 0x60},//max_pre_gain
	{0x47, 0x30},//AEC_outdoor_th
	{0x0b, 0x10},//
	{0x13, 0x75},//y_target


	{0xfe, 0x00},
	{0x05, 0x01},
	{0x06, 0x0d},
	{0x07, 0x00},
	{0x08, 0x14},
	{0xfe, 0x01},
	{0x27, 0x00},
	{0x28, 0xa0},
	{0x29, 0x04},//  level 0 13
	{0x2a, 0x60},
	{0x2b, 0x04},//  level 1 13
	{0x2c, 0x60},
	{0x2d, 0x04},//  level 2 13
	{0x2e, 0x60},
	{0x2f, 0x07},//  level 3 8
	{0x30, 0x80},
	{0xfe, 0x00},//
	{0xb6, 0x03},//AEC enable
	{0xfe, 0x00},

	/////////BLK//////
	{0x3f, 0x00},//prc close
	{0x40, 0x77},//
	{0x42, 0x7f},
	{0x43, 0x30},
	{0x5c, 0x08},
	{0x5e, 0x20},
	{0x5f, 0x20},
	{0x60, 0x20},
	{0x61, 0x20},
	{0x62, 0x20},
	{0x63, 0x20},
	{0x64, 0x20},
	{0x65, 0x20},

	///block////////////
	{0x80, 0xff},
	{0x81, 0x26},//38 //skin_Y 8c_debug
	{0x87, 0x90},//[7]middle gamma
	{0x84, 0x02},//output put foramat
	{0x86, 0x06},//02 //sync plority  lanking
	{0x8b, 0xbc},
	{0xb0, 0x80},//globle gain
	{0xc0, 0x40},//Yuv bypass

	//////lsc/////////////
	{0xfe, 0x01},
	{0xc2, 0x38},
	{0xc3, 0x25},
	{0xc4, 0x21},
	{0xc8, 0x19},
	{0xc9, 0x12},
	{0xca, 0x0e},
	{0xbc, 0x43},
	{0xbd, 0x18},
	{0xbe, 0x1b},
	{0xb6, 0x40},
	{0xb7, 0x2e},
	{0xb8, 0x26},
	{0xc5, 0x05},
	{0xc6, 0x03},
	{0xc7, 0x04},
	{0xcb, 0x00},
	{0xcc, 0x00},
	{0xcd, 0x00},
	{0xbf, 0x14},
	{0xc0, 0x22},
	{0xc1, 0x1b},
	{0xb9, 0x00},
	{0xba, 0x05},
	{0xbb, 0x05},
	{0xaa, 0x35},
	{0xab, 0x33},
	{0xac, 0x33},
	{0xad, 0x25},
	{0xae, 0x22},
	{0xaf, 0x27},
	{0xb0, 0x1d},
	{0xb1, 0x20},
	{0xb2, 0x22},
	{0xb3, 0x14},
	{0xb4, 0x15},
	{0xb5, 0x16},
	{0xd0, 0x00},
	{0xd2, 0x07},
	{0xd3, 0x08},
	{0xd8, 0x00},
	{0xda, 0x13},
	{0xdb, 0x17},
	{0xdc, 0x00},
	{0xde, 0x0a},
	{0xdf, 0x08},
	{0xd4, 0x00},
	{0xd6, 0x00},
	{0xd7, 0x0c},
	{0xa4, 0x00},
	{0xa5, 0x00},
	{0xa6, 0x00},
	{0xa7, 0x00},
	{0xa8, 0x00},
	{0xa9, 0x00},
	{0xa1, 0x80},
	{0xa2, 0x80},

	//////////cc//////////////
	{0xfe, 0x02},
	{0xc0, 0x01},
	{0xc1, 0x40},//Green_cc for d
	{0xc2, 0xfc},
	{0xc3, 0x05},
	{0xc4, 0xec},
	{0xc5, 0x42},
	{0xc6, 0xf8},
	{0xc7, 0x40},//for cwf
	{0xc8, 0xf8},
	{0xc9, 0x06},
	{0xca, 0xfd},
	{0xcb, 0x3e},
	{0xcc, 0xf3},
	{0xcd, 0x36},//for A
	{0xce, 0xf6},
	{0xcf, 0x04},
	{0xe3, 0x0c},
	{0xe4, 0x44},
	{0xe5, 0xe5},
	{0xfe, 0x00},

	///==========asde
	{0xfe, 0x01},
	{0x21, 0xbf},
	{0xfe, 0x02},
	{0xa4, 0x00},
	{0xa5, 0x40},//lsc_th
	{0xa2, 0xa0},//lsc_dec_slope
	{0xa6, 0x80},//dd_th
	{0xa7, 0x80},//ot_th
	{0xab, 0x31},
	{0xa9, 0x6f},
	{0xb0, 0x99},//edge effect slope low
	{0xb1, 0x34},//edge effect slope low
	{0xb3, 0x80},//saturation dec slope
	{0xde, 0xb6},
	{0x38, 0x0f},
	{0x39, 0x60},
	{0xfe, 0x00},
	{0x81, 0x26},
	{0xfe, 0x02},
	{0x83, 0x00},
	{0x84, 0x45},
	////////////YCP//////////
	{0xd1, 0x38},//saturation_cb
	{0xd2, 0x38},//saturation_Cr
	{0xd3, 0x40},//contrast
	{0xd4, 0x80},//contrast center
	{0xd5, 0x00},//luma_offset
	{0xdc, 0x30},
	{0xdd, 0xb8},//edge_sa_g,b
	{0xfe, 0x00},
	//////////dndd///////////
	{0xfe, 0x02},
	{0x88, 0x15},//dn_b_base
	{0x8c, 0xf6},//[2]b_in_dark_inc
	{0x89, 0x03},//dn_c_weight
	//////////EE ///////////
	{0xfe, 0x02},
	{0x90, 0x6c},// EEINTP mode1
	{0x97, 0x45},// edge effect
	////==============RGB Gamma ////
	{0xfe, 0x02},
	{0x15, 0x0a},
	{0x16, 0x12},
	{0x17, 0x19},
	{0x18, 0x1f},
	{0x19, 0x2c},
	{0x1a, 0x38},
	{0x1b, 0x42},
	{0x1c, 0x4e},
	{0x1d, 0x63},
	{0x1e, 0x76},
	{0x1f, 0x87},
	{0x20, 0x96},
	{0x21, 0xa2},
	{0x22, 0xb8},
	{0x23, 0xca},
	{0x24, 0xd8},
	{0x25, 0xe3},
	{0x26, 0xf0},
	{0x27, 0xf8},
	{0x28, 0xfd},
	{0x29, 0xff},
	       //// small  RGB gamma////
	/*
	{0xfe, 0x02},
	{0x15, 0x0b},
	{0x16, 0x0e},
	{0x17, 0x10},
	{0x18, 0x12},
	{0x19, 0x19},
	{0x1a, 0x21},
	{0x1b, 0x29},
	{0x1c, 0x31},
	{0x1d, 0x41},
	{0x1e, 0x50},
	{0x1f, 0x5f},
	{0x20, 0x6d},
	{0x21, 0x79},
	{0x22, 0x91},
	{0x23, 0xa5},
	{0x24, 0xb9},
	{0x25, 0xc9},
	{0x26, 0xe1},
	{0x27, 0xee},
	{0x28, 0xf7},
	{0x29, 0xff},
	*/

	///=================y gamma
	{0xfe, 0x02},
	{0x2b, 0x00},
	{0x2c, 0x04},
	{0x2d, 0x09},
	{0x2e, 0x18},
	{0x2f, 0x27},
	{0x30, 0x37},
	{0x31, 0x49},
	{0x32, 0x5c},
	{0x33, 0x7e},
	{0x34, 0xa0},
	{0x35, 0xc0},
	{0x36, 0xe0},
	{0x37, 0xff},

	//AWB clear
	{0xfe, 0x01},
	{0x4f, 0x00},
	{0x4d, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4d, 0x10}, // 10
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4d, 0x20}, // 20
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4d, 0x30},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00}, // 30
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4d, 0x40}, // 40
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4d, 0x50}, // 50
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4d, 0x60}, // 60
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4d, 0x70}, // 70
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4d, 0x80}, // 80
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4d, 0x90}, // 90
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4d, 0xa0}, // a0
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4d, 0xb0}, // b0
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4d, 0xc0}, // c0
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4d, 0xd0}, // d0
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4e, 0x00},
	{0x4f, 0x01},
	/////// awb value////////
	{0xfe, 0x01},
	{0x4f, 0x00},
	{0x4d, 0x30},
	{0x4e, 0x00},
	{0x4e, 0x80},
	{0x4e, 0x80},
	{0x4e, 0x02},
	{0x4e, 0x02},
	{0x4d, 0x40},
	{0x4e, 0x00},
	{0x4e, 0x80},
	{0x4e, 0x80},
	{0x4e, 0x02},
	{0x4e, 0x02},
	{0x4e, 0x02},
	{0x4d, 0x53},
	{0x4e, 0x08},
	{0x4e, 0x04},
	{0x4d, 0x62},
	{0x4e, 0x10},
	{0x4d, 0x72},
	{0x4e, 0x20},
	{0x4f, 0x01},

	/////1600x1200size//
	{0xfe, 0x00},//
	{0x90, 0x01}, ////crop enable
	{0x95, 0x04},  ////1600x1200
	{0x96, 0xb0},
	{0x97, 0x06},
	{0x98, 0x40},

	{0xfe, 0x03},
	{0x17, 0x00}, //widv
	{0x40, 0x40},  //00
	{0x41, 0x02}, // Pclk_polarity
	{0x42, 0x40},
	{0x43, 0x06}, //output buf width

	////output DVP/////
	{0xfe, 0x00},
	{0x82, 0xfe},
	{0xf2, 0x70},
	{0xf3, 0xff},
	{0xf4, 0x00},
	{0xf5, 0x30},

	{0x00, 0x00}
};


static struct reginfo sensor_vga[] = {
	{0xfe, 0x00},
	{0xfa, 0x00},
	{0xc8, 0x00},

	{0x99, 0x55},// 2/5 subsample
	{0x9a, 0x06},
	{0x9b, 0x02},
	{0x9c, 0x00},
	{0x9d, 0x00},
	{0x9e, 0x00},
	{0x9f, 0x02},
	{0xa0, 0x00},
	{0xa1, 0x00},
	{0xa2, 0x00},

	{0x90, 0x01},
	{0x95, 0x01},//480
	{0x96, 0xe0},
	{0x97, 0x02},//640
	{0x98, 0x80},

	{0x00, 0x00},
};

static struct reginfo sensor_svga[] = {
	{0xfe, 0x00},
	{0xfa, 0x00},
	{0xc8, 0x00},// close scaler

	{0x99, 0x22},// 1/2 subsample
	{0x9a, 0x07},
	{0x9b, 0x00},
	{0x9c, 0x00},
	{0x9d, 0x00},
	{0x9e, 0x00},
	{0x9f, 0x00},
	{0xa0, 0x00},
	{0xa1, 0x00},
	{0xa2, 0x00},

	{0x90, 0x01},
	{0x95, 0x02},//600
	{0x96, 0x58},
	{0x97, 0x03},//800
	{0x98, 0x20},

	{0x00, 0x00},
};

static struct reginfo sensor_xga[] = {
	{0xfe, 0x00},
	{0xfa, 0x00},
	{0xc8, 0x00},// close scaler

	{0x99, 0x33},// 2/3 subsample
	{0x9a, 0x00},
	{0x9b, 0x02},
	{0x9c, 0x00},
	{0x9d, 0x00},
	{0x9e, 0x00},
	{0x9f, 0x02},
	{0xa0, 0x00},
	{0xa1, 0x00},
	{0xa2, 0x00},

	{0x90, 0x01},
	{0x95, 0x03},//768
	{0x96, 0x00},
	{0x97, 0x04},//1024
	{0x98, 0x00},

	{0x00, 0x00},
};


static struct reginfo sensor_uxga[] = {

	{0xfe, 0x00},
	{0xc8, 0x00},
	{0xfa, 0x11},

	{0x99, 0x11},// disable sambsample
	{0x9a, 0x06},
	{0x9b, 0x00},
	{0x9c, 0x00},
	{0x9d, 0x00},
	{0x9e, 0x00},
	{0x9f, 0x00},
	{0xa0, 0x00},
	{0xa1, 0x00},
	{0xa2, 0x00},

	{0x90, 0x01},
	{0x95, 0x04},//1200
	{0x96, 0xb0},
	{0x97, 0x06},//1600
	{0x98, 0x40},

	{0x00, 0x00},
};

static  struct reginfo  ev_neg4_regs[] = {
	{0xfe, 0x01},
	{0x13, 0x40},
	{0xfe, 0x02},
	{0xd5, 0xc0},
	{0xfe, 0x00},
	{0x00, 0x00},
};
static  struct reginfo  ev_neg3_regs[] = {
	{0xfe, 0x01},
	{0x13, 0x50},
	{0xfe, 0x02},
	{0xd5, 0xd0},
	{0xfe, 0x00},
	{0x00, 0x00},
};
static  struct reginfo  ev_neg2_regs[] = {
	{0xfe, 0x01},
	{0x13, 0x60},
	{0xfe, 0x02},
	{0xd5, 0xe0},
	{0xfe, 0x00},
	{0x00, 0x00},
};
static  struct reginfo  ev_neg1_regs[] = {
	{0xfe, 0x01},
	{0x13, 0x70},
	{0xfe, 0x02},
	{0xd5, 0xf0},
	{0xfe, 0x00},
	{0x00, 0x00},
};

static  struct reginfo  ev_zero_regs[] = {
	{0xfe, 0x01},
	{0x13, 0x78}, //
	{0xfe, 0x02},
	{0xd5, 0x00},
	{0xfe, 0x00},
	{0x00, 0x00},
};

static  struct reginfo  ev_pos1_regs[] = {
	{0xfe, 0x01},
	{0x13, 0x98},
	{0xfe, 0x02},
	{0xd5, 0x10},
	{0xfe, 0x00},
	{0x00, 0x00},
};
static  struct reginfo  ev_pos2_regs[] = {
	{0xfe, 0x01},
	{0x13, 0xb0},
	{0xfe, 0x02},
	{0xd5, 0x20},
	{0xfe, 0x00},
	{0x00, 0x00},
};

static  struct reginfo  ev_pos3_regs[] = {
	{0xfe, 0x01},
	{0x13, 0xc0},
	{0xfe, 0x02},
	{0xd5, 0x30},
	{0xfe, 0x00},
	{0x00, 0x00},
};

static  struct reginfo  ev_pos4_regs[] = {
	{0xfe, 0x01},
	{0x13, 0xd0},
	{0xfe, 0x02},
	{0xd5, 0x50},
	{0xfe, 0x00},
	{0x00, 0x00},
};

static  struct reginfo  wb_auto_regs[] = {
	{0xfe, 0x00},
	{0xb3, 0x60},
	{0xb4, 0x40},
	{0xb5, 0x60},
	{0x82, 0xfe},
	{0x00, 0x00},
};

static  struct reginfo  wb_incandescent_regs[] = {
	{0xfe, 0x00},
	{0x82, 0xfc},
	{0xb3, 0x50},
	{0xb4, 0x40},
	{0xb5, 0xa8},
	{0x00, 0x00},
};

static  struct reginfo  wb_flourscent_regs[] = {
	{0xfe, 0x00},
	{0x82, 0xfc},
	{0xb3, 0x5c},
	{0xb4, 0x40},
	{0xb5, 0x5c},
	{0x00, 0x00},
};
static  struct reginfo  wb_daylight_regs[] = {
	{0xfe, 0x00},
	{0x82, 0xfc},
	{0xb3, 0x54},
	{0xb4, 0x40},
	{0xb5, 0x54},
	{0x00, 0x00},
};

static  struct reginfo  wb_cloudy_regs[] = {
	{0xfe, 0x00},
	{0x82, 0xfc},
	{0xb3, 0x68},
	{0xb4, 0x50},
	{0xb5, 0x50},
	{0x00, 0x00},
};

static  struct reginfo  scence_night60hz_regs[] = {
	{0xfe, 0x01},
	{0x13, 0xb0},
	{0xfe, 0x00},//AWB
	{0xb3, 0x60},
	{0xb4, 0x40},
	{0xb5, 0x60},
	{0x82, 0xfe},
	{0xfe, 0x02},
	{0xd5, 0x10},
	{0xd1, 0x38},
	{0xd2, 0x38},
	{0x89, 0x03},
	{0x00, 0x00},
};


static  struct reginfo  scence_auto_regs[] = {
	{0xfe, 0x01},
	{0x13, 0x78}, //zero ae
	{0xfe, 0x02},
	{0xd5, 0x00},//luma offset
	{0xd1, 0x38},
	{0xd2, 0x38},
	{0x89, 0x03},
	{0xfe, 0x00},//AWB
	{0xb3, 0x60},
	{0xb4, 0x40},
	{0xb5, 0x60},
	{0x82, 0xfe},
	{0x00, 0x00},
};


static  struct reginfo  scence_sunset60hz_regs[] = {
	{0xfe, 0x00},
	{0x82, 0xfc},
	{0xb3, 0x50},
	{0xb4, 0x40},
	{0xb5, 0xa8},
	{0xfe, 0x01},
	{0x13, 0x78}, //zero ae
	{0xfe, 0x02},
	{0xd5, 0x00},
	{0xd1, 0x38},
	{0xd2, 0x38},
	{0x89, 0x03},
	{0xfe, 0x00},
	{0x00, 0x00}

};

static struct reginfo scence_party_indoor_regs [] = {
	{0xfe, 0x00},
	{0x82, 0xfe},//awb
	{0xb3, 0x60},
	{0xb4, 0x40},
	{0xb5, 0x60},
	{0xfe, 0x01},
	{0x13, 0xa0},
	{0xfe, 0x02},
	{0xd1, 0x42},
	{0xd2, 0x42},
	{0xd5, 0x00},//offset
	{0x89, 0x03},
	{0x00, 0x00}
};

static struct reginfo scence_sports_regs [] = {
	{0xfe, 0x00},//AWB
	{0x82, 0xfe},
	{0xb3, 0x60},
	{0xb4, 0x40},
	{0xb5, 0x60},
	{0xfe, 0x01},
	{0x13, 0x78}, //zero ae
	{0xfe, 0x02},
	{0xd5, 0x00},//luma offset
	{0xd1, 0x38},
	{0xd2, 0x38},
	{0x89, 0x01},
	{0x00, 0x00},
};

static  struct reginfo  colorfx_none_regs[] = {
	{0xfe, 0x00},
	{0x83, 0xe0},
	{0x00, 0x00},
};
static  struct reginfo  colorfx_mono_regs[] = {
	{0xfe, 0x00},
	{0x83, 0x12},
	{0x00, 0x00},
};
static  struct reginfo  colorfx_negative_regs[] = {
	{0xfe, 0x00},
	{0x83, 0x01},
	{0x00, 0x00},
};

static  struct reginfo  colorfx_sepiagreen_regs[] = {
	{0xfe, 0x00},
	{0x83, 0x52},
	{0x00, 0x00},
};

static  struct reginfo  colorfx_sepiablue_regs[] = {
	{0xfe, 0x00},
	{0x83, 0x62},
	{0x00, 0x00},
};

static  struct reginfo  colorfx_sepia_regs[] = {
	{0xfe, 0x00},
	{0x83, 0x82},
	{0x00, 0x00},
};

static struct reginfo antibanding_50hz_regs[] = {
	{0xfe, 0x00},
	{0x05, 0x01},
	{0x06, 0x0d},
	{0x07, 0x00},
	{0x08, 0x14},
	{0xfe, 0x01},
	{0x27, 0x00},
	{0x28, 0xa0},
	{0x29, 0x04},//  level 0 13
	{0x2a, 0x60},
	{0x2b, 0x04},//  level 1 13
	{0x2c, 0x60},
	{0x2d, 0x04},//  level 2 13
	{0x2e, 0x60},
	{0x2f, 0x07},//  level 3 8
	{0x30, 0x80},
	{0xfe, 0x00},//
	{0x00, 0x00},
};

static struct reginfo antibanding_60hz_regs[] = {
	{0xfe, 0x00},
	{0x05, 0x01},
	{0x06, 0x21},
	{0x07, 0x00},
	{0x08, 0x14},
	{0xfe, 0x01},
	{0x27, 0x00},
	{0x28, 0x83},
	{0x29, 0x04},
	{0x2a, 0x9b},
	{0x2b, 0x04},
	{0x2c, 0x9b},
	{0x2d, 0x04},
	{0x2e, 0x9b},
	{0x2f, 0x07},
	{0x30, 0xad},
	{0xfe, 0x00},
	{0x00, 0x00},
};

static struct reginfo  sensor_out_yuv[] = {
	{0x00, 0x00},
};


static const struct gc2035_win_size gc2035_win_sizes[] = {
	/* SVGA */
	{
		.width = 800,
		.height = 600,
		.regs  = sensor_svga,
	},
	/* VGA */
	{
		.width = 640,
		.height = 480,
		.regs  = sensor_vga,
	},
	/* XGA */
	{
		.width = 1024,
		.height = 768,
		.regs = sensor_xga,
	},
	/* UXGA */
	{
		.width = 1600,
		.height = 1200,
		.regs  = sensor_uxga,
	}

};


/* only one fixed colorspace per pixelcode */
struct gc2035_data_fmt {
	enum v4l2_mbus_pixelcode code;
	enum v4l2_colorspace colorspace;
	struct reginfo	*regs;
};

static const struct gc2035_data_fmt gc2035_data_fmts[] = {
	{
		.code = V4L2_MBUS_FMT_YUYV8_2X8,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.regs	= sensor_out_yuv,
	},
};

static const struct gc2035_data_fmt *sensor_find_datafmt(
		enum v4l2_mbus_pixelcode code,
		const struct gc2035_data_fmt *fmt,
		int n)
{
	int i;
	for (i = 0; i < n; i++)
		if (fmt[i].code == code)
			return fmt + i;

	return fmt;
}

static const struct gc2035_win_size *sensor_find_win(
		struct v4l2_mbus_framefmt *mf,
		const struct gc2035_win_size *win,
		int n)
{
	int i;
	for (i = 0; i < n; i++)
		if (win[i].width == mf->width && win[i].height == mf->height)
			return win + i;

	return win;
}

static struct gc2035_info *to_sensor(struct v4l2_subdev *sd)
{
	return container_of(sd, struct gc2035_info, sd);
}

static int gc2035_write(struct i2c_client *client, uint8_t reg, uint8_t val)
{
	int err, cnt;
	u8 buf[2];
	struct i2c_msg msg[1];

	buf[0] = reg & 0xFF;
	buf[1] = val;

	msg->addr = client->addr;
	msg->flags = I2C_M_NOSTART;
	msg->buf = buf;
	msg->len = sizeof(buf);
	cnt = 3;
	err = -EAGAIN;
	err = i2c_transfer(client->adapter, msg, 1);
	if(1 != err) {
		pr_err("[gc2035] write reg(0x%x, val:0x%x) failed, ecode=%d \
				\n", reg, val, err);
		return err;
	}
	
	return 0;
}

static uint8_t gc2035_read(struct i2c_client *client, uint8_t reg)
{
	int err;
	struct i2c_msg msg[2];
	char buf = 0xff;

	msg[0].addr = client->addr;
	msg[0].flags = I2C_M_NOSTART;
	msg[0].buf = &reg;
	msg[0].len = 1;

	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].buf = &buf;
	msg[1].len = 1;

	err = i2c_transfer(client->adapter, msg, 2);
	if (err != 2)
		pr_err("[gc2035] read reg(0x%x)failed!\n", reg);

	return buf;
}

static int gc2035_write_array(struct i2c_client *client,
		struct reginfo *regarray)
{
	int i = 0, err;

	while ((regarray[i].reg != 0) || (regarray[i].val != 0)) {
		err = gc2035_write(client, regarray[i].reg, regarray[i].val);
		if (err != 0) {
			pr_err("[gc2035] I2c write %dth regs faild!\n", i);
			return err;
		}
		i++;
	}
	return 0;
}


#if 0
static const struct v4l2_subdev_pad_ops gc2035_pad_ops = {
	.enum_mbus_code = gc2035_enum_mbus_code,
	.enum_frame_size = gc2035_enum_frame_sizes,
	.get_fmt = gc2035_get_fmt,
	.set_fmt = gc2035_set_fmt,
};
#endif

static int gc2035_g_chip_ident(struct v4l2_subdev *sd,
		struct v4l2_dbg_chip_ident *chip)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	return v4l2_chip_ident_i2c_client(client, chip, V4L2_IDENT_GC2035, 0);
}


static int gc2035_reset(struct v4l2_subdev *sd, u32 val)
{
	return 0;
}

static int is_sensor_gc2035(struct v4l2_subdev *sd)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	u8 id0, id1;
	id0 = gc2035_read(client, 0xf0);
	id1 = gc2035_read(client, 0xf1);
	pr_info("[GC2035]-Sensor id 0x%x%x, req 0x2035!\n", id0, id1);
	if (id0 == 0x20 && id1 == 0x35)
		return 1;
	else
		return 0;
}

static int gc2035_init(struct v4l2_subdev *sd, u32 val)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	if (val)
		return !is_sensor_gc2035(sd);
	else
		return gc2035_write_array(client, sensor_init);

}
#ifdef CONFIG_VIDEO_ADV_DEBUG
static int gc2035_g_register(struct v4l2_subdev *sd,
		struct v4l2_dbg_register *reg)
{
	pr_info("[gc2035] %s\n", __func__);
	return 0;
}

static int gc2035_s_register(struct v4l2_subdev *sd,
		const struct v4l2_dbg_register *reg)
{
	pr_info("[gc2035] %s\n", __func__);
	return 0;
}
#endif


static int gc2035_set_exposure(struct i2c_client *client,
		struct v4l2_ctrl *ctrl)
{
	int ret = -1;
	switch (ctrl->val) {
		case -4:
			ret = gc2035_write_array(client, ev_neg4_regs);
			break;
		case -3:
			ret = gc2035_write_array(client, ev_neg3_regs);
			break;
		case -2:
			ret = gc2035_write_array(client, ev_neg2_regs);
			break;
		case -1:
			ret = gc2035_write_array(client, ev_neg1_regs);
			break;
		case 0:
			ret = gc2035_write_array(client, ev_zero_regs);
			break;
		case 1:
			ret = gc2035_write_array(client, ev_pos1_regs);
			break;
		case 2:
			ret = gc2035_write_array(client, ev_pos2_regs);
			break;
		case 3:
			ret = gc2035_write_array(client, ev_pos3_regs);
			break;
		case 4:
			ret = gc2035_write_array(client, ev_pos4_regs);
			break;
		default:
			break;
	}
	return ret;
}


static int gc2035_set_wb(struct i2c_client *client,  struct v4l2_ctrl *ctrl)
{
	int ret = -1;
	pr_info("[gc2035] %s\n", __func__);
	switch (ctrl->val) {
		case V4L2_WHITE_BALANCE_AUTO:
			ret = gc2035_write_array(client, wb_auto_regs);
			break;
		case V4L2_WHITE_BALANCE_INCANDESCENT:
			ret = gc2035_write_array(client, wb_incandescent_regs);
			break;
		case V4L2_WHITE_BALANCE_FLUORESCENT:
			ret = gc2035_write_array(client, wb_flourscent_regs);
			break;
		case V4L2_WHITE_BALANCE_DAYLIGHT:
			ret = gc2035_write_array(client, wb_daylight_regs);
			break;
		case V4L2_WHITE_BALANCE_CLOUDY:
			ret = gc2035_write_array(client, wb_cloudy_regs);
			break;
		default:
			break;
	}
	return ret;
}


static int gc2035_set_scence(struct i2c_client *client, struct v4l2_ctrl *ctrl)
{
	int ret = -1;
	pr_info("[gc2035] %s\n", __func__);
	switch (ctrl->val) {
		case V4L2_SCENE_MODE_NONE:
			ret = gc2035_write_array(client, scence_auto_regs);
			break;
		case V4L2_SCENE_MODE_NIGHT:
			ret = gc2035_write_array(client, scence_night60hz_regs);
			break;
		case V4L2_SCENE_MODE_SUNSET:
			ret = gc2035_write_array(client, scence_sunset60hz_regs);
			break;
		case V4L2_SCENE_MODE_PARTY_INDOOR:
			ret = gc2035_write_array(client, scence_party_indoor_regs);
			break;
		case V4L2_SCENE_MODE_SPORTS:
			ret = gc2035_write_array(client, scence_sports_regs);
			break;
		default:
			break;
	}
	return ret;

}



static int gc2035_set_colorfx(struct i2c_client *client, struct v4l2_ctrl *ctrl)
{
	int ret = -1;
	pr_info("[gc2035] %s\n", __func__);
	switch (ctrl->val) {
		case V4L2_COLORFX_NONE:
			ret = gc2035_write_array(client, colorfx_none_regs);
			break;
		case V4L2_COLORFX_BW:
			ret = gc2035_write_array(client, colorfx_mono_regs);
			break;
		case V4L2_COLORFX_SEPIA:
			ret = gc2035_write_array(client, colorfx_sepia_regs);
			break;
		case V4L2_COLORFX_NEGATIVE:
			ret = gc2035_write_array(client, colorfx_negative_regs);
			break;
		default:
			break;
	}
	return ret;
}



static int gc2035_set_powlinefreq(struct i2c_client *client,
		struct v4l2_ctrl *ctrl)
{
	int ret = -1;
	pr_info("[gc2035] %s\n", __func__);
	switch (ctrl->val) {
		case V4L2_CID_POWER_LINE_FREQUENCY_DISABLED:
		case V4L2_CID_POWER_LINE_FREQUENCY_60HZ:
		case V4L2_CID_POWER_LINE_FREQUENCY_AUTO:
			ret = gc2035_write_array(client, antibanding_60hz_regs);
			break;
		case V4L2_CID_POWER_LINE_FREQUENCY_50HZ:
			ret = gc2035_write_array(client, antibanding_50hz_regs);
			break;
		default:
			break;
	}
	return ret;
}


static int gc2035_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd =
		&container_of(ctrl->handler, struct gc2035_info, ctrls)->sd;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret = -1;
	pr_info("[gc2035] %s\n", __func__);
	switch (ctrl->id) {
		case V4L2_CID_EXPOSURE_ABSOLUTE:
			ret = gc2035_set_exposure(client, ctrl);
			break;
		case V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE:
			ret = gc2035_set_wb(client, ctrl);
			break;
		case V4L2_CID_SCENE_MODE:
			ret = gc2035_set_scence(client, ctrl);
			break;
		case V4L2_CID_COLORFX:
			ret = gc2035_set_colorfx(client, ctrl);
			break;
		case V4L2_CID_POWER_LINE_FREQUENCY:
			ret = gc2035_set_powlinefreq(client, ctrl);
			break;
		default:
			break;
	}
	return ret;
}


static struct v4l2_ctrl_ops gc2035_ctrl_ops = {
	.s_ctrl = gc2035_s_ctrl,
};



static const struct v4l2_subdev_core_ops gc2035_core_ops = {
	.g_chip_ident = gc2035_g_chip_ident,
	.reset = gc2035_reset,
	.init = gc2035_init,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_register = gc2035_g_register,
	.s_register = gc2035_s_register,
#endif
};



static int gc2035_enum_mbus_fmt(struct v4l2_subdev *sd, unsigned int index,
		enum v4l2_mbus_pixelcode *code)
{
	pr_info("[gc2035] %s\n", __func__);
	if (index >= ARRAY_SIZE(gc2035_data_fmts))
		return -EINVAL;
	*code = gc2035_data_fmts[index].code;
	return 0;
}


static int gc2035_try_mbus_fmt_internal(struct gc2035_info *sensor,
		struct v4l2_mbus_framefmt *mf,
		struct gc2035_data_fmt **ret_fmt,
		struct gc2035_win_size  **ret_size)
{
	int ret = 0;

	if (ret_fmt != NULL)
		*ret_fmt = sensor_find_datafmt(mf->code, gc2035_data_fmts,
				ARRAY_SIZE(gc2035_data_fmts));
	if (ret_size != NULL)
		*ret_size = sensor_find_win(mf, gc2035_win_sizes,
				ARRAY_SIZE(gc2035_win_sizes));

	return ret;
}

static int gc2035_try_mbus_fmt(struct v4l2_subdev *sd,
		struct v4l2_mbus_framefmt *mf)
{

	struct gc2035_info *sensor = to_sensor(sd);
	pr_info("[gc2035] %s\n", __func__);
	return gc2035_try_mbus_fmt_internal(sensor, mf, NULL, NULL);
}

static int gc2035_s_mbus_fmt(struct v4l2_subdev *sd,
		struct v4l2_mbus_framefmt *mf)
{
	struct gc2035_data_fmt *ovfmt;
	struct gc2035_win_size *wsize;
	struct i2c_client *client =  v4l2_get_subdevdata(sd);
	struct gc2035_info *sensor = to_sensor(sd);
	int ret;

	pr_info("[gc2035] %s\n", __func__);
	ret = gc2035_try_mbus_fmt_internal(sensor, mf, &ovfmt, &wsize);
	if (ovfmt->regs)
		ret = gc2035_write_array(client, ovfmt->regs);
	if (wsize->regs)
		ret = gc2035_write_array(client, wsize->regs);
	return ret;


}

static int gc2035_g_mbus_fmt(struct v4l2_subdev *sd,
		struct v4l2_mbus_framefmt *mf)
{
	pr_info("[gc2035] %s\n", __func__);
	return 0;
}

static int gc2035_s_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *parms)
{
	pr_info("[gc2035] %s\n", __func__);
	return 0;
}

static int gc2035_g_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *parms)
{
	pr_info("[gc2035] %s\n", __func__);
	return 0;
}


static int gc2035_enum_framesizes(struct v4l2_subdev *sd,
		struct v4l2_frmsizeenum *fsize)
{
	if (fsize->index >=  ARRAY_SIZE(gc2035_win_sizes))
		return -1;
	fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fsize->discrete.width = gc2035_win_sizes[fsize->index].width;
	fsize->discrete.height = gc2035_win_sizes[fsize->index].height;
	return 0;
}

static unsigned int gc2035_numerator = 1;
static unsigned int gc2035_denominator = 15;   

static int gc2035_g_frame_interval(struct v4l2_subdev *sd,
		struct v4l2_subdev_frame_interval *interval)
{

	pr_info("[gc2035] %s\n",__func__);
	if(interval == NULL)
		return -1;

	interval->interval.numerator = 1;
	interval->interval.denominator = 15;

	return 0;                              
}

static int gc2035_s_frame_interval(struct v4l2_subdev *sd,
		struct v4l2_subdev_frame_interval *interval)
{

	pr_info("[gc2035] %s\n",__func__);

	if(interval == NULL)
		return -1;

	gc2035_numerator = interval->interval.numerator;
	gc2035_denominator = interval->interval.denominator;


	return 0;                              
}

static int gc2035_enum_frameintervals(struct v4l2_subdev *sd, 
		struct v4l2_frmivalenum *fival)
{

	pr_info("[gc2035] %s\n",__func__);
	if(fival == NULL)
		return -1;

	if(fival->index != 0)
		return -1; 

	fival->type = V4L2_FRMSIZE_TYPE_DISCRETE; 
	fival->discrete.numerator = 1;
	fival->discrete.denominator = 15;

	return 0;                              
}


static const struct v4l2_subdev_video_ops gc2035_video_ops = {
	.enum_mbus_fmt = gc2035_enum_mbus_fmt,
	.try_mbus_fmt = gc2035_try_mbus_fmt,
	.s_mbus_fmt = gc2035_s_mbus_fmt,
	.g_mbus_fmt = gc2035_g_mbus_fmt,
	.s_parm = gc2035_s_parm,
	.g_parm = gc2035_g_parm,
	.enum_framesizes = gc2035_enum_framesizes,
	.enum_frameintervals = gc2035_enum_frameintervals,
	.s_frame_interval = gc2035_s_frame_interval,
	.g_frame_interval = gc2035_g_frame_interval,

};

static const struct v4l2_subdev_ops gc2035_subdev_ops = {
	.core = &gc2035_core_ops,
	.video = &gc2035_video_ops,
};

static const struct i2c_device_id gc2035_id[] = {
	{ "gc2035_demo", 0},
	{}
};
MODULE_DEVICE_TABLE(i2c, gc2035_id);

static int gc2035_probe(struct i2c_client *client,
		    const struct i2c_device_id *id)
{
	struct v4l2_subdev *sd;
	struct gc2035_info *sensor;
	int ret;

	pr_info("[gc2035] %s\n", __func__);

	sensor = devm_kzalloc(&client->dev, sizeof(*sensor), GFP_KERNEL);
	if (!sensor)
		return -ENOMEM;

	mutex_init(&sensor->lock);
	sensor->client = client;

	sd = &sensor->sd;

	ret = v4l2_ctrl_handler_init(&sensor->ctrls, 4);
	if (ret < 0)
		return ret;
	v4l2_ctrl_new_std(&sensor->ctrls, &gc2035_ctrl_ops,
			V4L2_CID_EXPOSURE_ABSOLUTE, -4, 4, 1, 0);

	v4l2_ctrl_new_std_menu(&sensor->ctrls, &gc2035_ctrl_ops,
			V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE, 9, ~0x14e,
			V4L2_WHITE_BALANCE_AUTO);
	v4l2_ctrl_new_std_menu(&sensor->ctrls, &gc2035_ctrl_ops,
			V4L2_CID_SCENE_MODE,
			V4L2_SCENE_MODE_TEXT, ~0x1f01,
			V4L2_SCENE_MODE_NONE);

/*
	v4l2_ctrl_new_std_menu(&sensor->ctrls, &gc2035_ctrl_ops,
			V4L2_CID_COLORFX, V4L2_COLORFX_EMBOSS, ~0xf,
			V4L2_COLORFX_NONE);
*/
	v4l2_ctrl_new_std_menu(&sensor->ctrls, &gc2035_ctrl_ops,
			V4L2_CID_POWER_LINE_FREQUENCY,
			V4L2_CID_POWER_LINE_FREQUENCY_AUTO, 0,
			V4L2_CID_POWER_LINE_FREQUENCY_AUTO);
	sensor->sd.ctrl_handler = &sensor->ctrls;


	v4l2_i2c_subdev_init(sd, client, &gc2035_subdev_ops);
	strlcpy(sd->name, "gc2035_demo", sizeof(sd->name));

	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
		V4L2_SUBDEV_FL_HAS_EVENTS;
	sensor->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.type = MEDIA_ENT_T_V4L2_SUBDEV_SENSOR;
	ret = media_entity_init(&sd->entity, 1, &sensor->pad, 0);
	if (ret < 0)
		return ret;
	return 0;
}

static int gc2035_remove(struct i2c_client *client)
{
	return 0;
}
static struct i2c_driver gc2035_demo_driver = {
	.driver = {
		.owner  = THIS_MODULE,
		.name   = "gc2035_demo",
	},
	.probe      = gc2035_probe,
	.remove     = gc2035_remove,
	.id_table   = gc2035_id,
};

module_i2c_driver(gc2035_demo_driver);

MODULE_AUTHOR("peter");
MODULE_DESCRIPTION("GC0308 CMOS Image Sensor driver");
MODULE_LICENSE("GPL");


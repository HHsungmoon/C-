#pragma once

#ifndef __SUB_GAME_H__
#define __SUB_GAME_H__


#define DKey_EXT		224
//#define DKey_Left		75
//#define DKey_Right		77
//#define DKey_Up			72
//#define DKey_Down		80

#define LEFT		75
#define RIGHT		77
#define UP			72
#define DOWN		80

#define DKey_ESC		27


typedef enum {
	EBLACK,
	EDARK_BLUE,
	EDARK_GREEN,
	EDARK_SKY_BLUE,
	EDARK_RED,
	EDARK_VOILET,
	EDARK_YELLOW,
	EGRAY,
	EDARK_GRAY,
	EBLUE,
	EGREEN,
	ESKY_BLUE,
	ERED,
	EVOILET,
	EYELLOW,
	EWHITE,
}Tconsole_color;


void _goto_xy(int x, int y);
void _hide_cursor();
void _clear_screen();
void _initialize_random();

char* current_time();


#endif	//__SUB_GAME_H__
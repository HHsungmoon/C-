
#ifndef __Game_base__
#define __Game_base__

//»ö»ó
enum Color {
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_SKYBLUE,
    DARK_RED,
    DARK_VOILET,
    DAKR_YELLOW,
    GRAY,
    DARK_GRAY,
    BLUE,
    GREEN,
    SKYBLUE,
    RED,
    VIOLET,
    YELLOW,
    WHITE,
};

void Hide_Cursor();
void gotoxy(int x, int y);
void goto_xy(int x, int y);
int random_rotation_num();
int random_block_num();
void clear_screen();
void set_color(unsigned short text);


#endif


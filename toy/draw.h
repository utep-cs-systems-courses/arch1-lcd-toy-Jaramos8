#ifndef draw_included
#define draw_included

typedef unsigned int u_int;
typedef unsigned char u_char;

extern signed char y;

/** Draw string at col,row
 *  Type: 8x12 Font
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString8x12(u_char col, u_char row, char *string, 
		   u_int fgColorBGR, u_int bgColorBGR);

/** 8x12 font - this function draws background pixels
 */
void drawChar8x12(u_char col, u_char row, char c, 
		 u_int fgColorBGR, u_int bgColorBGR);

/* This function draws a diamond.
 */
void drawDiamond(u_char offc, u_char offr, u_int color);

/*
  this function draws a box that moves to the right
 */
void draw_right();

/*
  this function draws a box that moves to the left
 */
void draw_left();

/*
  this function draws a small house.
 */
void draw_shape(u_char offc, u_char offr, u_int color, u_int color2);

#endif // included

#include "lcdutils.h"
#include "lcddraw.h"
#include "main.h"
#include "draw.h"

signed char y = 64;

/** 8x12 font - this function draws background pixels
 *  
 */
void drawChar8x12(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x80;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 7, rrow + 11); /* relative to requested col/row */
  while (col < 12) {
    while (row < 8) {
      u_int colorBGR = (font_8x12[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      row++;
      bit >>= 1;
    }
    row = 0;
    bit = 0x80;
    col++;
  }
}

/** Draw string at col,row
 *  Type: 8x12 font
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString8x12(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar8x12(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 9;
  }
}
/* Draws Shape: Diamond on top of Triangle */

void draw_shape(u_char offc, u_char offr, u_int color, u_int color2) 
{
  /* Diamond */
  for(u_char r = 0; r < 10; r++){       
    for(u_char c = 0; c <= r; c++){            
      drawPixel(offc-c, offr+r, color);
      drawPixel(offc+c, offr+r, color);
      drawPixel(offc-c, offr+19-r, color);  
      drawPixel(offc+c, offr+19-r, color);
    }
  }
 
   /* Tiangle */
  
  for(u_char r = 0; r < 10; r++){                              
    for(u_char c = 0; c <= r; c++){
      drawPixel(offc-c, offr+r+19, color);
      drawPixel(offc+c, offr+r+19, color);
    }
  }
}

void draw_right()
{
  if(y < 0){                             /* checks if y is out of bounds*/
    y += 128;                            /* if so, move it to the correct position inbounds*/
  }
  for(u_char r = 30; r<40; r++){         /* these 2 loops make the main black box*/
    for(u_char c = 0; c<10; c++){
      signed char s = y;
      s+=c;
      if(s < 0){                         /* if new pixel position is out of bounds*/
      s+=128;                          /* then move it to a correct position inbounds*/
	drawPixel(s,r,COLOR_BLACK);
      }
      else{                              /* otherwise, was already inbounds*/
	drawPixel(y+c,r,COLOR_BLACK);
      }
    }
  }
  for(u_char r = 30; r<40; r++){         /* this erases the previous position of the box*/
    for(u_char c = 0; c<5; c++){
      signed char s = y;
      s+=c;
      s-=5;
      if(s < 0){                         /* if the new pixel position is out of bounds*/
      s+=128;                          /* then move it the a correct position inbounds*/
	drawPixel(s,r,COLOR_WHITE);
      }
      else{                              /* otherwise, was already inbounds*/
	drawPixel(y+c-5,r,COLOR_WHITE);
      }
    }
  }
  y+=5;                                  /* move y to the right 5 pixels*/
}
					 
void draw_left()                         /* this function draws a square moving to the left */
{
  if(y < 0){                            /* checks if y is negative/out of bounds */
    y += 128;                           /* if so, changes y to the correct value inbounds */
  }
  for(u_char r = 30; r<40; r++){        /* This draws the main black box */
    for(u_char c = 0; c<10; c++){      
      signed char s = y;
      s+=c;
      if(s < 0){                        /* This checks if the position of the next pixel to be drawn is out of bounds */
	s+=128;                         /* if so, then it changes it to the correct position inbounds */
	drawPixel(s,r,COLOR_BLACK);
      }
      else{                             /* else it was already inbounds */
	drawPixel(y+c,r,COLOR_BLACK);
      }
    }
  }
  for(u_char r = 30; r<40; r++){        /* this erases the previous position of the box without erasing the new box */
    for(u_char c = 0; c<5; c++){   
      signed char s = y;
      s+=c;
      s+=10;
      if(s < 0){                        /* checks if new pixel is out of bounds */
	s+=128;                         /* if so, move it to the proper position inbounds */
	drawPixel(s,r,COLOR_WHITE);
      }
      else{                             /* else, was already inbounds */
	drawPixel(y+c+10,r,COLOR_WHITE);
      }
    }
  }
  y-=5;                                 /* move y to the left 5 pixels */
}

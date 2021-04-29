/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  //  fillRectangle(30,30, 60, 60, COLOR_ORANGE);

  u_char offset_r = 100, offset_c = 60;
  
    for(int r =0; r<= 50; r++){
      for(int c = 0; c <= r; c++){
       drawPixel(offset_c + c, offset_r-r, COLOR_ORANGE);
       drawPixel(offset_c - c, offset_r-r, COLOR_ORANGE);
     }
    }
}

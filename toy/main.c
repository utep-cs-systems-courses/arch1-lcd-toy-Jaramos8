#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw.h"
#include "main.h"
#include "stateMachines.h"
#include "buzzer.h"
#include "switches.h"

#define LED_GREEN BIT6             // P1.6
#define LED_RED BIT0

short redrawScreen3 = 0;          /* needed for special actions */
char substateLed2 = 0;
char substateLed = 0;             /* this is the substate for the led */
short redrawScreen = 0;           /* true if anything needs to be redrawn */
short redrawScreen2 = 1;          /* true for the typewriter section */
u_int fontFgColor = COLOR_RED;    /* these are the 2 font colors */
u_int fontFgColor2 = COLOR_WHITE;
int secCount = 0;                 /* keeps track of time */
char seconds = 0;                 /* keeps track of number of times an interval passed */
char state_changed = 0;           /* true if a state has changed with the led */
void wdt_c_handler()
{
  switch(master){
  case 0:
    secCount ++;
    if(secCount == 10){
      buzzer_set_period(0);
    }
    if (secCount == 25 && seconds <= 7) {		/* 10 times/sec, while seconds < 8 */
      seconds++;
      secCount = 0;
      redrawScreen = 1;
      redrawScreen2 = 1;
    }
    if(secCount == 250 && seconds > 7){                 /* once/sec after typewriter */
      secCount = 0;
      redrawScreen = 1;
      color_advance();                                  /* advance color */
    }
    break;
  case 1:
    secCount++;
    switch(movestate){                                  /* different behavior based on movestate */
    case 0:
    case 1:
      if(secCount == 5){                                /* every 5 counts it moves more */
	redrawScreen = 1;
	secCount = 0;
      }
      break;
    case 3:
      break;
    }
    break;
  case 2:
    seconds++;
    if(seconds == 125){
      seconds = 0;
      substateLed++;
    }
    if(substateLed == 5){
      substateLed = 0;
    }
    and_sr(~0x8);	      /* GIE disable interrupts */
    state_changed = state_advance(substateLed); /* i just dont want this interrupted */
    or_sr(0x8);	              /* GIE enable interrupts */
    break;
  case 4:
    seconds++;
    if(seconds == 125){
      seconds = 0;
      substateLed2++;
    }
    if(substateLed2 == 2){
      substateLed2 = 0;
    }
    and_sr(~0x8);            /* GIE disable interrupts */
    or_sr(0x8);              /* GIE enable interrupts */
    break;
  }
}
  

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */
  P1DIR |= LED_RED;
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  buzzer_init();
  switch_init();

  clearScreen(COLOR_BLACK);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */ 
  
  while (1) {			/* forever */
    if (redrawScreen) {
      switch(master){
      case 0:
	redrawScreen = 0;
	if(redrawScreen3){           /* only redraws the entire screen once */
	  clearScreen(COLOR_BLACK); 
	  seconds = 1;
	  secCount = 0;
	  redrawScreen3 = 0;
	}
	else if(redrawScreen2){     /* then it does the typewriter */
	  redrawScreen2 = 0;
	  main_menu_advance();
	}
	else{                       /* then it draws the main text that flips colors */
	  drawString8x12(screenWidth/2-36, screenHeight/2-55,"********", fontFgColor, COLOR_BLACK);
	  drawString5x7(screenWidth/2-48, screenHeight/2-40,"Press S1 to Play", fontFgColor, COLOR_BLACK);
	  drawString5x7(screenWidth/2-27, screenHeight/2-25,"Press S2", fontFgColor, COLOR_BLACK);
	  drawString5x7(screenWidth/2-27, screenHeight/2-15,"to reload", fontFgColor, COLOR_BLACK);

	  drawString5x7(screenWidth/2-45, screenHeight/2,"Press S3 to Play", fontFgColor, COLOR_BLACK);
	  drawString5x7(screenWidth/2-30, screenHeight/2+10,"Buzzer", fontFgColor, COLOR_BLACK);
	  drawString5x7(screenWidth/2-45, screenHeight/2+25,"Press S4 to Play ", fontFgColor, COLOR_BLACK);
	  drawString5x7(screenWidth/2-32, screenHeight/2+35,"LED", fontFgColor, COLOR_BLACK);
	  
	  draw_shape(screenWidth/2, screenHeight/2+50, fontFgColor, fontFgColor2); 

	}
	break;
      case 1:
	redrawScreen = 0;
	switch(movestate){                  /* different behavior based on movestate */
	case 0:
	case 1:
	  and_sr(~0x8);                     /* I dont want this getting interrupted */
	  motion_advance();                 /* advances the square */
	  or_sr(0x8);                       /* re-enable interrupts now */
	  break;
	case 3:
	  if(redrawScreen3){                /* only draws this once, then waits until button press */
	    clearScreen(COLOR_WHITE);
	    seconds = 0;
	    secCount = 0;
	    redrawScreen3 = 0;
	  }
	  drawString5x7(screenWidth/2-48, screenHeight/2-10,"Press S2 to move", COLOR_BLACK, COLOR_WHITE);
	  drawString5x7(screenWidth/2-30, screenHeight/2-2,"to the left", COLOR_BLACK, COLOR_WHITE);
	  drawString5x7(screenWidth/2-48, screenHeight/2+10,"Press S3 to move", COLOR_BLACK, COLOR_WHITE);
	  drawString5x7(screenWidth/2-35, screenHeight/2+20,"to the right", COLOR_BLACK, COLOR_WHITE);
	  break;
	}
	break;
      case 2:	
	break;
      }
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    secCount = 0;
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}


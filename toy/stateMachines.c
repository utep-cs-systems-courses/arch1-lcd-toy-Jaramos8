#include <msp430.h>
#include "stateMachines.h"
#include "lcdutils.h"
#include "buzzer.h"
#include "lcddraw.h"
#include "main.h"
#include "draw.h"

#define LED_GREEN BIT6
#define LED_RED BIT0

u_char rcolS = screenWidth/2-36;
int master = 0;                 /* master state set automatically to 0 */
int substate = 0;               /* substate set automatically to 0 */
int x = 500;                    /* x set to 0 */
char *string = "Welcome!";
int colorState = 0;             /* state of the color */
int movestate = 0;              /* state of the movement */

void color_advance()   		   /* switch between different color modes */
{
  switch(colorState){
  case 0:
    fontFgColor2 = (fontFgColor == COLOR_RED) ? COLOR_RED : COLOR_WHITE;  /* updates both colors */
    fontFgColor = (fontFgColor == COLOR_RED) ? COLOR_WHITE : COLOR_RED;
    buzzer_set_period(0);
  }
}

void main_menu_advance()           /* runs the typewriter part of the main menu */
{
  buzzer_set_period(2000000/500);
  u_char rrowS = screenHeight/2-50;
  drawChar8x12(rcolS, rrowS, *string++, fontFgColor, COLOR_BLACK);
  rcolS+=9;
}

void motion_advance()                /* operates the movement of the box */
{
  buzzer_set_period(2000000/(x+y));  /* sound depends on position */
  switch(movestate){                 /* switch chooses direction */
  case 0:
    draw_right();
    break;
  case 1:
    draw_left();
    break;
  default:
    break;
  }
}


void ambulance_advance(int stateA)      /* extra state machine not being used */
{
  switch(stateA){
  case 0:
    buzzer_set_period(2000000/2500);    /* set buzzer */
    red_on_all();                   /* 2 lines set lights */
    break;
  case 1:
    buzzer_set_period(2000000/500);     /* set buzzer */
    red_off();                     /* set leds */
    break;
  }
}


void red_off()                  /* red light off*/
{
  P1OUT &= ~LED_RED;
}

void green_off()                /* green light off */
{
  P1OUT &= ~LED_GREEN;
}

void both_on()                  /* both lights on */
{
  P1OUT |= LED_RED;
  P1OUT |= LED_GREEN;
}

char red_on_all()	        /* 100% brightness red */
{
  P1OUT |= LED_RED;
  return 1;			
}

char toggle_red()		/* 50% brightness red */
{
  static char state = 0;

  switch (state) {
  case 0:
    P1OUT |= LED_RED;
    state = 1;
    break;
  case 1:
    P1OUT &= ~LED_RED;
    state = 0;
    break;
  }
  return 1;			
}

char red_33()		        /* 33% brightness red */
{
  static char state2 = 0;

  switch (state2) {
  case 0:
    P1OUT &= ~LED_RED;
    state2 = 1;
    break;
  case 1:
    P1OUT &= ~LED_RED;
    state2 = 2;
    break;
  case 2:
    P1OUT |= LED_RED;
    state2 = 0;
    break;
  }
  return 1;			
}

char red_66()		        /* 66% brightness red */
{
  static char state3 = 0;
  
  switch (state3) {
  case 0:
    P1OUT &= ~LED_RED;
    state3 = 1;
    break;
  case 1:
    P1OUT |= LED_RED;
    state3 = 2;
    break;
  case 2:
    P1OUT |= LED_RED;
    state3 = 0;
    break;
  }
  return 1;		       
}

char red_25()	                /* 25% brightness red */
{
  static char state4 = 0;
  
  switch (state4) {
  case 0:
    P1OUT &= ~LED_RED;
    state4 = 1;
    break;
  case 1:
    P1OUT &= ~LED_RED;
    state4 = 2;
    break;
  case 2:
    P1OUT &= ~LED_RED;
    state4 = 3;
    break;
  case 3:
    P1OUT |= LED_RED;
    state4 = 0;
  }
  return 1;			
}

char green_on_all()		/* 100% brightness green */
{
  P1OUT |= LED_GREEN;
  return 1;			
}

char toggle_green()		/* 50% brightness green */
{
  static char state5 = 0;
  
  switch (state5) {
  case 0:
    P1OUT &= ~LED_GREEN;
    state5 = 1;
    break;
  case 1:
    P1OUT |= LED_GREEN;
    state5 = 0;
    break;
  }
  return 1;		      
}

char green_33()		/* 33% brightness green */
{
  static char state6 = 0;
  
  switch (state6) {
  case 0:
    P1OUT &= ~LED_GREEN;
    state6 = 1;
    break;
  case 1:
    P1OUT &= ~LED_GREEN;
    state6 = 2;
    break;
  case 2:
    P1OUT |= LED_GREEN;
    state6 = 0;
    break;
  }
  return 1;			
}

char green_66()		/* 66% brightness green */
{
  static char state7 = 0;
  
  switch (state7) {
  case 0:
    P1OUT &= ~LED_GREEN;
    state7 = 1;
    break;
  case 1:
    P1OUT |= LED_GREEN;
    state7 = 2;
    break;
  case 2:
    P1OUT |= LED_GREEN;
    state7 = 0;
    break;
  }
  return 1;		      
}

char green_25()		/* 25% brightness green */
{
  static char state8 = 0;

  switch (state8) {
  case 0:
    P1OUT &= ~LED_GREEN;
    state8 = 1;
    break;
  case 1:
    P1OUT &= ~LED_GREEN;
    state8 = 2;
    break;
  case 2:
    P1OUT &= ~LED_GREEN;
    state8 = 3;
    break;
  case 3:
    P1OUT |= LED_GREEN;
    state8 = 0;
  }
  return 1;			  
}

char state_advance(char substateLed);              /* function written in assembly in state_advance.s */


char state_advance(char substateLed)   		   /* switch between different dimming modes*/
{
  char led_changed = 0;
  switch(substateLed){
  case 0:
  led_changed = red_on_all();    /* 100% brightness red*/ 
    break;
  case 1:
  led_changed = red_66();        /* 66% brightness red */
    break;
  case 2:
  led_changed = toggle_red();    /* 50% brightness red */
    break;
  case 3:
  led_changed = red_33();        /* 33% brightness red */
    break;
  case 4:
  led_changed = red_25();        /* 25% brightness red */ 
    break;
  }
  return led_changed;
}


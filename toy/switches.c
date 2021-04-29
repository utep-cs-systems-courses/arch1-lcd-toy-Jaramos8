#include <msp430.h>
#include "switches.h"
#include "stateMachines.h"
#include "buzzer.h"
#include "main.h"
#include "lcdutils.h"

#define RED_LED BIT0;

char switch_state_down, switch_state_changed, blink_count, blink_count2, seconds; /* effectively boolean */
int master, x;

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  return p2val;
}

void 
switch_init()			/* setup switches */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  master = 0;
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switch(master){
  case 0:
    if((p2val & SW1) == 0){       /* Load Game */
      seconds = 0;                /* next few lines update variables */
      secCount = 0;               /* need to reset secCount */
      movestate = 3;
      master = 1;
      redrawScreen = 1;
      redrawScreen3 = 1;
      buzzer_set_period(0);
    }
    else if((p2val & SW4) == 0){  /* Load dimming demo */
      seconds = 0;                /* next few lines update variables */
      secCount = 0;
      redrawScreen = 0;
      redrawScreen2 = 0;
      master = 2;                 /* updated the master state */
    }
    else if((p2val & SW3) == 0){  /* load ambulance */
      seconds = 0;                /* next few lines update variables */
      secCount = 0;
      redrawScreen = 0;
      redrawScreen2 = 0;
      master = 4;                 /* updated the master state */
    }
    else if ((p2val & SW2) == 0){ /* reload Main Menu */
      master = 0;                 /* next few lines update variables */
      secCount = 0;
      seconds = 0;
      string = "Welcome!";
      redrawScreen = 1;
      redrawScreen3 = 1;
      rcolS = screenWidth/2-36;
    }
    break;
  case 1:
    if((p2val & SW1) == 0){       /* load game */
      movestate = 3;
      master = 1;
      seconds = 0;                /* next few lines update variables */
      secCount = 0;
      redrawScreen = 1;
      redrawScreen3 = 1;
      buzzer_set_period(0);
    }
    else if((p2val & SW2) == 0){  /* move to the left */
      seconds = 0;                /* next few lines update variables */
      secCount = 0;
      movestate = 1;
      master = 1;
      buzzer_set_period(0);
    }
    else if((p2val & SW3) == 0){  /* move to the right */
      seconds = 0;                /* next few lines update variables */
      secCount = 0;
      movestate = 0;
      master = 1;
      buzzer_set_period(0);
    }
    else if ((p2val & SW4) == 0){ /* Back to Main Menu */
      master = 0;                 /* next few lines update variables */
      secCount = 0;
      seconds = 0;
      string = "Welcome!";
      redrawScreen = 1;
      redrawScreen3 = 1;
      rcolS = screenWidth/2-36;
    }
    break;
  case 2:
    if((p2val & SW3) == 0){       /* back to Main Menu */
      master = 0;                 /* next few lines update variables */
      secCount = 0;
      seconds = 8;
      P1OUT &= ~RED_LED;          /* i believe the code breaks if this stays on */
      string = "Welcome!";
      redrawScreen = 0;
      redrawScreen2 = 0;
      rcolS = screenWidth/2-36;
    }
    break;
  case 4:
    if((p2val & SW4) == 0){       /* Back to Main Menu */
      master = 0;                 /* next few lines update variables */
      secCount = 0;
      seconds = 8;
      P1OUT &= ~RED_LED;          /* i believe the code breaks if this stays on */
      string = "Welcome!";
      redrawScreen = 0;
      redrawScreen2 = 0;
      rcolS = screenWidth/2-36;
    }
    break;
  }
  switch_state_changed = 1;
}

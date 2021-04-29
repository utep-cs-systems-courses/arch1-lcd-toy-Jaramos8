#include <msp430.h>
#include "switches.h"

/* Switch on P2 (SW1-4) */
void
__interrupt_vec(PORT2_VECTOR) Port_1(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();
  }
}


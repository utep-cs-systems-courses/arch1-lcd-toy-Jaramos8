#ifndef stateMachine_included
#define stateMachine_included

extern int master;         /* this is the master state */ 

extern int movestate;      /* the move state */

extern int colorState;

extern int substate;

extern unsigned char rcolS;

extern int x;              

extern char seconds;

extern char *string;

/* This function advances the color
 */
void color_advance();

/* This function advances the main menu type writer section
 */
void main_menu_advance();

/* This function advances the motion of the box
 */
void motion_advance();

/* Turns off the red led
 */
void red_off();

/* Turns off the green led
 */
void green_off();

/* Turns on both leds
 */
void both_on();

/* advances the state of the dimming sequence
 */
char state_advance(char substateLed);

/* turns on the red led 100% brightness
 */
char red_on_all();

/* red led 50% brightness
 */
char toggle_red();

/* red led 33% brightness
 */
char red_33();

/* red led 66% brightness
 */
char red_66();

/* red led 25% brightness
 */
char red_25();

/* green led 100% brightness
 */
char green_on_all();

/* green led 50% brightness
 */
char toggle_green();

/* green led 33% brightness
*/
char green_33();

/* green led 66% brightness
 */
char green_66();

/* green led 25% brightness
 */
char green_25();

/* advances the ambulance state
 */
void ambulance_advance(int stateA);
#endif // included

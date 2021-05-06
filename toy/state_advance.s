	.arch msp430g2553
	.p2align 1,0
	.text
jt:
	.word case0
	.word case1
	.word case2
	.word case3
	.word case4

	.extern red_on_all
	.extern red_66
	.extern toggle_red
	.extern red_33
	.extern red_25

	.global state_advance

state_advance:
	sub #2, r1		;make room for local var
	mov.b #0, 0(r1)		;char led_changed = 0
	cmp.b #5, r12           ;check if selector is inbounds
	jhs done		;if not, then done
	add.b r12, r12		;selector*2
	mov jt(r12), r0		;use jump table

case0:	call #red_on_all        ;call 100% brightness
	mov.b r12, 0(r1)	;mov return value into led_changed
	jmp done

case1:	call #red_66	        ;call 66% brightness
	mov.b r12, 0(r1)	;mov return value into led_changed
	jmp done

case2:	call #toggle_red        ;call 50% brightness
	mov.b r12, 0(r1)	;mov return value into led_changed
	jmp done

case3:	call #red_33    	;call 33% brightness
	mov.b r12, 0(r1)	;mov the return value into led_changed
	jmp done

case4:	call #red_25		;call 25% brightness
	mov.b r12, 0(r1)	;mov return value into led_changed
	jmp done

done:	mov.b 0(r1), r12	;mov led_changed to be returned
	add #2, r1		;reset stack
	pop r0			;return
	

# Lab 5: Alexandre TRUONG

Link to my `Digital-electronics-2` GitHub repository:

   [https://github.com/AkaiRyussei/Digital-electronics-2](https://github.com/AkaiRyussei/Digital-electronics-2)


### 7-segment library

1. In your words, describe the difference between Common Cathode and Common Anode 7-segment display.
   * CC SSD : CC is active high, each segment-driving output is normally low, but goes high to turn a segment on.
   * CA SSD : CA is active low, each segment-driving output is normally high, but goes low to turn a segment on.

2. Code listing with syntax highlighting of two interrupt service routines (`TIMER1_OVF_vect`, `TIMER0_OVF_vect`) from counter application with at least two digits, ie. values from 00 to 59:

```c
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Increment counter value from 00 to 59.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    // WRITE YOUR CODE HERE
    cnt0++;
	if(cnt0 > 9)
	{
		cnt0 = 0;
		cnt1++;
		if (cnt1 > 5)				// for assignment
		{
			cnt1 = 0;				// for assignment
		}
	}

}
```

```c
/**********************************************************************
 * Function: Timer/Counter0 overflow interrupt
 * Purpose:  Display tens and units of a counter at SSD.
 **********************************************************************/
ISR(TIMER0_OVF_vect)
{
    static uint8_t pos = 0;

    // WRITE YOUR CODE HERE
    if (pos == 0){
		SEG_update_shift_regs(cnt0, 0);
	}
	else if (pos == 1) {
		SEG_update_shift_regs(cnt1, 1);
	}
	pos++;
	if(pos > 1)
	{
		pos = 0;

	}

}
```

3. Flowchart figure for function `SEG_clk_2us()` which generates one clock period on `SEG_CLK` pin with a duration of 2&nbsp;us. The image can be drawn on a computer or by hand. Use clear descriptions of the individual steps of the algorithms.

   ![flowchart](https://i.postimg.cc/wxkpGS3s/Flowchart.png)


### Kitchen alarm

Consider a kitchen alarm with a 7-segment display, one LED and three push buttons: start, +1 minute, -1 minute. Use the +1/-1 minute buttons to increment/decrement the timer value. After pressing the Start button, the countdown starts. The countdown value is shown on the display in the form of mm.ss (minutes.seconds). At the end of the countdown, the LED will start blinking.

1. Scheme of kitchen alarm; do not forget the supply voltage. The image can be drawn on a computer or by hand. Always name all components and their values.

   ![Circuit](https://i.postimg.cc/nVKFtXSr/assignment.png)
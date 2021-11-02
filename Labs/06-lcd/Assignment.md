# Lab 6: ALEXANDRE TRUONG

Link to my `Digital-electronics-2` GitHub repository:

[https://github.com/AkaiRyussei/Digital-electronics-2](https://github.com/AkaiRyussei/Digital-electronics-2)


### LCD display module

1. In your words, describe what ASCII table is.
   * ASCII table: It's a table that contains letters, numbers, special characters, ... Each character is assigned a 7 bit code which is used to represent those characters in hexa, binary ...

2. (Hand-drawn) picture of time signals between ATmega328P and LCD keypad shield (HD44780 driver) when transmitting three character data `De2`.

   ![picture of time signals](https://github.com/AkaiRyussei/Digital-electronics-2/blob/main/Labs/06-lcd/time%20signals.png?raw=true)


### Stopwatch

1. Flowchart figure for `TIMER2_OVF_vect` interrupt service routine which overflows every 16&nbsp;ms but it updates the stopwatch LCD approximately every 100&nbsp;ms (6 x 16&nbsp;ms = 100&nbsp;ms). Display tenths of a second and seconds `00:seconds.tenths`. Let the stopwatch counts from `00:00.0` to `00:59.9` and then starts again. The image can be drawn on a computer or by hand. Use clear descriptions of the individual steps of the algorithms.

   ![flowchart](https://github.com/AkaiRyussei/Digital-electronics-2/blob/main/Labs/06-lcd/Flowchart.png?raw=true)


### Custom characters

1. Code listing of two custom character definition. Always use syntax highlighting and meaningful comments:

```c
/* Variables ---------------------------------------------------------*/
// Custom character definition
uint8_t customChar[16] = {
    // WRITE YOUR CODE HERE
    0b00100,
	0b01010,
	0b10001,
	0b10000,
	0b10000,
	0b10001,
	0b01010,
	0b00100,
    0b11011,
	0b10101,
	0b01110,
	0b01111,
	0b01111,
	0b01110,
	0b10101,
	0b11011


};
```


### Kitchen alarm

Consider a kitchen alarm with an LCD, one LED and three push buttons: start, +1 minute, -1 minute. Use the +1/-1 minute buttons to increment/decrement the timer value. After pressing the Start button, the countdown starts. The countdown value is shown on the display in the form of mm.ss (minutes.seconds). At the end of the countdown, the LED will start blinking.

1. Scheme of kitchen alarm; do not forget the supply voltage. The image can be drawn on a computer or by hand. Always name all components and their values.

   ![kitchen alarm](https://github.com/AkaiRyussei/Digital-electronics-2/blob/main/Labs/06-lcd/Kitchen%20alarm%20with%20LCD%20display.png?raw=true)
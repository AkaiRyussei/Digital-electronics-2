# Lab 7: ADC and UART serial communication

![LCD-keypad shield](Images/arduino_uno_adc.jpg)

### Learning objectives

After completing this lab you will be able to:

* Understand the analog-to-digital conversion process
* How to use internal ADC unit
* Understand the UART communication

The purpose of the laboratory exercise is to understand analog-to-digital number conversion and the use of an internal 8-channel 10-bit AD converter. Another goal is to understand serial asynchronous communication, data frame structure and communication options using an internal USART unit.

### Table of contents

* [Preparation tasks](#preparation)
* [Part 1: Synchronize repositories and create a new folder](#part1)
* [Part 2: Analog-to-Digital Conversion](#part2)
* [Part 3: UART communication](#part3)
* [Experiments on your own](#experiments)
* [Lab assignment](#assignment)
* [References](#references)

<a name="preparation"></a>

## Preparation tasks (done before the lab at home)

1. Use schematic of the [LCD keypad shield](../../Docs/arduino_shield.pdf) and find out the connection of five push buttons: Select, Left, Up, Down, and Right.

   &nbsp;

   &nbsp;

   &nbsp;

   &nbsp;

   &nbsp;

   &nbsp;

2. According to the connection, calculate the voltage values on pin PC0[A0] if one button is pressed at a time. In this case, the voltage on the pin is given by the [voltage divider](https://www.allaboutcircuits.com/tools/voltage-divider-calculator/), where resistors R3, R4, R5 and R6 are applied successively.

   ![Equation: Voltage divider](Images/eq_divider1.png)

   ![Equation: Voltage divider](Images/eq_divider2.png)

   &nbsp;

   ![Equation: Voltage divider](Images/eq_divider3.png)

   &nbsp;

   ![Equation: Voltage divider](Images/eq_divider4.png)

   &nbsp;

   ![Equation: Voltage divider](Images/eq_divider5.png)

   &nbsp;

3. Calculate the voltage value if none of the push buttons is pressed.

   ![Equation: Voltage divider](Images/eq_divider6.png)

   &nbsp;

4. Calculate the ADC values for these voltages according to the following equation if reference is Vref=5V and number of bits for analog to digital conversion is n=10.

   ![Equation: ADC conversion](Images/eq_adc.png)

   | **Push button** | **PC0[A0] voltage** | **ADC value (calculated)** | **ADC value (measured)** with R2=2k instead of 3k |
   | :-------------: | :-----------------: | :------------------------: | :-----------------------------------------------: |
   |      Right      |      0&nbsp;V       |             0              |                         0                         |
   |       Up        |    0.495&nbsp;V     |            101             |                        145                        |
   |      Down       |       1.203V        |            246             |                        329                        |
   |      Left       |        1.97V        |          403.062           |                        507                        |
   |     Select      |        3.18V        |          650.628           |                        743                        |
   |      none       |         5V          |            1023            |                       1023                        |

<a name="part1"></a>


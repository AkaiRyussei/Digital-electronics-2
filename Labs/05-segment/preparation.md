## Preparation tasks (done before the lab at home)

1. Read the [7-segment display tutorial](https://www.electronics-tutorials.ws/blog/7-segment-display-tutorial.html) and find out what is the difference between:
   * Common Cathode 7-segment display (CC SSD) : all the cathode connections of the LED segments are joined together to logic “0” or ground. The individual segments are illuminated by application of a “HIGH”, or logic “1” signal via a current limiting resistor to forward bias the individual Anode terminals (a-g).
   * Common Anode 7-segment display (CA SSD) : all the anode connections of the LED segments are joined together to logic “1”. The individual segments are illuminated by applying a ground, logic “0” or “LOW” signal via a suitable current limiting resistor to the Cathode of the particular segment (a-g).

2. In the following table, write the binary values of the segments for display 0 to 9 on a common anode 7-segment display.

   | **Digit** | **A** | **B** | **C** | **D** | **E** | **F** | **G** | **DP** |
   | :-------: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :----: |
   |     0     |   0   |   0   |   0   |   0   |   0   |   0   |   1   |   1    |
   |     1     |   0   |   1   |   1   |   0   |   0   |   0   |   0   |   1    |
   |     2     |   1   |   1   |   0   |   1   |   1   |   0   |   1   |   1    |
   |     3     |   0   |   0   |   0   |   0   |   1   |   1   |   0   |   1    |
   |     4     |   0   |   1   |   1   |   0   |   0   |   1   |   1   |   1    |
   |     5     |   1   |   0   |   1   |   1   |   0   |   1   |   1   |   1    |
   |     6     |   1   |   0   |   1   |   1   |   1   |   1   |   1   |   1    |
   |     7     |   1   |   1   |   1   |   0   |   0   |   0   |   0   |   1    |
   |     8     |   1   |   1   |   1   |   1   |   1   |   1   |   1   |   1    |
   |     9     |   1   |   1   |   1   |   0   |   0   |   1   |   1   |   1    |

3. Use schematic of the [Multi-function shield](../../Docs/arduino_shield.pdf) and find out the connection of seven-segment display. What is the purpose of two shift registers 74HC595?

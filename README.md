Motivation:
for my M.S. degree I had to make a bare mettal C application. I look at that project and now see it as beneath my current skill level.
I want to re-visit this type of project with fresh, better devloped eyes. I want to do domething similar but more complex. 

overview:
I am going to have two line following robots explore every point on a variable sized grid. together they will need to explore each node before they can stop exploring.
they will need to communicate to share what nodes they have each explored as well as to avoid colision.

there will be a bluetooth board on each of the 3PI robots. there will be SPI communication between the 3PI and the bluetooth board.
there will be some bluetooth communication between each of the bluetooth boards.

I intend to make a woring solution to this problem. I also intend to simulate as much of the logic as I can in software not on the microcontrollers.

total there will be 4 microcontrolers total. I will need to build a PCB to integrate the 3PI and the bluetooth boards. 

background:
I will be using the pololu 3pi line follownig robot. I will have written all of the software from the ground up from PWM control logic to location maping.
https://www.pololu.com/product/975

I will be using an ESP32 board as a bluetoooth bridge for the communication between the line following robots.
I will be using bluetooth drivers that came with the bard and only write the application for this board.
https://www.espressif.com/en/products/devkits/esp32-devkitc/overview


# Embedded GPS destination follower on TM4C123GH6PM:
## Project description:

This repo was submitted for Introduction to Embedded Systems' [CSE211s] final project. It aims to localize the user using the embedded program on the microcontroller, Tiva, and guide them to their destination co-ordinates (longitude, latitude) using a `NEO-6M GPS module`, a `16x2 LCD` and the board's `built-in LEDs`.

## How to use:
The code was built and loaded using uVision's Keil (`4.0` and `5.0` work fine).

1. Clone the repository locally
2. Setup the new Keil project, and be sure to include the `startup file` in your runtime environment.
  
  
__Important note:__ to activate the FPU that's used to calculate the distance as well as the coordinates, this is how the __Reset_Handler__ block in the startup file should look like:
```assembly 
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]

		; CPACR is located at address 0xE000ED88
		LDR.W R0, =0xE000ED88
		; Read CPACR
		LDR R1, [R0]
		; Set bits 20-23 to enable CP10 and CP11 coprocessors
		ORR R1, R1, #(0xF << 20)
		; Write back the modified value to the CPACR
		STR R1, [R0]; wait for store to complete
		DSB
		;reset pipeline now the FPU is enabled
		ISB				
				
                IMPORT  __main
                LDR     R0, =__main
                BX      R0
                ENDP
```
3. Build the target files. Be sure to select `[x] use MicroLIB` from `code generation` in target settings when building.
4. Load the files to the microcontroller and press the reset button.
5. Schematic of the connections are attached below.
  
<p align="center">
    <img width="710" src="https://github.com/Abdoemad220/Embedded_project/assets/99722575/4d70dd33-5126-4ef6-bfc7-02eaf05cd203" alt="Schematic of used circuit.">
</p>
  
    
__Important note:__ This repository's code assumes that the `NEO-6M GPS` module was configured to only send `GPGGA` NMEA messages.
  

## What to expect when running the project:
While the GPS module tries to find a fix on the user's position, the module's red built-in led will keep blinking, and the LCD should display `"Fix not found!"` with a blinking cursor, each blink signifies a new attempt at finding a position.
<p align="center">
    <img src="https://github.com/Abdoemad220/Embedded_project/assets/99722575/c60c897a-e8f2-43ea-b3d3-b6fa9169c5b2" alt="LCD showing "Fix not found!\"">
</p>
  

After a fix has been found, the LCD will display the user's current location (longitude, latitude), as well as the distance (in `m`) required to reach their target.
<p align="center">
    <img src="https://github.com/Abdoemad220/Embedded_project/assets/99722575/d8875f8f-09ad-45a1-a364-45863dc65aa5" alt="LCD showing latitude, longitude, and distance.">
</p>
  
  
When target reaches their destination (within `1m`) the built-in led turns `green`, when distance is less than `5m` the Tiva's built-in led will turn `yellow`, otherwise the led remains `red`.
  




## To-be implemented:
The code can be modified to show the angle the user is required to take to reach their destination.

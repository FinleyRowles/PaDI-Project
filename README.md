# STM32 Seven Segment Display Name Project

## Overview
This project is a **Programming and Digital Interfacing** assignment that uses an **STM32 microcontroller** to display a name on a **seven-segment display**, one character at a time. The system includes two push buttons:
- **Button 1**: Displays the first name (**Finley**)
- **Button 2**: Displays the last name (**Rowles**)

## Features
- Utilizes **semaphores and mutexes** for safe multithreading.
- Implements **interrupts** to detect button presses.
- Displays each character for **700ms** before moving to the next.
- Clears the display between characters for better readability.

## Components Used
- **STM32 Microcontroller**
- **Seven-Segment Display**
- **Two Push Buttons**

## Wiring
| **STM32 Pin** | **Component**        |
|--------------|---------------------|
| D9          | Push Button 1 (PB1)  |
| D8          | Push Button 2 (PB2)  |
| D1 - D7     | Seven-Segment Display Segments (A-G) |

## Setup & Usage
1. Flash the **main.cpp** file to your STM32 board.
2. Connect the **seven-segment display** and **push buttons** as per the wiring table.
3. Press **PB1** to display "Finley".
4. Press **PB2** to display "Rowles".

# STM32 Programming and Digital Interfacing project (First Year)

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

## Breadboard
![VideoCapture_20250303-202332](https://github.com/user-attachments/assets/243c3a26-7811-4ef9-b3df-bb0abea00ea3)


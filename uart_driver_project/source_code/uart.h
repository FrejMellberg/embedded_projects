#ifndef __UART_H
#define __UART_H // Definierar vår headerfil för uart

#include "stm32f4xx.h" //Hämtar källkoden och hänvisningar för arbete på STM-Hårdvara. 
		       //Innehåller register och bits definitioner som vi ska använda.
#include <stdio.h> //Inkluderar standard I/O för C

void USART2_Init(void); // Kallar på och refererar till deklarationen av vår UART-funktion
#endif //Förtydligar avslutningen av vår headerfil

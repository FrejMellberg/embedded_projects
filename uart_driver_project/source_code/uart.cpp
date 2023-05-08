#include "uart.h" //Hämtar vår samlingsfil för headers och funktioner

/*
En funktion som initierar och konfigurerar USART-protokollet.
Ställer in klocka/aktiverar usart2 och GPIO port(A)
Mode och funktion för usart2 pins(PA2 & PA3).
Baud rate
Data bits,start/stop, parity.
Enable USART.
*/
void USART2_Init(void) { //Deklarerar en funktion för att initiera USART-protkokollet och dess beståndsdelar

/* 
1. Enablea klocktillgång för usart2. Genom att ge tillgång till klockan synkas USART2 mot systemklockans frekvens.
 Värt att tänka på är att den perifera bus som USART2 ligger på har hälften av systemklockans frekvens, och kan ändras genom prescalers.
 Detta kan vara användbart i situationer då strömförsörjning är begränsad. Lägre frekvens, lägre konsumtion.
 */
RCC->APB1ENR |= 0x20000; //Aktiverar USART2 genom att sätta bit 17 i APB1ENR till 1.

// 2. Enablea klocktillgång för portA.
// GPIOs är organiserade i olika ports. PortA är den port som våra för usart2 relevanta pins tillhör.
RCC->AHB1ENR |= 0x01; //Atkiverar GPIOA genom att sätta bit 0 i AHB1ENR till 1. 

// 3. Enablea pins relaterade till vald port, för alternativ funktion
GPIOA->MODER &= ~0x00F0; //Rensar bitarna 4-7 för att förbereda pins PA2 och PA3.
//& samt ~forcerar en invertering som leder till att bitarna som via hex betecknas med 1, i realvärde ersätts med 0

GPIOA->MODER |= 0x00A0; //Sätter bitarna 5 och 7 till 1 för att aktivera alternativ funktionalitet på pins PA2 och PA3
// Varje pin i mode-registret har 2 bits vilket ger 4 möjliga modes. Här sätts de som PA2=1 0 PA3=1 0.

// 4. Välja typen av alternativ funktion för de valde pinsen
GPIOA->AFR[0] &= ~0xFF00; //Rensar bitarna 8-15 för att förbereda pins PA2 och PA3
GPIOA->AFR[0] |= 0x7700; //Sätter vi bitarna 8-11 samt 12-15 till formatet 0111. Detta ger AF7 vilket är USART funktionen
			 //AFR[0] är AF registret för pin 0-7. Att det, till från MODER, är uppdelad beror på att varje pin här har 4 bit.

/* Konstruktion av enhetens kommunikation avslutas */


// Konfiguration utav USART2

USART2->BRR = 0x0683; //Sätter vi standard baud-rate med hjälp av hexadecimalen 0x0683 (9600bps).
		      //Baud rate är överföringshastighet och räknas ut i förhållande till klockfrekvensen.
		      //BR=SysClk/(16xClkDiv)
USART2->CR1 = 0x000C; //Sätter vi tx och rx till att arbeta i 8 bitars data. (8 bitars data, 1 stop bit, ingen paritet)
		      // En Start-bit är också inkluderad, för att informera mottagande enhet om att data är inkommande. 

USART2->CR2 = 0x000;  //Nollställer CR2,
USART2->CR3 = 0x000;  //Nollställer CR3, Ser till att tex. IrDA och DMA transmisson/reception är disabled 
USART2->CR1 |= 0x2000;//Omställer bit 13 (UART-Aktiveringen) till 1

}
// UART Write
int USART2_write(int ch){ //Deklarerar skrivfunktionen (Överföringen av data till terminalen)
//Sätter vi ett krav som kontrollerar att statusen på överföringen är tom och kan ta emot nästa karaktär (byte)
// När bit 7 i SR blir 1 uppfylls kravet. Återställs till 0 när vi skriver till DR nedan.
  while(!(USART2->SR & 0x0080)){} 
  
  USART2->DR = (ch & 0xFF); //Sätter överföringen av byten till dataregistret

  return ch;

}
// UART Read
int USART2_read(void){ //Deklarerar läsfunktionen (mottagning av information)
//Sätter vi ett krav som kontrollerar om det finns mer data att hämta.
//bit 5 i SR, återställs när vi läser ut datan nedan.
  while(!(USART2->SR & 0x0020)){} 
  
  return USART2->DR; //Läser ut datan
}

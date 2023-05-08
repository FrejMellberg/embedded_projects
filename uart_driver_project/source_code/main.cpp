#include "Led.h"

// Skapar globala variabler som kan hålla de olika LED:ens state. Dvs om dom är på eller av.
LedState_Type led1_state;
LedState_Type led2_state;
LedState_Type led3_state;

Led led1(RED,ON); // skapar objektet led1 som är på PB14 och får "state on". minnesplats static.

int main(void){ //huvudfunktion konstruerar och hanterar LED-lamporna
  USART2_Init(); // Initierar och konfigurerar USART2_Init

  Led led2(BLUE,ON); // skapar objekt led2, minnesplats på stacken.

  Led *led3 = new Led(YELLOW,ON); // skapar ett led3 objekt med new operatorn, allokerar minnesplats dynamiskt på heap.

  led1_state = led1.getState(); // Sätter led1_state variablen till det state som led1 har(ON)

  led1.setState(OFF); // Ändrar led1's state till OFF

  delete led3; // Eftersom "new" kan leda till "memory leaks" måste/bör den deletas. Sker ej automatiskt som med led2.

  while(1){} // Evighets loop

}

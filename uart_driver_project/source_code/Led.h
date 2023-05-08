#ifndef LED_H
#define LED_H

#include <stdint.h>
#include "uart.h"
#include "stm32f4xx.h" //Device Header för enhetsspecifika angivelser om hårdvaran

/*
Här definieras olika macros som kan användas i Led.cpp.
Genom att ge namn åt de olika pins, bits och portar som ska användas blir koden i Led.cpp enklare att förstå.
*/
//Definera vilken GPIO som skall vara ansvarig för LED-funktionen
#define LED_PORT GPIOB

//Definerar klocksignalen för porten
#define LED_PORT_CLOCK (1U<<1)

//Definera de olika pinsen för de olika LED-färgerna
#define LED_RED_PIN (1U<<14) // ändrar bit 14 till 1, utan att ändra några andra bits i registret.
#define LED_GREEN_PIN (1U<<12)
#define LED_BLUE_PIN (1U<<15)
#define LED_YELLOW_PIN (1U<<13)

//Definera mode bits för varje LED-färg
// Här ställs "general purpose output mode" in för de olika pinsen. Eller förbereds, ställs in i led.cpp förstås.
#define LED_RED_MODE_BIT (1U<<28) // PB14, PB eftersom led_port är GPIOB
#define LED_GREEN_MODE_BIT (1U<<24) // PB12
#define LED_YELLOW_MODE_BIT (1U<<26) // PB13
#define LED_BLUE_MODE_BIT (1U<<30) // PB15

//Definerar de olika LED-färgerna som finns
//Typedef enum låter oss definera ord som siffror vilket gör koden mer läsbar.
//DVS LedColor_Type GREEN == LedColor_Type 1
typedef enum {
  RED = 0,
  GREEN,
  YELLOW,
  BLUE
}LedColor_Type;

//Definerar / numrerar de olika lägena(state) som LED kan befinna sig i
typedef enum {
  OFF = 0,
  ON = 1
}LedState_Type;

// Definerar de attribut som LED består utav
// En klass för att kunna konstruera våra LED-objekt
class Led{

  private:
      LedColor_Type color;
      LedState_Type state;

  public:

      Led(LedColor_Type _color,LedState_Type _state); // konstruktor member-funktion
      void setState(LedState_Type _state); // Ställ in state member-funktion
      LedState_Type getState() const; // kontrollera state member-funktion

};

#endif

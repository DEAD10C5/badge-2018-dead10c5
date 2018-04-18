#include "EEPROM.h"
#include "ssd1306.h"
#include "font6x8.h"

//Rename the pins to something more descriptive
int led1 = 3;
int led2 = 5;
int led3 = 6;
int led4 = 9;
int led5 = 10;
int led6 = 11;
int leds[6] = {led1, led2, led3, led4, led5, led6};
int button1 = 2;
int pot1 = A3;
int pot2 = A2;
int pot3 = A1;
int pot4 = A0;
int pots[4] = {pot1, pot2, pot3, pot4};
volatile int buttonState = 0;

void setup() {
  initialize();
}

void loop() {
  int potValue[4];
  oledPots(readPots(potValue));
}

void buttonPress() {
  int potValue[4];
  serialPots(readPots(potValue));
  int unlockValues = getUnlocks();
  sweepRight();
  unlockLeds(unlockValues);
}


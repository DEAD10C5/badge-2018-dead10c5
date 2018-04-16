#include "EEPROM.h"

int led1 = 3;
int led2 = 5;
int led3 = 6;
int led4 = 9;
int led5 = 10;
int led6 = 11;
int leds[6] = {led1, led2, led3, led4, led5, led6};

int button1 = 2;

int pot1 = A2;
int pot2 = A3;
int pot3 = A4;
int pot4 = A5;
int pots[4] = {pot1, pot2, pot3, pot4};

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  for (int ledCounter = 0; ledCounter <= 5;  ledCounter += 1) {
    pinMode(leds[ledCounter], OUTPUT);
  }
  for (int potCounter = 0; potCounter <=3; potCounter += 1) {
    pinMode(pots[potCounter], INPUT);
  }

  Serial.println(EEPROM.read(0));

  if (EEPROM.read(0) != 0) {
    int randSeed(analogRead(A0)*10);
    randomSeed(randSeed);
    for (int byteCounter = 1; byteCounter <= 24; byteCounter += 2) {
      int element = random(1024);
      EEPROM.write(byteCounter, highByte(element));
      EEPROM.write(byteCounter + 1, lowByte(element));     
    }
    EEPROM.write(0, 1);
  }

  for (int byteCounter = 1; byteCounter <= 24; byteCounter += 2) {
    Serial.print("Byte ");
    Serial.print(byteCounter);
    Serial.print(": ");
    byte high = EEPROM.read(byteCounter);
    byte low = EEPROM.read(byteCounter + 1);
    int element = word(high, low);
    Serial.println(element, DEC);
  }
  
  pinMode(button1, INPUT_PULLUP);
  Serial.print("pots: ");
  Serial.println(sizeof(pots) / sizeof(int));
  Serial.print("leds: ");
  Serial.println(sizeof(leds) / sizeof(int));
  
}

void sweepRight() {
  int ledCount = (sizeof(leds) / sizeof(int));
  for (int ledCounter = 0; ledCounter < ledCount;  ledCounter += 1) {
    for (int fadeValue = 0 ; fadeValue <= 100; fadeValue += 1) {
      analogWrite(leds[ledCounter], fadeValue);
      delay(1);
    }
  }
  for (int ledCounter = 0; ledCounter < ledCount;  ledCounter += 1) {
    for (int fadeValue = 100 ; fadeValue >= 0; fadeValue -= 1) {
      analogWrite(leds[ledCounter], fadeValue);
      delay(1);
    }
  }  
}

void sweepLeft() {
  int ledCount = (sizeof(leds) / sizeof(int));
  for (int ledCounter = (ledCount-1); ledCounter >= 0;  ledCounter -= 1) {
    for (int fadeValue = 0 ; fadeValue <= 100; fadeValue += 1) {
      analogWrite(leds[ledCounter], fadeValue);
      delay(1);
    }
  }
  for (int ledCounter = (ledCount-1); ledCounter >= 0;  ledCounter -= 1) {
    for (int fadeValue = 100 ; fadeValue >= 0; fadeValue -= 1) {
      analogWrite(leds[ledCounter], fadeValue);
      delay(1);
    }
  }
}

void strobeLed(int led, int blinks) {
  for (int flashCounter = 1 ; flashCounter <= blinks; flashCounter += 1) {
    analogWrite(led, 255);
    delay(25);
    analogWrite(led, 0);
    delay(25);
  }
}

void pulseLed(int led, int pulses) {
  for (int pulseCounter = 1; pulseCounter <= pulses; pulseCounter += 1) {
    for (int fadeValue = 0; fadeValue <= 100; fadeValue += 1) {
      analogWrite(led, fadeValue);
      delay(10);
    }
    for (int fadeValue = 100 ; fadeValue >= 0; fadeValue -= 1) {
      analogWrite(led, fadeValue);
      delay(10);
    }
  }
}

void loop() {
  if (digitalRead(button1) == LOW) {
    
    int potCount = (sizeof(pots) / sizeof(int));
    int ledCount = (sizeof(leds) / sizeof(int));

    int potRead[potCount];
    
    for (int potCounter = 0; potCounter < potCount; potCounter +=1) {
      potRead[potCounter] = analogRead(pots[potCounter]);
    }
    for (int potCounter = 0; potCounter < potCount; potCounter +=1) {
          Serial.print(potRead[potCounter]);
          Serial.print("\n");
    }

    for (int counter = 0; counter < 5; counter +=1) {
      sweepRight();
      sweepLeft();
    }
    strobeLed(led1, 10);
    strobeLed(led2, 10);
    strobeLed(led3, 10);
    strobeLed(led4, 10);
    strobeLed(led5, 10);
    strobeLed(led6, 10);
    
    for (int counter = 0; counter < 5; counter += 1) {
      sweepRight();
    }
    delay(100);
    for (int counter = 0; counter < 5; counter += 1) {
      sweepLeft();
    }

    pulseLed(led1, 1);
    pulseLed(led2, 1);
    pulseLed(led3, 1);
    pulseLed(led4, 1);
    pulseLed(led5, 1);
    pulseLed(led6, 1);
  }
}
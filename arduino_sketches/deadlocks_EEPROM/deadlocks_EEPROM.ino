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

void setup() {
  Serial.begin(115200);
  while ( !Serial ) {
    ;
  }
  //Set the LED pins to output mode
  for ( int ledCounter = 0; ledCounter <= 5;  ledCounter += 1)  {
    pinMode(leds[ledCounter], OUTPUT);
  }
  //Set the potentiometer pins to input mode
  for ( int potCounter = 0; potCounter <=3; potCounter += 1 ) {
    pinMode( pots[potCounter], INPUT );
  }

  if ( EEPROM.read(0) == 1 ) {
    Serial.println( "This badge has been initialized." );
  }
  else {
    Serial.println( "This badge has NOT been initialized." );
    
    //Set up the random number generator
    int randSeed( analogRead(A0)*10 );
    randomSeed( randSeed );

    //Create 24 random numbers and write them to the EEPROM
    Serial.println( "Creating lock combinations." );
    for ( int byteCounter = 1; byteCounter <= 24; byteCounter += 1 ) {
      int element = random( 10 );
      EEPROM.write( byteCounter, element );  
    }

    //Write to EEPROM that none of the combintations have been matched
    for ( int comboCounter = 25; comboCounter <= 30; comboCounter += 1 ) {
      EEPROM.write( comboCounter, 0 );
    }

    //Setting the first byte of the EEPROM to value '1' to indicate that the badge has been initialized
    EEPROM.write( 0, 1 );
    
  }

  //Set up the input pin for the button
  pinMode( button1, INPUT_PULLUP );

  ssd1306_128x64_i2c_init();
  ssd1306_fillScreen(0x00);
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  
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
    int potRead[potCount];
    
    for (int potCounter = 0; potCounter < potCount; potCounter +=1) {
      potRead[potCounter] = (analogRead(pots[potCounter])/112);
    }
    for (int potCounter = 0; potCounter < potCount; potCounter +=1) {
          Serial.println(potRead[potCounter]);
    }

    sweepRight();
  }

  int potCount = (sizeof(pots) / sizeof(int));
  for (int potCounter = 0; potCounter < potCount; potCounter +=1) {
    char output[14];
    String str;
    str = "Combo ";
    str = str + String(potCounter + 1);
    str = str + ": ";
    str = str + String(analogRead(pots[potCounter])/112);
    str.toCharArray(output,14);
    ssd1306_printFixed (0,  ((potCounter + 1) * 8), output, STYLE_NORMAL);
  }
}

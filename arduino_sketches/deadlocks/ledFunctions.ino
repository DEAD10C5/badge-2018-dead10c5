const int ledCount = (sizeof(leds) / sizeof(int));

void unlockLeds(int *punlockValues) {
  for (int ledCounter = 0; ledCounter < ledCount;  ledCounter += 1) {
    if (punlockValues[ledCounter] == 1) {
      analogWrite(leds[ledCounter], 100);
    }
    else {
      analogWrite(leds[ledCounter], 0);
    }
  }
}

void sweepRight() {
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

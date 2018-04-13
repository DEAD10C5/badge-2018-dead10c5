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

int combos[6][4];

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

  int randSeed(analogRead(A0)*10);
  randomSeed(randSeed);
  for (int firstCount = 0; firstCount < 6; firstCount += 1) {
    for (int secondCount = 0; secondCount < 4; secondCount += 1) {
      combos[firstCount][secondCount] = random(1024);
    }
  }
  
  pinMode(button1, INPUT_PULLUP);
  Serial.print("pots: ");
  Serial.print(sizeof(pots) / sizeof(int));
  Serial.print("\n");
  Serial.print("leds: ");
  Serial.print(sizeof(leds) / sizeof(int));
  Serial.print("\n");
  Serial.print("The random seed is: ");
  Serial.print(randSeed);
  Serial.print("\n");
  for (int firstCount = 0; firstCount < 6; firstCount += 1) {
    for (int secondCount = 0; secondCount < 4; secondCount += 1) {
      Serial.print("Combination ");
      Serial.print(firstCount);
      Serial.print(", position ");
      Serial.print(secondCount);
      Serial.print(": ");
      Serial.print(combos[firstCount][secondCount]);
      Serial.print("\n");
    }
  }  
}

void sweepRight() {
  int ledCount = (sizeof(leds) / sizeof(int));
  for (int ledCounter = 0; ledCounter < ledCount;  ledCounter += 1) {
    for (int fadeValue = 0 ; fadeValue <= 100; fadeValue += 10) {
      analogWrite(leds[ledCounter], fadeValue);
      delay(3);
    }
  }
  for (int ledCounter = 0; ledCounter < ledCount;  ledCounter += 1) {
    for (int fadeValue = 100 ; fadeValue >= 0; fadeValue -= 10) {
      analogWrite(leds[ledCounter], fadeValue);
      delay(3);
    }
  }  
}

void sweepLeft() {
  int ledCount = (sizeof(leds) / sizeof(int));
  for (int ledCounter = (ledCount-1); ledCounter >= 0;  ledCounter -= 1) {
    for (int fadeValue = 0 ; fadeValue <= 100; fadeValue += 10) {
      analogWrite(leds[ledCounter], fadeValue);
      delay(3);
    }
  }
  for (int ledCounter = ledCount; ledCounter >= 0;  ledCounter -= 1) {
    for (int fadeValue = 100 ; fadeValue >= 0; fadeValue -= 10) {
      analogWrite(leds[ledCounter], fadeValue);
      delay(3);
    }
  }
}

void blinkLed(int led, int blinks) {
  for (int flashCounter = 1 ; flashCounter <= blinks; flashCounter += 1) {
    analogWrite(led, 255);
    delay(100);
    analogWrite(led, 0);
    delay(100);
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
    sweepRight();
    sweepLeft();
    blinkLed(led1, 5);
  } 
}

int potCount = 4;

void serialPots(int* potValues) {
  for (int potCounter = 0; potCounter < potCount; potCounter +=1) {
    Serial.print("Position");
    Serial.print(potCounter + 1);
    Serial.print(": ");
    Serial.println(potValues[potCounter]);
  }
}

void oledPots(int* potValues) {
  ssd1306_printFixed (0, 8, "DE:AD:10:C5", STYLE_NORMAL);
  for (int potCounter = 0; potCounter < potCount; potCounter +=1) {
    char output[14];
    String str;
    str = "Combo ";
    str = str + String(potCounter + 1);
    str = str + ": ";
    str = str + String(potValues[potCounter]);
    str.toCharArray(output,15);
    ssd1306_printFixed (0,  ((potCounter + 2) * 8), output, STYLE_NORMAL);
  }
}

int *readPots(int potValues[4]) {
  for (int potCounter = 0; potCounter < potCount; potCounter +=1) {
    potValues[potCounter] = analogRead(pots[potCounter]) / 112;
  }
  return potValues;
}


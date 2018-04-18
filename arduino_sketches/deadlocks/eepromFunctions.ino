int getUnlocks() {
  int unlocks[6];
  for ( int comboCounter = 0; comboCounter <= 5; comboCounter += 1 ) {
    unlocks[comboCounter] = EEPROM.read(comboCounter + 25);
  }
  return(&unlocks);
}

void initialize() {
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

  attachInterrupt(0, buttonPress, LOW);

  ssd1306_128x64_i2c_init();
  ssd1306_fillScreen(0x00);
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  
}

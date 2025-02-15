# IoT-Device-Localization-with-ESP8266-and-RFM69
 A system using ESP8266, ATmega328 and RFM69 to track the location of IoT devices wirelessly
4. LED Blinking Indicator
This section implements a blinking mechanism for the blue LED (LED_BLUE) as a heartbeat indicator. Using the millis() function, the program calculates the time elapsed since the last blink. If the elapsed time exceeds the predefined interval (10 ms), the LED's state is toggled between ON and OFF. This functionality ensures the LED blinks at consistent intervals, providing a visual cue that the program is running as expected.
 unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis; // save the last time you blinked the LED
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    // set the LED with the ledState of the variable:
    digitalWrite(LED_BLUE, ledState);
  }

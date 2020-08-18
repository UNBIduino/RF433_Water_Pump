#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <JC_Button.h>

RH_ASK driver;

//const char *pump_on = "{\"pump\":\"on\"}\r\n";
//const char *pump_off = "{\"pump\":\"off\"}\r\n";

const char *pump_on = "pump_on_on\r\n";
const char *pump_off = "pump_off_off\r\n";

const byte BUTTON_PIN_7(7), BUTTON_PIN_4(4), LED_PIN(13);              // the standard Arduino "pin 13" LED
Button myBtn7(BUTTON_PIN_7);       // define the button
Button myBtn4(BUTTON_PIN_4);       // define the button



void setup()
{
  Serial.begin(9600);	  // Debugging only
  myBtn4.begin();              // initialize the button object
  myBtn7.begin();              // initialize the button object
  pinMode(LED_PIN, OUTPUT);   // set the LED pin as an output
  if (!driver.init()) {
    Serial.println("init failed");
  }
}

unsigned long led_milli = 0;

void loop()
{


  //  delay(1000); myBtn4.read();               // read the button
  myBtn7.read();               // read the button
  myBtn4.read();               // read the button

  if (myBtn4.wasReleased())    // if the button was released, change the LED state
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Button4");
    led_milli = millis();
    //Send the message
    Serial.println(pump_off);
    driver.send((uint8_t *)pump_off, strlen(pump_off));
    driver.waitPacketSent();
    ///////////////////////////
  }

  if (myBtn7.wasReleased())    // if the button was released, change the LED state
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Button7");
    led_milli = millis();
    //Send the message
    Serial.println(pump_on);
    driver.send((uint8_t *)pump_on, strlen(pump_on));
    driver.waitPacketSent();
    ///////////////////////////
  }

  //Turn off the led if milli is exeed
  if (millis() > led_milli + 100) {
    digitalWrite(LED_PIN, LOW);
  }

}

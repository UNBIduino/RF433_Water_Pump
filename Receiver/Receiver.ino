#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;
//RH_ASK driver=RH_ASK(2000,7);

#define BUFF_LEN 50
#define LED_PIN 13
#define PUMP_PIN 3

uint8_t buf[BUFF_LEN];
const char *pump_on = "pump_on_on\r\n";
const char *pump_off = "pump_off_off\r\n";

boolean pump_should_on = false;

void setup()
{
  Serial.begin(9600);  // Debugging only
  pinMode(LED_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pump_off_task(); //turn off the pin for the first time
  if (!driver.init()) {
    Serial.println("init failed");
  } else {
    Serial.println("init success");
  }
}

void loop()
{
  uint8_t buflen = BUFF_LEN - 1;
  buf[ BUFF_LEN - 1] = 0;//just terminating the last as "0"
  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    // Message with a good checksum received, dump it.
    char* message = (char*)buf;
    Serial.print("Message: ");
    Serial.println(message);
    //    if (!compare("keymessage", (const char *)json["key"], 5))
    if (compare(pump_on, (const char *)message, 10)) {
      Serial.println("Pump on");
      pump_should_on = true;
    }
    if (compare(pump_off, (const char *)message, 12)) {
      Serial.println("Pump off");
      pump_should_on = false;
    }
  }
  if (pump_should_on) {
    pump_on_task();
  } else {
    pump_off_task();
  }
}

void pump_on_task() {
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(PUMP_PIN, LOW);
}

void pump_off_task() {
  digitalWrite(LED_PIN, LOW);
  digitalWrite(PUMP_PIN, HIGH);
}

boolean compare(char *char1, const char *char2, size_t len)
{
  for (size_t i = 0; i < len; i++) // interating over the char of char array to check if the char array are same
  {
    if (char1[i] != char2[i])
    {
      return false;
    }
  }
  return true;
}

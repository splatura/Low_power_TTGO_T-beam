#include "t_beam.h"
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 10       /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);         

void setup() {
  
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);  

  Serial.begin(115200);
  delay(1000); //Take some time to open up the Serial Monitor
  u8x8.setCursor(0, 0);
  u8x8.inverse();
  u8x8.print(" GPS Location  ");
  u8x8.noInverse();
  u8x8.setCursor(0, 2);
  u8x8.print("NO GPS FIX");

  T_beam t_beam = T_beam();
  TinyGPSLocation mylocation = t_beam.getLocation();
    Serial.print(F("SUCCES"));
    Serial.print(mylocation.lat(), 6);
    Serial.print(F(","));
    Serial.print(mylocation.lng(), 6);
    Serial.println();
    u8x8.clearLine(2);
    u8x8.setCursor(0, 2);
    u8x8.print(mylocation.lat(), 6);
    u8x8.setCursor(0, 3);
    u8x8.print(mylocation.lng(), 6);

  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  Serial.println("Going to sleep now");
  Serial.flush();
  t_beam.low_power_deep_sleep_timer(uS_TO_S_FACTOR * TIME_TO_SLEEP);
  
  Serial.println("This will never be printed");
}


void loop() {
  //This is not going to be called
}

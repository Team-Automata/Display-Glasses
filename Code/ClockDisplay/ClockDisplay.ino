/*********************************************************************
Smart display glasses using a 128x32 monochrome OLED.
https://github.com/Team-Automata/Display-Glasses

Inspired by the work of Alain Mauer (http://www.alainsprojects.com/). 
Based on the Adafruit GFX library.
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h> // Requires a modified glcdfont.c file with mirrored characters
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 displayRight = Adafruit_SSD1306();

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

bool timerEnable = true;
long time_start_ms = 0;
long time_now_s = 0;
long time_duration_s = 90;

void setup()   {                
  Serial.begin(9600);

  displayRight.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  displayRight.setRotation(3); // Rotate display 90 degrees
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  displayRight.display();
  delay(1000);

  // text setup
  displayRight.setTextSize(1);
  displayRight.setTextColor(WHITE);

  time_start_ms = millis();
}


void loop() {
  displayRight.clearDisplay();
  updateTimer(); // To be replaced with a clock

  // Because of the mirror setup, everything must be printed in reverse
  displayRight.println("01/6"); // Test date
  displayRight.println("F 801"); // Test temperature
  displayRight.println("  5  "); // Test mail notification
  displayRight.println("liamE");
  
  displayRight.display();
  delay(100);
}

void updateTimer() {
  if (timerEnable) {
    time_now_s = time_duration_s - ((millis() - time_start_ms) / 1000);
    if (time_now_s < 0) {
      time_now_s = 0;
      time_duration_s = 0;
      time_start_ms = millis();
    }
  } else {
    time_now_s = time_duration_s;
  }
  
  char time_string[] = {'0', '0', ':', '0', '0', '\0'};
  time_string[4] = time_now_s / 60 / 10 + '0';
  time_string[3] = time_now_s / 60 % 10 + '0';
  time_string[1] = time_now_s % 60 / 10 + '0';
  time_string[0] = time_now_s % 60 % 10 + '0';

  displayRight.setCursor(0,0);
  displayRight.println(time_string);
}

/*********************************************************************
Smart display glasses using a 128x32 monochrome OLED.
https://github.com/Team-Automata/Display-Glasses

Inspired by the work of Alain Mauer (http://www.alainsprojects.com/). 
Uses the Adafruit GFX library and the OneSheeld Library.
*********************************************************************/

// OneSheeld Settings
#define CUSTOM_SETTINGS
#define INCLUDE_CLOCK_SHIELD

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h> // Requires a modified glcdfont.c file with mirrored characters
#include <Adafruit_SSD1306.h>
#include <OneSheeld.h>

// Display Settings
Adafruit_SSD1306 displayRight = Adafruit_SSD1306();

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// Variables for timer function
bool timerEnable = false;
long time_start_ms = 0;
long time_now_s = 0;
long time_duration_s = 90;

// Variables for the date and time
int hour, minute, second, day, month, year;

void setup()   {                
  // Display setup
  displayRight.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  displayRight.setRotation(3); // Rotate display 90 degrees
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  displayRight.display();
  delay(1000);

  // Text setup
  displayRight.setTextSize(1);
  displayRight.setTextColor(WHITE);

  // OneSheeld setup
  OneSheeld.begin();
  Clock.queryDateAndTime(); // Start the clock shield
}


void loop() {
  displayRight.clearDisplay();
  displayRight.setCursor(0,0);
  
  // Get the date and time
  hour = Clock.getHours();
  minute = Clock.getMinutes();
  second = Clock.getSeconds();
  day = Clock.getDay();
  month = Clock.getMonth();
  year = Clock.getYear();

  // Because of the mirror setup, everything must be printed in reverse
  // Display Time
  char minuteString[3];
  sprintf (minuteString, "%02i", minute);
  displayRight.print(minuteString[1]);
  displayRight.print(minuteString[0]);
  displayRight.print(":");
  char hourString[3];
  sprintf (hourString, "%02i", hour);
  displayRight.print(hourString[1]);
  displayRight.println(hourString[0]);

  // Display Seconds
  /*char secondString[3];
  sprintf (secondString, "%02i", second);
  displayRight.print(secondString[1]);
  displayRight.println(secondString[0]);*/

  // Dislplay Date
  char dayString[3];
  sprintf (dayString, "%02i", day);
  displayRight.print(dayString[1]);
  displayRight.print(dayString[0]);
  displayRight.print("/");
  char monthString[3];
  sprintf (monthString, "%02i", month);
  displayRight.print(monthString[1]);
  displayRight.println(monthString[0]);
  
  displayRight.display();
  delay(2000);
}

/*void updateTimer() {
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
}*/

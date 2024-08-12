//LIBRARIES
#include <Wire.h>                           //Arduino I2C Library
#include <Adafruit_SSD1306.h>               //OLED Screen Library
#include <Adafruit_GFX.h>                   //OLED Screen Graphics Library
#include <Adafruit_SHT31.h>                 //temp and humidity sensor library

//DEFINiTIONS
Adafruit_SHT31 sht31 = Adafruit_SHT31();

//OLED Display Defintions
#define SCREEN_WIDTH 128                                                      // OLED display width, in pixels
#define SCREEN_HEIGHT 32                                                      // OLED display height, in pixels
#define OLED_RESET    -1                                                      // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);     //Declaring the display name (display)


void setup() 
{
  Wire.begin();                                     //Initializes I2C pins on the arduino 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);        //Initializes the specific I2C channels for OLED screen
  display.display();                                //Displays current display settings   

  Serial.println("SHT31 test");
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }

  //Displays new settings
  display.clearDisplay();               //Clears previous display
  display.setTextSize(1);               //Sets font size
  display.setTextColor(WHITE);          //Sets text color (Can only be white)
  display.setCursor(0,0);               //Sets starting pixel of text [(0,0) is top left side of screen]
  display.println("Hello");             //String set to be displayed ["ln" means that the next string will be on a new line]
  display.println("World");             //String set to be displayed 
  display.display();                    //Displays current display settings to OLED
}

void loop() 
{
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  display.clearDisplay();               //Clears previous display
  display.setTextSize(1);               //Sets font size
  display.setTextColor(WHITE);          //Sets text color (Can only be white)
  display.setCursor(0,0);               //Sets starting pixel of text [(0,0) is top left side of screen]

  if (! isnan(t)) {                     //display temp if number is measured, else print error
    display.print("Temp *C = "); display.print(t); display.print("\t\t");
  } else{
    display.println("Failed to read temperature");
  }
  
  if (! isnan(h)) {                     //display hum if number is measured, else print error
    display.print("Hum. % = "); display.print(h);
  } else{
    display.println("Failed to read humidity");
  }

  display.display();                    //Displays current display settings to OLED
  delay(500);                           //delay 500ms to keep displayed valuesS
}

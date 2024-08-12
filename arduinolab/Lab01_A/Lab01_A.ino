
/* BMEN 3200
 * 
 * Displays "Hello World" to the OLED screen 
 * 
 * Name(s): 
 * Date:
 * 
  */

//LIBRARIES
#include <Wire.h>                           //Arduino I2C Library
#include <Adafruit_SSD1306.h>               //OLED Screen Library
#include <Adafruit_GFX.h>                   //OLED Screen Graphics Library
#include <Adafruit_SHT31.h>                 //temp and humidity sensor library

//DEFINiTIONS

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
  
}

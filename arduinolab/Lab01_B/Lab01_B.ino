
/* BMEN 3200
 *   
 * Each time the reading pin goes from HIGH to LOW (e.g. because of a push-button
 * press), the LED pin is toggled from LOW to HIGH or HIGH to LOW. Displays the state 
 * of LED on the the OLED display screen, and counts 
 * the number of times the button has been pushed.    
 *  
 * Adapted from (https://www.arduino.cc/en/tutorial/switch) and
 * Sparkfun SIK Tutorial (https://www.sparkfun.com/sikcode)
 * 
 * Name(s): 
 * Date: 
 */

//LIBRARIES
#include <Wire.h>                           //Arduino I2C Library
#include <Adafruit_SSD1306.h>               //OLED Screen Library
#include <Adafruit_GFX.h>                   //OLED Screen Graphics Library

//DEFINITIONS
#define ReadingPin 12                        //Pin associated with reading signal from button
#define LEDPin 11                            //Pin associated with LED

//OLED Display Defintions
#define SCREEN_WIDTH 128                                                      // OLED display width, in pixels
#define SCREEN_HEIGHT 32                                                      // OLED display height, in pixels
#define OLED_RESET    -1                                                      // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);     //Declaring the display name (display)


//VARIABLES
int reading;                           //The current reading from the reading pin
int previous = HIGH;                   //The previous reading from the LED pin
int LEDstate = HIGH;                   //The current state of the LED pin
int buttonPressCount;                  //Counts number of times button has been pressed

// the following variables are long's because the time, measured in miliseconds,
// which will quickly become a bigger number than can be stored in an int.
long timer = 0;                          //Measures the last time the reading pin was toggled
long debounce = 500;                     //What is the purpose of debounce?

void setup()
{
  pinMode(ReadingPin, INPUT);           //Initiates the button pin as input pin which which the arduino is reading (Requires external pullup resistor)
//pinMode(ReadingPin, INPUT_PULLUP);    //Initializes button pin as input pin which which the arduino is reading with internal pullup resistor on arduino
  pinMode(LEDPin, OUTPUT);              //Initializes LED pin as output pin which which the arduino will send a signal to

  digitalWrite(LEDPin, LEDstate);          //Set initial LED state (ON)

  Wire.begin();                                     //Initializes I2C pins on the arduino 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);        //Initializes the specific I2C channels for OLED screen
  display.display();                                //Displays current display settings to OLED  

  //Displays new settings
  display.clearDisplay();               //Clears previous display
  display.setTextSize(1);               //Sets font size
  display.setTextColor(WHITE);          //Sets text color (Can only be white)
  display.setCursor(0,0);               //Sets starting pixel of text [(0,0) is top left side of screen]
  display.println("Hello");             //String set to be displayed ["ln" means that the next string will be on a new line]
  display.println("World");             //String set to be displayed 
  display.display();                    //Displays current display settings to OLED

  delay(3000);                          //Delays code for 3 secs before going into loop
}

void loop()
{
  reading = digitalRead(ReadingPin);         //Continually reads state of input pin

  //TURN ON or OFF LED when button is pushed (goes from a "HIGH" state to "LOW" state)
  if (reading == LOW && previous == HIGH && (millis() - timer) > debounce)
  { 
    buttonPressCount++;                   //Adds 1 to the count
    
    //Turn LED ON
    if (LEDstate == LOW)                   
    {
      LEDstate = HIGH;
    }
    //Turn LED OFF
    else
    {
      LEDstate = LOW;             
    }
    timer = millis();                      //resets timer [millis() is the current length of time the the program has been runnining]        
  }
  
  OLED_BUTTON(LEDstate);                   //Function that Updates display to indicate if LED is ON or OFF and number of times the button has been pressed

  digitalWrite(LEDPin, LEDstate);          //Changes state of LED
  previous = reading;                      //Updates "previous" to last state of "reading"
}

//FUNCTIONS

void OLED_BUTTON(int state)                          //Updates display to indicate if LED is ON or OFF and number of times the button has been pressed
{
    
  if (state == HIGH)
  {
    display.clearDisplay();                 //Font size and color will keep previous settings if not updated
    display.setCursor(0,0);
    display.println("LED is: ON");
    display.println();
    display.println("Button has been");
    display.print("pressed: ");
    display.print(buttonPressCount);            //Displays value of variable
    display.print(" Time(s)");
    display.display();
  }

  //Display settings when LED is OFF 
  else
  {
    display.clearDisplay();               //Clear Display
    display.setCursor(0,0);
    display.println("LED is: OFF");
    display.println();
    display.println("Button has been");
    display.print("pressed: ");
    display.print(buttonPressCount);            //Displays value of variable
    display.print(" Time(s)");
    display.display();
  }
}


/* 
  */

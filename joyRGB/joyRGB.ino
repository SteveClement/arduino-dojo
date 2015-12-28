// Analog joystick to RGB Neopixel test with Serial debug

#include <Wire.h>
#include <Adafruit_NeoPixel.h>

// Pin where first neopixel is connected
#define PIN 6

// Pins where Left/Right and Up/Down are connected. Essentially they are 10k potentiometers who are mid-value when idle
#define LRPin A0
#define UDPin A1

// Pins where the LEDs are connected
#define ledPin0 12
#define ledPin1 11

// Instantiate pixel (1 pixel, on pin 6)
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

// Variables to store the value of the potentiometers
int LR = 0;
int UD = 0;

// Time periods of blinks in milliseconds (1000 to a second).
const unsigned long greenLEDinterval = 500;
const unsigned long redLEDinterval = 1000;

// Variable holding the timer value so far. One for each "Timer"
unsigned long greenLEDtimer = millis();
unsigned long redLEDtimer = millis();

// unsigned long for millis() it gets huge, fast. This can be used to see how long our code runs on our Arduino
unsigned long currentMillis = millis();

void setup() {
  // put your setup code here, it will be run once

  // Setting up Serial console
  Serial.begin(9600);
  Serial.println("Starting Joystick Test…");

  // Setting up analog inputs
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);

  pixel.begin();
  pixel.show();
}

// Toggles the LED pin and makes a note when it got toggled
void toggleGreenLED ()
  {
   if (digitalRead(ledPin1) == LOW)
      digitalWrite(ledPin1, HIGH);
   else
      digitalWrite(ledPin1, LOW);

  // remember when we toggled it
  greenLEDtimer = millis();  
  }  // end of toggleGreenLED

void toggleRedLED ()
  {
   if (digitalRead(ledPin0) == LOW)
      digitalWrite(ledPin0, HIGH);
   else
      digitalWrite(ledPin0, LOW);

  // remember when we toggled it
  redLEDtimer = millis ();  
  }  // end of toggleRedLED

void loop() {
  // put your main code here, it will be run repeatedly

  // Read the analog values of Left/Right
  LR = analogRead(LRPin);
  
  // Read the analog values of Up/Down
  UD = analogRead(UDPin);

  // Normalizing values from potentiometers and passing to the pixel, don't forget to show your pixel
  pixel.setPixelColor(0, pixel.Color(UD*0.25,LR*0.25,LR*0.25));
  pixel.show();

  // Handling the blink of one LED.
  //if ( (millis() - greenLEDtimer) >= greenLEDinterval)
  //   toggleGreenLED();

  // The other LED is controlled the same way. Repeat for more LEDs
  //if ( (millis() - redLEDtimer) >= redLEDinterval) 
  //   toggleRedLED();

  if (UD > 1000) {
    Serial.println("U/D Limit reached toggling RedLED");
    toggleRedLED();
  }

  if (LR > 1000) {
    Serial.println("L/R Limit reached toggling GreenLED");
    toggleGreenLED();
  }
}

#include "U8glib.h" // include the U8glib library for OLED display

U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NONE); // create an OLED display object

// define constants for the ultrasonic distance sensors trigger and echo pins
const int TRIG_PIN = 13;
const int ECHO_PIN = 12;

unsigned Duration; // variable for the duration of the ultrasonic pulse
int Distance = 0; // variable for the distance measured by the sensor
int Distance1 = 0; // variable for the first distance measurement
int Distance2 = 0; // variable for the second distance measurement
int GetSpeed; // variable for storing the calculated speed
String PrintSpeed; // variable for the speed as a string

void setup()
{
    pinMode(TRIG_PIN, OUTPUT); // sets the trigger pin as output
    pinMode(ECHO_PIN, INPUT); // sets the echo pin as input
    Serial.begin(9600); // initialize the serial port
    pinMode(7, INPUT_PULLUP); // set pin 7 as an input with a button
}

void loop()
{
    // only run the following code if the button connected to pin 7 is pressed (LOW)
    if (digitalRead(7) == LOW) 
    { 
        oled.firstPage(); 
        do
        {
            draw(); 
        } while (oled.nextPage());
        // measure the distance for the first time
        Distance1 = GetDistance(); 
        // wait for 250 milliseconds
        delay(250); 
        // measure the distance for the second time
        Distance2 = GetDistance(); 
        // calculate the speed by dividing the distance by the time
        GetSpeed = ((Distance2 - Distance1) / 0.250) * 0.036;
        PrintSpeed = String(GetSpeed): 

        // code for printing what is on the oled display in the serial port
        Serial.print("Hastighet:");
        Serial.println(GetSpeed);
        Serial.print("km/h:");
        delay(100);
    }
}

// function for measuring the distance to an object using the ultrasonic sensor
float GetDistance()
{  
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2); 
    digitalWrite(TRIG_PIN, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(TRIG_PIN, LOW); 
    // assign the duration of the pulse on the echo pin
    Duration = pulseIn(ECHO_PIN, HIGH); 

    // calculate the distance by multiplying the duration by the speed of sound and dividing by 2
    Distance = Duration * 0.034 / 2; 
    return Distance; 
}

// function for updating the OLED display with the current speed
void draw(void)
{
    // Set font to Helvetica size 24  
    oled.setFont(u8g_font_helvB24);
    // Draw the variable that contains the messured speed
    oled.drawStr(0, 40, String(abs(GetSpeed)).c_str());
    // draw the string "km/h"
    oled.drawStr(50, 40, String("km/h").c_str());
}

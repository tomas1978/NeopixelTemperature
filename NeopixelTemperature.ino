#include <Adafruit_NeoPixel.h>
 
#define PIN      6
#define N_LEDS   24
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
 
int tempSensorPort=0;

void setup() {
  strip.begin();
  Serial.begin(9600);
}
 
void loop() {
  strip.fill(0,0,0);  
  // reads the value of the potentiometer (value between 0 and 1023)
  int val = sensorToTemp(tempSensorPort); 
  Serial.println(val);
  
  //Convert sensor value to a value between 0 and N_LEDS
  val = map(val, -20, 50, 0, N_LEDS);
  
  Serial.println(val);
  int blue=255, red=0;
  for(int i=0;i<val;i++){
    //strip.setPixelColor(i,255,0,0);
    blue-=11*val;
    red+=11*val;
    strip.setPixelColor(i,red,0,blue);
  }
  strip.show();
  delay(10);
}

//Convert from analog sensor value to temperature in degrees C
float sensorToTemp(int analogPort) {
  int rawAnalogValue = analogRead(analogPort);
    float volt = (float)rawAnalogValue * 5.0 / 1023.0;
    float degC = (volt-0.5) * 100.0;
    return degC;
}

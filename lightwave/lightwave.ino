/**
 * This Arduino project displays wave with a line of LEDs.
 * The LEDs do not need to be placed with same distances.
 *
 * Author: Jakob Voss
 * License: Public Domain
 */
#include <math.h>

// customize here
byte ledPin[] = {5,6,9};    // PWM pins
float ledPos[] = {0,15,21}; // positions in mm
float waveLength = 60;      // in mm
float waveSpeed  = 0.018;   // in m/s (=mm/ms)

// the height is measured in the range 0...255 but one
// can use values outside of this range
int waveHeight  = 300;
int normalHeight = 100; 


void setup() {
  Serial.begin(9600);
  for (byte i = 0; i < sizeof(ledPin); i++) {
    pinMode(ledPin[i], OUTPUT);
  }
}

void loop() {
  for (byte i = 0; i < sizeof(ledPin); i++) {
    analogWrite( ledPin[i], waveAmplitude( millis(), ledPos[i] ) );
  }
  // we may delay a few miliseconds or do something else here...
}

// Returns the wave's amplitude (0..255) at time t and position p.
byte waveAmplitude(unsigned long t, float p) {
  p -= t * waveSpeed;

  float x = p / waveLength;
  x = x - (int)x;
 
  float amp = waveform(x) * waveHeight / 2 + normalHeight;

  return (byte) constrain(amp,0,255);
}

// Any function [0...1] -> [-1..1]
double waveform(double x) {
    // TODO: cnoidal wave is more realistic
    return sin( x * 2*M_PI );
}


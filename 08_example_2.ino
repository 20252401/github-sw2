#define PIN_LED  9
#define PIN_TRIG 12   // sonar sensor TRIGGER
#define PIN_ECHO 13   // sonar sensor ECHO

#define SND_VEL 346.0     // sound velocity at 24 celsius degree (unit: m/sec)
#define INTERVAL 25       // sampling interval (unit: msec)
#define PULSE_DURATION 10 // ultra-sound Pulse Duration (unit: usec)
#define _DIST_MIN 100.0   // minimum distance to be measured (unit: mm)
#define _DIST_MAX 300.0   // maximum distance to be measured (unit: mm)

#define TIMEOUT ((INTERVAL / 2) * 1000.0) // maximum echo waiting time (unit: usec)
#define SCALE (0.001 * 0.5 * SND_VEL)     // coefficient to convert duration to distance

unsigned long last_sampling_time = 0;   

void setup() {
 
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);  
  pinMode(PIN_ECHO, INPUT);   
  digitalWrite(PIN_TRIG, LOW);  
  
  Serial.begin(57600);
}

void loop() { 
  float distance;

  if (millis() < (last_sampling_time + INTERVAL))
    return;

  distance = USS_measure(PIN_TRIG, PIN_ECHO); 

  int pwmVal = 255; 

  if ((distance == 0.0) || (distance < _DIST_MIN) || (distance > _DIST_MAX)) {
      pwmVal = 255;
  } else {
      if (distance <= 200.0) {
          float ratio = (distance - 100.0) / (200.0 - 100.0); 
          pwmVal = 255 - (int)(ratio * 255.0); 
      }
      else {
          float ratio = (300.0 - distance) / (300.0 - 200.0); 
          pwmVal = 255 - (int)(ratio * 255.0);
      }
  }
  
  analogWrite(PIN_LED, pwmVal);

  Serial.print(distance);
  Serial.print(" ");
  Serial.println(pwmVal);

  last_sampling_time += INTERVAL;
}

float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE; 
}

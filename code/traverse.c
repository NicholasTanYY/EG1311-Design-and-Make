#include <Servo.h>
Servo myservo;
int SERVO_PIN = 2;              // Pin for servo on Arduino
int pos;                        // Angle for servo
int TRIG_PIN = 13;              // Pin for TRIG pin of Ultrasonic Distance sensor on Arduino
int ECHO_PIN = 12;              // Pin for ECHO pin of Ultrasonic Distance sensor on Arduino
int MOTOR_PIN1 = 6;             // Pin for motor 1 on Arduino
int MOTOR_PIN2 = 5;             // Pin for motor 2 on Arduino
int MOTOR_PIN3 = 11;            // Pin for motor 3 on Arduino
int MOTOR_PIN4 = 3;             // Pin for motor 4 on Arduino    
float SPEED_OF_SOUND = 0.0345;  // Used for calculating distance away from Ultrasonic Distance Sensor

void setup() {
  pinMode(MOTOR_PIN1, OUTPUT);  // Pin mode for motor 1
  pinMode(MOTOR_PIN2, OUTPUT);  // Pin mode for motor 2
  pinMode(MOTOR_PIN3, OUTPUT);  // Pin mode for motor 3
  pinMode(MOTOR_PIN4, OUTPUT);  // Pin mode for motor 4
  pinMode(TRIG_PIN, OUTPUT);    // Pin mode for TRIG on Ultrasonic Distance sensor
  digitalWrite(TRIG_PIN, LOW);  // Switches Ultrasonic Distance sensor's TRIG off
  pinMode(ECHO_PIN, INPUT);     // Pin mode for ECHO on Ultrasonic Distance sensor
  Serial.begin(9600);           // Initialize serial communication
  myservo.attach(SERVO_PIN);    // Attaches servo to corresponding pin on Arduino
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);             // Activate Ultrasonic Distance sensor
  delayMicroseconds(10);                    // for 10 microseconds
  digitalWrite(TRIG_PIN, LOW);              // Turns off Ultrasonic Distance sensor
  int microsecs = pulseIn(ECHO_PIN, HIGH);  // Measures duration of pulse
  float cms = microsecs*SPEED_OF_SOUND/2;   // Calculates distance of obstacle from Ultrasonic Distance sensor
  Serial.println(cms);                      // Prints distance measured in the serial monitor
  if (cms >= 8)                             // All motors run when distance from Ultrasonic Distance sensor >= 8cm
  {
    digitalWrite(MOTOR_PIN1, HIGH);
    digitalWrite(MOTOR_PIN2, HIGH);
    digitalWrite(MOTOR_PIN3, HIGH);
    digitalWrite(MOTOR_PIN4, HIGH);    
  }
  else                                      // All motors stop when distance from Ultrasonic Distance sensor < 8cm
  {
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, LOW);
    digitalWrite(MOTOR_PIN3, LOW);
    digitalWrite(MOTOR_PIN4, LOW);
    delay(1000);
  
    for (pos = 0; pos <= 180; pos += 1) {   // Rotate servo by 180 degrees
      myservo.write(pos);
      delay(10);                       
    }
    for (pos = 180; pos >= 0; pos -= 1) {   // Rotate servo back to original position
      myservo.write(pos);
      delay(10);                      
    }
  }
  delay(5);
}
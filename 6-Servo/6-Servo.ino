#include <Servo.h> // Include the library through Servo.h

const int servoPin = 10;
const int potPin = A0;

// Declare a Servo object from the library
Servo myServo;

void setup(){
	// Servo must be initialized through attach
	myServo.attach(servoPin);

	// Begin the serial communication
	Serial.begin(9600);
}

void loop(){
	int potVal = analogRead(potPin);
	int servoPos = map(potVal, 0, 1023, 5, 175); // Map the potentiometer value to safe servo position

	// Write the position to the servo (~0-180 deg)
	myServo.write(servoPos);

	// Declare and initialize a static (keeps value between loops) prevTime
	// to keep time without delay
	static unsigned long prevTime = 0;

	// Use the millis function to trigger when prevTime is elapsed by 1000ms
	if((millis() - prevTime) >= 1000){
		prevTime = millis(); // update prevTime
		// Show on Serial in pretty text
		Serial.println("Read " + String(potVal) + ", setting Servo to " + String(servoPos));
	}
}


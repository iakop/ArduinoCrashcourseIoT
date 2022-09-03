// Define the pins for LED and potentiometer
const int ledPin = 11;
const int potPin = A0;

void setup(){
	//Set pinMode for ledPin:
	pinMode(ledPin, OUTPUT);

	// pinMode makes no difference for analog pins
	// But can influence signal on outside electronics
	pinMode(potPin, INPUT); 

	// Setup the UART serial
	Serial.begin(9600);
}


void loop(){
	int potVal = analogRead(potPin);
	int ledVal = potVal/4; // Divided by four since the 0..1023 range is 4 times larger than 0..255

	// Show on Serial what we wrote, in pretty text
	Serial.println("Read " + String(potVal) + ", setting LED to " + String(ledVal));

	// Try viewing this in Serial Plotter
	//Serial.println("potVal:" + String(potVal) + "," + "ledVal:" + String(ledVal));

	// Write to LED
	analogWrite(ledPin, ledVal);
}
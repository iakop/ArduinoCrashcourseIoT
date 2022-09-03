// Set an integer value (whole number) with the name "ledPin"
const int ledPin = 11;

// setup() runs exactly once at the start of the program
void setup(){
	pinMode(ledPin, OUTPUT); // pinMode configures pin to in- or output
}

void loop(){
	// Turn the LED on and off with 1000ms interval
	digitalWrite(ledPin, HIGH); // HIGH means on, as in high voltage
	delay(1000); // Halts the Arduino for 1000ms, so the light stays on for that interval
	digitalWrite(ledPin, LOW);
	delay(1000); // Needed so it doesn't immediately turn on again
}
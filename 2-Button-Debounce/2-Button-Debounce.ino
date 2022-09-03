// Set a constant integer value for LED and button 
const int ledPin = 11;
const int buttonPin = 12;

// Boolean values can only be either true or false
bool ledState = false;
bool buttonVal, prevButtonVal = false; // You can declare and assign many at once

void setup(){
	pinMode(ledPin, OUTPUT); // Like in blinky
	pinMode(buttonPin, INPUT); // THe button is an IN-put
}

void loop(){
	// Always get new button data 
	buttonVal = digitalRead(buttonPin);

	// Check the button is pressed/released "!=" means different from, or not equal to
	if(buttonVal != prevButtonVal){
		// Only if the button was pressed
		if(buttonVal == HIGH){
			ledState = !ledState; // Set ledState to opposite of before
			digitalWrite(ledPin, ledState); // And write to the pin accordingly
		}

		// Update the previous button value to the current one
		prevButtonVal = buttonVal;

		delay(50); // Wait a bit for the signal to settle
	}
}
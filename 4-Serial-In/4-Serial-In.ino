// Set a constant integer value for LED
const int ledPin = 11;

void setup(){
	// Setup LED
	pinMode(ledPin, OUTPUT);

	// Setup the UART Serial communication with computer at 9600 B/s
	Serial.begin(9600);
	Serial.println("To set LED, write \"on\", or \"off\":"); // Prompt for input
}

void loop(){
	// Keep looping until you send a serial string
	if(Serial.available() > 0){
		// Read into inStr, and trim the lineshift off the end
		String inStr = Serial.readString();
		inStr.trim();

		// Print what we received
		Serial.println("Received: " + inStr);

		// Turn on or off, if correct string was sent
		if(inStr == "on"){
			digitalWrite(ledPin, HIGH);
			Serial.println("Turning ON pin " + String(ledPin) + "\'s LED"); // Print what we do
		}
		else if(inStr == "off"){
			digitalWrite(ledPin, LOW);
			Serial.println("Turning OFF pin " + String(ledPin) + "\'s LED");
		}
		else{
			Serial.println("Invalid input!");
		}
	}
}
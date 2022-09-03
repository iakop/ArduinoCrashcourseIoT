// Keep track of time
unsigned int count = 0;

void setup(){
	// Setup the UART Serial communication with computer at 9600 B/s
	Serial.begin(9600);
	Serial.println("Hello World!"); // Write Hello World to terminal
}

void loop(){
	// Write how many seconds have passed
	Serial.print("Now ");
	Serial.print(count);
	Serial.println(" seconds have passed!");

	count++; // Increment count by 1

	delay(1000); // Wait one second
}
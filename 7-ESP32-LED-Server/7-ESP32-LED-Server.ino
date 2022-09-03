// Include ESP32 specific libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Write WiFi Access Point settings
const String ssid = "MyESP32";
const String pass = "12345678";
const String ip = "192.168.0.1";

// Declare and assign ledPin
const int ledPin = 25;

// Enter settings for Websocket
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Our function definition for websocket events
void onEvent( AsyncWebSocket *server,
				AsyncWebSocketClient *client,
				AwsEventType type,
				void *arg,
				uint8_t *data,
				size_t len ){
	switch (type) {
	case WS_EVT_CONNECT:
		Serial.println("WebSocket client #" + String(client->id()) + " connected from: " + client->remoteIP());
		break;
		case WS_EVT_DATA:
		handleWsMsg(arg, data, len);
		break;
		default:
		break;
	}
}

// What happens when receiving a websocket message
void handleWsMsg(void *arg, uint8_t *data, size_t len){
	// Point to websocket info object from arg
	AwsFrameInfo * info = (AwsFrameInfo*)arg;

	// Verify that data is formatted correctly and final
	if( info->final
		&& info->index == 0
		&& info->len == len
		&& info->opcode == WS_TEXT ){

	data[len] = '\0'; // Create a valid c string by marking the end
	String dataStr = String((char*)data); // Cast the string to search it

	// Convert the data string to an integer for analogWrite
	int ledLvl = dataStr.toInt();

	String status = "Received " + dataStr + ", set LED to " + String(ledLvl);
	ws.textAll(status); // Write status over websocket
	Serial.println(status); // Write status on Serial
	
	analogWrite(ledPin, ledLvl); // Write the level to LED
	}
}

void setup(){
	// Begin Serial, 115200 baud to not hold up socket for long
	Serial.begin(115200);

	// Initialize SPIFFS to serve webpage
	if(!SPIFFS.begin()){
		Serial.println("SPIFFS error");
		return;
	}


	// Convert IP from string to IP object
	IPAddress myIP;
	myIP.fromString(ip.c_str());

	// Start WiFi Access Point with given settings
	WiFi.mode(WIFI_AP_STA);
	WiFi.softAPConfig(myIP, myIP, IPAddress(255, 255, 255, 0));
	WiFi.softAP(ssid.c_str(), pass.c_str());

	// Write the Access Point details on Serial
	Serial.println("SSID: " + ssid + ", IP: " + ip + ", Pass: " + pass);

	// Route for root / web page
	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
		request->send(SPIFFS, "/index.html", String(), false);
	});

	// Register Websocket events and handler
	ws.onEvent(onEvent);
	server.addHandler(&ws);

	// Start server
	server.begin();
}

void loop() {
	// Clean up clients every loop
	ws.cleanupClients();
}

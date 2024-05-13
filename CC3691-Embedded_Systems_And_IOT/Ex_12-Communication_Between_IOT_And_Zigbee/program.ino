void setup() {
Serial.begin(9600); // Set the baud rate to 9600
}
void loop() {
// Send data to XBee module
Serial.println("Hello XBee!");
// Receive data from XBee module
if (Serial.available() > 0) {
String receivedData = Serial.readString();
Serial.println("Received data: " + receivedData);
}
delay(1000); // Delay for 1 second
}

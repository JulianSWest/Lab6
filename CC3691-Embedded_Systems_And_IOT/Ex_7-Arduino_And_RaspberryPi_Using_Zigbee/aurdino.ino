void setup() {
Serial.begin(9600); // Begin serial communication
}
void loop() {
Serial.println("Hello from Arduino!"); // Send data over serial
delay(1000); // Wait for 1 second
}

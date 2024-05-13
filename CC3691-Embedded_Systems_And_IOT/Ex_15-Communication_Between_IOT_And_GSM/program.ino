#include<SoftwareSerial.h>
SoftwareSerial sim8001(0,1);
#define button1 7
bool button_state;
void setup()
{
pinMode(button1,INPUT_PULLUP);
sim8001.begin(9600);
Serial.begin(9600);
delay(100);}
void loop()
{
button_state=digitalRead(button1);
if(button_state==LOW)
{
Serial.println("Button pressed");
delay(200);
SendSMS();
}
if(sim8001.available())
Serial.write(sim8001.read());
}
void SendSMS()
{
Serial.println("Sending SMS...");
sim8001.print("AT+CMGF=1\r");
delay(100);
sim8001.print("AT+CMGS=\"+9865533668\"\r");
delay(100);
sim8001.print("SIM8001 is working");
delay(100);
sim8001.println();
Serial.println("Text Sent.");
delay(400);
}

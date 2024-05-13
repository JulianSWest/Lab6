#include<Servo.h>

int IRSensor = 7;
int LED = 38;
int LED2 = 39;

const int tr1 = 13, eh1 = 12, tr2 = 6, eh2 = 5;
const int bz = 2;
unsigned long val1, dis1, val2, dis2;
Servo myservo1;
Servo myservo2;
int pos = 0;

const int g1 = 35;
const int y1 = 36;
const int r1 = 37;
const int g2 = 32;
const int y2 = 33;
const int r2 = 34;
const int g3 = 29;
const int y3 = 30;
const int r3 = 31;
const int g4 = 26;
const int y4 = 27;
const int r4 = 28;
const int pRed = 25;
const int pgreen = 24;
const int pIN = 23;

void setup() {
  // put your setup code here, to run once:
  pinMode (IRSensor, INPUT);
  pinMode (LED, OUTPUT);
  pinMode (LED2, OUTPUT);

  pinMode(tr1, OUTPUT);
  pinMode(tr2, OUTPUT);
  pinMode(bz, OUTPUT);
  pinMode(eh1, INPUT);
  pinMode(eh2, INPUT);
  myservo1.attach(9);
  myservo2.attach(3);
  myservo1.write(pos);
  myservo2.write(pos);

  pinMode (r1, OUTPUT);
  pinMode (y1, OUTPUT);
  pinMode (g1, OUTPUT);
  pinMode (r2, OUTPUT);
  pinMode (y2, OUTPUT);
  pinMode (g2, OUTPUT);
  pinMode (r3, OUTPUT);
  pinMode (y3, OUTPUT);
  pinMode (g3, OUTPUT);
  pinMode (r4, OUTPUT);
  pinMode (y4, OUTPUT);
  pinMode (g4, OUTPUT);
  pinMode (pRed, OUTPUT);
  pinMode (pgreen, OUTPUT);
  pinMode (pIN, INPUT);

  digitalWrite (r1, HIGH);
  digitalWrite (r2, HIGH);
  digitalWrite (r3, HIGH);
  digitalWrite (r4, HIGH);
  digitalWrite (pRed, HIGH);

  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  //Checking if there is any train or not..
  int sensor_status = digitalRead (IRSensor);
  if (sensor_status == 1) {
    digitalWrite(LED, HIGH); // Red LED ON When a train is coming
    digitalWrite(LED2, LOW); // Turning off Green LED
    railSystem();
  }
  else if (sensor_status == 0)
  {
    digitalWrite(LED2, HIGH); //Green LED ON When there is no train
    digitalWrite(LED, LOW);  //Turning off Red LED
    StreetLight();
  }
}

//function for railway system..
void railSystem() {
  digitalWrite(tr1, LOW);     //Clearing Ultrasonic Sensor 1's Trigger pin
  delayMicroseconds(2);
  digitalWrite(tr1, HIGH);
  delayMicroseconds(10);      //Activating trigger for 10ms
  digitalWrite(tr1, LOW);
  val1 = pulseIn(eh1, HIGH);  //Receiving echo
  dis1 = (val1 * 0.0343) / 2; // Calculating Train1 Distance

  digitalWrite(tr2, LOW);     //Clearing Ultrasonic Sensor 2's Trigger pin
  delayMicroseconds(2);
  digitalWrite(tr2, HIGH);
  delayMicroseconds(10);      //Activating trigger for 10ms
  digitalWrite(tr2, LOW);
  val2 = pulseIn(eh2, HIGH);  //Receiving echo
  dis2 = (val2 * 0.0343) / 2;  // Calculating Train2 Distance

  Serial.println("distance is ");
  Serial.println(dis1);             //Showing Distance on Virtual Terminal
  Serial.println(dis2);
  if (dis1 < 300 || dis2 < 300)    //Checking train distance
  {
    for (pos = 0; pos <= 90; pos += 1) {
      myservo1.write(pos);          //Activating barrier with servo motors
      myservo2.write(pos);
      //delay(10);
    }

    delay(1000);
    digitalWrite(tr1, LOW);
    delayMicroseconds(2);
    digitalWrite(tr1, HIGH);
    delayMicroseconds(10);
    digitalWrite(tr1, LOW);
    val1 = pulseIn(eh1, HIGH);
    dis1 = (val1 * 0.0343) / 2;

    digitalWrite(tr2, LOW);
    delayMicroseconds(2);
    digitalWrite(tr2, HIGH);
    delayMicroseconds(10);
    digitalWrite(tr2, LOW);
    val2 = pulseIn(eh2, HIGH);
    dis2 = (val2 * 0.0343) / 2;

    if (dis1 < 200 || dis2 < 200) {   //Checking distance for buzzer sounf
      digitalWrite(bz, HIGH);         //buzzer on
      Serial.println("distance2 is ");
      Serial.println(dis1);
      Serial.println(dis2);
    }
  } else if (dis1 >= 300 && dis2 >= 300)
  {
    for (pos = 90; pos >= 0; pos -= 1) {
      myservo1.write(pos);               //Deactivating barrier with servo motors
      myservo2.write(pos);
     // delay(10);
    }

    digitalWrite(bz, LOW);             //Buzzer Off
    delay(200);
  }
}

//function for StreetLight system..
void StreetLight() {

  int crossIn = digitalRead (pIN);      //Checking if the pedesrtian light switch is ON or OFF
  if (crossIn == HIGH) {
    WalkCycle();                        //If sqitch is on start walkCycle function
  }
  else
  {
    delay(50);
    digitalWrite (r1, LOW);             //Road light
    digitalWrite(g1, HIGH);
    digitalWrite(r2, HIGH);
    digitalWrite(r3, HIGH);
    digitalWrite(r4, HIGH);
    delay(1500);                        //Waiting time
  }
  int crossIn2 = digitalRead (pIN);
  if (crossIn2 == HIGH) {
    WalkCycle();
  }
  else
  {
    digitalWrite(g1, LOW);

    digitalWrite(y1, HIGH);
    digitalWrite(r2, HIGH);
    digitalWrite(r3, HIGH);
    digitalWrite(r4, HIGH);
    delay(800);
  }
  int crossIn3 = digitalRead (pIN);
  if (crossIn3 == HIGH) {
    WalkCycle();
  }
  else
  {
    digitalWrite(y1, LOW);
    digitalWrite(r2, LOW);

    digitalWrite(r1, HIGH);
    digitalWrite(g2, HIGH); //2nd light
    digitalWrite(r3, HIGH);
    digitalWrite(r4, HIGH);
    delay(1500);
  }
  int crossIn4 = digitalRead (pIN);
  if (crossIn4 == HIGH) {
    WalkCycle();
  }
  else
  {
    digitalWrite(g2, LOW);

    digitalWrite(y2, HIGH);
    digitalWrite(r1, HIGH);
    digitalWrite(r3, HIGH);
    digitalWrite(r4, HIGH);
    delay(800);
  }
  int crossIn5 = digitalRead (pIN);
  if (crossIn5 == HIGH) {
    WalkCycle();
  }
  else
  {
    digitalWrite(y2, LOW);
    digitalWrite(r3, LOW);

    digitalWrite(g3, HIGH); //3rd light
    digitalWrite(r1, HIGH);
    digitalWrite(r2, HIGH);
    digitalWrite(r4, HIGH);
    delay(1500);
  }
  int crossIn6 = digitalRead (pIN);
  if (crossIn6 == HIGH) {
    WalkCycle();
  }
  else
  {
    digitalWrite(g3, LOW);

    digitalWrite(y3, HIGH);
    digitalWrite(r1, HIGH);
    digitalWrite(r2, HIGH);
    digitalWrite(r4, HIGH);
    delay(800);
  }
  int crossIn7 = digitalRead (pIN);
  if (crossIn7 == HIGH) {
    WalkCycle();
  }
  else
  {
    digitalWrite(y3, LOW);
    digitalWrite(r3, LOW);
    digitalWrite(r4, LOW);

    digitalWrite(g4, HIGH); //4th light
    digitalWrite(r1, HIGH);
    digitalWrite(r2, HIGH);
    digitalWrite(r3, HIGH);
    delay(1500);
  }
  int crossIn8 = digitalRead (pIN);
  if (crossIn8 == HIGH) {
    WalkCycle();
  }
  else
  {
    digitalWrite(g4, LOW);
    digitalWrite(r4, LOW);


    digitalWrite(y4, HIGH);
    digitalWrite(r1, HIGH);
    digitalWrite(r2, HIGH);
    digitalWrite(r3, HIGH);
    delay(800);
  }
  digitalWrite(y4, LOW);
  digitalWrite(r4, LOW);
  digitalWrite(r1, LOW);
}

//function for Pedestrian Light..
void WalkCycle() {
  delay(300);
  //making all the street light OFF
  digitalWrite (g1, LOW); digitalWrite (g2, LOW); digitalWrite (g3, LOW); digitalWrite (g4, LOW);
  digitalWrite (y1, LOW); digitalWrite (y2, LOW); digitalWrite (y3, LOW); digitalWrite (y4, LOW);
  digitalWrite (r1, HIGH); digitalWrite (r2, HIGH); digitalWrite (r3, HIGH); digitalWrite (r4, HIGH);


  digitalWrite (pgreen, HIGH); //Pedestrian Green Light ON
  digitalWrite (pRed, LOW);    //Pedestrian Red Light Off
  delay (1500);
  digitalWrite (pgreen, LOW);  //Turn off pedestrian light after 3sec
  delay(100);
  for (int x = 0; x < 5; x++) {  // Flash green Ped LED 5times
    digitalWrite(pgreen, HIGH);
    delay(100);
    digitalWrite(pgreen, LOW);
    delay(100);
  }
  digitalWrite(pRed, HIGH);   //Turn of pedestrian Red LED
}

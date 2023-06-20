// AIM 

/* if distance is (0, 5cm) then beep and show dist 
else if b/w (5,10) then show temp and dist
else if b/w (10,max) then show humid and dist*/


#include <LiquidCrystal.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN 2
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(7,8,9,10,11,12);
#define trigPin 4 // define TrigPin
#define echoPin 6 // define EchoPin.
#define MAX_DISTANCE 200 // Maximum sensor distance is rated at 400-500cm.
float timeOut = MAX_DISTANCE * 60,dist; 
int soundVelocity = 340; // define sound speed=340m/s

void setup() {
  pinMode(trigPin,OUTPUT);// set trigPin to output mode
  pinMode(echoPin,INPUT); // set echoPin to input mode
  pinMode(3,OUTPUT);//buzzer
  dht.begin();
  lcd.begin(16,2);
}

void loop() {
  delay(100); // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
   dist=getSonar();// in cm
   delay(250);
   float h = dht.readHumidity();
   float t = dht.readTemperature();
if(dist>10.0){
  lcd.setCursor(0,0);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.setCursor(0,1);
  lcd.print("Distance: ");
  lcd.print(dist);
  lcd.print("CM");
  delay(1000);
  lcd.clear();
}
else if(dist>5.0){
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Distance: ");
  lcd.print(dist);
  lcd.print("CM");
  delay(1000);
  lcd.clear(); 
}
else{
  buzz();
  lcd.setCursor(0,0);
  lcd.print("TOO CLOSE");
  lcd.setCursor(0,1);
  lcd.print("Distance: ");
  lcd.print(dist);
  lcd.print("CM");
  delay(1000);
  lcd.clear(); 
}
}

float getSonar() {
  unsigned long pingTime;
  float distance;
  digitalWrite(trigPin, HIGH); // make trigPin output high level lasting for 10μs to triger HC_SR04,
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pingTime = pulseIn(echoPin, HIGH, timeOut); // Wait HC-SR04 returning to the high level and measure out this waitting time
  distance = (float)pingTime * soundVelocity / 2 / 10000; // calculate the distance according to the time
  return distance; // return the distance value
}
void buzz(){
  digitalWrite(3,HIGH);//active buzzer pin set to 3
  delay(2000);
  digitalWrite(3,LOW);
}

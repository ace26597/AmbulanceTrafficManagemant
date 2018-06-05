/*   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

Servo myservo10;
Servo myservo20;
Servo myservo30;
Servo myservo40;
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

int Lane1[] = {22, 24, 26}; // Lane 1 Red, Yellow and Green
int Lane2[] = {28, 30, 32}; // Lane 2 Red, Yellow and Green
int Lane3[] = {34, 36, 38}; // Lane 3 Red, Yellow and Green
int Lane4[] = {40, 42, 44}; // Lane 4 Red, Yellow and Green

int pos;

int sig1 = 47;
int sig2 = 49;
int sig3 = 50;
int sig4 = 52;

char g1,y1,g2,y2,g3,y3,g4,y4,currentstate;

void setup() {
  myservo10.attach(2);
  myservo20.attach(4);
  myservo30.attach(6);
  myservo40.attach(8);
  myservo1.attach(3);
  myservo2.attach(5);
  myservo3.attach(7);
  myservo4.attach(9);

  pinMode(sig1, INPUT);
  pinMode(sig2, INPUT);
  pinMode(sig3, INPUT);
  pinMode(sig4, INPUT);

  // put your setup code here, to run once:
  SPI.begin();
  Serial.begin(9600);   // Initiate a serial communication
  for (int i = 0; i < 3; i++)
  {
    pinMode(Lane1[i], OUTPUT);
    pinMode(Lane2[i], OUTPUT);
    pinMode(Lane3[i], OUTPUT);
    pinMode(Lane4[i], OUTPUT);
  }
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(Lane1[i], LOW);
    digitalWrite(Lane2[i], LOW);
    digitalWrite(Lane3[i], LOW);
    digitalWrite(Lane4[i], LOW);
  }

  Serial.println("Setup");
}

void loop() {
  Serial.println("loop");
  green1();
  yellow1();
  green3();
  yellow3();
  green4();
  yellow4();
  green2();
  yellow2();
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane1[1], LOW);
}

void servooff()
{
  servoleftoff1();
  servoleftoff2();
  servoleftoff3();
  servoleftoff4();
  servorightoff1();
  servorightoff2();
  servorightoff3();
  servorightoff4();
}
void getrfid()
{
  if (digitalRead(sig1) == HIGH)
  {
    servooff();
    servolefton1();
    while (digitalRead(sig1) == HIGH)
    {
      alllow();
      Serial.println("while1");
      digitalWrite(Lane4[0], HIGH);
      digitalWrite(Lane2[0], HIGH);
      digitalWrite(Lane3[0], HIGH);
      digitalWrite(Lane1[2], HIGH);
      digitalRead(sig1);
    }
    servoleftoff1();
    alllow();
    gotocurrentstate();
  }
  if (digitalRead(sig2) == HIGH)
  {
    servooff();
    servolefton2();
    while (digitalRead(sig2) == HIGH)
    {
      alllow();
      Serial.println("while2");
      
      digitalWrite(Lane4[0], HIGH);
      digitalWrite(Lane1[0], HIGH);
      digitalWrite(Lane3[0], HIGH);
      digitalWrite(Lane2[2], HIGH);
      digitalRead(sig2);
    }
    servoleftoff2();
    alllow();
    gotocurrentstate();
  }
  if (digitalRead(sig3) == HIGH)
  {
    servooff();
    servolefton3();
    while (digitalRead(sig3) == HIGH)
    {
      alllow();
      Serial.println("while3");
      digitalWrite(Lane4[0], HIGH);
      digitalWrite(Lane2[0], HIGH);
      digitalWrite(Lane1[0], HIGH);      
      digitalWrite(Lane3[2], HIGH);
      digitalRead(sig3);
    }
    servoleftoff3();
    alllow();
    gotocurrentstate();
  }
  if (digitalRead(sig4) == HIGH)
  {
    servooff();
    servolefton4();
    while (digitalRead(sig4) == HIGH)
    {
      alllow();
      Serial.println("while4");
      digitalWrite(Lane1[0], HIGH);
      digitalWrite(Lane2[0], HIGH);
      digitalWrite(Lane3[0], HIGH);
      digitalWrite(Lane4[2], HIGH);
      digitalRead(sig4);
    }
    servoleftoff4();
    alllow();
        gotocurrentstate();
  }
}

void gotocurrentstate()
{
  if(currentstate=g1)
  {
      servolefton1();
  servorighton1();
    green1();
  }
    if(currentstate=g2)
  {
      servolefton2();
  servorighton2();
    green2();
  }
    if(currentstate=g3)
  {
      servolefton3();
  servorighton3();
    green3();
  }
  
    if(currentstate=g4)
  {
      servolefton4();
  servorighton4();
    green4();
  }
    if(currentstate=y1)
  {
    yellow1();
  }
    if(currentstate=y2)
  {
    yellow2();
  }
    if(currentstate=y4)
  {
    yellow4();
  }
    if(currentstate=y3)
  {
    yellow3();
  }
}
void alllow()
{
    for (int i = 0; i < 3; i++)
  {
    digitalWrite(Lane1[i], LOW);
    digitalWrite(Lane2[i], LOW);
    digitalWrite(Lane3[i], LOW);
    digitalWrite(Lane4[i], LOW);
  }
}

void green1()
{
  currentstate=g1;
  Serial.println("Green1");
  digitalWrite(Lane1[2], HIGH);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane2[0], HIGH);
  servolefton1();
  servorighton1();
  for (int i = 0; i <= 70; i++)
  {
    getrfid();
    delay(100);
    digitalWrite(Lane1[2], HIGH);
    digitalWrite(Lane3[0], HIGH);
    digitalWrite(Lane4[0], HIGH);
    digitalWrite(Lane2[0], HIGH);
  }
}
void yellow1()
{
  currentstate=y1;
  Serial.println("Yellow1");
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane3[1], HIGH);
  for (int i = 0; i <= 30; i++)
  {
    getrfid();
    delay(100);
    digitalWrite(Lane1[2], LOW);
    digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane3[1], HIGH);
  }
  servoleftoff1();
  servorightoff1();
}
void green3()
{
  currentstate=g3;
  Serial.println("Green3");
    digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane3[2], HIGH);
   servolefton3();
  servorighton3();
  for (int i = 0; i <= 70; i++)
  {
    getrfid();
    delay(100);

    digitalWrite(Lane1[1], LOW);
    digitalWrite(Lane3[1], LOW);
      digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane4[0], HIGH);
    digitalWrite(Lane1[0], HIGH);
    digitalWrite(Lane3[2], HIGH);
  }
}
void yellow3()
{
  currentstate=y3;
  Serial.println("Yellow3");
  digitalWrite(Lane1[0],HIGH);
  digitalWrite(Lane2[0],HIGH);
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
  for (int i = 0; i <= 30; i++)
  {
    getrfid();
    delay(100);
      digitalWrite(Lane1[0],HIGH);
  digitalWrite(Lane2[0],HIGH);
    digitalWrite(Lane3[2], LOW);
    digitalWrite(Lane4[0], LOW);
    digitalWrite(Lane3[1], HIGH);
    digitalWrite(Lane4[1], HIGH);
  }
  servoleftoff3();
  servorightoff3();
}
void green4()
{
  currentstate=g4;
  Serial.println("Green4");
    digitalWrite(Lane1[0],HIGH);
  digitalWrite(Lane2[0],HIGH);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane4[2], HIGH);
  servorighton4();
  servolefton4();
  for (int i = 0; i <= 70; i++)
  {
    getrfid();
    delay(100);
      digitalWrite(Lane1[0],HIGH);
  digitalWrite(Lane2[0],HIGH);
    digitalWrite(Lane3[1], LOW);
    digitalWrite(Lane4[1], LOW);
    digitalWrite(Lane3[0], HIGH);
    digitalWrite(Lane4[2], HIGH);
  }
}
void yellow4()
{
  currentstate=y4;
  Serial.println("Yellow4");
    digitalWrite(Lane1[0],HIGH);
  digitalWrite(Lane3[0],HIGH);
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane2[1], HIGH);
  for (int i = 0; i <= 30; i++)
  {
    getrfid();
    delay(100);
      digitalWrite(Lane1[0],HIGH);
  digitalWrite(Lane3[0],HIGH);
    digitalWrite(Lane4[2], LOW);
    digitalWrite(Lane2[0], LOW);
    digitalWrite(Lane4[1], HIGH);
    digitalWrite(Lane2[1], HIGH);
  }
  servorightoff4();
  servoleftoff4();
}
void green2()
{
  currentstate=g2;
  Serial.println("Green2");
    digitalWrite(Lane1[0],HIGH);
  digitalWrite(Lane3[0],HIGH);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane2[2], HIGH);
        servorighton2();
  servolefton2();
  for (int i = 0; i <= 70; i++)
  {
    getrfid();
    delay(100);
    digitalWrite(Lane1[0],HIGH);
  digitalWrite(Lane3[0],HIGH);
    digitalWrite(Lane4[1], LOW);
    digitalWrite(Lane2[1], LOW);
    digitalWrite(Lane4[0], HIGH);
    digitalWrite(Lane2[2], HIGH);
  }
}
void yellow2()
{
  currentstate=y2;
  Serial.println("Yellow2");
    digitalWrite(Lane3[0],HIGH);
  digitalWrite(Lane4[0],HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane2[1], HIGH);
  for (int i = 0; i <= 30; i++)
  {
    getrfid();
    delay(100);
      digitalWrite(Lane4[0],HIGH);
  digitalWrite(Lane3[0],HIGH);
    digitalWrite(Lane1[0], LOW);
    digitalWrite(Lane2[2], LOW);
    digitalWrite(Lane1[1], HIGH);
    digitalWrite(Lane2[1], HIGH);
  }
  servoleftoff2();
  servorightoff2();
}

void servorighton1()
{
  for (pos = 90; pos <= 180; pos += 1) { // goes from 90 degrees to 180 degrees
    // in steps of 1 degree
    myservo10.write(pos);              // tell servo to go to position in variable 'pos'
  }
}

void servorightoff1()
{

  for (pos = 180; pos >= 90; pos -= 1) {  // goes from 180 degrees to 90 degrees
    myservo10.write(pos);                     // tell servo to go to position in variable 'pos'
  }
}

void servorighton2()
{
  for (pos = 90; pos <= 180; pos += 1) { // goes from 90 degrees to 180 degrees
    // in steps of 1 degree
    myservo20.write(pos);              // tell servo to go to position in variable 'pos'
  }
}

void servorightoff2()
{

  for (pos = 180; pos >= 90; pos -= 1) {  // goes from 180 degrees to 90 degrees
    myservo20.write(pos);                     // tell servo to go to position in variable 'pos'
  }
}

void servorighton3()
{
  for (pos = 90; pos <= 180; pos += 1) { // goes from 90 degrees to 180 degrees
    // in steps of 1 degree
    myservo30.write(pos);              // tell servo to go to position in variable 'pos'
  }
}

void servorightoff3()
{

  for (pos = 180; pos >= 90; pos -= 1) {  // goes from 180 degrees to 90 degrees
    myservo30.write(pos);                     // tell servo to go to position in variable 'pos'
  }
}
void servorighton4()
{
  for (pos = 90; pos <= 180; pos += 1) { // goes from 90 degrees to 180 degrees
    // in steps of 1 degree
    myservo40.write(pos);              // tell servo to go to position in variable 'pos'
  }
}

void servorightoff4() {

  for (pos = 180; pos >= 90; pos -= 1) {  // goes from 180 degrees to 90 degrees
    myservo40.write(pos);                     // tell servo to go to position in variable 'pos'
  }
}

void servolefton1(){
      for (pos = 90; pos >= 0; pos -= 1) {  // goes from 90 degrees to 0 degrees
    myservo1.write(pos);                     // tell servo to go to position in variable 'pos'
}
}

void servoleftoff1(){
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
}
}
void servolefton2(){
      for (pos = 90; pos >= 0; pos -= 1) {  // goes from 90 degrees to 0 degrees
    myservo2.write(pos);                     // tell servo to go to position in variable 'pos'
}
}

void servoleftoff2(){
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
}
}
void servolefton3(){
      for (pos = 90; pos >= 0; pos -= 1) {  // goes from 90 degrees to 0 degrees
    myservo3.write(pos);                     // tell servo to go to position in variable 'pos'
}
}

void servoleftoff3(){
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo3.write(pos);              // tell servo to go to position in variable 'pos'
}
}
void servolefton4(){
      for (pos = 90; pos >= 0; pos -= 1) {  // goes from 90 degrees to 0 degrees
    myservo4.write(pos);                     // tell servo to go to position in variable 'pos'
}
}

void servoleftoff4(){
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo4.write(pos);              // tell servo to go to position in variable 'pos'
}
}


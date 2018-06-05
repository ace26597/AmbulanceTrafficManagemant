/*   Typical pin layout used:++
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
#include <RFID.h>
#include <Servo.h>
#include <SoftwareSerial.h>

int sig1 = 5;
int sig2 = 4;
int sig3 = 3;
int sig4 = 2;
    
int pos;
#define LOW 0
#define HIGH 1

#define SDA_DIO 10
#define RESET_DIO 9
#define SDA2_DIO 8
#define SDA3_DIO 7
#define SDA4_DIO 6

RFID RC522(SDA_DIO, RESET_DIO);
RFID RC5222(SDA2_DIO, RESET_DIO);
RFID RC5223(SDA3_DIO, RESET_DIO);
RFID RC5224(SDA4_DIO, RESET_DIO);

void setup()
{

  SPI.begin();      // Initiate  SPI bus
  RC522.init();
  RC5222.init();
  RC5223.init();
  RC5224.init();

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);

  digitalWrite(5, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

  Serial.println("Approximate your card to the reader...");
  Serial.println();
}


void loop()
{
  digitalWrite(sig1, LOW);
  digitalWrite(sig2, LOW);
  digitalWrite(sig3, LOW);
  digitalWrite(sig4, LOW);
  getrfid1();
  digitalWrite(sig1, LOW);
  digitalWrite(sig2, LOW);
  digitalWrite(sig3, LOW);
  digitalWrite(sig4, LOW);
  getrfid2();
  digitalWrite(sig1, LOW);
  digitalWrite(sig2, LOW);
  digitalWrite(sig3, LOW);
  digitalWrite(sig4, LOW);
  getrfid3();
  digitalWrite(sig1, LOW);
  digitalWrite(sig2, LOW);
  digitalWrite(sig3, LOW);
  digitalWrite(sig4, LOW);
  getrfid4();
  digitalWrite(sig1, LOW);
  digitalWrite(sig2, LOW);
  digitalWrite(sig3, LOW);
  digitalWrite(sig4, LOW);
  delay(1000);
}

void getrfid1()
{
  if (RC522.isCard())
  {
    /* If so then get its serial number */
    RC522.readCardSerial();
    Serial.println("Card detected at 1:");
    Serial.println("Cardnumber:");
    Serial.print("Dec: ");
    Serial.print(RC522.serNum[0], DEC);
    Serial.print(", ");
    Serial.print(RC522.serNum[1], DEC);
    Serial.print(", ");
    Serial.print(RC522.serNum[2], DEC);
    Serial.print(", ");
    Serial.print(RC522.serNum[3], DEC);
    Serial.print(", ");
    Serial.print(RC522.serNum[4], DEC);
    Serial.println(" ");
    

      digitalWrite(sig1, HIGH);
      delay(5000);
      digitalWrite(sig1, LOW);
    
    Serial.println();
    Serial.println();
  }
}
void getrfid2()
{
  if (RC5222.isCard())
  {
    /* If so then get its serial number */
    RC5222.readCardSerial();
    Serial.println("Card detected at 2:");
    Serial.println("Cardnumber:");
    Serial.print("Dec: ");
    Serial.print(RC5222.serNum[0], DEC);
    Serial.print(", ");
    Serial.print(RC5222.serNum[1], DEC);
    Serial.print(", ");
    Serial.print(RC5222.serNum[2], DEC);
    Serial.print(", ");
    Serial.print(RC5222.serNum[3], DEC);
    Serial.print(", ");
    Serial.print(RC5222.serNum[4], DEC);
    Serial.println(" ");

      digitalWrite(sig2, HIGH);
      delay(5000);
      digitalWrite(sig2, LOW);
    
    Serial.println();
    Serial.println();
  }
}

void getrfid3()
{
  if (RC5223.isCard())
  {
    /* If so then get its serial number */
    RC5223.readCardSerial();
    Serial.println("Card detected at 3:");
    Serial.println("Cardnumber:");
    Serial.print("Dec: ");
    Serial.print(RC5223.serNum[0], DEC);
    Serial.print(", ");
    Serial.print(RC5223.serNum[1], DEC);
    Serial.print(", ");
    Serial.print(RC5223.serNum[2], DEC);
    Serial.print(", ");
    Serial.print(RC5223.serNum[3], DEC);
    Serial.print(", ");
    Serial.print(RC5223.serNum[4], DEC);
    Serial.println(" ");
      digitalWrite(sig3, HIGH);
      delay(5000);
      digitalWrite(sig3, LOW);
    
    Serial.println();
    Serial.println();
  }
}

void getrfid4()
{
  if (RC5224.isCard())
  {
    /* If so then get its serial number */
    RC5224.readCardSerial();
    Serial.println("Card detected at 4:");
    Serial.println("Cardnumber:");
    Serial.print("Dec: ");
    Serial.print(RC5224.serNum[0], DEC);
    Serial.print(", ");
    Serial.print(RC5224.serNum[1], DEC);
    Serial.print(", ");
    Serial.print(RC5224.serNum[2], DEC);
    Serial.print(", ");
    Serial.print(RC5224.serNum[3], DEC);
    Serial.print(", ");
    Serial.print(RC5224.serNum[4], DEC);
    Serial.println(" ");
      digitalWrite(sig4, HIGH);
      delay(5000);
      digitalWrite(sig4, LOW);
    
    Serial.println();
    Serial.println();
  }
}

/*void servolefton1(){
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
*/

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>

#define SS_PIN 10
#define RST_PIN 9 
#define LED_ACCESS_PIN 7
#define motorSteps 64     // change this depending on the number of steps
// per revolution of your motor
#define motorPin1 6
#define motorPin2 5
#define motorPin3 4
#define motorPin4 3
#define button 8

const int step_ = 1600;
int trigPin = A0;
int echoPin = A1;
int button1 = 0;

// initialize of the Stepper library:
Stepper myStepper(motorSteps, motorPin4, motorPin2, motorPin3, motorPin1);
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


void setup() 
{
  myStepper.setSpeed(100);
 // initialize the Serial port:
  Serial.begin(9600);   // Initiate a serial communication
  lcd.begin();
  lcd.setCursor(1,0);
  lcd.clear();
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("PLEASE TAG YOUR E-KTP CARD to the READER TAG...");
  Serial.println(); 
  pinMode( LED_ACCESS_PIN , OUTPUT);
  pinMode( echoPin, INPUT );
  pinMode( trigPin, OUTPUT);
  pinMode( button, INPUT_PULLUP);
}
void distance1()
{
  long duration, distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/29.1;
  Serial.print(distance);
  Serial.println("CM");
if(distance<=10)
{
  myStepper.step(0);
  delay(2000);
  digitalWrite(LED_ACCESS_PIN, HIGH);
  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(3,0);
  lcd.print("ADA OBJEK!");
  digitalWrite(LED_ACCESS_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_ACCESS_PIN, LOW);
  lcd.clear();
  Serial.println("TRUE");
  return distance1();  
} 
  /* else {
   access = false;
  
     digitalWrite(LED_ACCESS_PIN, LOW);
    myStepper.step(-step_);
    delay(1000);
}
*/
}
void buttoon(){
    button1 = digitalRead(button);
if (button1 == LOW)  {
    Serial.println("Authorized Access");
    Serial.println();
    lcd.setCursor(1, 0);
    lcd.println("ACCESS GRANTED");
    lcd.println();
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(4, 0);
    lcd.print("Sky Hunter");
    lcd.setCursor(4, 1);
    lcd.print("Project");
    Serial.println("BUKA"); 
    delay(3000);
    digitalWrite(7, HIGH);
    myStepper.step(step_);
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(2, 0);
    lcd.print("PASS THE DOOR");
    lcd.setCursor(0, 1);
    lcd.print("Welcome to Home");
    Serial.println("PASS THE DOOR");
    digitalWrite(7, LOW);   
    delay(6000); 
    distance1();
    delay(6000);      
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(4, 0);
    lcd.print("CLOSING");
    lcd.setCursor(2, 1);
    lcd.print("See You ^_^");
    Serial.println("CLOSING");
    digitalWrite(7, HIGH); 
    delay(3000);
    lcd.clear();
    myStepper.step(-step_);
    Serial.println("TUTUP");
    digitalWrite(7, LOW); 
    delay(3000);
    lcd.clear();
} 
}
void loop() {
   lcd.setCursor(3, 0);
 // Print at cursor Location:
   lcd.print("WELCOME TO");
   //goto column 2 and second line
   lcd.setCursor(0, 1);
   lcd.print("SKY HUNTER TEAM");
   buttoon();  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
     Serial.println();
     Serial.print("Message : ");
     content.toUpperCase(); 
  if (content.substring(1) == "04 28 5D 4A F9 2C 80") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lcd.setCursor(1, 0);
    lcd.println("ACCESS GRANTED");
    lcd.println();
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Assalamua'laikum");
    lcd.setCursor(1, 1);
    lcd.print("Garage Opening");
    Serial.println("BUKA");
    delay(1000);
    digitalWrite(7, HIGH);
    myStepper.step(step_);
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(4, 0);
    lcd.print("PASSED");
    lcd.setCursor(0, 1);
    lcd.print("Welcome to Home");
    Serial.println("PASSED");
    digitalWrite(7, LOW);   
    delay(1000);   
    distance1(); 
    delay(3000);       
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(4, 0);
    lcd.print("CLOSING");
    lcd.setCursor(2, 1);
    lcd.print("See You ^_^");
    Serial.println("CLOSING");
    digitalWrite(7, HIGH);    
    delay(1000);
    lcd.clear();
    myStepper.step(-step_);
    Serial.println("TUTUP");
    digitalWrite(7, LOW); 
    delay(1000);
    lcd.clear();  
  }
  else
  {  
    Serial.println("ACCESS DENIED");
    digitalWrite(7, HIGH);
    delay(100);
    digitalWrite(7, LOW);
    delay(100);
    digitalWrite(7, HIGH);
    delay(100);
    digitalWrite(7, LOW);
    delay(100);
    digitalWrite(7, HIGH);
    delay(100);
    digitalWrite(7, LOW);
    delay(100); 
    Serial.println(" Access denied");
    Serial.println();
    lcd.clear();
    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Access Denied !!");
    delay(2000);
    lcd.clear();   
  }
lcd.clear();
}

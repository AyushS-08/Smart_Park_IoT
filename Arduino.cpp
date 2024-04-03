#include <SoftwareSerial.h>

SoftwareSerial nodemcu(2,3);
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo1;
int IR1 = A0;
int IR2 = A1;

int Slot = 2;
bool flag1 = false;
bool flag2 = false;
int parking1_slot1_ir_s = 4; // parking slot1 infrared sensor connected with pin number 4 of arduino
int parking1_slot2_ir_s = 7;

String sensor1;
String sensor2;


String cdata =""; // complete data, consisting of sensors values

void setup()
{
   lcd.begin(16, 2);
  lcd.backlight();
Serial.begin(9600);
nodemcu.begin(9600);

pinMode(parking1_slot1_ir_s, INPUT);
pinMode(parking1_slot2_ir_s, INPUT);
pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  myservo1.attach(10);
  myservo1.write(0);

   lcd.setCursor(0, 0);
    lcd.print("   ARDUINO  ");
    lcd.setCursor(0, 1);
    lcd.print("PARKING SYSTEM ");
    delay(2000);
    lcd.clear();

}

void loop()
{

p1slot1();
p1slot2();

 
 
   cdata = cdata + sensor1 +"," + sensor2 + ","; // comma will be used a delimeter
   Serial.println(cdata);
   nodemcu.println(cdata);
   delay(6000); // 100 milli seconds
   cdata = "";
digitalWrite(parking1_slot1_ir_s, HIGH);
digitalWrite(parking1_slot2_ir_s, HIGH);

 if (digitalRead(IR1) == LOW && !flag1) {
    if (Slot > 0) {
      flag1 = true;
      myservo1.write(90);
      Slot--;
    } else {
      lcd.setCursor(0, 0);
      lcd.print("   SORRY :(  ");
      lcd.setCursor(0, 1);
      lcd.print(" Parking Full ");
      delay(3000);
      lcd.clear();
    }
  }

  if (digitalRead(IR2) == LOW && !flag2) {
    flag2 = true;
    myservo1.write(0);
    Slot++;
  }

  lcd.setCursor(0, 0);
  lcd.print("WELCOME!");
  lcd.setCursor(0, 1);
  lcd.print("Slot left:");
  lcd.print(Slot);
}


void p1slot1() // parkng 1 slot1
{
  if( digitalRead(parking1_slot1_ir_s) == LOW)
  {
  sensor1 = "255";
 delay(200);
  }
if( digitalRead(parking1_slot1_ir_s) == HIGH)
{
  sensor1 = "0"; 
 delay(200); 
}

}

void p1slot2() // parking 1 slot2
{
  if( digitalRead(parking1_slot2_ir_s) == LOW)
  {
  sensor2 = "255";
  delay(200);
  }
if( digitalRead(parking1_slot2_ir_s) == HIGH) 
  {
  sensor2 = "0"; 
 delay(200);
  }
}
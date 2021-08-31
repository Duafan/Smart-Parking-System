//PROJECT MIKROKONTROLER DAN SISTEM ANTARMUKA
#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo1;
Servo servo2;

const int Slot1 = A0;
const int Slot2 = A1;
const int Slot3 = A2;

const int servo_sensor1 = A3;
const int servo_sensor2 = A4;

const int servo_1 = 5;
const int servo_2 = 6;

int value_1 = 0;
int value_2 = 0;

char data = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (Slot1, INPUT);
  pinMode (Slot2, INPUT);
  pinMode (Slot3, INPUT);

  pinMode(servo_sensor1, INPUT);
  pinMode(servo_sensor2, INPUT);

  servo1.attach(servo_1);
  servo2.attach(servo_2);
}

void loop() {
  // put your main code here, to run repeatedly:
  value_1 = analogRead(servo_sensor1);
  value_2 = analogRead(servo_sensor2);

  if (value_1 <500) //Membuka gerbang servo 1 jika IR mendeteksi benda
  {
    servo1.write(0);
    delay(1000);
  }

  if (value_1 >500) //Menutup gerbang servo 1
  {
    servo1.write(90);
    delay(60);
    if(Serial.available()>0)
    {
      data = Serial.read();
      if(data == '1') //Kondisi jika tombol open entry gate ditekan pada aplikasi android
      {
        servo1.write(0);
        delay(1000);
        servo1.write(90);
      }
      else if(data == '2') //Kondisi jika tombol open exit gate ditekan pada aplikasi android
      {
        servo2.write(0);
        delay(1000);
        servo2.write(90);
      }
    }
  }

  if (value_2 <500) //Membuka gerbang servo 2 jika IR mendeteksi benda
  {
    servo2.write(0);
    delay(1000);
  }

  if (value_2 >500) //Menutup gerbang servo 2
  {
    servo2.write(90);
    delay(60); 
    if(Serial.available()>0)
    {
      data = Serial.read();
      if(data == '1') //Kondisi jika tombol open entry gate ditekan pada aplikasi android
      {
        servo1.write(0);
        delay(1000);
        servo1.write(90);
      }
      else if(data == '2') //Kondisi jika tombol open entry gate ditekan pada aplikasi android
      {
        servo2.write(0);
        delay(1000);
        servo2.write(90);
      }
    }
  }
  
  if (analogRead(Slot1)>500 && analogRead(Slot2)>500 && analogRead(Slot3)>500) //Kondisi saat Slot 1, Slot 2, dan Slot 3 Kosong
  {
    Serial.print("Available");
    Serial.print("|");
    Serial.print("Available");
    Serial.print("|");
    Serial.println("Available");
    delay(1000);
  }
  else if (analogRead(Slot1)<500 && analogRead(Slot2)>500 && analogRead(Slot3)>500) //Kondisi saat Slot 1 terisi,  Slot 2 dan Slot 3 Kosong
  {
    Serial.print("Occupied");
    Serial.print("|");
    Serial.print("Available");
    Serial.print("|");
    Serial.println("Available");
    delay(1000);
  }
  else if (analogRead(Slot1)>500 && analogRead(Slot2)<500 && analogRead(Slot3)>500) //Kondisi saat Slot 2 terisi,  Slot 1 dan Slot 3 Kosong
  {
    Serial.print("Available");
    Serial.print("|");
    Serial.print("Occupied");
    Serial.print("|");
    Serial.println("Available");
    delay(1000);
  }
  else if (analogRead(Slot1)>500 && analogRead(Slot2)>500 && analogRead(Slot3)<500) //Kondisi saat Slot 3 terisi,  Slot 1 dan Slot 2 Kosong
  {
    Serial.print("Available");
    Serial.print("|");
    Serial.print("Available");
    Serial.print("|");
    Serial.println("Occupied");
    delay(1000);
  }
  else if (analogRead(Slot1)<500 && analogRead(Slot2)<500 && analogRead(Slot3)>500) //Kondisi saat Slot 1 dan Slot 2 terisi, Slot 3 Kosong
  {
    Serial.print("Occupied");
    Serial.print("|");
    Serial.print("Occupied");
    Serial.print("|");
    Serial.println("Available");
    delay(1000);
  }
  else if (analogRead(Slot1)>500 && analogRead(Slot2)<500 && analogRead(Slot3)<500) //Kondisi saat Slot 2 dan Slot 3 terisi, Slot 1 Kosong
  {
    Serial.print("Available");
    Serial.print("|");
    Serial.print("Occupied");
    Serial.print("|");
    Serial.println("Occupied");
    delay(1000);
  }
  else if (analogRead(Slot1)<500 && analogRead(Slot2)>500 && analogRead(Slot3)<500) //Kondisi saat Slot 1 dan Slot 3 terisi, Slot 2 Kosong
  {
    Serial.print("Occupied");
    Serial.print("|");
    Serial.print("Available");
    Serial.print("|");
    Serial.println("Occupied");
    delay(1000);
  }
  else if (analogRead(Slot1)<500 && analogRead(Slot2)<500 && analogRead(Slot3)<500)//Kondisi saat Slot 1, Slot 2 dan Slot 3 Terisi
  {
    Serial.print("Occupied");
    Serial.print("|");
    Serial.print("Occupied");
    Serial.print("|");
    Serial.println("Occupied");
    delay(1000);
  }
}

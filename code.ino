//This code is created by Mr. Abhinav . to know more search #ATALL channel on youtube

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"


#define DHTPIN 2
#define OLED_RESET 4
#define DHTTYPE DHT11   // DHT 11
#define ea 3   //EA1 of motor driver
#define sw 4   // Switch 
#define in1 5  //IN1 of motor driver
#define in2 6  //IN2 of motor driver
#define led1 9 // led 1
#define led2 10 // led 2
#define po A0  // potentiometer
           
int x, y , z , a ;
float H , T;

Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin(9600);
  dht.begin();
  pinMode(ea ,OUTPUT);
  pinMode(sw ,INPUT_PULLUP);
  pinMode(in1 ,OUTPUT);
  pinMode(in2 ,OUTPUT);
  pinMode(led1 ,OUTPUT);
  pinMode(led2 ,OUTPUT);
  pinMode(po ,INPUT);
  Serial.Println("Created by Mr. ABHINAV . Youtube channel : #ATALL");
  delay(3000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
 
 analogWrite(led1 , 0);
  analogWrite(led2 , 0);
}

void loop() 
{   
  H = dht.readHumidity();
  T = dht.readTemperature();
  display.setTextSize(1);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(1,0);
  display.println("Temperature:"); 
  display.setCursor(1,10);
  display.println("Fan speed:"); 
  
    temp(); 
x = digitalRead(sw);
Serial.print("Switch: ");Serial.println(x);
if(x == 1)
{
  analogWrite(led1 , 5);
  analogWrite(led2 , 0);
  digitalWrite(in1 , HIGH);
  digitalWrite(in2 , LOW);

  ffan();
}
else
{ analogWrite(led1 , 0);
  analogWrite(led2 , 5);
  digitalWrite(in1 , HIGH);
  digitalWrite(in2 , LOW);

  manual();
}

}

void temp(){
  if (isnan(H) || isnan(T))
   {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
   }

  
 // Serial.print(F("%  Temperature: "));
  
  Serial.print(T);
  Serial.println("°C ");
  display.setTextSize(1);
  display.setCursor(72,0);
  display.println(T);
  display.drawPixel(103,0, WHITE);
  display.drawPixel(103, 1, WHITE);
  display.drawPixel(103, 2, WHITE);
  display.drawPixel(104, 0, WHITE);
  display.drawPixel(104, 2, WHITE);
  display.drawPixel(105, 0, WHITE);
  display.drawPixel(105, 1, WHITE);
  display.drawPixel(105, 2, WHITE);
  display.setCursor(109,0);
  display.println("C");
  display.display();
  
  Serial.print("Humidity:");
  Serial.println(H);
  }

void ffan(){

  display.setTextSize(2);
  display.setCursor(20,19);
  display.println("Automatic"); 
  display.display();  
  display.setTextSize(1);
  if(T < 19 ){
    analogWrite(ea,45);
    display.setCursor(70,10);
    display.println("5 %");
    display.display();  
 
  }
  else if (T >19.00 && T < 26.00){
    analogWrite(ea,90);
    display.setCursor(70,10);
    display.println("25 %");
    display.display();
     
  }
  else if (T >26.00 && T < 30.00){
    analogWrite(ea,135);
    display.setCursor(70,10);
    display.println("50 %");
    display.display();
     
  }
  else if (T >30 && T < 32){
    analogWrite(ea,200);
    display.setCursor(70,10);
    display.println("80 %");
    display.display();
     
  }
  else if (T >32.00){
    analogWrite(ea,225);
    display.setCursor(70,10);
    display.println("100 %");
    display.display();
     
  }
 
}

void manual()
{ 
  display.setTextSize(2);
  display.setCursor(30,19);
  display.println("Manual"); 
  display.display();
  y = analogRead(po);
  z = map(y, 0 , 1024, 0,225);
  analogWrite(ea ,z);
  a = map(y, 0 , 1023, 0,100);
  display.setTextSize(1);
  display.setCursor(70,10);
  display.println(a);
   display.setCursor(90,10);
  display.println("%");
  display.display();
 
}

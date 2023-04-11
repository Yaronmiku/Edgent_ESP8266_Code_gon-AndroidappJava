2809#define BLYNK_TEMPLATE_ID "TMPLEbM0wghM"
#define BLYNK_DEVICE_NAME "esp"
//#include <DHT.h>
#include <Servo.h>/////
#include "DHTesp.h"
#include <Wire.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_NODE_MCU_BOARD
#include "BlynkEdgent.h"
//DHT dht(13, DHT11);     //DHT out -->D7
#define led1 D1 
#define led2 D8 
#define button1 D5 //D1
#define button2 D2 //D2
FirebaseData firebaseData;
FirebaseJson json;///////////////////////////////////
boolean bt1_state=HIGH;
boolean bt2_state=HIGH;
DHTesp dht;
int vitri = 0;///
int servo = D6;
String path ="/";
Servo myservo;
float t_canhbao;
float h_canhbao;
float t,h;
byte degree[8] = {0B01110,0B01010,0B01110,0B00000,0B00000,0B00000,0B00000,0B00000};
BlynkTimer timer;
WidgetLED led(V0);
boolean blynkState=0;

void setup(){
  Serial.begin(115200);
  delay(100);
  myservo.attach(servo);
  myservo.write (0);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  digitalWrite(led2,LOW);
 
  BlynkEdgent.begin();
  //dht.begin();
  dht.setup(13, DHTesp::DHT11);
  timer.setInterval(3000,readSensor);
  timer.setInterval(1000,updateBlynk);
Firebase.begin("esp8266-dht11-firebase-7ed96-default-rtdb.firebaseio.com","5MmDkgSpA6zTFvQqBXCamF79OCL5qY2S5NR9mRRv");
Firebase.reconnectWiFi(true);
if(!Firebase.beginStream(firebaseData,path))
 { 
  Serial.println("REASON"+ firebaseData.errorReason() );
  Serial.println();
 }  
}

void loop(){
  BlynkEdgent.run();
  timer.run();
  if(Blynk.connected()){
    if(blynkState==0){
      blynkState=1;

    }
  }
check_button();
dkservo();
senddata();
}
BLYNK_WRITE(V3){
  int p = param.asInt();
  digitalWrite(led1, p); 
}
BLYNK_WRITE(V4){
  int p = param.asInt();
  digitalWrite(led2, p); 
}
void readSensor(){
//  float h_temp = dht.readHumidity();
//  float t_temp = dht.readTemperature(); 
  float h_temp = dht.getHumidity();
  float t_temp = dht.getTemperature();
  Serial.print(dht.getStatusString());
  if (isnan(h_temp) || isnan(t_temp)) {
    Serial.println("Failed to read from DHT sensor!");
    //return;
  }else{
    h = h_temp;
    t = t_temp;
    Serial.print("Nhiệt độ: "); Serial.println(t);
    Serial.print("Độ ẩm: "); Serial.println(h);
  }
}
void updateBlynk(){
  if (led.getValue()) {
    led.off();
  } else {
    led.on();
  }
  Blynk.virtualWrite(V1,t);
  Blynk.virtualWrite(V2,h);
}
void check_button(){
  if(digitalRead(button1)==LOW){
    if(bt1_state==HIGH){
      digitalWrite(led1,!digitalRead(led1));
      Blynk.virtualWrite(V3,digitalRead(led1));
      bt1_state=LOW;
      delay(200);
    }
  }else{
    bt1_state=HIGH;
  }
  if(digitalRead(button2)==LOW){
    if(bt2_state==HIGH){
      digitalWrite(led2,!digitalRead(led2));
      Blynk.virtualWrite(V4,digitalRead(led2));
      bt2_state=LOW;
      delay(200);
    }
  }else{
    bt2_state=HIGH;
  }


}
void dkservo()
{
  int l1 = digitalRead(led2);
  myservo.write (vitri); 
    if(l1 == 0)  {vitri = 0; }
    if(l1== 1) {vitri = 180; }
 
}
void senddata()
{

  //Serial.print("nhiet do:"); Serial.print(nhietdo); Serial.print("do am:");  Serial.println(doam);
  Firebase.setFloat(firebaseData,  "temp",t);
  Firebase.setFloat(firebaseData, "humidity",h);
 delay(1000);
}

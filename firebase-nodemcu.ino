#include <ESP8266WiFi.h>   // thêm thư viện esp8266
#include <FirebaseESP8266.h>  // thư viện hỗ trợ kết nối firebase với esp 8266
#include <Servo.h> 

#define FIREBASE_HOST "smarthome-73149.firebaseio.com"                     // địa chỉ của project firebse
#define FIREBASE_AUTH "XyJKPU0iMFKcFTWg1xwcsIMPOQPkQcANbWjh8IEH"           //  key generated from firebase
#define WIFI_SSID "Sinh Vien"                                          // thông tin tên và passwifi
#define WIFI_PASSWORD "987654321" 

FirebaseData firebasedata;
Servo myservo;
String fireStatus = " ";                                                     


int led1 = D1;
int led2 = D2;
int servo = D3;
int Quat =D5;
String statusLed;
String statusLed2;
String servodemmo;
void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);       
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(servo, OUTPUT);
  pinMode(Quat, OUTPUT);    
  connectWifi();         // hàm kết nối với wifi
                                                       
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);    // connect tới firebase                                 
  Firebase.setString(firebasedata, "LED_STATUS", "OFF");  // tạo database trên firebase
  Firebase.setString(firebasedata, "LED_STATUS_1", "OFF");
  Firebase.setInt(firebasedata, "MQ2",200);
  Firebase.setString(firebasedata, "SERVO","");
  myservo.attach(servo);

}

void loop() {
  MQ2(); // hàm cảm biến khí ga
  Led(); // hàm bật tắt đèn
  Led2();
  servo1(); // hàm đóng, mở cửa
  digitalWrite(Quat, HIGH);
  
}
void MQ2(){
  int MQ2 = analogRead(A0);
  Serial.println(MQ2);
  Firebase.setInt(firebasedata, "MQ2",MQ2);
//  if(MQ2 > 150){
//    digitalWrite(LED_BUILTIN, LOW);                                                 
//    digitalWrite(led3, HIGH);
//    }
//  else if (MQ2 < 150){
//    digitalWrite(LED_BUILTIN, HIGH);                                              
//    digitalWrite(led3, LOW);
//    }
  }
void servo1(){
  
  Firebase.getString(firebasedata, "SERVO");  
  servodemmo = firebasedata.stringData();
  if (servodemmo == "1") {                                                         
    myservo.write(0); 
  } 
  else if (servodemmo == "0") {                                                 
    myservo.write(150);
  }
  else {
    Serial.println("Please send ON/OFF");
  }

  }
void Led(){
  Firebase.getString(firebasedata, "LED_STATUS");  
  statusLed = firebasedata.stringData();
  if (statusLed == "ON") {                                                        
    Serial.println("Led Turned ON");                         
    digitalWrite(LED_BUILTIN, LOW);                                              
    digitalWrite(led1, HIGH); 
  } 
  else if (statusLed == "OFF") {                                                  
    Serial.println("Led Turned OFF");
    digitalWrite(LED_BUILTIN, HIGH);                                             
    digitalWrite(led1, LOW); 
  }
  else {
    Serial.println("Wrong Credential! Please send ON/OFF");
  }
}
void Led2(){
  Firebase.getString(firebasedata, "LED_STATUS_1");  
  statusLed2 = firebasedata.stringData();
  if (statusLed2 == "ON") {                                                        
    Serial.println("Led Turned ON");                         
    digitalWrite(LED_BUILTIN, LOW);                                              
    digitalWrite(led2, HIGH); 
  } 
  else if (statusLed2 == "OFF") {                                                  
    Serial.println("Led Turned OFF");
    digitalWrite(LED_BUILTIN, HIGH);                                             
    digitalWrite(led2, LOW); 
  }
  else {
    Serial.println("Wrong Credential! Please send ON/OFF");
  }
  
}

void connectWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     // truy cập đến ip và pass wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());
  }
//  void DIEU_HOA() {
//  if (nhiet_do < 30) {
//    step_time = 850;
//    TURN(step_time);
//    return;
//  }
//
//  if ( (nhiet_do > 30) && (nhiet_do <= 40) ) {
//    step_time = 750;
//    TURN(step_time);
//    return;
//  }
//
//  if (nhiet_do > 40) {
//    step_time = 560;
//    TURN(step_time);
//    return;
//  }
//}

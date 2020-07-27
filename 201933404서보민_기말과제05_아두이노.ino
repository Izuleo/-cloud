// DB key : FiaxcOcu7uM3hwuOnCoX4NHQxggk1we5GjLtOsl3

// Project name : Firebase-LED-Contrlo.firebaseio.com

#include <ESP8266WiFi.h>                                               

#include <FirebaseArduino.h>      

#define FIREBASE_HOST "hellofirebase-e29a1.firebaseio.com"
#define FIREBASE_AUTH "h2xWzPGsMeR9wmU8vWNcaphdMlHrCIzbND8BrppY"

//와이파이 아이디와 비밀번호 입력
#define WIFI_SSID "olleh_GIGA_WIFI_CC91"
#define WIFI_PASSWORD "0000006977"


String fireStatus = "";   // firebase DB로 부터 받은 값 저장 
int led = D4;        // NodeMCU LED pin   
                                                  
void setup() { 
  Serial.begin(9600); 
  delay(1000);   
  pinMode(led, OUTPUT);                 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                              
  Serial.print("Connecting to "); 
  Serial.print(WIFI_SSID); 
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print("."); 
    delay(500); 
    } 
    Serial.println(); 
    Serial.print("Connected to "); 
    Serial.println(WIFI_SSID); 
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // firebase에 연결 
    Firebase.setString("LED_STATUS", "OFF");              //초기 LED 상태를 OFF로 설정 }
}

void loop() 
{ 
  fireStatus = Firebase.getString("LED_STATUS"); // Firebase 데이터베이스로 부터 LED 상태 값 읽음 
  if (fireStatus == "ON")   {       // Firebase 데이터베이스로 부터 받은 LED 상태 값이 “ON”이면 LED 켜기 
    Serial.println("Led Turn On"); // Serial Monitor에 “Led Turned ON” 문자열 출력 
    digitalWrite(led, HIGH);          // LED OFF 
    } else if (fireStatus == "OFF")  {    // Firebase 데이터베이스로 부토 LED 상태 값 읽음 
      Serial.println("Led Turned OFF");  // Serial Monitor에 “Led Turned OFF” 문자열 출력 
      digitalWrite(led, LOW);          // LED OFF 
      } else { Serial.println("Command Error! Please send ON/OFF");
      }
      
  }

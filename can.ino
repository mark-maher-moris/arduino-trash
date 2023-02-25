
#include <WiFi.h>
#include <FirebaseESP32.h>

#include <LiquidCrystal.h> //include LCD library (standard library)
#include <Keypad.h> //include keypad library - first you must install library (library link in the video description)

#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>


#define redLED 10 //define the LED pins
#define greenLED 11




FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;







char* actNumber ="1234"; //create a password
int pozisyon = 0; //keypad position
int trigPin = 13;    // TRIG pin
int echoPin = 12;    // ECHO pin
const byte rows = 4; //number of the keypad's rows and columns
const byte cols = 4;
float duration_us, distance_cm;
double cutsNumber = 0 ; 
double points = 0 ;
char keyMap [rows] [cols] = { //define the cymbols on the buttons of the keypad

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


byte rowPins [rows] = {2, 3, 4, 5}; //pins of the keypad
byte colPins [cols] = {6, 7, 8, 9};

Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, rows, cols);

LiquidCrystal lcd (A0, A1, A2, A3, A4, A5); // pins of the LCD. (RS, E, D4, D5, D6, D7)

void setup(){
// begin serial port
  Serial.begin (9600);

  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2);
  pinMode(redLED, OUTPUT);  //set the LED as an output
  pinMode(greenLED, OUTPUT);
  setLocked (true); //state of the password
  
  
  
  
  sensors.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; 
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);
  

  
  
  
}

void loop(){

  char whichKey = myKeypad.getKey(); //define which key is pressed with getKey

  lcd.setCursor(0, 0);
  lcd.print("    Welcome");
  lcd.setCursor(0, 1);
  lcd.print("ENTER YOUR CODE ");

  if(whichKey == '*' || whichKey == '#' || whichKey == 'A' ||       //define invalid keys
  whichKey == 'B' || whichKey == 'C' || whichKey == 'D'){

    pozisyon=0;
    setLocked (true);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PRESS AND THROW ");
       // generate 10-microsecond pulse to TRIG pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
    if (distance_cm < 20){
    cutsNumber ++ ;
      // saffar
    }
    
      Firebase.getDouble(fbdo, F("/users/1234/points"), &points);
    // get user points from firebase
    points = points + cutsNumber ;
    // set user new points for firebase 
    // 
          Firebase.getDouble(fbdo, F("/users/1234/points"), &points);
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    Firebase.setDouble(fbdo, F("/users/1234/points"),points);
       
}    
    
    
    

    

  Serial.println(" cm");
    delay(800);
    lcd.clear();
  }
  if(whichKey == actNumber [pozisyon]){

    pozisyon ++;
  }
  if(pozisyon == 4){
    setLocked (false);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("** Code: 1234**");
    delay(3000);
 

  delay(200);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    THANK YOU");
    lcd.setCursor(0, 1);
    lcd.print("TAKE YOUR POINTS");
    delay(7000);
    lcd.clear();
  }
  delay(100);
}

void setLocked(int locked){
  if(locked){
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    }
    else{
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
    }
  }
    /* /////////////////////////////////


#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "Saif's iPhone"
#define WIFI_PASSWORD "666666666"
#define API_KEY "AIzaSyBAtY159LKZWaFq5OSjsTpiuuPDigdZv-Q"
#define DATABASE_URL "https://default-rtdb.firebaseio.com/"
#define USER_EMAIL "@gmail.com"
#define USER_PASSWORD "TrashCan"


FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;


void setup() {
  pinMode(D1,INPUT_PULLUP);
  pinMode(D2,OUTPUT);
  
  Serial.begin(115200);
  sensors.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; 
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);
  

  
}

void loop() {

     Firebase.getBool(fbdo, F("/test/motor"), &runMotor);
     Serial.printf("Get bool ref... %s\n", Firebase.getBool(fbdo, F("/test/motor"), &runMotor) ? runMotor ? "true" : "false" : fbdo.errorReason().c_str());
       //////////////////////////////
  ; 
  Firebase.getDouble(fbdo, F("/test/points"), &points);
  
 points = points + cutsNumber ;
    
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    Firebase.setDouble(fbdo, F("/users/user/points"),points);
       
}   

   
}
  
 }
 
 */

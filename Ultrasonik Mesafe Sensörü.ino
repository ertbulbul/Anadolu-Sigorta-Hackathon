#define echoPin D8
#define trigPin D7
#define ledPin D6
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <avr/pgmspace.h>


//Wifi Name
const char* ssid = "AS-HACKATHON";
//Wifi Password
const char* password = "Hackathon2019";
char* getlink1 = "http://10.16.56.127:8888/api/addData?pressure=";
char* getlink2= "&userId=5dd8fdc77a591b098cd721bb&pipeName=K2";

void setup() {
 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  
 
  while (WiFi.status() != WL_CONNECTED) { 
    delay(1000);
    Serial.print("Connecting..");   
  }
  Serial.println("Connected.");
  //Serial.println(WiFi.localIP());
  
  
}

void loop() {

  int olcum = mesafe();
  Serial.println("ölçüm değeri: ");
  Serial.println(olcum);
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
    //Ben eklicem
  
    char myConcatenation[80];
    char myCharArray[47]="http://10.16.56.127:8888/api/addData?pressure=";
    sprintf(myConcatenation,"%s%d%s",myCharArray,olcum,getlink2);
    Serial.println(myConcatenation);
    http.begin(myConcatenation);  //Specify request destination
    int httpCode = http.GET();                                   //Send the request
 
  if (httpCode > 0) { //Check the returning code
    String payload = http.getString();   //Get the request response payload
    Serial.println(payload.charAt(48));
    if(payload.charAt(48) == '1'){
      digitalWrite(ledPin, HIGH);
    }else{
      digitalWrite(ledPin, LOW);
    }
    
    Serial.println(payload);             //Print the response payload    
  }
   
  http.end();   //Close connection
   
  }
  Serial.println("request atıldı");
   
  delay(300);

   
    
}

int mesafe(){
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  //Serial.println(duration / 10.0);
  
  return distance;
}

char * BufferInsertStringValue(char * s,int startingPosition, char * command) {
  int i = 0;
  int stringLength=strlen(s)-1;
  for ( i = 0;i <= stringLength;i++) {
    command[startingPosition + i - 1] = s[i];
     }
  command[startingPosition + i] = '\0';
  return command;
}

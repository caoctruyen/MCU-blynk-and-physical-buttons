
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "kPAZ24skBejFxOn_F6CH1SYYl-WtHSfo";
char ssid[] = "Truyen"; 
char pass[] = "truyen123";
//#include <BlynkSimpleStream.h>


// Set your LED and physical button pins here
const int ledPin1 = 5;
const int ledPin2 = 4;
const int ledPin3 = 0;
const int ledPin4 = 2;
const int btnPin1 = 14;
const int btnPin2 = 13;
const int btnPin3 = 12;
const int btnPin4 = 15;

BlynkTimer timer;
void checkPhysicalButton();

int led1State = LOW;
int btn1State = HIGH;

int led2State = LOW;
int btn2State = HIGH;

int led3State = LOW;
int btn3State = HIGH;

int led4State = LOW;
int btn4State = HIGH;

// Every time we connect to the cloud...
BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(V7);
  Blynk.syncVirtual(V8);
  Blynk.syncVirtual(V9);
  Blynk.syncVirtual(V10);

  // Alternatively, you could override server state using:
  //Blynk.virtualWrite(V7, led1State);
  //Blynk.virtualWrite(V8, led2State);
  //Blynk.virtualWrite(V9, led3State);
  //Blynk.virtualWrite(V10, led4State);

}

// When App button is pushed - switch the state
BLYNK_WRITE(V7) {
  led1State = param.asInt();
  digitalWrite(ledPin1, led1State);
}
  
 BLYNK_WRITE(V8) {
  led2State = param.asInt();
  digitalWrite(ledPin2, led2State);
 }
BLYNK_WRITE(V9) {
  led3State = param.asInt();
  digitalWrite(ledPin3, led3State);
}
BLYNK_WRITE(V10) {
  led4State = param.asInt();
  digitalWrite(ledPin4, led4State);
}

void checkPhysicalButton()
{
  if (digitalRead(btnPin1) == LOW) {
    // btn1State is used to avoid sequential toggles
    if (btn1State != LOW) {

      // Toggle LED state
      led1State = !led1State;
      digitalWrite(ledPin1, led1State);

      // Update Button Widget
      Blynk.virtualWrite(V7, led1State);
    }
    btn1State = LOW;
  } else {
    btn1State = HIGH;
  }

  if (digitalRead(btnPin2) == LOW) {
    // btnState is used to avoid sequential toggles
    if (btn2State != LOW) {

      // Toggle LED state
      led2State = !led2State;
      digitalWrite(ledPin2, led2State);

      // Update Button Widget
      Blynk.virtualWrite(V8, led2State);
    }
    btn2State = LOW;
  } else {
    btn2State = HIGH;
  }

  if (digitalRead(btnPin3) == LOW) {
    // btnState is used to avoid sequential toggles
    if (btn3State != LOW) {

      // Toggle LED state
      led3State = !led3State;
      digitalWrite(ledPin3, led3State);

      // Update Button Widget
      Blynk.virtualWrite(V9, led3State);
    }
    btn3State = LOW;
  } else {
    btn3State = HIGH;
  }

  if (digitalRead(btnPin4) == LOW) {
    // btnState is used to avoid sequential toggles
    if (btn4State != LOW) {

      // Toggle LED state
      led4State = !led4State;
      digitalWrite(ledPin4, led4State);

      // Update Button Widget
      Blynk.virtualWrite(V10, led4State);
    }
    btn4State = LOW;
  } else {
    btn4State = HIGH;
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
 Blynk.begin(auth, ssid, pass);

  pinMode(ledPin1, OUTPUT);
  pinMode(btnPin1, INPUT_PULLUP);
  digitalWrite(ledPin1, led1State);
  

  pinMode(ledPin2, OUTPUT);
  pinMode(btnPin2, INPUT_PULLUP);
  digitalWrite(ledPin2, led2State);
  

  pinMode(ledPin3, OUTPUT);
  pinMode(btnPin3, INPUT_PULLUP);
  digitalWrite(ledPin3, led3State);
  

  pinMode(ledPin4, OUTPUT);
  pinMode(btnPin4, INPUT_PULLUP);
  digitalWrite(ledPin4, led4State);

  // Setup a function to be called every 100 ms
  timer.setInterval(100L, checkPhysicalButton);
}

void loop()
{
  Blynk.run();
  timer.run();
}

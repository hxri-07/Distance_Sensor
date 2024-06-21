#include <Wire.h>
#include <FirebaseArduino.h>
// Set these to run example.
#define FIREBASE_HOST "https://dstmsrmnt01-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "AIzaSyCAisbYwDM4QyUWrfDnE1UUmS-j4BOTRAw"
#define WIFI_SSID "krishna_5G"
#define WIFI_PASSWORD "giridhari"
#define echoPin 2            
#define trigPin 4 
long duration;
int distance;

void setup() {
Serial.begin(9600);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
// connect to wifi.
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println();
Serial.print("connected: ");
Serial.println(WiFi.localIP());
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.set("LED_STATUS", 0);
Firebase.setInt("distance", 0);
}

void loop() {

/*
 * For Utlrasonic sensor distance measurement
 */

// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance = duration (microsecond) × (1/2) x speed of sound (microsecond)
​
distance = duration*0.034/2; // The speed of sound in air is approximately 343 meters per second (at room temperature)
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
Firebase.setInt("distance",distance);
delay(2000);

}

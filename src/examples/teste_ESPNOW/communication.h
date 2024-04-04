#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

//PROTOTIPO FUNCÕES

void getReadings();
void updateDisplay();


// REPLACE WITH THE MAC Address of your receiver 
//uint8_t broadcastAddress[] = {0x78, 0x21, 0x84, 0xDF, 0x1C, 0x58}; //ESP VELHO
uint8_t broadcastAddress[] = {0x54, 0x43, 0xB2, 0x46, 0x97, 0x0C}; //ESP NOVO
//uint8_t broadcastAddress[] = {0x40, 0x22, 0xD8, 0x03, 0x81, 0xF0}; //ESP THETA


// Define variables to store and to be sent
float toque;


// Define variables to store incoming readings
float incomingTouch;


// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    float toque;

} struct_message;

// Create a struct_message called BME280Readings to hold sensor readings
struct_message TOUCH_READING;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

esp_now_peer_info_t peerInfo;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingTouch = incomingReadings.toque;

}

void getReadings(){
  //COLOCAR UM GERADOR DE ALEATORIO AQUI
  toque = touchRead(4);

}

void updateDisplay(){
  
  // Display Readings in Serial Monitor
  Serial.println("INCOMING READINGS");
  Serial.print("Touch: ");
  Serial.print(incomingReadings.toque);
  Serial.println();

  if(incomingReadings.toque < 50){
    digitalWrite(2, HIGH); 
  }else{
    digitalWrite(2, LOW);
  }
}
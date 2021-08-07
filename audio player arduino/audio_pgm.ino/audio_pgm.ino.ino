#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"
const int Sensor = A6; // Sensor connected to analog pin A6
const int Sensor2 = A3;
int threshold = 100; // Threshold is set to 100
int sensorReading = 0; 
int sensor2Reading = 0;// variable to store the value read from the sensor pin
const int volp = A1;
const int sensp = A0;
int vol =0;
int sens = 0;
TMRpcm tmrpcm;

void setup()
{
pinMode(Sensor,INPUT);
pinMode(Sensor2,INPUT);
pinMode(vol,INPUT);
pinMode(sens,INPUT);
tmrpcm.speakerPin=9;
Serial.begin(9600);
if(!SD.begin(SD_ChipSelectPin))
{
  Serial.println("SD fail");
  return;
  digitalWrite(2,HIGH);
}
tmrpcm.play("new.wav");
}

void loop() {
  vol = analogRead(volp);
  vol = map(vol, 0, 1023, -1, 7);
  sens = analogRead(sensp);
  sens = map(sens, 0, 1023, 50, 1035);
  tmrpcm.setVolume(vol);
  sensorReading = analogRead(Sensor);
  sensor2Reading = analogRead(Sensor2);
  threshold = sens;
// if the sensor reading is greater than the threshold:
if (sensorReading >= threshold)
{
// toggle the status of the ledPin:
Serial.println(sensorReading); 
tmrpcm.play("test.wav");

}
if (sensor2Reading >= threshold)
{
// toggle the status of the ledPin:
Serial.println(sensor2Reading);
tmrpcm.play("new.wav");
delay(50);

}
else
{
  if(!tmrpcm.isPlaying()) 
tmrpcm.disable();
}
}

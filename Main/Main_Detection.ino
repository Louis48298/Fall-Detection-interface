#include "Arduino.h"
#include <fall_detection.h>
#include <SoftwareSerial.h>

#define RX_Pin 3
#define TX_Pin 1

SoftwareSerial mySerial = SoftwareSerial(RX_Pin, TX_Pin);
FallDetection_60GHz radar = FallDetection_60GHz(&mySerial);


void setup() {
  
  Serial.begin(115200);
  Serial.println("Ready");
}

void loop()
{*
  // show the data
  radar.recvRadarBytes();           //Receive radar data and start processing
  radar.showData();                 //Serial port prints a set of received data frames
  radar.showRadarData();            //Serial port prints the radar data
  
  radar.Fall_Detection();           //Human fall detection
  if(radar.sensor_report != 0x00){
    switch(radar.sensor_report){
        case NOFALL:
            Serial.println("Le capteur détecte que ce n'est pas une chute.");
            Serial.println("----------------------------");
            break;
        case FALL:
            Serial.println("Le capteur détecte que c'est une chute.");
            Serial.println("----------------------------");
            break;
    }
  }
  radar.HumanExis_Func();           //Human existence information output
  if(radar.sensor_report != 0x00){
    switch(radar.sensor_report){
      case NOONE:
        Serial.println("Le capteur ne détecte aucune présence.");
        Serial.println("----------------------------");
        break;
      case SOMEONE:
        Serial.println("Le capteur détecte une présence.");
        Serial.println("----------------------------");
        break;
      case MOVE:
        Serial.println("Le capteur détecte un mouvement.");
        Serial.println("----------------------------");
        break;
    }
  }
  delay(200); //Add time delay to avoid program jam
}
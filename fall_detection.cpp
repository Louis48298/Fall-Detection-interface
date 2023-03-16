#include "Arduino.h"
#include "fall_detection.h"

FallDetection_60GHz::FallDetection_60GHz(Stream *s)
    : stream(s){
  this->newData = false;
}

// Receive data and process
void FallDetection_60GHz::recvRadarBytes(){
  while (stream->available()) {                  //Data received
    if(stream->read() == MESSAGE_HEAD1){           //Receive header frame 1
      if(stream->read() == MESSAGE_HEAD2){         //Receive header frame 2
        dataLen = stream->readBytesUntil(MESSAGE_END2, Msg, 20); //Read data frame
        if (dataLen > 0 && dataLen < 20){
          Msg[dataLen] = MESSAGE_END2;            //Add end frame 2
          this->newData = true;                 //Data frame received
        }
      }
    }
  }
}

//Radar transmits data frames for display via serial port
void FallDetection_60GHz::showData(){
  if(this->newData){
    Serial.print(MESSAGE_HEAD1, HEX);          //Print header frame 1
    Serial.print(' ');
    Serial.print(MESSAGE_HEAD2, HEX);         //Print header frame 2
    Serial.print(' ');
    char charVal[4];
    for (byte n = 0; n < dataLen+1; n++) { 
      sprintf(charVal, "%02X", Msg[n]);
      Serial.print(charVal);
      Serial.print(' ');
    }
    Serial.println();
    this->newData = false;
    Msg[dataLen] = {0};
  }
}

// Judgment of occupied and unoccupied, approach and distance
void FallDetection_60GHz::HumanExis_Func(){
  recvRadarBytes(); 
  reset_val();
  if(this->newData){
    switch(Msg[0]){ 
      case HUMAN_PSE_RADAR:
        switch(Msg[1]){
          case PRESENCE_INF:
            switch(Msg[4]){
              case NOONE_HERE:
                showData();
                sensor_report = NOONE;
                break;
              case SOMEONE_HERE:
                showData();
                sensor_report = SOMEONE;
                break;
            }
            break;
          case MOVE_INF:
            switch(Msg[4]){
              case PSE_NONE:
                showData();
                sensor_report = NONEPSE;
                break;
              case STATIONARY:
                showData();
                sensor_report = STATION;
                break;
              case MOVEMENT:
                showData();
                sensor_report = MOVE;
                break;
            }
            break;
          case BODY_SIG:
            showData();
            sensor_report = BODYVAL;
            bodysign_val = Msg[4];
            break;
        }
        break;
    }
  }
}

//Respiratory sleep data frame decoding
void FallDetection_60GHz::Fall_Detection(){
  recvRadarBytes();
  reset_val();
  if(this->newData){
    switch(Msg[0]){
      case FALL_DETECTION:
        switch(Msg[1]){
          case FALL_STATE:
            switch(Msg[4]){
              case NO_FALL:
                showData();
                sensor_report = NOFALL;
                break;
              case FALLING:
                showData();
                sensor_report = FALL;
                break;
            }
            break;
          case RESIDENT_STATE:
            switch(Msg[4]){
              case NO_RESIDENT:
                showData();
                sensor_report = NORESIDENT;
                break;
              case RESIDENT:
                showData();
                sensor_report = RESIDENCY;
                break;
            }
            break;
        }
        break;
    }
  }
}




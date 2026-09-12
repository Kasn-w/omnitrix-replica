#include <TFT_eSPI.h>
#include <WiFiManager.h>
#include<WiFi.h>
#include <time.h>
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2SNoDAC.h"

#include "omicore.h"
#include "activate.h"
#include "openup.h"
#include "selecte.h"
#include "tranform.h"
#include "wait.h"
#include "icon7.h"

#define I2S_SPEAKER_SERIAL_CLOCK GPIO_NUM_5 // BCLK
#define I2S_SPEAKER_LEFT_RIGHT_CLOCK GPIO_NUM_5 // WSEL
#define I2S_SPEAKER_SERIAL_DATA GPIO_NUM_17       // pin 17 on the ESP32S2 where the speaker is connected

AudioGeneratorWAV *wav;
AudioFileSourcePROGMEM *file;
AudioOutputI2SNoDAC *out;

int bt[] = {3,4,18,21};
const int btrange = sizeof(bt)/sizeof(bt[0]);

int mod, rotacount, omcount;
int modc = 1;
String ltime, ldate;

TFT_eSPI ipsdisp= TFT_eSPI();           

void setup() {
  Serial.begin(115200);
  for(int i = 0;i < btrange ; i++){
    Serial.println(String(bt[i]) + " pin");
    pinMode(bt[i], INPUT); 
  }

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_3,1); 

  file = new AudioFileSourcePROGMEM( activate, sizeof(activate) );
  out = new AudioOutputI2SNoDAC();
  out -> SetPinout(I2S_SPEAKER_SERIAL_CLOCK, I2S_SPEAKER_LEFT_RIGHT_CLOCK, I2S_SPEAKER_SERIAL_DATA);
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);
  
  ipsdisp.begin();             //Initiatise SPI Bus
  ipsdisp.init();              //Initialise ST7789
  ipsdisp.setRotation(rotacount);      //Value 1 means landescape mode; Value 2 means potrait mode
  ipsdisp.setSwapBytes(true);  //Swap the byte order for pushImage() - corrects endianness
  ipsdisp.fillScreen(TFT_BLACK);

}

void loop() {
  //Trigger Once
  if (mod != modc){
    mod = modc;
    switch (mod){
      case 1 :
      //ipsdisp.pushImage(0,0,240,240,om);  //ipsdisp.pushImage(x1,y1,x2,y2,array of image 3 containting 16-bit RGB565 data of each pixel) 
        Disom();
        delay(100);
        break;
      case 2:
        Disom();
        ipsdisp.fillRect(25,70,193,102,TFT_GREEN); ipsdisp.fillRect(30,75,183,92,TFT_BLACK);

        ipsdisp.setTextColor(TFT_GREEN);
        for(int i = 0;i < 3 ; i++){
          ipsdisp.setCursor(60 + (i * 40),50,8);
          ipsdisp.print(".");
          Wifi_setup(false);
          delay(60);
        }

        Gettime();
        delay(100);
        ipsdisp.setTextColor(TFT_WHITE);
        ipsdisp.fillRect(20,23,200,194,TFT_GREEN); ipsdisp.fillRect(25,28,190,184,TFT_BLACK);
        ipsdisp.drawCentreString(ltime,120,67 ,7);
        ipsdisp.drawCentreString(ldate,120,132 ,4);
        break;
      case 10:
        ipsdisp.pushImage(39,39,165,165,core);
        omcount = 2;
        while ((digitalRead(4) == LOW)&&(digitalRead(21) == LOW)){
          if (wav->isRunning()){
            if (!wav->loop()) wav->stop();
          }else{
            Serial.printf("WAV done\n");
            Serial.print("count 2 = " + String(omcount));
            if (omcount == 2){ file = new AudioFileSourcePROGMEM( openup, sizeof(openup) ); omcount += 1;
            }else if (omcount == 3) file = new AudioFileSourcePROGMEM( wait, sizeof(wait) );
          
            out = new AudioOutputI2SNoDAC();
            out -> SetPinout(I2S_SPEAKER_SERIAL_CLOCK, I2S_SPEAKER_LEFT_RIGHT_CLOCK, I2S_SPEAKER_SERIAL_DATA);
      
            wav = new AudioGeneratorWAV();
            wav->begin(file, out);      
          }
        }
        ipsdisp.fillScreen(TFT_GREEN);
        omcount = 4;
        Serial.printf("WAV done\n");
        Serial.print("count 3 = " + String(omcount));
          
        file = new AudioFileSourcePROGMEM( tranform, sizeof(tranform) );
          
        out = new AudioOutputI2SNoDAC();
        out -> SetPinout(I2S_SPEAKER_SERIAL_CLOCK, I2S_SPEAKER_LEFT_RIGHT_CLOCK, I2S_SPEAKER_SERIAL_DATA);
      
        wav = new AudioGeneratorWAV();
        wav->begin(file, out);  
    
        while (omcount == 4){
          if (wav->isRunning()){
            if (!wav->loop()) wav->stop();
          }else omcount = 0; modc = 1;
        }
        delay(80);
        break;
     }
  }else{  //---------------------- LOOP ----------------------------
    switch (mod){
      case 1:
      int i;
      i = 0;
      if ((digitalRead(4) == HIGH)||(digitalRead(21) == HIGH)){
        ipsdisp.fillScreen(TFT_BLACK);
        ipsdisp.pushImage(39,39,165,165,core);
        ipsdisp.fillCircle(120, 120, 73, TFT_BLACK);
        mod = 0;
      }
      while ((digitalRead(4) == HIGH)||(digitalRead(21) == HIGH)){
        if (wav->isRunning()){
          if (!wav->loop()) wav->stop();
        }else{
          Serial.printf("WAV done\n");
          Serial.print("count 1 = " + String(omcount));
          if (omcount == 0){ file = new AudioFileSourcePROGMEM( activate, sizeof(activate) ); omcount = 1;
          }else if (omcount == 1) file = new AudioFileSourcePROGMEM( selecte, sizeof(selecte) ); modc = 10;
          
          out = new AudioOutputI2SNoDAC();
          out -> SetPinout(I2S_SPEAKER_SERIAL_CLOCK, I2S_SPEAKER_LEFT_RIGHT_CLOCK, I2S_SPEAKER_SERIAL_DATA);
      
          wav = new AudioGeneratorWAV();
          wav->begin(file, out);
          i ++;
          if (i > 7) i = 0;
          ipsdisp.pushImage(70,70,100,100,icon7[i]);
          delay(80);
        }
      }
      break;
      case 2:
      if (digitalRead(4) == HIGH){
        rotacount += 1; 
        if (rotacount > 3) rotacount = 0;
        ipsdisp.setRotation(rotacount);
        mod = 0;
      }else if (digitalRead(21) == HIGH){
        ipsdisp.fillScreen(TFT_BLACK);
        ipsdisp.drawCentreString("Going to sleep",120,40 ,4); ipsdisp.drawCentreString("Prees to stop",120,180 ,4);
        unsigned long time1 = millis(); int sumtime;
        delay(100);
        while ((digitalRead(3) == LOW)&&(digitalRead(4) == LOW)&&(digitalRead(18) == LOW)&&(digitalRead(21) == LOW)){
          unsigned long time2 = millis();
          int sumtimec = sumtime;
          sumtime = 10 - ((time2 - time1) / 1000);
          if (sumtime != sumtimec) ipsdisp.fillRect(0,70,240,100,TFT_BLACK);
          ipsdisp.drawCentreString(String(sumtime),120,100 ,7);
          if (sumtime <= 0){
            ipsdisp.fillScreen(TFT_BLACK); 
            esp_deep_sleep_start(); }
          delay(100);
        }mod = 0;
      }
      break;
    }
  }
       
  if (digitalRead(3) == HIGH){
    modc += 1;
    if (modc > 2) modc = 1;
  }else if (digitalRead(18) == HIGH){
    Wifi_setup(true);
  }

  Serial.print("mod : ");
  Serial.println(mod);
  if (wav->isRunning()){
    if (!wav->loop()) wav->stop();}
  delay(70);
}

void Disom(){
  ipsdisp.fillScreen(TFT_BLACK);
  ipsdisp.fillTriangle(78,120,0,-55,0,295,TFT_GREEN); ipsdisp.fillTriangle(48,120,0,35,0,205,TFT_BLACK);
  ipsdisp.fillTriangle(162,120,240,-55,240,295,TFT_GREEN); ipsdisp.fillTriangle(192,120,240,35,240,205,TFT_BLACK);
}

void Gettime(){
  WiFiClient Client;
  String tmi; String tse;
  configTime(7 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nLoading time");
  while (!time(nullptr)) { Serial.print("*"); delay(1000);}
    
  time_t now = time(nullptr); struct tm* p_tm = localtime(&now);
  delay(100);
  tmi = String(p_tm->tm_min); tse = String(p_tm->tm_sec);
  if (p_tm->tm_min < 10) tmi = "0" + tmi;
  if (p_tm->tm_sec < 10)tse = "0" + tse;
  
  ltime = String(p_tm->tm_hour) + " : " + tmi;
  ldate = String(p_tm->tm_mday) + "/" + String(p_tm->tm_mon + 1) + "/" + String(p_tm->tm_year + 2443);
}


void Wifi_setup(bool x){
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  bool res;
  if (x == false) {
    res = wm.autoConnect("Omitrix");
    Serial.println(res);
    if(!res) modc = 15;
  }else wm.resetSettings();
}

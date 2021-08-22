#include "carFunc.h"
static int cnt = 0;

void setup(){

  Serial.begin(9600);//一秒ごとにセンサーの状態を受信
  sensorSetup();
  
  timer0PWMInit();//モーターをPWM制御するための関数
  pinMode(SW1,INPUT_PULLUP);
 
  pinMode(PD4,OUTPUT);//右モーターの逆転側
  digitalWrite(PD4,LOW);

  
  pinMode(PD7,OUTPUT);//左モーター側の逆転側
  digitalWrite(PD7,LOW);

  pinMode(PD5,OUTPUT);//右モーターの正転
  pinMode(PD6,OUTPUT);//左モーターの正転
}

void loop(){
  
  if(!digitalRead(SW1)){
    cnt++;
  }
  if(cnt % 2 == 0){
    //停止
   if(cnt == 1){ 
    OCR0B = 0;
    OCR0A = 0;
    digitalWrite(PD4,LOW);
    digitalWrite(PD7,LOW);
  }else{//動作スタート
//直進
    bitSet(TCCR0A, COM0A1);
    bitSet(TCCR0A, COM0B1);
    OCR0B = 245;//右モーター出力
    OCR0A = 255;//左モーター出力
    digitalWrite(PD4,LOW);
    digitalWrite(PD7,LOW);
    


//右旋回
    if(PINB >= 24 && PINB <= 31){
      OCR0A = 255;
      OCR0B = 0;
    }

//左旋回
    if(PINB >= 48 && PINB <= 240){
      OCR0A = 0;
      OCR0B = 255;
    }

    //右端だけセンサー反応の時は大きく右旋回
    if(PINB == 1){
      OCR0A = 255;
      OCR0B = 0;
      delayMs(100);
    }
    //左端だけセンサー反応の時は大きく左旋回
    if(PINB == 128){
      OCR0A = 0;
      OCR0B = 255;
      delayMs(100);
    }

//ラインを見失ったときの処理
    if(PINB == 0){

      //後退
      bitClear(TCCR0A, COM0A1);
      bitClear(TCCR0A, COM0B1);
      digitalWrite(PD4,HIGH);
      digitalWrite(PD7,HIGH);
      delayMs(10);
      
      //右旋回
      bitSet(TCCR0A, COM0A1);
      bitSet(TCCR0A, COM0B1);
      OCR0A = 255;
      OCR0B = 0;
    }
  }
}

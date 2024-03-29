#define MaxFlashColorsSize 9
#define MaxColorSize 4
#define commandLength 5
char command[commandLength];
boolean CommandComplete;
int pwm;
int alpha;
int FadeDelay = 20;
int FlashSpeed = 100;
boolean isfading = 0;
boolean isflashing = 0;
int redVal;
int blueVal;
int greenVal;
int RGBpins[MaxColorSize] = {3, 5, 6, 9}; //{red,green,blue,alpha}
int red[MaxColorSize] = {255,0,0}; //{red,green,blue}
int green[MaxColorSize] = {0,255,0};
int blue[MaxColorSize] = {0,0,255};
int orange[MaxColorSize] = {255,165,0};
int pink[MaxColorSize] = {255,0,255};
int purple[MaxColorSize] = {128,0,128};
int teal[MaxColorSize] = {0,128,128};
int yellow[MaxColorSize] = {255,255,0};
int white[MaxColorSize] = {255,255,255};
int black[MaxColorSize] = {0,0,0};

//0=red,1=orange,2=yellow,3=green,4=teal,5=blue,6=purple,7=pink,8=white
int* FlashColors[MaxFlashColorsSize] = {red, orange, yellow, green, teal, blue, purple, pink, white};
int SetFlashColors[MaxFlashColorsSize] = {1,0,0,1,0,1,0,0,0};


void setup(){
  Serial.begin(115200);
  for(int i = 0; i < MaxColorSize; i++){
    pinMode(RGBpins[i], OUTPUT);
  }
}

void SetColor(int *Color){
  for(int i = 0; i < MaxColorSize;){
    analogWrite(RGBpins[i], Color[i]);
    i++;
  }
}

void Fade(){
  if(isfading == 1){
    redVal = 255;
    blueVal = 0;
    greenVal = 0;
    for( int i = 0 ; i < 255 ; i++){
      greenVal += 1;
      redVal -= 1;
      analogWrite(RGBpins[1], 255 - greenVal);
      analogWrite(RGBpins[0], 255 - redVal);
      delay(FadeDelay);
    }
    redVal = 0;
    blueVal = 0;
    greenVal = 255;
    for(int i = 0 ; i < 255 ; i++){
      blueVal += 1;
      greenVal -= 1;
      analogWrite(RGBpins[2], 255 - blueVal);
      analogWrite(RGBpins[1], 255 - greenVal);
      delay(FadeDelay);
    }
    redVal = 0;
    blueVal = 255;
    greenVal = 0;
    for(int i = 0 ; i < 255 ; i++){
      redVal += 1;
      blueVal -= 1;
      analogWrite(RGBpins[0], 255 - redVal);
      analogWrite(RGBpins[2], 255 - blueVal);
      delay(FadeDelay);
    }
  } 
}  

void Flash(){
  if(isflashing == 1){
    for(int i = 0; i < MaxFlashColorsSize; i++){
      if(SetFlashColors[i] == 1){
        SetColor(FlashColors[i]);
        delay(FlashSpeed);  
      } 
    }
  }
}


void loop(){
   if(Serial.available() >= commandLength){
    for(int i = 0; i < commandLength;){
    command[i] = Serial.read();
    i++;
    }

    if(command[0] == 'F' && command[1] == 'D'){
      FadeDelay = (command[2] - 48)*100 + (command[3] - 48)*10 + (command[4] - 48);
    }
    
    if(command[0] == 'F' && command[1] == 'S'){
      FlashSpeed = (command[2] - 48)*100 + (command[3] - 48)*10 + (command[4] - 48);
    }
    
    if(command[0] == 'F' && command[1] == 'C'){
      int Position = (command[2] - 48)*10 + (command[3] - 48);
      SetFlashColors[Position] = (command[4] - 48);
      for(int i = 0; i < MaxFlashColorsSize; i++){Serial.print(SetFlashColors[i]);}
      Serial.print('\n');
    }

    if(command[0] == 'T' && command[1] == 'E'){
      if(command[2] == 'F' && command[3] == 'A' && command[4] == '1'){
        isfading = 1;
      }
      if(command[2] == 'F' && command[3] == 'A' && command[4] == '0'){
        isfading = 0;
        loop();
      }
      if(command[2] == 'F' && command[3] == 'L' && command[4] == '1'){
        isflashing = 1;
      } 
      if(command[2] == 'F' && command[3] == 'L' && command[4] == '0'){
        isflashing = 0;
        loop();
      }     
    }


    if(command[0] == 'S' && command[1] == 'C'){
      if(command[2] == '0' && command[3] == '0' && command[4] == '0'){
        SetColor(blue);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '1'){
        SetColor(green);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '2'){
        SetColor(orange);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '3'){
        SetColor(pink);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '4'){
        SetColor(purple);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '5'){
        SetColor(red);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '6'){
        SetColor(teal);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '7'){
        SetColor(white);
      } 
      if(command[2] == '0' && command[3] == '0' && command[4] == '8'){
        SetColor(yellow);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '9'){
        SetColor(black);
      }
    }

    if(command[0] == 'r' && command[1] == 'e'){
      pwm = (command[2] - 48)*100 + (command[3] - 48)*10 + (command[4] - 48);
      analogWrite(RGBpins[0], pwm);
    }
    if(command[0] == 'g' && command[1] == 'r'){
      pwm = (command[2] - 48)*100 + (command[3] - 48)*10 + (command[4] - 48);
      analogWrite(RGBpins[1], pwm);
    }
    if(command[0] == 'b' && command[1] == 'l'){
      pwm = (command[2] - 48)*100 + (command[3] - 48)*10 + (command[4] - 48);
      analogWrite(RGBpins[2], pwm);
    }
    if(command[0] == 'a' && command[1] == 'l'){
      alpha = (command[2] - 48)*100 + (command[3] - 48)*10 + (command[4] - 48);
      analogWrite(RGBpins[3], alpha);
    }
    


    Serial.print("DTR-OK");Serial.print('\n');
    Serial.flush();
    delay(10);
  }
  else{
    Fade();
    Flash();
  }
}




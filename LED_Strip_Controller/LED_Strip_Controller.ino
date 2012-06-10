char command[5];
int pwm;
int FadeDelay = 20;
boolean isfading = 0;
int redVal;
int blueVal;
int greenVal;
int RGBpins[] = {3, 5, 6}; //{red,green,blue}
int red[3] = {255,0,0}; //{red,green,blue}
int green[3] = {0,255,0};
int blue[3] = {0,0,255};
int orange[3] = {255,165,0};
int pink[3] = {255,0,255};
int purple[3] = {128,0,128};
int teal[3] = {0,128,128};
int yellow[3] = {255,255,0};
int white[3] = {255,255,255};
int black[3] = {0,0,0};


void setup(){
  Serial.begin(115200);
  for(int i = 0; i < 3; i++){
    pinMode(RGBpins[i], OUTPUT);
  }
}

void SetColor(int *Color, int n_Length){
  for(int i = 0; i < n_Length;){
    analogWrite(RGBpins[i], Color[i]);
    i++;
  }
}

void checkFade(){
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


void loop(){
  if(Serial.available() >= 5){
    for(int n = 0; n < 5;){
      command[n] = Serial.read();
      n ++; 
    }

    if(command[0] == 'F' && command[1] == 'S'){
      FadeDelay = (command[2] - 48)*100 + (command[3] - 48)*10 + (command[4] - 48);
    }

    if(command[0] == 'T' && command[1] == 'E'){
      if(command[2] == '0' && command[3] == '1' && command[4] == 'F'){
        isfading = 1;
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == 'F'){
        isfading = 0;
        loop();
      }        
    }  

    if(command[0] == 'S' && command[1] == 'C'){
      if(command[2] == '0' && command[3] == '0' && command[4] == '0'){
        SetColor(blue,3);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '1'){
        SetColor(green,3);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '2'){
        SetColor(orange,3);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '3'){
        SetColor(pink,3);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '4'){
        SetColor(purple,3);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '5'){
        SetColor(red,3);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '6'){
        SetColor(teal,3);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '7'){
        SetColor(white,3);
      } 
      if(command[2] == '0' && command[3] == '0' && command[4] == '8'){
        SetColor(yellow,3);
      }
      if(command[2] == '0' && command[3] == '0' && command[4] == '9'){
        SetColor(black,3);
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


    Serial.print("OK");
    Serial.flush();
    delay(10);
  }else{
    checkFade();
  }  
}




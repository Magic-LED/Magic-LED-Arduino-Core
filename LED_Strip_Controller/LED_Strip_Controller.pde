char command[5];
int pwm;
int RGBpins[] = {3, 5, 6}; //{red,green,blue}
const int red[] = {255,0,0}; //{red,green,blue}
const int green[] = {0,255,0};
const int blue[] = {0,0,255};
const int orange[] = {255,165,0};
const int pink[] = {255,0,255};
const int purple[] = {128,0,128};
const int teal[] = {0,128,128};
const int yellow[] = {255,255,0};
const int white[] = {255,255,255};



void setup(){
  Serial.begin(115200);
  for(int i = 0; i < 3; i++){pinMode(RGBpins[i], OUTPUT);}
}


void set_Color(int Color[3]){
  for(int i = 0; i < 3;){
    RGBpins[i] = Color[i];
    i++;
  }
}

void loop(){
  if(Serial.available() >= 5){
    for(int n = 0; n < 5;){
     command[n] = Serial.read();
     n ++; 
    }
    
    if(command[0] == 'r' && command[1] == 'e'){
      pwm = (command[2] - 48)*100 + (command[3] - 48)*10 + (command[4] - 48);
      analogWrite(RGBpins[0], pwm);
    }
    else if(command[0] == 'g' && command[1] == 'r'){
      pwm = (command[2] - 48)*100 + (command[3] - 48)*10 + (command[4] - 48);
      analogWrite(RGBpins[1], pwm);
    }
    else if(command[0] == 'b' && command[1] == 'l'){
      pwm = (command[2] - 48)*100 + (command[3] - 48)*10 + (command[4] - 48);
      analogWrite(RGBpins[2], pwm);
    }
    else{
    }
   
    Serial.print("OK");
    Serial.print('\n');
    Serial.flush();
    delay(10);
  }
  
}

//#include<Servo.h>
#include<Leg.h>
#include <math.h>
// 11 // 10


Leg loa;
Leg loo;
Leg laa;
Leg lao;
//Servo omz;

void setup() {
  
  Serial.begin(9600);
  delay(500);
  pinMode(13,OUTPUT);
  for(int i=0;i<5;i++){
    digitalWrite(13,LOW);
    delay(500);
    digitalWrite(13,HIGH);
    Serial.println(5-i);
    delay(500);
  }
    digitalWrite(13,LOW);
    Serial.println("Starting");
    delay(500);
    
  //int ust_pin,int alt_pin,float ust_def,float ust_max,float ust_min,float ust_duz,float alt_def,float alt_min,float alt_max
  int omz=0;
  lao.setReady(3,2,4,17,145,30,90,114,20,115,100);    //4
  lao.alt_reverse=true;
  laa.setReady(6,7,5,10,135,22,80,119,20,125,98);    //5
  laa.ust_reverse=true;
  laa.omuz_reverse=true;

  //loo.setReady(11,12,13,30,171,51,110,50,37,123,85);
  loo.setReady(11,12,13,35,171,51,110,50,32,123,85); //13
  loo.alt_reverse=true;
  loa.setReady(8,9,10,23,165,45,110,104,32,120,106);   //10
  loa.ust_reverse=true;
  loa.omuz_reverse=true;
  //omz.attach(13);
  //omz.write(90);

  
  
  //lao.setReady(3,2,34,145,30,90,114,25,115);    //4
  //lao.alt_reverse=true;
   

  //setDef();
  sitReady();
  getUp();
  delay(3500);
  
  walkTest2();
  
  //loa.setLegXY(0,-0.5,12);
  //laa.setLegXY(0,-0.5,12);
  //loo.setLegXY(0,-0.5,12);
  //lao.setLegXY(0,-0.5,12);
  //loa.setLegXY(0,-4,12);
  //delay(3000);
  //loo.setLegXY(0,0,8);
  

}

int walk_cm=2;
float walk_min_dis=9.5f;
float walk_max_dis=12.5f;


void grup1(float x,float dis){
    loo.setLegXY(x,1.5f,dis);
    laa.setLegXY(x,-1.5f,dis);
}
void grup2(float x,float dis){
    loa.setLegXY(x,-1.5f,dis);
    lao.setLegXY(x,1.5f,dis);
}
void grupController(int i){ // 0-16
  int index=i<walk_cm*2?i-walk_cm:walk_cm*4-i;
  grup1(index,i<walk_cm*2?walk_max_dis:walk_min_dis);
  grup2(-1*index,i>walk_cm*2?walk_max_dis:walk_min_dis);
}
void grupEnd(){
  grup1(0,walk_max_dis);
  grup2(0,walk_max_dis);
}
/*
 * int i=0;
    for(i=0;i<walk_cm*4;i++){
      grupController(i);
      delay(50);
    }
    delay(50);
    grupEnd();
 */
float walk_range_max=-2.5f;
float walk_range_min=0.75f;
float omuz_left=-0.5f;
float omuz_right=-0.5f;

void walkTest2(){

  for(int i=0;i<4;i++){
    /*for(float x=walk_range_max;x<walk_range_min;x+=0.1f){
      loo.setLegXY(x,0,12);
      delay(20);
    }*/
    float per =(walk_range_min-walk_range_max)/5.0f;
    for(int i=1;i<=5;i++){
      loo.setLegXY(per*i,omuz_left,12.5f);
      laa.setLegXY(per*i,omuz_right,12.5f);
      lao.setLegXY(walk_range_max-1,omuz_left,8.5f); 
      loa.setLegXY(walk_range_max-1,omuz_right,8.5f); 
      delay(26);
    }
    for(int i=1;i<=5;i++){
      loo.setLegXY((walk_range_max+walk_range_min)/2.0f,omuz_left,8.5f); 
      laa.setLegXY(walk_range_max-1,omuz_right,8.5f); 
      lao.setLegXY(per*i,omuz_left,12.5f);
      loa.setLegXY(per*i,omuz_right,12.5f);
      delay(26);
    }
    //delay(115);
  }
  //loo.setLegXY(0,0,12); 
  setDef();
}
/*
 * 
  loo.setLegXY(0,0,12);
  for(float x=0;x<4;x+=1){
    loo.setLegXY(x,0,12);
    laa.setLegXY(x,0,12);
    delay(50);
  }
  loo.setLegXY(0,0,10);
  laa.setLegXY(0,0,10);
  delay(100);
  loo.setLegXY(-4,0,12);
  laa.setLegXY(-4,0,12);
  for(float x=-4;x<4;x+=1){
    loo.setLegXY(x,0,12);
    laa.setLegXY(x,0,12);
    delay(50);
  }
  //loo.setLegXY(-4,0,12);
  delay(100);
  loo.setLegXY(0,0,10);
  laa.setLegXY(0,0,10);
  delay(200);
  loo.setLegXY(0,0,12);
  laa.setLegXY(0,0,12);
 */

  /*
  for(float x=0;x>-4;x-=0.1f){
    loo.setLegXY(x,0,12);
    delay(20);
  }
  for(float x=-4;x<4;x+=0.1f){
    loo.setLegXY(x,0,10);
    delay(8);
  }
  loo.setLegXY(4,0,12);
  for(float x=4;x>0;x-=0.1f){
    loo.setLegXY(x,0,12);
    delay(20);
  }
  loo.setLegXY(0,0,12);
  */
//========================================
void singleLegLift(){
   loo.setLegXY(0,0,11);
   loa.setLegXY(0,0,11);
   lao.setLegXY(0,0,11);
   laa.setLegXY(0,0,11);
  delay(500);
  
//Turn Lift
  for(float y=0;y>-4;y-=0.1f){
    loa.setLegXY(0,y,11);
    delay(50);
  }
  delay(500);
  
  for(float dis=11;dis>8;dis-=0.1f){
    loo.setLegXY(0,0,dis);
    delay(20);
  }
  
  delay(500);
// Lift
for(int i=0;i<3;i++){
  for(float dis=11;dis<14.5f;dis+=0.1f){
    loa.setLegXY(0,-4,dis);
    delay(20);
  }
  
  delay(500);
  for(float dis=14.5f;dis>11;dis-=0.1f){
    loa.setLegXY(0,-4,dis);
    delay(20);
  }
  
  delay(500);
}

//Turn Normal
  
  for(float dis=8;dis<11;dis+=0.1f){
    loo.setLegXY(0,0,dis);
    delay(20);
  }
  
  delay(500);
  for(float y=-4;y<0;y+=0.1f){
    loa.setLegXY(0,y,11);
    delay(50);
  }
  delay(500);

  setDef();
  
}

void LookUp(){
  
  for(int dis=12;dis>=10;dis-=1){
    laa.setLegXY(0,0,dis);
    lao.setLegXY(0,0,dis);
    
    loa.setLegXY(0,0,12+(12-dis));
    loo.setLegXY(0,0,12+(12-dis));
    delay(85);
  }
  delay(2000);
    
  for(int dis=10;dis<=12;dis+=1){
    laa.setLegXY(0,0,dis);
    lao.setLegXY(0,0,dis);
    loa.setLegXY(0,0,12+(12-dis));
    loo.setLegXY(0,0,12+(12-dis));
    delay(85);
  }
}
void sitReady() {
  setLegXY(0,0,8);
  writeUst(10);
}
void sit(){
  setLegXY(0,0,12);
  writeOmuz(0);
  for(int dis=12;dis>=8;dis-=1){
    setLegXY(0,0,dis);
    delay(65);
  }
  setLegXY(0,0,8);
  for(int angle=60;angle>10;angle-=1){
    writeUst(angle);
    delay(30);
  }
  writeUst(10);
}
  
void getUp(){
  for(int angle=10;angle<60;angle+=1){
    writeUst(angle);
    delay(30);
  }
  setLegXY(0,0,8);
  for(int dis=8;dis<=12;dis+=1){
    setLegXY(0,0,dis);
    delay(65);
  }
  setLegXY(0,0,12);
  
}
void setLegXY(float x,float y,float dis){
   loo.setLegXY(x,y,dis);
   loa.setLegXY(x,y,dis);
   lao.setLegXY(x,y,dis);
   laa.setLegXY(x,y,dis);
}
//=============================================
float wake=11;
bool dd=true;
//70$ 25# / 15$ 40#
String msg="";
void loop() {

  if(Serial.available()>0){
    char c=Serial.read();
    if(c=='#'){
      int x=msg.toInt();
      loo.writeUst(x);//+2+23
      loa.writeUst(x);//+19
      lao.writeUst(x);//+7
      laa.writeUst(x);
      Serial.println("#"+String(x));
      msg="";
    }else if(c=='$'){
      int x=msg.toInt();
      lao.writeAlt(x);
      laa.writeAlt(x);
      //delay(500);
      loo.writeAlt(x);
      loa.writeAlt(x);
      Serial.println("$"+String(x));
      msg="";
      
    }else if(c=='%'){
      int x=msg.toInt();
      writeOmuz(x);
      Serial.println("%"+String(x));
      msg="";
      
    }else if(c=='&'){
      int x=msg.toInt();
      String m=(x==0?"default position":(x==1?"sitting...":(x==2?"getting up...":"unknown")));
      Serial.println("%"+m);
      if(x==0)
        setDef();
      else if(x==1)
        sit();
      else if(x==2)
        getUp();
      else if(x>=3)
        walkDeneme(x);
      
      msg="";
    }else if(c=='!'){
      int x=msg.toInt();
      if(x==0)
        walkTest2();
      if(x==1)
        singleLegLift();
      if(x==2)
       LookUp();
      msg="";
    }else{
      msg+=c;
    }    
  }else if(false){
  }
}
//==================
//70$ 25# / 15$ 40#
/*
  15,90,14,
  25,70,11.5f,
  40,50,10.5f,
 */

float value_up[3]={25,70,11.5f,};
float values[12]={
  3,85,16,
  27,50,12.5f,
  45,30,9.5f,
  60,15,8
};
void walkDeneme(float c){
  walk1(c);
  
}
void walkXY(float x,float y,float distance){

  float hip = sqrt((distance*distance)+(y*y));
  float angle = asin((y/hip))*180/PI;
  
  Serial.println(String(hip)+" - "+String(angle)+"  for:"+String(x)+"/"+String(y)+"/"+String(distance));
  loo.writeOmuz(angle);
  walkX(x,hip);
  
}
void walkX(float x,float dis){

  float hip = sqrt((dis*dis)+(x*x));
  float angle = asin((x/hip))*180/PI;
  walk3(hip,angle);
  //Serial.println(String(hip)+" - "+String(angle)+"  for:"+String(x)+"/"+String(dis));
   
}
/*
 * //float b = 11.5;
  //float a = 10  ;
  //float A =   (acos(((b*b)+(c*c)-(a*a))/(2*b*c))/PI)*180.0f;
  //float C =   (acos(((a*a)+(b*b)-(c*c))/(2*a*b))/PI)*180.0f;

  //Serial.println(String(A-45));
  writeUst(40);
  writeAlt(13,0);
 * 
 */
void walk1(float cm){
  walk1(cm,0);
}
void walk1(float cm,float angle){
  int sz=(sizeof(values)/sizeof(float));
  cm=cm>values[2]?values[2]:(cm<values[sz-1]?values[sz-1]:cm);
  int no = 0;
  for(int i=1;i<sz/3;i++){
    if(values[i*3 +2]<=cm)
      {
        no=i-1;
        break;
      }
  }

  float mn=values[(no+1)*3+2];
  float mx=values[no*3+2];
  float percent =(cm-mn)/(mx-mn);
  float ust= (values[no*3]-values[(no+1)*3])*percent+values[(no+1)*3];
  float alt= (values[no*3+1]-values[(no+1)*3+1])*percent+values[(no+1)*3+1];
  
  
  writeUst(ust+angle);
  writeAlt(alt,0);
  writeOmuz(0);

}

void walk3(float cm,float angle){
  int sz=(sizeof(values)/sizeof(float));
  cm=cm>values[2]?values[2]:(cm<values[sz-1]?values[sz-1]:cm);
  int no = 0;
  for(int i=1;i<sz/3;i++){
    if(values[i*3 +2]<=cm)
      {
        no=i-1;
        break;
      }
  }

  float mn=values[(no+1)*3+2];
  float mx=values[no*3+2];
  float percent =(cm-mn)/(mx-mn);
  float ust= (values[no*3]-values[(no+1)*3])*percent+values[(no+1)*3];
  float alt= (values[no*3+1]-values[(no+1)*3+1])*percent+values[(no+1)*3+1];
  
  
  loo.writeUst(ust-angle);
  loo.writeAlt(alt);
  //writeOmuz(0);

}

void walk2(){
  
    for(float i=wake;i<15.5;i+=0.1f){
      walkDeneme(i);
      delay(10);
    }
    delay(1000);
    wake=14;
    for(float i=wake;i>8;i-=0.1f){
      walkDeneme(i);
      delay(10);
    }
    wake=8;
    
    delay(1000);
    for(float i=wake;i<12;i+=0.1f){
      walkDeneme(i);
      delay(10);
    }
    wake=12;
    delay(1500);
}
//=================

//70$Alt 25# -> 15$Alt 40#
//15$Alt 40#Ust
  
  /*
  delay(700);
  writeAlt(50,0);
  writeUst(30);
  delay(700);
  writeAlt(15,0);
  writeUst(40);
  delay(700);
  writeOmuz(25);
  */

//writes all Servo of Leg for idle
void setDef(){
      writeUst(27);
      writeAlt(50,0);
      writeOmuz(0);
}
//writes Shoulder Servo of Legs
void writeOmuz(int x){
      loo.writeOmuz(x);
      loa.writeOmuz(x);
      lao.writeOmuz(x);
      laa.writeOmuz(x);
}
//writes Upper Servo of Legs
void writeUst(int x){
      loo.writeUst(x);
      loa.writeUst(x);
      lao.writeUst(x);
      laa.writeUst(x);
}
//writes Lower Servo of Legs
void writeAlt(int x,int dly){
      lao.writeAlt(x);
      laa.writeAlt(x);
      delay(dly);
      loo.writeAlt(x);
      loa.writeAlt(x);
}

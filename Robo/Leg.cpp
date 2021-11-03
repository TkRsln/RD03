/*
**‎22 ‎April ‎2021 ‎Thursday, ‏‎20:57:39 
**Author: CodX07
**Simple Leg Library
*/



#include <Leg.h>
#include <Servo.h>
#include <math.h>

/*
	float array which contains angles for distance from ground. 
	I tried "Cosine theorem" first, but some unstable angles occurred so i decided to record angles for distance from ground.
	[upper servo angle, lower servo angle, distance from ground as cantimeter]
*/
float dis_values[12]={
  3,85,16,
  27,50,12.5f,
  45,30,9.5f,
  60,15,8
};

Leg::Leg(int ust_pin,int alt_pin,int omz_pin,float ust_def,float ust_max,float ust_min,float ust_duz,float alt_def,float alt_min,float alt_max){
	Leg::ust_def=ust_def;
      	Leg::ust_max=ust_max;//Max "upper leg servo" angle to be
      	Leg::ust_duz=ust_duz;//Idle "upper leg servo" angle to be
      	Leg::ust_min=ust_min;//Min "upper leg servo" angle to be
      	Leg::alt_max=alt_max;//Same things for "lower leg servo"
      	Leg::alt_min=alt_min;
      	Leg::alt_def=alt_def;
      
      	Leg::ust.attach(ust_pin);//upper leg servo pin
      	Leg::alt.attach(alt_pin);//lower leg servo pin
	Leg::omuz.attach(omz_pin);//shoulder leg servo pin
}
Leg::Leg(){}
void Leg::setReady(int ust_pin,int alt_pin,int omz_pin,float ust_def,float ust_max,float ust_min,float ust_duz,float alt_def,float alt_min,float alt_max,float omuz_def){
	//if you invoke class with default constractor, you can use this method for assign values
	Leg::ust_def=ust_def;
      	Leg::ust_max=ust_max;
      	Leg::ust_duz=ust_duz;
      	Leg::ust_min=ust_min;
      	Leg::alt_max=alt_max;
      	Leg::alt_min=alt_min;
      	Leg::alt_def=alt_def;
	Leg::omuz_def=omuz_def;
      
      	Leg::ust.attach(ust_pin);
      	Leg::alt.attach(alt_pin);
	Leg::omuz.attach(omz_pin);
	  
	Leg::writeOmuz(0);
	  
}


/*
	this function uses basic trigonometry to calculate foot point
	x stands for:
		calculates how far to the forward and backward to put its foot in "cantimeter" (range can be minus value for forward/backward)
	y stands for:
		calculates how far to the left and right to put its foot in "cantimeter" (range can be minus value for left/right)
	distance stands for:
		how far should be robot up from ground
*/
void Leg::setLegXY(float x,float y,float distance){
  float hip = sqrt((distance*distance)+(y*y)); //
  float angle = asin((y/hip))*180/M_PI ;
  Leg::writeOmuz(angle);
  Leg::setLegX(x,hip);
}
//calculates angles for upper and lower servo by X value (Forward/Backward) and distance from ground
void Leg::setLegX(float x,float dis){
  float hip = sqrt((dis*dis)+(x*x));
  float angle = asin((x/hip))*180/M_PI ;
  Leg::setLegDis(hip,angle);
}
void Leg::setLegDis(float cm){
	Leg::setLegDis(cm,0);
}
//calculates only upper and lower servos. (Forward/Backward)
void Leg::setLegDis(float cm,float angle/*initial angle for rotation*/){
  int sz=(sizeof(dis_values)/sizeof(float));
  cm=cm>dis_values[2]?dis_values[2]:(cm<dis_values[sz-1]?dis_values[sz-1]:cm);
  int no = 0;
  for(int i=1;i<sz/3;i++){
    if(dis_values[i*3 +2]<=cm)
      {
        no=i-1;
        break;
      }
  }
  float mn=dis_values[(no+1)*3+2];
  float mx=dis_values[no*3+2];
  float percent =(cm-mn)/(mx-mn);
  float ust= (dis_values[no*3]-dis_values[(no+1)*3])*percent+dis_values[(no+1)*3];
  float alt= (dis_values[no*3+1]-dis_values[(no+1)*3+1])*percent+dis_values[(no+1)*3+1];
  
  Leg::writeUst(ust+angle);
  Leg::writeAlt(alt);
}
// attaches upper and lower servos
void Leg::setReady(int ust_pin,int alt_pin){
      Leg::ust.attach(ust_pin);
      Leg::alt.attach(alt_pin);
}
//reverses lower servo angle for leg (since left leg works opposite way than right, you can see 180-angle if reverse is true)
void Leg::writeNAlt(int angle){
	Leg::alt.write(alt_reverse?180-angle:angle);
	Leg::alt_current=angle;
	
}
void Leg::writeNUst(int angle){
	Leg::ust.write(ust_reverse?180-angle:angle);
	Leg::ust_current=angle;
}
void Leg::writeAlt(int angle){
	writeNAlt(angle+alt_min);
}
void Leg::writeUst(int angle){
	writeNUst(angle+ust_min);
}
//shoulder functions (since left leg works opposite way than right)
void Leg::writeOmuz(int angle){
	Leg::writeNOmuz(angle+Leg::omuz_def);
}
//shoulder functions (since left leg works opposite way than right)
void Leg::writeNOmuz(int angle){
	Leg::omuz.write(omuz_reverse?180-angle:angle);
	Leg::omuz_current=angle;
}

void Leg::write(int ust,int alt){
	Leg::writeUst(ust);
	Leg::writeAlt(alt);
}



//sets default angle
void Leg::setDef(){
	Leg::writeNUst(Leg::ust_def);
    	Leg::writeNAlt(Leg::alt_def);
	Leg::writeNOmuz(Leg::omuz_def);
}
//for max distance from ground
void Leg::setUp(){
	Leg::writeNUst(Leg::ust_max);
    	Leg::writeNAlt(Leg::alt_max);
}
//for idle distance from ground
void Leg::setDuz(){
	Leg::writeNUst(Leg::ust_duz);
    	Leg::writeNAlt(Leg::alt_def);
}

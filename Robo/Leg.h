#include <Servo.h>

class Leg {
	public:
    Servo ust;
    Servo alt;
	Servo omuz;
    
    float ust_def=0;
    float ust_max=0;
    float ust_min=0;
    float ust_duz=0;
	float ust_current;
    
    float alt_def=0;
    float alt_max=0;
    float alt_min=0;
	float alt_current;
	

	float omuz_min=0;
	float omuz_def=0;
	float omuz_max=0;
	float omuz_current=0;
	
	bool ust_reverse;
	bool alt_reverse;
	bool omuz_reverse;
	
	Leg(int ust_pin,int alt_pin,int omz_pin,float ust_def,float ust_max,float ust_min,float ust_duz,float alt_def,float alt_min,float alt_max);
	Leg();
	void setReady(int ust_pin,int alt_pin,int omz_pin,float ust_def,float ust_max,float ust_min,float ust_duz,float alt_def,float alt_min,float alt_max,float omuz_def);
	void setReady(int ust_pin,int alt_pin);
	void setDef();
	void setUp();
	void setDown();
	void setDuz();
	void writeNUst(int angle);
	void writeNAlt(int angle);
	void writeUst(int angle);
	void writeAlt(int angle);
	void writeNOmuz(int angle);
	void writeOmuz(int angle);
	void write(int ust,int alt);
	
	void setLegXY(float x,float y,float distance);
	void setLegX(float x,float dis);
	void setLegDis(float cm);
	void setLegDis(float cm,float angle);
};
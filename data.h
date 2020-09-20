#ifndef DATA_H
#define DATA_H

int Pin1 = D1;//IN1 is connected 
int Pin2 = D2;//IN2 is connected   
int Pin3 = D3;//IN3 is connected 
int Pin4 = D4;//IN4 is connected 

 
int pole1[] ={0,0,0,0, 0,1,1,1, 0};//pole1, 8 step values
int pole2[] ={0,0,0,1, 1,1,0,0, 0};//pole2, 8 step values
int pole3[] ={0,1,1,1, 0,0,0,0, 0};//pole3, 8 step values
int pole4[] ={1,1,0,0, 0,0,0,1, 0};//pole4, 8 step values

int poleStep = 0; 
int  dirStatus = 3;// stores direction status 3= stop (do not change)

String buttonTitle1[] ={"CCW", "CW"};//Watch Video for details (on Udemy)
String buttonTitle2[] ={"CCW", "CW"};
String argId[] ={"ccw", "cw"};


#endif /* DATA_H */

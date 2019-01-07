#include "MotorPID.h"
#include "Invkin.h"
int X , Y , Z ;
int move ; 
int base_pwm=7;
int base_dir=34;

Invkin IK(50,0,23);

MotorPID motor(3,22,A0,35); //shoulder

MotorPID motor1(5,28,A3,30); //elbow



int a = 1573 ; //Link angle at set up shoulder for potentiometer

int b = 1467; //Link angle at set up elbow for potentiometer

int a1 = 30 ;  // Link angle at that value 

int b1 = 60 ; //Link angle at that value 

int k1 = a + 5.5*a1 ;

int k2 = b - 4*b1 ; 

void setup() { 
  Serial.begin(9600);
  motor.setPID(0.39,0.000001,-0.02);
  pinMode(base_dir,OUTPUT);
  pinMode(base_pwm,OUTPUT);
  motor1.setPID(0.25,0.00001,0.02);
  motor.x = k1 - 5.5*IK.theta2  ;  // + goes down relative to position now to zero to relative position
  motor1.x = k2  - 4*IK.theta3 ;    // - goes up relative to position now to zero relative position
 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("X : ");
  Serial.print(IK.X );  
  Serial.print("  Y : ") ; 
  Serial.print(IK.Y);  
  Serial.print("  Z : ");  
  Serial.print(IK.Z);  
  IK.transform();
  motor.x = k1 - 5.5*IK.theta2  ;  // + goes down relative to position now to zero to relative position
  motor1.x = k2  - 4*IK.theta3 ; 
  Serial.println("------Shoulder Motor---------");
  Serial.println(" ");
  motor.errorcheck();
  Serial.println("------Elbow Motor---------");
  Serial.println(" ");
  motor1.errorcheck() ;
  delay(1000);
  Serial.println(" move ?? "); 
  while(Serial.available()){
  move = Serial.parseInt();
 
 if(move==0){}
 if(move==1){
  IK.X = IK.X + 1 ;
 }
 if(move==2){
  IK.X = IK.X - 1 ;
  }

 if(move==3){
   digitalWrite(base_dir,LOW);
   analogWrite(base_pwm,150);
   
   delay(200);
   analogWrite(base_pwm,0);
 }
   
 if(move==4){
   analogWrite(base_pwm,100);
   digitalWrite(base_dir,HIGH);
   delay(300);
   analogWrite(base_pwm,0);
   }
 if(move==5){
  IK.Z = IK.Z + 1 ;
  }
 if(move==6){
  IK.Z = IK.Z - 1 ;
   }

  }
  
  
}

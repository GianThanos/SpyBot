//------------------------------------------------------------libraries

#include <NewPing.h>

//------------------------------------------------------------inputs

int arA = 23;
int arB = 25;
int deA = 27;
int deB = 29;

int led_tape = 26; //led tape

const int trigPin_fr = 30; // sonic sensors  
const int echoPin_fr = 28;

//-------------------------------------------------------------var

int vel = 153;
boolean led_status = false;

long duration_fr; // sonic sensors var
int distance_fr ;
NewPing sonar(trigPin_fr, echoPin_fr, distance_fr);

//----------------------------------------------------------------set up

void setup()
{

  Serial.begin(9600);  
  pinMode(deA, OUTPUT);
  pinMode(deB, OUTPUT);
  pinMode(arA, OUTPUT);
  pinMode(arB, OUTPUT);
  pinMode(led_tape,OUTPUT);
  pinMode(trigPin_fr, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_fr, INPUT); // Sets the echoPin as an Input
}

//--------------------------------------------------------------loop
void loop()
{ 
  while (Serial.available()) 
  {
    delay(30);   
    if (Serial.available() >0)
    {
      char data_rec = Serial.read();  
      //-----------------------------------------------movement
      
      if (data_rec == 't'){
          
        digitalWrite(trigPin_fr, LOW); 
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin_fr, HIGH); 
        delayMicroseconds(10);
        digitalWrite(trigPin_fr, LOW);
        duration_fr = pulseIn(echoPin_fr, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
        distance_fr= duration_fr*0.034/2;
        Serial.println(distance_fr);
        }
        
      if (data_rec == 's' ){          //backward
        backward();  }      
      else if (data_rec == 'w' ){     //forward
        forward(); }      
      else if (data_rec == 'a' ){     //left
        left();}     
      else if (data_rec == 'd' ){     //right
        right();}        
      else if (data_rec == 'p'){
        stop_mov();}
        
      //-----------------------------------------------led
      else if (data_rec == 'e'){
        led_switch();}
            

    }
  }
  
}

//---------------------------------------------------------------------functions
//int calculateDistance_fr(){ 
//  
//  digitalWrite(trigPin_fr, LOW); 
//  delayMicroseconds(2);
//  // Sets the trigPin on HIGH state for 10 micro seconds
//  digitalWrite(trigPin_fr, HIGH); 
//  delayMicroseconds(10);
//  digitalWrite(trigPin_fr, LOW);
//  duration_fr = pulseIn(echoPin_fr, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
//  distance_fr= duration_fr*0.034/2;
//  return distance_fr;
//}

void backward(){
 analogWrite(deB, 0);
 analogWrite(arB, 0);
 analogWrite(deA, vel);
 analogWrite(arA, vel);}
 
void forward(){
 analogWrite(deA, 0);
 analogWrite(arA, 0);
 analogWrite(deB, vel);
 analogWrite(arB, vel);}
 
void stop_mov (){
 analogWrite(deB, 0);
 analogWrite(arB, 0);
 analogWrite(deA, 0);
 analogWrite(arA, 0);}
 
void right(){
 analogWrite(deB, vel); 
 analogWrite(arB, 0);
 analogWrite(deA, 0);
 analogWrite(arA, vel);}

void left(){
 analogWrite(deB, 0);
 analogWrite(arB, vel);
 analogWrite(arA, 0);
 analogWrite(deA, vel);}
 
void led_switch(){
  if (led_status == false){
    digitalWrite(led_tape,HIGH);
    delay(100);
    led_status = true;}
  else {
    digitalWrite(led_tape,LOW);
    delay(100);
    led_status = false ;} }
    



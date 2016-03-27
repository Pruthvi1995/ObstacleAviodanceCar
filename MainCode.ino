#include <Servo.h>

#define trigPin 3
#define inPin 2
#define back 10
#define fwd 11
#define speedo 100
#define speedoback 50
#define speedoturn 160
#define straight 90
Servo servoMain;
Servo servoEye;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(inPin, INPUT);
  servoMain.attach(5);
  servoEye.attach(6);
  pinMode(4,OUTPUT);
  pinMode(fwd,OUTPUT);
  pinMode(back,OUTPUT);
  
  digitalWrite(4,HIGH);
  servoMain.write(straight);
  servoEye.write(90);
  delay(200);
}
int duration, distance, chk;
void loop()
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(inPin, HIGH);
  distance = (duration/2)/29.1;
  Serial.println(distance);
  drive();
  delay(50);
  if(distance < 50)
  {
    stopcar();
    delay(500);    
    chk = check();
    if(chk == 1)
    {
      while(goright())
      {
        
      }
    }
    else if(chk == 2)
    {
      while(goleft())
      {
                                                                                                                                                
      }
    }
    else
    {
      delay(500);
      while(distance < 50)      
      {
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(inPin, HIGH);
        distance = (duration/2)/29.1;
      }
    }
  }
}

void stopcar()
{
  digitalWrite(fwd,LOW);
  digitalWrite(back, LOW);
}

void drive()
{
  analogWrite(fwd, speedo);
  analogWrite(back, LOW);
}

void driveturn()
{
  analogWrite(fwd, speedoturn);
  analogWrite(back, LOW);
}

void driveback()
{
  digitalWrite(fwd,LOW);
  digitalWrite(back,speedoback);
}

int checkleft()
{
  servoEye.write(10);
  delay(500);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(inPin, HIGH);
  distance = (duration/2)/29.1;    
  servoEye.write(90);
  return distance;
//  if(distance > 50)
//  {
//    digitalWrite(trigPin, HIGH);
//    delayMicroseconds(1000);
//    digitalWrite(trigPin, LOW);
//    duration = pulseIn(inPin, HIGH);
//    distance = (duration/2)/29.1;  
//    if(distance > 50)
//    {
//      servoEye.write(90);
//      return true;
//    }
//  }
//  servoEye.write(90);
//  return false;
}
int checkright()
{
  servoEye.write(170);
  delay(500);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(inPin, HIGH);
  distance = (duration/2)/29.1;   
  servoEye.write(90);
  return distance;
//  if(distance > 50)
//  {
//    digitalWrite(trigPin, HIGH);
//    delayMicroseconds(1000);
//    digitalWrite(trigPin, LOW);
//    duration = pulseIn(inPin, HIGH);
//    distance = (duration/2)/29.1;  
//    if(distance > 50)
//    {
//      servoEye.write(90);
//      return true;
//    }
//  }
//  servoEye.write(90);
//  return false;
}

//right = 1
//left = 2
int check()
{
  int rightdist = checkright();
  int leftdist = checkleft();
  if(leftdist > 50)
  {
    if(rightdist > 50)
    {
      if(rightdist > leftdist)
      {
        return 1;            
      }
      else
      {
        return 2;
      }
    }
    else
    {
      return 2;   
    }
  }
  else
  {
    if(rightdist > 50)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
}

bool goright()
{
  int i = 0;
  servoMain.write(75);
  driveback();
  delay(700);
  stopcar();
  delay(100);
  servoMain.write(105);      
  driveturn();
  while(i<10)
  {
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(inPin, HIGH);
    distance = (duration/2)/29.1;
    if(distance < 40)
    {
      delay(100);
      stopcar();
      return true;
    }
    delay(100);
    i++;
  }
  stopcar();
  delay(100);
  servoMain.write(straight); 
  return false;
}

bool goleft()
{
  int i = 0;
  servoMain.write(105);
  driveback();
  delay(700);
  stopcar();
  delay(100);
  i=0;
  servoMain.write(75);
  driveturn();
  while(i<10)
  {
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(inPin, HIGH);
    distance = (duration/2)/29.1;
    if(distance < 40)
    {     
      stopcar();
      delay(100);
      return true;
    }
    delay(100);
    i++;
  }
  stopcar();
  delay(100);
  servoMain.write(straight); 
  return false;
}



void setup() 
{
  pinMode(12, INPUT); //echo 1
  pinMode(13, OUTPUT); //trigger 1
  pinMode(10, INPUT); //echo 2
  pinMode(11, OUTPUT); //trigger 2
  pinMode(6, OUTPUT); //buzzer 1 +
  pinMode(7, OUTPUT); //buzzer 1 -
  Serial.begin(9600);
}

float dist1, dist2;
long dur1, dur2; 

void loop() 
{
  digitalWrite(13, LOW);
  digitalWrite(11, LOW);
  delayMicroseconds(10);
  //-------------------
  digitalWrite(13, HIGH);
  delayMicroseconds(10);
  digitalWrite(13, LOW);

  dur1 = pulseIn(12, HIGH);
  dist1 = dur1*0.034/2;
  //--------------------
  digitalWrite(11, HIGH);
  delayMicroseconds(10);
  digitalWrite(11, LOW);

  dur2 = pulseIn(10, HIGH);
  dist2 = dur2*0.034/2;
  /*--------------------
   * Distance is measured
   * Main function executed now
   -------------------*/
  int a=0, b=0, c=0, d=0, x=0;
  //store conditions in a, b, c, d and finally make condition numbered in x; 
  if ((dist1>=150)or(dist2>=150))
  {
    a = 1;
  }
  if (((dist1>=100)and(dist1<150))or((dist2>=100)and(dist2<150)))
  {
    b = 1;
  }
  if (((dist1>=75)and(dist1<100))or((dist2>=75)and(dist2<100)))
  {
    c = 1;
  }
  if (((dist1<75)and(dist1>=15))or((dist2<75)and(dist2>=15)))
  {
    d = 1;
  }
  //Now, number x.
  if(d==1)
  {
    x=1; //close level 1
  }
  if((c==1)and(d!=1))
  {
    x=2; //close level 2
  }
  if((b==1)and(c!=1)and(d!=1))
  {
    x = 3; //close level 3
  }
  if((a==1)and(b!=1)and(c!=1)and(d!=1))
  {
    x = 4; //close level 4
  }
  
  if(x==4)
  {
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
    delay(500);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    delay(1000);
  }
  else if(x==3)
  {
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
    delay(500);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    delay(500);  
  }
  else if(x==2)
  {
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
    delay(250);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    delay(250);   
  }
  else if(x==1) //15 is kept for rain problem, if there's rain, distance would be less than 15, otherwise for less than 15 vehicle will collide anyway
  {
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
  }
  else
  {  
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
  }
  //Print to serial monitor now
  Serial.print("Distance 1: ");
  Serial.println(dist1);
  Serial.print("Distance 2: ");
  Serial.println(dist2);
}  

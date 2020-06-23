#include<SD.h>
#include<SPI.h>

File Speed;

void setup() 
{
  pinMode(10, OUTPUT);//SD CARD
  pinMode(9, INPUT); //echo 1
  pinMode(8, OUTPUT); //trigger 1
  pinMode(7, INPUT);//echo 2
  pinMode(6, OUTPUT);//trigger 2
  pinMode(3, OUTPUT);//LED
  Serial.begin(9600);
  delay(3000);
}

int dist1, dist2, dur1, dur2, t = 1;
long gap;

void loop() 
{
  digitalWrite(8, LOW);
  digitalWrite(6, LOW);
  delayMicroseconds(10);
  //-------------------
  digitalWrite(8, HIGH);
  delayMicroseconds(10);
  digitalWrite(8, LOW);

  dur1 = pulseIn(9, HIGH);
  dist1 = dur1*0.034/2;
  //-------------------
  digitalWrite(6, HIGH);
  delayMicroseconds(10);
  digitalWrite(6, LOW);

  dur2 = pulseIn(7, HIGH);
  dist2 = dur2*0.034/2;  
  /*-------------------
   * We have measured the distances from individual sensors now
   */
  Serial.print(int(t));
  Serial.print(",");
  Serial.print(int(dist1));
  Serial.print(",");
  Serial.print(int(dist2)); 
  Serial.print(",");
  Serial.println(gap);
  if(SD.begin())
  {
    Serial.println("SD card is ready to use");
  }
  Speed = SD.open("Speed.txt", FILE_WRITE);
  if(Speed)
  {
    Speed.print(int(t));
    Speed.print(",");
    Speed.print(int(dist1));
    Speed.print(",");
    Speed.print(int(dist2));
    Speed.print(",");
    Speed.println(int(gap));
    Speed.close(); 
  }
  else
  {
    Serial.println("Error opening Speed.txt");
  }
  t++;
  if(abs(dist1-dist2)>=50) //change error value 50 acc to background 
  {
    digitalWrite(3, HIGH);
    gap++;
  }
  else
  {
    digitalWrite(3, LOW);
    gap = 0;
  }
  delay(100);
  /*--------------------------------------------------------------------------------------------------------
   * Now we will have gap which will show when vehicle ENTERS first sensor's and second sensor's vicinity.
   * Let distance between sensors be d, and time gap obtained is first largest value of 'gap'.
   * The speed of object will be: v = d/gap; 
   */
}

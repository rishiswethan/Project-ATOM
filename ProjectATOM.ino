#include <SoftwareSerial.h>
#define rxPin 9
#define txPin 13

SoftwareSerial BTserial(rxPin, txPin); // RX | TX

char ch;//,chf,chb;
int proxEn=1,readFlag=1,dist,irEn=1,trigPin=A2,trigPin2=8,i,echoPin=A5,echoPin2=A3,beep=A4,irPin=12,irProxPin=A1,irEncoderPin=A0,irProxStatus=0,pwmL=10,pwmR=11,distance=200,duration,distance2,duration2,beepEn=0,irStatus,flag=1,flagstop=0,flagEn=0,numRot=0,sr,cl=0,cr=0,left=0,right=0,chf=0,chb=0,Speed=0;
long nr=0,cnt=0,test=0;

void Right()
{
  PORTD = B10000100;
  flagEn=0;
  digitalWrite(pwmL,HIGH);
  digitalWrite(pwmR,HIGH);
  //SetSpeed();
}
void Left()
{
  PORTD = B00011000;
  //PORTD = B10000100;
  flagEn=0;
  digitalWrite(pwmL,HIGH);
  digitalWrite(pwmR,HIGH);
  //SetSpeed();
}
void Front()
{
  PORTD = B00010100;
  left=Speed-cl;
  right=Speed-cr; 
  flagEn=1;
  flagstop=0;
  SetSpeed();
}
void Back()
{
  PORTD = B10001000;
  //PORTD = B10001000;
  left=Speed-cl;
  right=Speed-cr;
  flagEn=0; 
  SetSpeed();
}
void Stop()
{
  PORTD = B00000000;
  flagEn=0; 
  SetSpeed();
}
void SetSpeed()
{
  analogWrite(pwmL,left);
  analogWrite(pwmR,right);
}

void setup() 
{
  //Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission 9600
  DDRD = B11111100;//7-0
  chf='n';
  chb='n';
  char c='h';
  left=255;
  right=255;
  //SetSpeed();
  BTserial.begin(9600);//9600
  //Serial.begin(38400);
  BTserial.println(" Hello#");
  //BTserial.write(c);
  //Serial.println("Hello");

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(beep,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT); 
  pinMode(A3,INPUT); 
  pinMode(pwmL,OUTPUT);
  pinMode(pwmR,OUTPUT);

  //enable ir only if no sunlight
  if(analogRead(A1)>100)
  {
    irEn=0;
    analogWrite(beep,170);
    delay(100);
    analogWrite(beep,LOW);
    delay(100);
    analogWrite(beep,170);
    delay(100);
    analogWrite(beep,LOW);
    delay(100);
    analogWrite(beep,170);
    delay(100);
    analogWrite(beep,LOW);
    delay(100);
    analogWrite(beep,170);
    delay(100);
    analogWrite(beep,LOW);
    delay(100);
    analogWrite(beep,170);
    delay(100);
    analogWrite(beep,LOW);
  }
  else
  {
    irEn=1;
    analogWrite(beep,170);
    delay(100);
    analogWrite(beep,LOW);
    delay(100);
    analogWrite(beep,170);
    delay(100);
    analogWrite(beep,LOW);
  }
  dist=25;
}


void loop()
{
  //BTserial.println(distance);
  //delay(1000);

  if(readFlag==1)
  if(BTserial.available()>0)  // Send data only when you receive data:
  {
     String data=BTserial.readString();
     
     //BTserial.flush();
     //delay(1000);
     //char c[]="hello#";//test
     //BTserial.write(c);
     String s="";
     digitalWrite(beep,HIGH);
     delay(100);
     digitalWrite(beep,LOW);
     delay(100);
     digitalWrite(beep,HIGH);
     delay(100);
     digitalWrite(beep,LOW);
     //for(i=0;i<data.length()-2;i++)
     //{
     // s=s+String(data.charAt(i));
     //}
     
     
     //BTserial.print(" -r- "+data+"#");
     
     
     //BTserial.print(String(data+"#"));
     //BTserial.write('c');
     //BTserial.write(data);
     //BTserial.println('c');
     //BTserial.println(data);
     //BTserial.write(String(data));
     //delay(20);
     ch=data.charAt(0);
     if(ch=='f')
     {
       cnt=0;
       Front();
     }
     else if(ch=='b')
     {
       Back();
     }
     else if(ch=='r')
     {
       Right();
     }
     else if(ch=='l')
     {
       Left();
     }
     else if(ch=='s')
     {
       Stop();
     }
     else if(ch=='m')
     {
       cnt=0;
       if(data.charAt(1)=='l')
       {
        String time=String(data.charAt(2))+String(data.charAt(3))+String(data.charAt(4))+String(data.charAt(5))+String(data.charAt(6));
        Left();
        delay(time.toInt());
        if(time.toInt()>700)
        {
          Right();
          delay(50);
        }
        Stop();
       }
       else if(data.charAt(1)=='r')
       {
        String time=String(data.charAt(2))+String(data.charAt(3))+String(data.charAt(4))+String(data.charAt(5))+String(data.charAt(6));
        Right();
        delay(time.toInt());
        if(time.toInt()>700)
        {
          Left();
          delay(50);
        }
        Stop();
       }
       else if(data.charAt(1)=='f')
       {
        numRot=(String(data.charAt(2))+String(data.charAt(3))+String(data.charAt(4))).toInt();
        cnt=0;
        flagstop=0;
        flagEn=1;
        Front();
        delay(10);
        chf=1;
       }
        else if(data.charAt(1)=='b')
       {
        numRot=(String(data.charAt(2))+String(data.charAt(3))+String(data.charAt(4))).toInt();
        cnt=0;
        flagstop=0;
        flagEn=1;
        Back();
        delay(10);
        chf=1;
       }
     }
     else if(ch=='c')
     {
       cl=(String(data.charAt(1))+String(data.charAt(2))+String(data.charAt(3))).toInt();
       cr=(String(data.charAt(4))+String(data.charAt(5))+String(data.charAt(6))).toInt();
       Speed=(String(data.charAt(7))+String(data.charAt(8))+String(data.charAt(9))).toInt();
     }
     else if(ch=='e')
     {
       irEn=String(data.charAt(1)).toInt();
       proxEn=String(data.charAt(2)).toInt();
     }
     //Serial.println("d:"+String(distance)+"ir: "+String(cnt));
    }
    if(chf==1)
     {
       if(cnt==numRot)
       {
        //char ch='r';
        Stop();
        delay(500);
        BTserial.print("  r#");
        flagEn=0;
        chf=0;
       }
     }

    //analogWrite(pwmL,test%255);
    //analogWrite(pwmR,test%255);
    //PORTD = B00010100;
    //test++;
    //delay(100);
    
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);

    duration = pulseIn(echoPin,HIGH,2500);
    distance= duration*0.034/2;

    digitalWrite(trigPin2,LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin2,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2,LOW);
    
    duration2 = pulseIn(echoPin2,HIGH,2500);
    //duration2 = duration2-duration;
    distance2 = (duration2*0.034/2);

    if(proxEn==0)
    {
      distance=0;
      distance2=0;
    }

    irStatus=analogRead(irEncoderPin);
    irProxStatus= analogRead(irProxPin);//+analogRead(A3);
    //irProxStatus=0;
    //Serial.println(String(distance2)+","+String(duration)+", "+String(irProxStatus)+","+String(HIGH));

    if(irStatus>100)
      irStatus=1;
    else
      irStatus=0;
      
    if(irProxStatus>100&&irEn==1)
      irProxStatus=1;
    else
      irProxStatus=0;
    
    if((distance<dist && distance>2 && proxEn==1)||irProxStatus>=1||(distance2<dist && distance2>2 && proxEn==1))
    {
      analogWrite(beep,170);
      beepEn=1;
    }
    else if(beepEn==1)
    {
      analogWrite(beep,LOW);
      beepEn=0;
    }
    
    
    if(irStatus==flag)
    {
      cnt++;
      flag=(flag+1)%2;          
    }
    //flagstop=0;
    if(((distance<dist && distance>2 && proxEn==1)||(distance2<dist && distance2>2 && proxEn==1)||(irProxStatus>=1)) && flagstop==0 && flagEn==1)
    {
      BTserial.print(String("  o"+String(cnt)+"#"));
      if(chf==1)
      {
        chf=0;
        chb=1;
        numRot=cnt;
        cnt=0;
        readFlag=0;
        Back();
        if(cnt<2)
        {
          delay(500);
          //numRot=0;
        }
      }
      else
      {
        chf=0;
        Back();
        delay(500);
        Stop();
      }
      flagstop=1;
    }
    /*else if(irProxStatus>=1 && flagstop==0 && flagEn==1)
    {
      if(chf==1)
      {
        BTserial.print(String("  o1#"));
        chf=0;
        chb=0;
        numRot=cnt;
        cnt=0;
        readFlag=0;
        Back();
        if(cnt<2)
          delay(500);
          BTserial.print("  a#");
      }
      else
      {
        chf=0;
        Back();
        delay(500);
        Stop();
        BTserial.print(String("  o1#"));
        flagstop=1;
      }
    }*/
    if(chb==1)
    {
      if(cnt==numRot)
      {
        Front();
        delay(100);
        Stop();
        delay(1000);
        BTserial.print("  a#");
        readFlag=1;
        chb=0;
      }
    }
    
    /*if(flagEn==1 && (!(distance<23 && distance>0)))
    {
      BTserial.print(String("g#"));//Free to go
      flagEn=0;
    }*/
    delay(10);
}

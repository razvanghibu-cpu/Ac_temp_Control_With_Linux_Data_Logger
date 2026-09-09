
#include <dht.h>
#include <Servo.h>
dht DHT;
Servo myservo;
int pin=3;
int chk,temp;
int fk=0;
bool on=false;

void press()
{
    for(int i=90;i<=115;i++){
      myservo.write(i);
      delay(20);

    }
    delay(300);
    for(int i=115;i>=90;i--){
      myservo.write(i);
      delay(20);

    }

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(5);
  

}

void loop() {
  chk=DHT.read11(pin);
  if(chk==0){
  temp=DHT.temperature;
  if(temp<25 && temp>22 && fk==1)
  {
    press();
    on=true;
    fk=0;
  }
  Serial.print("Code:");
  Serial.print(chk);
  Serial.print(",");
  Serial.print(temp);
  Serial.print("°C");
  Serial.print(",AC:");

  Serial.println(on ? "ON" : "OFF");
  
  if(temp>25 && on==false)
  {
    press();
    on=true;
  }
  if(temp<22 && on==true)
  {
    press();
    on=false;
  }
  }
  else
  {
    Serial.print("Error,");
    Serial.println(chk);
    if(on == true){
    press();
    on=false;
    fk=1;
    }


  }

  

  delay(120000);
  


}


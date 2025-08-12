#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 39
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);


int connectionid;
int val = 50;
int ldr;
int t,h;


void setup() {
  pinMode(12,OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial3.begin(115200);
  dht.begin();
  Serial.println("Serial Monitor Setup.....");
 // sendToESP("AT+RST", 2000);
 // sendToESP("AT+CWMODE=1", 1000);
 //sendToESP("AT+CWJAP=\"GSP-STAFF\",\"55r@G5b#\"", 5000);
  sendToESP("AT+CIFSR",5000);
  sendToESP("AT+CIPMUX=1", 5000);
  sendToESP("AT+CIPSERVER=1,80",2000);
  Serial.println("ESP8266 ready.Open IP shown");

}

void loop() {



  if(Serial3.available()){
    if(Serial3.find("+IPD,")){
      delay(300);



      connectionid=Serial3.read()-48;
      String webpage = "<html><body><h1>Hello GSP IoT Class</h1><h2>Final Number=";
      String add = String(number());
      String add1 ="<h2>LDR VALUE =";
      String add3 = String(ldrval());
      String temp1 = "<h2>Temperature =";
      String temp = String(dht1())+"&deg;C";
 
      String humd1 = "<h2>Humidity =";
      String humd = String(dht2())+"%";

      String refresh= "<meta http-equiv=\"refresh\"content=\"8\"></h2></h2></h2></h2></h2></body/</html>";
      webpage+=add+add1+add3+temp1+temp+humd1+humd+refresh;
      espsend(webpage);
      String closecommand="AT+CIPCLOSE=";
      closecommand+=connectionid;
      sendToESP(closecommand,300);
    }
  }

  if (ldr<=300){
  digitalWrite(12,HIGH);
  delay(2000);
}
else{
  digitalWrite(12,LOW);

}
}

int number(){
  val=val+5;
  return(val);
}

void espsend(String d){
  String cipsend="AT+CIPSEND=";
  cipsend+=connectionid;
  cipsend+=",";
  cipsend+=d.length();
  sendToESP(cipsend,1000);
  sendToESP(d,1000);
}
void sendToESP(String command, int delayTime)
{
  Serial3.println(command);
  delay(delayTime);
  while(Serial3.available())
  {
    Serial.write(Serial3.read()); 
  }
}


int ldrval(){
  ldr = analogRead(A4);
  return(ldr);
}

int dht1(){
  t = dht.readTemperature();
  return(t);
}
int dht2(){
  h = dht.readHumidity();
  return(h);
}

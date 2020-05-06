#include<ESP8266WiFi.h>
#include<SoftwareSerial.h>
#include<ThingSpeak.h>
char ssid[] = "Anurag";                            //Your hotspot ssid and pass
char pass[] = "";
WiFiClient client;
long channelId = 996887;
const char* writeapi = "B7UYNQSZLMX2PYHA";        //Write api key in thingspeak
const char* readapi = "5YT2UOPGOIXAI5BL";
char ip[] = "184.106.153.149";               //Ip address of thingspeak srever
//float h, t;
byte i = 0;
int temp, humi, gar, mg, fa, intru, hometemp, gardlight;
String  str;
int temperature, Humidity, Intruder, Garage, Gate, HTemp, Garli, firealarm;
//  SoftwareSerial s(16, 5);


void writething()
{
  while (Serial.available() > 0)                   // Don't read unless
  {
    Serial.readStringUntil('\n');
    gar = Serial.readStringUntil('\n').toInt();
    Serial.println(gar);
    mg = Serial.readStringUntil('\n').toInt();
    Serial.println(mg);
    gardlight = Serial.readStringUntil('\n').toInt();
    Serial.println(gardlight);
    fa = Serial.readStringUntil('\n').toInt();
    Serial.println(fa);
    intru = Serial.readStringUntil('\n').toInt();
    Serial.println(intru);
    humi = Serial.readStringUntil('\n').toInt();
    Serial.println(humi);
    temp = Serial.readStringUntil('\n').toInt();
    Serial.println(temp);
    hometemp = Serial.readStringUntil('\n').toInt();
    Serial.println(hometemp);

    ThingSpeak.setField(1, gar);
    ThingSpeak.setField(2, mg);
    ThingSpeak.setField(3, gardlight);
    ThingSpeak.setField(4, fa);
    ThingSpeak.setField(5, intru);
    ThingSpeak.setField(6, humi);
    ThingSpeak.setField(7, temp);
    ThingSpeak.setField(8, hometemp);
    ThingSpeak.writeFields(channelId, writeapi);
    break;
  }
}
void readthing()
{
  if (client.connect(ip, 80))
  {
    temperature = ThingSpeak.readIntField(channelId, 7, readapi);
    Humidity = ThingSpeak.readIntField(channelId, 6, readapi);
    Intruder = ThingSpeak.readIntField(channelId, 5, readapi);
    Garage = ThingSpeak.readIntField(channelId, 1, readapi);
    Gate = ThingSpeak.readIntField(channelId, 2, readapi);
    HTemp = ThingSpeak.readIntField(channelId, 8, readapi);
    Garli = ThingSpeak.readIntField(channelId, 3, readapi);
    firealarm = ThingSpeak.readIntField(channelId, 4, readapi);
    int statusCode = ThingSpeak.getLastReadStatus();
    if (statusCode == 200) {
      Serial.println("read:" + String(Garage));
      String str = String(Garage);
      char* cString = (char*) malloc(sizeof(char) * (str.length() + 1));
      str.toCharArray(cString, str.length() + 1);
      Serial.write(cString);
    }
    else
      Serial.println("No data read");
  }
}
void setup() {
  Serial.begin(9600);
  //s.begin(9600);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Wifi connected");
  ThingSpeak.begin(client);
  while (!Serial)
    ;
}

void loop() {
  writething();
  delay(15000);
  readthing();
  delay(1000);

}

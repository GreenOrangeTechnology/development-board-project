#include <dht11.h>
dht11 DHT11;
#define DHT11PIN 2
void setup(){
  Serial.begin(9600);
}

void loop(){
  Serial.println("/n");
  int chk = DHT11.read(DHT11PIN);
   Serial.print("Read sensor: ");
  switch (chk)
  {
    case DHTLIB_OK: 
                Serial.println("OK"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.println("Checksum error"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.println("Time out error"); 
                break;
    default: 
                Serial.println("Unknown error"); 
                break;
  }

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (oC): ");
  Serial.println((float)DHT11.temperature, 2);
 delay(2000);//发送有点频繁,改为30秒或1分钟发送一次并保存到数据库
}

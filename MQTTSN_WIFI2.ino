#define NETWORK_WIFI
#define ARDUINO 100

#include <SPI.h>
#include <Payload.h>
#include <MqttsnClient.h>
#include <TaskManager.h>
#include <Timer.h>
#include <Wire.h>
#include <String.h>
#include <kSHT2x.h>

using namespace std;
using namespace tomyAsyncClient;
extern MqttsnClient* theClient;

int idx_l = 60;
int idx_h = 80;
char* feel;
/*============================================
 *
 *      MQTT-SN Client Application
 *
 *===========================================*/

#ifdef NETWORK_WIFI
WIFI_APP_CONFIG = {
    {
        "ArduinoEther",
        {225,1,1,1},         // Multicast group IP
        1883,                // Multicast group Port
        {10,10,0,102},       // Local IP for Arduino without DHCP server.
        12001,               // Local PortNo
        "Testbed-0",         // SSID
        "Testbed-0"          // PASSWORD
    },
    {
        300,            //KeepAlive
        true,           //Clean session
        false,          //EndDevice
        "willTopic",       //WillTopic   or 0   DO NOT USE NULL STRING "" !
        "willMessage"      //WillMessage or 0   DO NOT USE NULL STRING "" !
    }
};
#endif

/*------------------------------------------------------
 *             Create Topic
 *------------------------------------------------------*/
const char* topic1 = "sensor1/temp";
const char* topic2 = "sensor1/humd";
const char* topic3 = "sensor1/feel";
const char* topic4 = "human/feeling";
/*------------------------------------------------------
 *             Tasks invoked by Timer
 *------------------------------------------------------*/


void task1(void){
  Payload* pl1 = new Payload(100);
  char buff1[50];
  int t = SHT2x.GetTemperature();
  Serial.println("measure temperature");
  sprintf(buff1, "{\"sts\":{\"temp\": %4d, \"Units\":\"Degree C\"}}", t);
  pl1->set_raw(buff1);
  PUBLISH(topic1, pl1, 2);
}

void task2(void){
  Payload* pl2 = new Payload(100);
  char buff2[100];
  int h = SHT2x.GetHumidity();
  Serial.println("measure humidity");
  sprintf(buff2, "{\"sts\":{\"humd\": %4d, \"Units\":\"\%RH\"}}", h);
  pl2->set_raw(buff2);
  PUBLISH(topic2, pl2, 2);
}

void task3(void){
  Payload* pl3 = new Payload(100);
  char buff3[100];
  int t = SHT2x.GetTemperature();
  int h = SHT2x.GetHumidity();
  int disc = 0.81 * t + 0.01 * h * (0.99 * t - 14.3) + 46.3;

  if(disc < idx_l) {
    feel = "cold?";
    sprintf(buff3, "{\"sts\":{\"feel\": \"cold?\"}}");
    pl3->set_raw(buff3);
    PUBLISH(topic3, pl3, 2);
  } else if(disc > idx_h) {
    feel = "so warm?";
    sprintf(buff3, "{\"sts\":{\"feel\": \"so warm?\"}}", feel);
    pl3->set_raw(buff3);
    PUBLISH(topic3, pl3, 2);
  }
}

/*---------------  List of task invoked by Timer ------------*/

TASK_LIST = {
  {task1, 10},
  {task2, 10},
  {task3, 10},
  END_OF_TASK_LIST
};


/*------------------------------------------------------
 *       Tasks invoked by SUBSCRIBE
 *------------------------------------------------------*/

int on_publish(tomyAsyncClient::Payload* payload){
  Payload* pl4 = new Payload(100);
  uint16_t len1, len2;
  char buff[100];
  char* cmd;
  cmd = (char*)payload->get_str(0, &len1);

  //command analysis
  if((strstr(cmd, "cmd") != NULL)) {
     if((strstr(cmd, "no") != NULL || strstr(cmd, "No") != NULL || strstr(cmd, "NO") != NULL) && strstr(feel, "cold") != NULL) {
       idx_l = idx_l + 2;
       feel = "";
       sprintf(buff, "{\"res\":{\"setidx_l\": %4d}}", idx_l);
       pl4->set_raw(buff);
       PUBLISH(topic3, pl4, 2);
     } else if((strstr(cmd, "no") != NULL || strstr(cmd, "No") != NULL || strstr(cmd, "NO") != NULL) && strstr(feel, "warm") != NULL) {
       idx_h = idx_h - 2;
       feel = "";
       sprintf(buff, "{\"res\":{\"setidx_h\": %4d}}", idx_h);
       pl4->set_raw(buff);
       PUBLISH(topic3, pl4, 2);
     }
  }
  return 0;
}


/*------------ Link Callback to Topic -------------*/

SUBSCRIBE_LIST = {//SUB(topic, callback, QoS=0or1),
                  SUB(topic4, on_publish, 1),
                  END_OF_SUBSCRIBE_LIST
                 };

/*------------------------------------------------------
 *            Tasks invoked by INT0 interruption
 *------------------------------------------------------*/
void interruptCallback(void){
}


/*------------------------------------------------------
 *            setup() function
 *------------------------------------------------------*/
 void setup(void){
    Serial.begin(115200);
    Wire.begin();
 }

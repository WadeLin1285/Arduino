#include <SPI.h>
#include <Ethernet.h>

// 指定網路卡 MAC 卡號
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// 指定 IP 位址
byte ip[] = { 192, 168, 1, 200 };

// 初始化 Ethernet client library
EthernetClient client;

void setup() {
  // 初始化序列埠
  Serial.begin(9600);
  // 啟用 Ethernet 連線，預設會以 DHCP 取得 IP 位址
  Ethernet.begin(mac, ip);
  
  Serial.print("IP 位址：");
  Serial.println(Ethernet.localIP());
}

void loop() {

}

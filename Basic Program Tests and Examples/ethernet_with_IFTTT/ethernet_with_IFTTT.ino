#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF };  // REPLACE WITH REAL ADDR
byte ip[]  = {192,168,2,105};

byte server[] = { 64, 233, 187, 99 }; // Google
//char server[] = "maker.ifttt.com";

char MakerIFTTT_Key[] = "bJa2fXsJqd4GvtJBF-2agaj5wjoTpLTUJnB0x7S-Zyq";
char MakerIFTTT_Event[] = "Alert";

EthernetClient client;
// IFTTT Maker channel setting
const char* host = "maker.ifttt.com";
const char* url = "/trigger/Alert/with/key/bJa2fXsJqd4GvtJBF-2agaj5wjoTpLTUJnB0x7S-Zyq";
const int httpPort = 80;

void printMAC();
void printIP();
char *append_str(char *here, char *s);
char *append_ul(char *here, unsigned long u);
void setup() {
  Serial.begin(9600);
  printMAC();
  printIP();
  
  delay(5000);
  /*
  // this sets up the network connection, including IP addr via DHCP
  if (Ethernet.begin(mac) == 1) {
    Serial.println("MAC connected");
  }*/
  /*
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  }
  else 
    Serial.println("Correct MAC and IP address...");
  */
  //delay(1000);
  Ethernet.begin(mac);
  Serial.println(Ethernet.localIP());
  Serial.println("connecting...");
  int result = client.connect(server, 80);
  Serial.println(result);
  /*
  //if (client.connect("maker.ifttt.com", 80)) { //maker.ifttt.com
  if (!client.connect(host, httpPort)) {
    Serial.println("Sever connection failed");  // Boo!!!
    return; 
  }
  else {
    Serial.println("Server connected");

    String json = "{ \"value1\" : \"1\", \"value2\" : \"2\", \"value3\" : \"3\" }";
  
    // This will send the request to the server
    client.println(String("POST ")  + url + " HTTP/1.1");
    client.println(String("Host: ") + host);
    client.println("Cache-Control: no-cache");
    client.println("Content-Type: application/JSON");
    client.print("Content-Length: ");
    client.println(json.length());
    client.println();
    client.println(json);

    /*
    // construct the POST request
    char post_rqst[256];    // hand-calculated to be big enough

    char *p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, MakerIFTTT_Key);/*
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");
  
    // we need to remember where the content length will go, which is:
    char *content_length_here = p;

    // it's always two digits, so reserve space for them (the NN)
    p = append_str(p, "NN\r\n");

    // end of headers
    p = append_str(p, "\r\n");

    // construct the JSON; remember where we started so we will know len
    char *json_start = p;

    // As described - this example reports a pin, uptime, and "hello world"
    p = append_str(p, "{\"value1\":\"");
    p = append_ul(p, 0);
    p = append_str(p, "\",\"value2\":\"");
    p = append_ul(p, millis());
    p = append_str(p, "\",\"value3\":\"");
    p = append_str(p, "hello, world!");
    p = append_str(p, "\"}");

    // go back and fill in the JSON length
    // we just know this is at most 2 digits (and need to fill in both)
    int i = strlen(json_start);
    content_length_here[0] = '0' + (i/10);
    content_length_here[1] = '0' + (i%10);

    // finally we are ready to send the POST to the server!
    //client.print(post_rqst);
    client.stop();
    Serial.println("Completed !");
  }*/
}

void loop() {

}

void printMAC(){
  Serial.print("Conncect to MAC address: ");
  Serial.print(mac[0]);
  Serial.print(", ");
  Serial.print(mac[1]);
  Serial.print(", ");
  Serial.print(mac[2]);
  Serial.print(", ");
  Serial.print(mac[3]);
  Serial.print(", ");
  Serial.print(mac[4]);
  Serial.print(", ");
  Serial.println(mac[5]);
}
void printIP(){
  Serial.print("Conncect to IP address: ");
  Serial.print(ip[0]);
  Serial.print(", ");
  Serial.print(ip[1]);
  Serial.print(", ");
  Serial.print(ip[2]);
  Serial.print(", ");
  Serial.println(ip[3]);
}
char *append_str(char *here, char *s) {
    while (*here++ = *s++)
  ;
    return here-1;
}

char *append_ul(char *here, unsigned long u) {
    char buf[20];       // we "just know" this is big enough

    return append_str(here, ultoa(u, buf, 10));
}

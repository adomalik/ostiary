/*                                                                               
*           MMMMMMMMMMM                                                          
*       .MMMMMMMMMMMMMMM                                                        
*       MMMMMMMM.  .MMMMMMM                                                      
*      MMMMMM         MMMMMM                                                     
*     MMMMM..          .MMMM                                                     
*     MMMMM             MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM       
*     MMMMM             MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM       
*     MMMMM             MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM       
*     MMMMM             MMMM   M                                MMMMMMMMM        
*      MMMMMM         MMMMMM MM M MMMM M  MM  M MMMMMM          MMMMMMMMM        
*       MMMMMMMM.. MMMMMMMM  .MMM  MM  M MMM. MMM..MM           MMM  MMMM        
*        MMMMMMMMMMMMMMMM    MMMM  MM  M MMMM M MM MM                MMMM        
*           MMMMMMMMMMM                                                          
*
*
*      Ostiary Access Control
*  
*      04/24/2015 v0.02
*      Andrew Domalik
*
*    This program uses an Arduino Mega to drive a circuit to open a door strike 
*`   depending on the input from an NFC tag. The tag is checked against a MySQL 
*    databse. If it exists the Arduino will produce a HIGH output on pin 5, 
*    energizing the relay and opening the door strike for 10 seconds.
*
*/

//-------- INITAL SETUP-----------
#include <Wire.h>           
#include <Ethernet.h>     
#include <SPI.h>
#include "sha1.h"
#include "mysql.h"
#include <SPI.h>
#include <Ethernet.h>
#include <stdlib.h>

#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <avr/pgmspace.h> 

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

//IP and MAC address
byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x3C, 0xC6};
IPAddress ip(192,168,0,201);
IPAddress server_ip(192,168,0,200);

//MySQL connection
Connector my_conn;
char user[] = "root";
char password[] = "password"; 


//---------- ACCESS CONTROL DEFINITIONS -------------
#define DOORDELAY 10000                
#define DOORPIN1 relayPins[0]           // Define the trigger pin for the door hardware
#define REDPIN relayPins[1]             // Define the pin used to turn the LED to RED
#define GREENPIN relayPins[2]           // Define the pin used to turn the LED to GREEN

const byte relayPins[]= {6,7,8};            // Output pins
EthernetClient client;

void setup(){          
  Ethernet.begin(mac, ip);      // Initialize Ethernet device 
  Wire.begin();                 // start Wire library as I2C-Bus Master
  
  //Initialize output relays
  for(byte i=0; i<4; i++){        
    pinMode(relayPins[i], OUTPUT);                                                      
    digitalWrite(relayPins[i], LOW);                  // Sets the relay outputs to LOW (relays off)
  }

  pinMode(relayPins[1], OUTPUT);
  digitalWrite(relayPins[1],HIGH);
  
  Serial.begin(57600);         // Set up Serial output 
  nfc.begin();
   
  if (my_conn.mysql_connect(server_ip, 3306, user, password)) //initiate MySQL connection
  {
    delay(100);
  }
  else
  {
    Serial.println("Connection failed");
  }
   
} 

void loop()
{
  String readString = String(100); //string for pulling data 
  char c = 0;
  
    Serial.println("\nScan a NFC tag\n");
    
    if (nfc.tagPresent())
    {
        NfcTag tag = nfc.read();
        String readTag = tag.getUidString(); 
        char tagUid[64];
        readTag.toCharArray(tagUid, readTag.length());
        Serial.println(readTag);


        //HTTP Request and Response for Querying DB
        if (client.connect(server_ip,80)){
          
          
          char query[60];
          sprintf(query,"GET /ostiary/check.php?key=%s HTTP/1.1", tagUid);
          
          client.println(query);
          Serial.println(query);
          client.println("Host: localhost"); 
          client.println("Connection: close");
          client.println();
          Serial.println("Querying Database");
         Serial.println(client.available());
          
          while (client.available() || client.connected())
          {
            c = client.read();
            Serial.print(c);  // to see the value 
        
        //Look for Pipe character 
        if(c == '|'){
          c = client.read ();
          if (c == '1')
          {
            accessGranted();//Run door open sequence
            insertLog(tagUid); //Create log entry
          }
          else if (c == '0')
          {
            Serial.println("No such user");
            }
          }
         }
         client.stop();
      }
    delay(1000);

  }
}
  

//Log Entry into Database
void insertLog(char *tagId)  {
    
  char cardId[8];
  sprintf(cardId,"%s",tagId); 
  Serial.println(cardId);
  char logQuery[110];
  sprintf(logQuery,"INSERT INTO mydb.log (timestamp, card_id) VALUES (CURRENT_TIMESTAMP, '%s' )", tagId);  
  Serial.println(logQuery);
  my_conn.cmd_query(logQuery);
}
  
  
//Open door for delay seconds 
void accessGranted() {          
  
  digitalWrite(DOORPIN1, HIGH);
  digitalWrite(REDPIN, LOW);
  digitalWrite(GREENPIN, HIGH);
  Serial.println("Door Unlocked");
  
  delay(DOORDELAY);
  
  digitalWrite(DOORPIN1, LOW);
  digitalWrite(REDPIN, HIGH);
  digitalWrite(GREENPIN, LOW);
  Serial.println("Door Locked");
 
  
}

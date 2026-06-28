// Includes
#include "NetworkCreds.h"
#include "Time.h"


// Libraries
#include <ESP8266WiFi.h>
#include <WiFiManager.h>


// DEFINES
#define WIFI_TASK_RATE  30000 // 30 Seconds

// Typedefs
typedef struct
{
    int NodeID;
    int SoilMoistureReading;
} PacketStruct;


// Static Variables
static WiFiManager wifiManager;
static int WifiTimerIndex;
static IPAddress piPicoIP(192, 168, 1, 151); // Replace with your Raspberry Pi Pico IP address
static bool ConnectionSuccess;
static WiFiClient client;
static PacketStruct CurrentPacketData;


// Static Function Prototypes
static String BuildDataPacket(PacketStruct* PacketData);


void InitWiFi(void)
{
    // Wipe stored credentials for testing
    // wm.resetSettings();

    WiFi.mode(WIFI_STA);
    CurrentPacketData.NodeID = 0; // TODO: Implement a scheme to assign node IDs
    CurrentPacketData.SoilMoistureReading = 0;
    WifiTimerIndex = RegisterTimer();
}

void BeginWiFiConnection(void)
{
    // Connect to Wi-Fi network
    if (!wifiManager.autoConnect(ssid, password)) 
    {
        ConnectionSuccess = false;
        Serial.println("Connection failed! Connect to ");
        Serial.println(ssid);
        Serial.println(" to configure WiFi Network Connection.");
    }
    else
    {
        Serial.println("Connected to Wi-Fi network");
        ConnectionSuccess = true;
    }
}

void InitWiFiConnection(void)
{
    SetTimer(WifiTimerIndex, WIFI_TASK_RATE);
    if(ConnectionSuccess)
    {
        ConnectionSuccess = client.connect(piPicoIP, 80);
    }
}

// TODO: Address time lost bug ~150ms
void ServiceWiFiConnection(int Data)
{
    String postData;
    String PostRequest = "";

    if(IsTimerExpired(WifiTimerIndex))
    {
        if(!client.connected())
        {
            client.stop();
            InitWiFiConnection();
        }

        if(ConnectionSuccess)
        {
            // Build up data packet to send
            CurrentPacketData.SoilMoistureReading = Data;
            postData = BuildDataPacket(&CurrentPacketData);

            // Build and send the HTTP POST request
            PostRequest += "POST /post HTTP/1.1\r\n";
            PostRequest += "Host: 192.168.1.150\r\n";
            PostRequest += "Content-Type: application/x-www-form-urlencoded\r\n";
            PostRequest += "Content-Length: ";
            PostRequest += String(postData.length());
            PostRequest += "\r\n";
            PostRequest += postData;
            client.println(PostRequest);

            SetTimer(WifiTimerIndex, WIFI_TASK_RATE);
        }
    }

    // Print server response for testing
    //if(client.connected())
    //{
    //    // Check for incoming data
    //    if(client.available() > 0)
    //    {
    //        String line = client.readStringUntil('\n');
    //        Serial.println(line);
    //    }
    //}
}

static String BuildDataPacket(PacketStruct* PacketData)
{
    String Packet = "";

    Packet += "node=" + String(PacketData->NodeID);
    Packet += "&";
    Packet += "data=" + String(PacketData->SoilMoistureReading);

    return Packet;
}

bool GetConnectionStatus(void)
{
    return ConnectionSuccess;
}

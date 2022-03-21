#include <SPI.h>
#include <WiFiNINA.h>

#define WIFI_SSID "Your SSID go here"
#define WIFI_PASSWORD "Your Password go here"

char ssid[] = WIFI_SSID;
char password[] = WIFI_PASSWORD;

byte mac[6];

void setup() {
  // Setup Serial
  Serial.begin(9600);
  while (!Serial) ;
  Serial.println("Serial is ready");

  // Print MAC Address
  printMAC();  

  // Scan SSID
  for (int i = 1; i <= 3; i++) {
    Serial.print("\nScan net, cycle ");
    Serial.println(i);
    scanNet();
    delay(10000);
  }

  // Connect to preassign network
  connectNet();

  // End sketch signal
  Serial.println("End of sketch");
}

void loop() {

}

// Print MAC Address function
void printMAC() {
  WiFi.macAddress(mac);
  Serial.print("Arduino's MAC: ");
  for (int i = 5; i >= 1; i--) {
    Serial.print(mac[i], HEX);
    Serial.print(":");
  }
  Serial.println(mac[0], HEX);
}

// Scan for available network
void scanNet() {
  // Scan for network
  int numSsid = WiFi.scanNetworks();

  // If none available
  if (numSsid == -1) {
    Serial.println("Couldn't get a WiFi connection");
    while(true);
  }

  // Print list of available networks
  Serial.print("Number of available networks: ");
  Serial.println(numSsid);

  for (int i = 0; i < numSsid; i++) {
    // Index
    Serial.print(i);
    Serial.print(") ");
    // SSID
    Serial.print(WiFi.SSID(i));
    // BSSID
    byte bssid[6];
    WiFi.BSSID(i, bssid);
    Serial.print("\t\tBSSID: ");
    Serial.print(bssid[5],HEX);
    Serial.print(":");
    Serial.print(bssid[4],HEX);
    Serial.print(":");
    Serial.print(bssid[3],HEX);
    Serial.print(":");
    Serial.print(bssid[2],HEX);
    Serial.print(":");
    Serial.print(bssid[1],HEX);
    Serial.print(":");
    Serial.print(bssid[0],HEX);
    // Channel
    Serial.print("\tChannel: ");
    Serial.print(WiFi.channel(i));
    // Encryption type
    Serial.print("\tEncryption: ");
    printEncryptionType(WiFi.encryptionType(i));
  }
}

// Identify Encryption Type
void printEncryptionType(int thisType) {
  switch (thisType) {
    case ENC_TYPE_WEP:
      Serial.println("WEP");
      break;
    case ENC_TYPE_TKIP:
      Serial.println("WPA");
      break;
    case ENC_TYPE_CCMP:
      Serial.println("WPA2");
      break;
    case ENC_TYPE_NONE:
      Serial.println("None");
      break;
    case ENC_TYPE_AUTO:
      Serial.println("Auto");
      break;
    case ENC_TYPE_UNKNOWN:
    default:
      Serial.println("Unknown");
      break;
  }
}

// Connect to preassign WiFi
void connectNet() {
  Serial.println();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to "); Serial.println(ssid);
    WiFi.begin(ssid, password);
    delay(500);
  }
  Serial.print("Successfully connected to "); Serial.println(ssid);
}

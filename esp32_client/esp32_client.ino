#include "Arduino.h" 
#include "WiFi.h"
#include "Audio.h" //https://github.com/schreibfaul1/ESP32-audioI2S


// Digital I/O used
#define I2S_DOUT      14  // DIN connection
#define I2S_BCLK      27  // Bit clock
#define I2S_LRC       26  // Left Right Clock


Audio audio;
String ssid = "YOUR_SSID";
String password = "YOUR_PASSWD";

// String tts_server="http://192.168.4.100:3000/t2s?txt=";
String tts_server="https://gappu-nextjs.vercel.app/api/openai/text-to-speech/get?input=";
String text="no-matter-how-much-money-you-earn---it-is-not-yours-until-you-spend-it";
String payload = tts_server + text;


void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // byte* psdRamBuffer = (byte*)ps_malloc(200000);

  Serial.printf("Total heap: %d\n", ESP.getHeapSize());
  Serial.printf("Free heap: %d\n", ESP.getFreeHeap());
  Serial.printf("Total PSRAM: %d\n", ESP.getPsramSize());
  Serial.printf("Free PSRAM: %d\n", ESP.getFreePsram());

  Serial.println("");
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(15); // 0...21

  Serial.println(payload);
  audio.connecttohost(payload.c_str());
}

void loop()
{
  audio.loop();
}

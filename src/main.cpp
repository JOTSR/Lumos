#include <Utility.h>
#include <components/StripLed.h>
#include <components/BMP.h>
#include <components/Screen.h>
#include <components/Humidifier.h>
#include <components/Server.h>

//❌GPIO 1, 35, 34, 36, 39
// int gpios[] = {1, 2, 3, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33, 34, 35, 36, 39};

//Sound
#define SPEAK_R 32
#define SPEAK_L 33
#define MIC 25

//Buttons
#define KEY_1 12
#define KEY_2 13

//Strip LED
#define LED_PIN 4

//Modules
#define HUMIDIFIER 15
//i2c screen
//bpm280

void action1()
{
  Serial.print("Action1 not implemented\n");
}

void action2()
{
  Serial.print("Action2 not implemented\n");
}

Humidifier humidifier(HUMIDIFIER);

void setup()
{
  //----------------------------Serial
  Serial.begin(115200);
  Serial.print("\n");

  //----------------------------SPIFFS
  Serial.println(initSPIFFS() ? "SPIFFS init succed" : "SPIFFS init failed");
  
  //----------------------------WIFI
  Serial.println(initWifi() ? "WiFi init succed" : "WiFi init failed");

  //----------------------------Server
  startServe();

  //----------------------------GPIOs
  pinMode(SPEAK_R, OUTPUT);
  pinMode(SPEAK_L, OUTPUT);
  pinMode(MIC, OUTPUT);
  pinMode(KEY_1, INPUT_PULLDOWN);
  pinMode(KEY_2, INPUT_PULLDOWN);
  attachInterrupt(KEY_1, action1, RISING);
  attachInterrupt(KEY_2, action2, RISING);

  //----------------------------Screen
  // Initialising the UI will init the display too.
  oled.init();
  oled.clear();
  oled.update();

  //------------------------BMP
  Serial.println(initBMP() ? "BMP init succed" : "BMP init failed");

  //------------------------Strip LED
  Serial.println(initStripLed(LED_PIN) ? "StripLed init succed" : "StripLed init failed");
}

String weather[5] = {"☀", "⛅", "🌦", "⚡", "❄"};

void loop()
{
  //Strip LED
  random16_add_entropy(random(255));
  Fire2012WithPalette();
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  //Screen
  oled.home();
  oled.clear();
  oled.setScale(1);
  oled.invertText(true);
  oled.printf("Ciel clair %.0fC %.0fhP ", round(bmp.readTemperature()), bmp.readPressure() / 100);
  oled.update();

  oled.setScale(2);
  oled.invertText(false);
  oled.setCursor(1, 2);
  oled.print("Di.");
  oled.setCursor(1, 4);
  oled.print("08/08");
  oled.setCursor(1, 6);
  oled.print("13:27");
  oled.update();

  oled.setScale(1);
  oled.invertText(false);
  oled.setCursor(75, 2);
  oled.print("Bon anniv");
  oled.setCursor(75, 3);
  oled.print("ersaire");
  oled.setCursor(75, 4);
  oled.print("maman");
  oled.update();

  delay(500);
}

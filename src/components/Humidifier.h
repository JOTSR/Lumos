#include <Utility.h>

class Humidifier
{
private:
  int _gpio;
  int _pwmChannel = 0;
  int _pwmFreq = 5000;
  int _pwmRes = 8;
  int _intensity;
  bool _isOn = false;

public:
  Humidifier(int gpio)
  {
    _gpio = gpio;
    pinMode(gpio, OUTPUT);
    analogWriteFrequency(_pwmFreq);
    analogWriteResolution(_pwmRes);
    analogWriteChannel(_pwmChannel);
  }

  void switchOn() {
    _isOn = true;
    Serial.printf("Switch On {%d}\n", _intensity ? _intensity : -1);
    analogWrite(_gpio, _intensity ? _intensity : 0, 255);
  }

  void switchOff() {
    _isOn = false;
    analogWrite(_gpio, 0, 255);
  }

  void setIntensity(int intensity) {
    if(!_isOn) return;
    if (intensity < 0 || intensity > 100) return;
    _intensity = intensity;
    Serial.printf("Set intensity {%f} on {%d}\n", intensity * 2.55, _gpio);
    analogWrite(_gpio, (intensity * 2.55), 255);
  }
};
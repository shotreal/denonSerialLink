#ifndef DENONAVR3805_H
#define DENONAVR3805_H

#include <Arduino.h>

class DenonAVR3805 {
public:
    DenonAVR3805(HardwareSerial& serial);
    void powerOn();
    void powerOff();
    void volumeUp();
    void volumeDown();
    void mute();
    void unmute();
    void setVolume(int level);
    void setTunerInput();        
    void setTunerFrequency(const String& frequency);  

private:
    HardwareSerial& _serial;
    void sendCommand(const String& command);
};

#endif

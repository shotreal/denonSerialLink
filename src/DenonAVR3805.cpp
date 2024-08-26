#include "DenonAVR3805.h"

DenonAVR3805::DenonAVR3805(HardwareSerial& serial) : _serial(serial) {}

void DenonAVR3805::sendCommand(const String& command) {
    _serial.print(command);
}

void DenonAVR3805::powerOn() {
    sendCommand("PWON\r");
}

void DenonAVR3805::powerOff() {
    sendCommand("PWSTANDBY\r");
}

void DenonAVR3805::volumeUp() {
    sendCommand("MVUP\r");
}

void DenonAVR3805::volumeDown() {
    sendCommand("MVDOWN\r");
}

void DenonAVR3805::mute() {
    sendCommand("MUON\r");
}

void DenonAVR3805::unmute() {
    sendCommand("MUOFF\r");
}

void DenonAVR3805::setVolume(int level) {
    char buffer[10];
    sprintf(buffer, "MV%02d\r", level);
    sendCommand(buffer);
}

void DenonAVR3805::setTunerInput() {
    sendCommand("SITUNER\r"); // Command to switch to tuner input
}

void DenonAVR3805::setTunerFrequency(const String& frequency) {
    String command = "TF" + frequency + "\r";
    sendCommand(command);
}

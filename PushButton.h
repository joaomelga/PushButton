
#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <Arduino.h>

#define MIN_INTERVAL_BETWEEN_READINGS 5
#define READINGS_BUFFER_SIZE 10

class Switch {
   private:
    uint8_t _pressedFlag = 0;
    uint8_t _unpressedFlag = 0;
    uint8_t _clickedFlag = 0;
    uint8_t _holdedFlag = 0;
    uint8_t _previousBufferPosition = 0;
    uint8_t _currentBufferPosition = 0;
    uint8_t _crudeReadingsBuffer[READINGS_BUFFER_SIZE] = {0};
    uint8_t _avgReadingsBuffer[READINGS_BUFFER_SIZE] = {0};
    unsigned long _lastReadingTimeRef = millis();
    unsigned long _holdingTimeRef = millis();

    int _pin;
    int _activatedOn;
    char* _name;

   public:
    Switch(char* name, int pin, int activatedOn, uint8_t mode);
    char* getName();
    int getPin();
    int pressed();
    int unpressed();
    uint8_t clicked();
    uint8_t holded(uint32_t timeInMs);
    uint8_t isActive();
    void read();
};

#endif  // SWITCH_H

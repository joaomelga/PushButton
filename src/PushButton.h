
#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <Arduino.h>

#define MIN_INTERVAL_BETWEEN_READINGS 5
#define READINGS_BUFFER_SIZE 2

class Switch {
   private:
    uint8_t _pressedFlag = 0;
    uint8_t _unpressedFlag = 0;
    uint8_t _clickedFlag = 0;
    uint8_t _holdedFlag = 0;
    uint8_t _momentaryState = 0;
    
    /* uint8_t _previousBufferPosition = 0;
    uint8_t _currentBufferPosition = 0;
    uint8_t _crudeReadingsBuffer[READINGS_BUFFER_SIZE] = {0};
    uint8_t _avgReadingsBuffer[READINGS_BUFFER_SIZE] = {0}; */

    float _previousStateFiltered = 0;
    float _currentStateFiltered = 0;

    unsigned long _lastReadingTimeRef = millis();
    unsigned long _holdingTimeRef = millis();

    uint8_t _pin;
    int _activatedOn;
    char* _name;

   public:
    Switch(char* name, uint8_t pin, int activatedOn, uint8_t mode);
    void read();
    char* getName();
    uint8_t getPin();
    uint8_t pressed();
    uint8_t unpressed();
    uint8_t clicked();
    uint8_t holded(uint32_t timeInMs);
    uint8_t isActive();
};

#endif  // PUSHBUTTON_H

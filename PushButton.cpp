#include <PushButton.h>

Switch::Switch(char* name, int pin, int activatedOn, uint8_t mode) {
    _name = name;
    _pin = pin;
    _activatedOn = activatedOn;
    pinMode(pin, mode);
}

int Switch::getPin() {
    return _pin;
}

char* Switch::getName() {
    return _name;
}

void Switch::read() {
    float crudeReadingsAvg;
    uint8_t crudeReadingsSum = 0;

    if (millis() - _lastReadingTimeRef < MIN_INTERVAL_BETWEEN_READINGS) return;

    _crudeReadingsBuffer[_currentBufferPosition] = isActive();

    for (uint8_t i = 0; i < READINGS_BUFFER_SIZE; i++) crudeReadingsSum += _crudeReadingsBuffer[i];

    crudeReadingsAvg = (float)crudeReadingsSum / (float)READINGS_BUFFER_SIZE;
    _avgReadingsBuffer[_currentBufferPosition] = (crudeReadingsAvg > 0.5) ? 1 : 0;

    if (_avgReadingsBuffer[_previousBufferPosition] != _avgReadingsBuffer[_currentBufferPosition]) {
        if (_avgReadingsBuffer[_currentBufferPosition] > _avgReadingsBuffer[_previousBufferPosition]) {
            _pressedFlag = 1;
            _unpressedFlag = 0;
            _holdingTimeRef = millis();
        } else {
            _pressedFlag = 0;
            _unpressedFlag = 1;
            _clickedFlag = !_holdedFlag;
            _holdedFlag = 0;
        }
    }

    _previousBufferPosition = _currentBufferPosition;
    _currentBufferPosition = (_currentBufferPosition + 1) % READINGS_BUFFER_SIZE;
    _lastReadingTimeRef = millis();
}

int Switch::pressed() {
    if (_pressedFlag) {
        _pressedFlag = 0;
        return 1;
    }

    return 0;
}

int Switch::unpressed() {
    if (_unpressedFlag) {
        _unpressedFlag = 0;
        return 1;
    }

    return 0;
}

uint8_t Switch::clicked() {
    if (_clickedFlag) {
        _clickedFlag = 0;
        return 1;
    }

    return 0;
}

uint8_t Switch::holded(uint32_t timeInMs) {
    if (_pressedFlag && (millis() - _holdingTimeRef > timeInMs)) {
        _holdedFlag = 1;
        return 1;
    } else
        return 0;
}

uint8_t Switch::isActive() {
    if ((_activatedOn == HIGH && digitalRead(_pin)) || (_activatedOn == LOW && !digitalRead(_pin)))
        return 1;

    else
        return 0;
}

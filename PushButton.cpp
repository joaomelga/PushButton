#include <PushButton.h>

Switch::Switch(char* name, uint8_t pin, int activatedOn, uint8_t mode) {
    _name = name;
    _pin = pin;
    _activatedOn = activatedOn;
    pinMode(pin, mode);
}

uint8_t Switch::getPin() {
    return _pin;
}

char* Switch::getName() {
    return _name;
}

void Switch::read() {
    _momentaryState = isActive();
    _previousStateFiltered = _currentStateFiltered;
    _currentStateFiltered = _currentStateFiltered * 0.9 + _momentaryState * 0.1;

    if (_currentStateFiltered > 0.5 && _previousStateFiltered <= 0.5) {
        _pressedFlag = 1;
        _unpressedFlag = 0;
        _holdingTimeRef = millis();
    } else if (_currentStateFiltered <= 0.5 && _previousStateFiltered > 0.5) {
        _pressedFlag = 0;
        _unpressedFlag = 1;
        _clickedFlag = !_holdedFlag;
        _holdedFlag = 0;
    }
}

uint8_t Switch::pressed() {
    if (_pressedFlag) {
        _pressedFlag = 0;
        return 1;
    }

    return 0;
}

uint8_t Switch::unpressed() {
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
    if (_pressedFlag && (millis() - _holdingTimeRef > timeInMs) && !_holdedFlag) {
        _holdedFlag = 1;
        _holdingTimeRef = millis();
        return 1;
    } else
        return 0;
}

uint8_t Switch::isActive() {
    if ((_activatedOn == HIGH && digitalRead(_pin)) || (_activatedOn == LOW && !digitalRead(_pin)))
        return 1;
    else if (_activatedOn > HIGH && analogRead(_pin) > _activatedOn)
        return 1;
    else
        return 0;
}

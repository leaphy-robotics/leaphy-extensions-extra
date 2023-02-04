#include "SERIAL_BLUETOOTH.h"
#include <SoftwareSerial.h>

// Constructor
SERIALBLUETOOTH::SERIALBLUETOOTH(int baudRate, int TX, int RX, bool inverse_logic) {
    SoftwareSerial *ss = new SoftwareSerial(TX, RX, inverse_logic);
    // set as private member
    this->ss = ss;
    ss->begin(baudRate);
  
}

SERIALBLUETOOTH::~SERIALBLUETOOTH() {
    delete ss;
}

int SERIALBLUETOOTH::available() {
    return ss->available();
}

bool SERIALBLUETOOTH::begin(int baudRate) {
    return ss->begin(baudRate);
}

char SERIALBLUETOOTH::read() {
    return ss->read();
}

char SERIALBLUETOOTH::readString() {
    return ss->readString();
}

void SERIALBLUETOOTH::send(char c) {
    ss->write(c);
}


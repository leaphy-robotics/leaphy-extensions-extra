#ifndef SERIAL_BLUETOOTH_H
#define SERIAL_BLUETOOTH_H

// default module is HC-05

class SERIALBLUETOOTH {
  public:
    SERIALBLUETOOTH(int baudRate, int TX, int RX, bool inverse_logic);
	  bool begin(int baudRate);
    char read();
    char readString();
    void send(char c);
    int available();
}

#endif

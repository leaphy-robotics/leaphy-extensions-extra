#ifndef SERIAL_BLUETOOTH_H
#define SERIAL_BLUETOOTH_H

// default module is HC-05

class SERIALBLUETOOTH {
  public:
    OLEDDISPLAY(int TX, int RX, bool inverse_logic);
	  bool begin();
    String recieve();
    void send();
    int available();
}

#endif

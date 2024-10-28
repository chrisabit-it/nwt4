/***************************************************************************
                          win_modem.h  -  description
                             -------------------
    begin                : Wed Feb 14 2001
    copyright            : (C) 2001 by Lars Schnake
    email                : mail@lars-schnake.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MODEM_H
#define MODEM_H

//#############################################################################
//#############################################################################
//#############################################################################
//#############################################################################
//#############################################################################

// Quelltext für Windows
//#############################################################################
//#############################################################################
//#############################################################################
//#############################################################################
//#############################################################################


#include <qobject.h>
#include <windows.h>
#include <QString>

#include <qsocketnotifier.h>

/**modem class for serial communication
  *@author Lars Schnake
  *@author DL4JAL Andreas Lindenau Änderungen für NWT7 + HFM9
  */

enum wBaud {
  wBaud_9600 = 9600,
  wBaud_57600 = 57600,
  wBaud_115200 = 115200
};

enum wParity {
  wPARITY_NONE,
  wPARITY_ODD,
  wPARITY_EVEN,
  wPARITY_MARK,
  wPARITY_SPACE
};

enum wSerialLineState {
  wSERIAL_LINESTATE_DCD = 0x040,
  wSERIAL_LINESTATE_CTS = 0x020,
  wSERIAL_LINESTATE_DSR = 0x100,
  wSERIAL_LINESTATE_DTR = 0x002,
  wSERIAL_LINESTATE_RING = 0x080,
  wSERIAL_LINESTATE_RTS = 0x004,
  wSERIAL_LINESTATE_NULL = 0x000,
};

struct SerialPort_DCS {
  wBaud baud;
  wParity parity;
  unsigned char wordlen;
  unsigned char stopbits;
  bool rtscts;
  bool xonxoff;
  SerialPort_DCS() {
    baud = wBaud_57600;
    parity = wPARITY_NONE;
    stopbits = 1;
    rtscts = false;
    xonxoff = false;
  };
};

struct SerialPort_EINFO {
  int brk;
  int frame;
  int overrun;
  int parity;
  SerialPort_EINFO() {
    brk = frame = overrun = parity = 0;
  };
};

class Modem : public QObject {
 Q_OBJECT
 public:
  Modem();
  ~Modem();

/** lock and open serial port with settings of ConfigData*/
  bool opentty(QString seriell_dev);
/** unlock and close serial port */
  bool closetty();
/** write a char to port */
  bool writeChar(unsigned char);
/** write a char[] to port*/
  bool writeLine(const char *);
/** disconnect the notify connection ( see notify )*/
  void stop();
  int readttybuffer(void *, int);
  static Modem *modem;

  HANDLE fd;
  OVERLAPPED ov;
  SerialPort_DCS dcs;
  SerialPort_EINFO einfo;

 signals:
  // is emitted if data was received
  void charWaiting(unsigned char);
  void setTtyText(QString);

 public slots:
  // stop the notifier
  void stopNotifier();
  // read from port
  void readtty(int);

 private:
  bool modem_is_locked;
  QSocketNotifier *sn;
  bool data_mode;
  QString errmsg;
  // QString seriell_dev;
  unsigned char dataMask;
  QString qdev;
};
#endif // MODEM_H

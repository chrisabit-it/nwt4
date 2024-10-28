/***************************************************************************
                          lin_modem.h  -  description
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
// Quelltext für Linux
//#############################################################################
//#############################################################################
//#############################################################################
//#############################################################################
//#############################################################################
#include <qobject.h>

#include <qdir.h>

#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include <qsocketnotifier.h>

#include "konstdef.h"

class Modem : public QObject {

 Q_OBJECT
 public:
  Modem();
  ~Modem();

// lock and open serial port with settings of ConfigData
  bool opentty(QString seriell_dev);
// unlock and close serial port
  bool closetty();
// write a char to port
  bool writeChar(unsigned char);
// write a char[] to port
  bool writeLine(const char *);
// disconnect the notify connection ( see notify )
  void stop();
// neue funktion für den NWT7
  int readttybuffer(void *, int);

 public:
  static Modem *modem;

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
  int modemfd;
  QSocketNotifier *sn;
  struct termios initial_tty;
  unsigned char dataMask;
  bool unlock_device();
  QString qdev;
};

#endif


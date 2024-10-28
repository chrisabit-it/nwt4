/***************************************************************************
                          lin_modem.cpp  -  description
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

#include <fcntl.h>
#include <sys/ioctl.h>
#include <qtimer.h>

#ifdef Q_OS_WIN
#include "win_modem.h"
#else
#include "lin_modem.h"
#endif

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

//  defaults for UUCP style lock files :
#define LF_PATH             "/var/lock"
#define LF_PREFIX           "LCK.."

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

Modem *Modem::modem = 0;

Modem::Modem() : modemfd(-1), sn(0L), dataMask(0xFF) {
  qdev = "";
}

Modem::~Modem() {
  modem = NULL;
}

// open serial port with settings of ConfigData
bool Modem::opentty(QString seriell_dev) {

  emit setTtyText("?");

  int flags = O_RDWR;

  modemfd = open(seriell_dev.toLatin1(), flags | O_NDELAY);
  if (modemfd < 0) {
    return false;
  }
  tcflush(modemfd, TCIOFLUSH);

  struct termios newtio;
  if (tcgetattr(modemfd, &newtio) != 0) {
    return false;
  }
  cfsetospeed(&newtio, B57600);
  cfsetispeed(&newtio, B57600);

  newtio.c_cflag = (newtio.c_cflag & ~CSIZE) | CS8;//8 Databit
  newtio.c_cflag |= CLOCAL | CREAD;
  newtio.c_cflag &= ~(PARENB | PARODD);//no parity
  newtio.c_cflag &= ~CRTSCTS;//kein hardware handshake
  //newtio.c_cflag |= CSTOPB; //2 Stopbit
  newtio.c_cflag &= ~CSTOPB; //1 Stopbit
  newtio.c_iflag = IGNBRK;
  newtio.c_iflag &= ~(IXON | IXOFF | IXANY); //kein Softwarehandshake
  newtio.c_lflag = 0;
  newtio.c_oflag = 0;
  newtio.c_cc[VTIME] = 0;
  newtio.c_cc[VMIN] = 0;

  if (tcsetattr(modemfd, TCSANOW, &newtio) != 0) {
    return false;
  }

  int mcs = 0;
  ioctl(modemfd, TIOCMGET, &mcs);
  mcs |= TIOCM_RTS;
  ioctl(modemfd, TIOCMSET, &mcs);

  if (tcgetattr(modemfd, &newtio) != 0) {
    return false;
  }
  emit setTtyText(seriell_dev);
  return true;
}

bool Modem::closetty() {
  if (modemfd >= 0) {
    stop();
    // discard data not read or transmitted 
    tcflush(modemfd, TCIOFLUSH);
    if (tcsetattr(modemfd, TCSANOW, &initial_tty) < 0) {
#ifdef LDEBUG
      qDebug("Can't restore tty settings: tcsetattr()\n");
#endif
      ::close(modemfd);
      modemfd = -1;
      return false;
    }
    ::close(modemfd);
    modemfd = -1;
  }
  if (!unlock_device()) {
#ifdef LDEBUG
    qDebug("cannot unlock device !");
#endif
    return false;
  }
  return true;
}

void Modem::readtty(int) {
  char buffer[50];
  unsigned char c;
  int len;

  // read data in chunks of up to 50 bytes
  if ((len = ::read(modemfd, buffer, 50)) > 0) {
    // split buffer into single characters for further processing
    for (int i = 0; i < len; i++) {
      c = buffer[i] & dataMask;
      emit charWaiting(c);
    }
  }
}

void Modem::stop() {
  disconnect(SIGNAL(charWaiting(unsigned char)));
  stopNotifier();
}

void Modem::stopNotifier() {
  if (sn != 0) {
    sn->setEnabled(false);
    disconnect(sn);
    delete sn;
    sn = 0;
#ifdef LDEBUG
    qDebug("QSocketNotifier stopped!");
#endif
  }
}

bool Modem::writeChar(unsigned char c) {
#ifdef LDEBUG
  qDebug("UART-C: %x", c);
#endif
  return write(modemfd, &c, 1) == 1;
}

bool Modem::writeLine(const char *buf) {
  size_t a, b;
  a = strlen(buf);
  b = write(modemfd, buf, a);

#ifdef LDEBUG
  qDebug("UART-L: %s", buf);
#endif

  if (a == b) {
    return true;
  } else {
    return false;
  }
}

bool Modem::unlock_device() {

  if (!modem_is_locked && qdev == "") {
#ifdef LDEBUG
    qDebug("confused by unlock device, sorry !\n");
#endif
    return false;
  }
  const char *device = qPrintable(qdev);
  char lckf[128];
  const char *devicename = strrchr(device, '/');
  sprintf(lckf, "%s/%s%s", LF_PATH, LF_PREFIX, (devicename ? (devicename + 1) : device));

  if (unlink(lckf)) {
#ifdef LDEBUG
    qDebug("Unable to unlink lock file: ");
#endif
    return false;
  }
  return true;
}

int Modem::readttybuffer(void *bp, int maxlen) {
  int res = 0;

  if (modemfd > 0) {
    res += read(modemfd, bp, maxlen);
  }
  return res;
}

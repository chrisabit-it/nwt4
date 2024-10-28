/***************************************************************************
                          win_modem.cpp  -  description
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


#include "win_modem.h"
#include <string.h>
#include <stdio.h>
#include <QtGlobal>


#define SERIALPORT_BUFSIZE 4096

#ifndef max
	#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
	#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

Modem *Modem::modem = 0;

Modem::Modem(): sn(0L), data_mode(false),dataMask(0xFF)
{
  modem = this;
  modem_is_locked = false;
  qdev = "";
}

Modem::~Modem() {
  modem = NULL;
}

/* open serial port with settings of ConfigData*/
bool Modem::opentty(QString seriell_dev) {
  DCB dcb;

  const char *name;
  QString qs;
  qs = seriell_dev;
  //COM ab COM10 muessen gewandelt werden in \\.\COM10
  if(qs.length() > 4)qs = "\\\\.\\" + qs;
  //Wandlung in *char für API-Funktionen
  name = qPrintable(qs);
  //alles auf 0 setzen
  memset(&dcb, 0, sizeof(dcb));
  dcb.DCBlength = sizeof(dcb);
  dcb.BaudRate = CBR_57600;
  dcb.fBinary = 1;
  dcb.Parity = NOPARITY;
  dcb.StopBits = ONESTOPBIT;
  dcb.ByteSize = 8;
  dcb.fOutxCtsFlow = false;
  dcb.fDtrControl = DTR_CONTROL_ENABLE;
  dcb.fRtsControl = RTS_CONTROL_ENABLE;

  fd = CreateFileA(name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
  if(fd == INVALID_HANDLE_VALUE){
    emit setTtyText("?");
    return false;
  }
  if(!SetCommState(fd,&dcb)){
    emit setTtyText("?");
    return false;
  }
  ov.hEvent = CreateEvent(NULL, true, true, NULL);
  if(ov.hEvent == INVALID_HANDLE_VALUE){
    emit setTtyText("?");
    return false;
  }
  COMMTIMEOUTS cto = {MAXDWORD, 0, 0, 0, 0};
  if(!SetCommTimeouts(fd, &cto)){
    emit setTtyText("?");
    return false;
  }
  if(!SetupComm(fd, SERIALPORT_BUFSIZE, SERIALPORT_BUFSIZE)){
    emit setTtyText("?");
    return false;
  }
  memset(&einfo,0, sizeof(einfo));
  emit setTtyText(seriell_dev);
  return true;
}

bool Modem::closetty() {
  if(fd != INVALID_HANDLE_VALUE){
    CloseHandle(ov.hEvent);
    CloseHandle(fd);
    fd = INVALID_HANDLE_VALUE;
  }
  emit setTtyText("?");
  return true;
}

void Modem::stop() {
  disconnect(SIGNAL(charWaiting(unsigned char)));
  stopNotifier();
}

void Modem::stopNotifier() {
  if(sn != 0) {
    sn->setEnabled(false);
    disconnect(sn);
    delete sn;
    sn = 0;
#ifdef LDEBUG
    qDebug("QSocketNotifier stopped!");
#endif
  }
}

void Modem::readtty(int) {
  char buffer[50];

  // read data in chunks of up to 50 bytes
  DWORD dw=0;
  ReadFile(fd,buffer,50,&dw,nullptr);

  if(const int len = static_cast<int>(dw); len > 0) {
    // split buffer into single characters for further processing
    for(int i = 0; i < len; i++) {
      const unsigned char c = buffer[i] & dataMask;
      emit charWaiting(c);
    }
  }
}

bool Modem::writeChar(unsigned char c) {
  DWORD dw;

  WriteFile(fd, &c, 1, &dw, nullptr);
  return (dw > 0);
}

bool Modem::writeLine(const char *buf) {
  DWORD dw;

  int len = strlen(buf);
  WriteFile(fd, buf, len, &dw, nullptr);
  return (static_cast<int>(dw) == len);
}

int Modem::readttybuffer( void *bp, int maxlen)
{
  DWORD dw=0;
  ReadFile(fd,bp,maxlen,&dw,nullptr);
  return static_cast<int>(dw);
}

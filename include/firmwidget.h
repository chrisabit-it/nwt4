/***************************************************************************
                          firmwidget.h  -  description
                             -------------------
    copyright            : (C) 2003 by Andreas Lindenau
    email                : DL4JAL@darc.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef FIRMWIDGET_H
#define FIRMWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QString>

#include "konstdef.h"

class firmwidget : public QDialog {
 Q_OBJECT

 public:
  firmwidget(QWidget *parent = 0, const char *name = 0, bool modal = false);

 public slots:
  void setText(QString s);

 private:
  QLabel *label1;
};

#endif // FIRMWIDGET_H

/***************************************************************************
                          firmwidget.cpp  -  description
                             -------------------
    copyright            : (C) 2005 by Andreas Lindenau
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


#include "firmwidget.h"


//#####################################################################################
// Class für Firmwidget
//#####################################################################################
firmwidget::firmwidget(QWidget* parent, const char* name, bool modal): QDialog(parent)
{
  setModal(modal);
  this->resize(450,100);
  label1 = new QLabel(this);
  label1->setGeometry(10,10,400,30);
  label1->setText(tr("Firmware Update","Label"));
  label1->setAlignment(Qt::AlignHCenter);
}

void firmwidget::setText(QString s)
{
  setFocus();
  label1->setText(s);
  repaint();
}

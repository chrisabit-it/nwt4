/***************************************************************************
                          profildlg.h  -  description
                             -------------------
    begin                : Son Aug 17 2003
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

#ifndef PROFILDLG_H
#define PROFILDLG_H

#include <qdialog.h>
#include <qpushbutton.h>
#include <qdialog.h>
#include <qgroupbox.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qstring.h>

#include "konstdef.h"

class profildlg : public QDialog {
 Q_OBJECT

 public:
  profildlg(QWidget *parent = 0, const char *name = 0, bool modal = false);

  void setprofil(TProfil aprofil, int index);

  TProfil getprofil(int);

  void tip(bool atip);

 private slots:

  QString linenormalisieren(const QString &);

  void allespruefen();

  void allesloeschen();

 private:
//  tprofil profilarray[profilanz];

  QPushButton *ok;
  QPushButton *cancel;
  QPushButton *pruefen;
  QPushButton *loeschen;

  QLineEdit *eanfang[profilanz];
  QLineEdit *eende[profilanz];
  QLineEdit *eschritte[profilanz];
  QLineEdit *ebeschreibung[profilanz];
  QLabel *labelbeschreibung;
  QLabel *labelanfang;
  QLabel *labelende;
  QLabel *labelschritte;

};

#endif // PROFILDLG_H

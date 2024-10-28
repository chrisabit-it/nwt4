/***************************************************************************
                          main.cpp  -  description
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

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QString>
#include <QtGui>
#include <QDir>

#include "mainwindow.h"

#define I18N_PREFIX ":/i18n/app_"

int main(int argc, char *argv[]) {
  int indexhfc = 0;
  QString s;
  char c[] = "hfm9.hfc";
  QApplication app(argc, argv);
  QTranslator translator;

  if (QLocale::system().language() != QLocale::Language::German) {
    QStringList languages = QLocale::system().uiLanguages();
    languages.append("en_GB");
    for (const QString &locale : languages) {
      if (const QString i18nName = I18N_PREFIX + QLocale(locale).name(); translator.load(i18nName)) {
        QApplication::installTranslator(&translator);
        break;
      }
    }
  }

  QDir dir(argv[0]);
  QString programpath(dir.absolutePath());

  if (argc > 1) {
    s = argv[1];
    if (s.contains(".hfc"))indexhfc = 1;
  }
  if (argc > 2) {
    s = argv[2];
    if (s.contains(".hfc"))indexhfc = 2;
  }
  app.setQuitOnLastWindowClosed(true);
  MainWindow *mainWin = new MainWindow();
  app.setWindowIcon(QIcon(":images/appicon.png"));
  mainWin->setWindowIcon(QIcon(":images/appicon.png"));
  mainWin->show();
  //Den Pfad für Konfigurationsdateien setzen
  mainWin->setProgramPath(programpath);
  if (indexhfc != 0) {
    mainWin->loadConfig(argv[indexhfc]);
  } else {
    mainWin->loadConfig(c);
  }
  return app.exec();
}

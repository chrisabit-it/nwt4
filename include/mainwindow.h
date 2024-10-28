/***************************************************************************
                          mainwindow.h  -  description
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/qsystemdetection.h>

#include <QMainWindow>
#include "nwt7linux.h"

#include "konstdef.h"

class QAction;
class QMenu;
class Nwt7linux;

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  MainWindow();
  void setProgramPath(QString);

 protected:
  void closeEvent(QCloseEvent *event);
  virtual void paintEvent(QPaintEvent *);
  virtual void resizeEvent(QResizeEvent *);

 public slots:
  void setText(QString);
  void readSettings();
  void loadConfig(char *name);
  void loadGeraet(char *name);
  void setFontSize(int s);

 private slots:
  void msetmenu(emenuenable, bool);

  void druckediagramm();
  void druckediagrammpdf();
  void bildspeichern();

  void EinstellungLaden();
  void EinstellungSichern();

  void geraet_neu();

  void KurvenLaden();
  void KurvenSichern();

  void Info();
  void option();
  void firmupdate();

  void clickwobbeln(); //Wobbeln starten
  void clickwobbelneinmal(); //Einen Durchlauf wobbeln
  void clickwobbelnstop(); //Wobbeln stoppen
  void kalibrierenkanal1();
  void kalibrierenkanal2();
  void messsondeladen1();
  void messsondeladen2();
  void messsondespeichern1();
  void messsondespeichern2();
  void infosetfont();
  void setBreite();

  void messsetfont();
  void mkalibrierenk1();
  void mkalibrierenk2();
  void editsonde1();
  void editsonde2();
  void tabelleschreiben();
  void tabellespeichern();
  void setDaempfungdefault();
  void beenden();
  void version();
  void zaehlen();
  void tooltip();
  void setFrequenzmarken();
  void editProfile();
  void setHLine();

 private:
  void createActions();
  void createMenus();
  void createToolBars();
  void createStatusBar();
  void createToolTip(bool);
  void writeSettings();

  bool bbreite;

//    QTextEdit *textEdit;
  Nwt7linux *nwt7linux;
  QString curFile;
  QString infotext;
  QString infodatum;
  QString infoversion;
  QString programpath;

  QMenu *fileMenu;
  QMenu *editMenu;
  QMenu *helpMenu;
  QMenu *menuDatei;
  QMenu *menuEinstellung;
  QMenu *menuGeraet;
  QMenu *menuKurven;
  QMenu *menuwobbel;
//    QMenu *menuvfo;
  QMenu *menumessen;
#ifdef fzaehler
  QMenu *menuzaehlen;
#endif
  QMenu *menuhilfe;

  QToolBar *dateiToolBar;
  QToolBar *einstellungToolBar;
  QToolBar *sondenToolBar;
  QToolBar *kurvenToolBar;
  QAction *newAct;
  QAction *openAct;
  QAction *saveAct;
  QAction *saveAsAct;
  QAction *exitAct;
  QAction *cutAct;
  QAction *copyAct;
  QAction *pasteAct;
  QAction *aboutAct;
  QAction *aboutQtAct;

  QAction *mDrucken;
  QAction *mDruckenpdf;
  QAction *mSpeichernpng;
  QAction *mBeenden;

  QAction *mEinstellungLaden;
  QAction *mEinstellungSichern;

  QAction *mGeraetNeu;

  QAction *mInfo;
  QAction *mOption;
  QAction *mFirmware;
  QAction *mKurvenLaden;
  QAction *mKurvenSichern;
  QAction *mWobbeln;
  QAction *mEinmal;
  QAction *mStop;
  QAction *mEichenK1;
  QAction *mEichenK2;
  QAction *mSondeLadenK1;
  QAction *mSondeLadenK2;
  QAction *mSondeSpeichernK1;
  QAction *mSondeSpeichernK2;
  QAction *mFontInfo;
  QAction *mFrequenzmarke;
  QAction *mProfile;
  QAction *mVFODreh1;
  QAction *mVFODreh2;
  QAction *mVFODreh3;
  QAction *mWattFont;
  QAction *mWattEichenK1;
  QAction *mWattEichenK2;
  QAction *mWattSchreiben;
  QAction *mWattEditSonde1;
  QAction *mWattEditSonde2;
  QAction *mTabelleSpeichern;
  QAction *mDaempfungdefault;
  QAction *mVersion;
  QAction *mTooltip;
  QAction *mKurvenManager;
  QAction *mBreite;
  QAction *mHLine;

#ifdef fzaehler
  QAction *mZaehlen;
#endif

  bool bstart;
};

#endif

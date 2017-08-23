#ifndef FUNSELFCHECKINI_H
#define FUNSELFCHECKINI_H
#include <QHostInfo>
#include <QDebug>
#include <QString>
#include <QNetworkInterface>
class FunSelfCheckIni
{
   //Q_OBJECT

public:
  static QString getLocalHostName();
public:
  //static QString getLocalHostIP();
  static QList<QNetworkInterface> getNetWorkInterface();

};
#endif // FUNSELFCHECKINI_H

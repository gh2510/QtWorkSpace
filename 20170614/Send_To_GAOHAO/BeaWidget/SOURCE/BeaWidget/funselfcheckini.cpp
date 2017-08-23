#include<funselfcheckini.h>
 QString FunSelfCheckIni::getLocalHostName()
{
  return QHostInfo::localHostName();

}

QList<QNetworkInterface> getNetWorkInterface()
{
  return  QNetworkInterface::allInterfaces();
}

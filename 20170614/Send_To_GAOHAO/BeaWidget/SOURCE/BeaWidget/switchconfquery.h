#ifndef SWITCHCONFQUERY_H
#define SWITCHCONFQUERY_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include "Telnet/telnetmanager.h"
#include "labeledit.h"
class switchConfQuery : public QWidget
{
    Q_OBJECT

public:
    explicit switchConfQuery(telnetManager *teml,QWidget *parent = 0);
    ~switchConfQuery();

signals:
    void doQuery(QString);

private slots:
    void clearTextEdit();
    void queryBtn();
    void readServer(QString);
    void slot_socket_err();
private:
    QTextEdit *textEdit;
    bool flag;
    telnetManager  *telm;

     LabelEdit *queryCon;
};

#endif // SWITCHCONFQUERY_H

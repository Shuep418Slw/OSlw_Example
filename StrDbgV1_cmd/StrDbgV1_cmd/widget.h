#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "qmessagebox.h"
#include <qfiledialog.h>
#include<qmessagebox.h>
#include <qlist.h>
#include<qtextstream.h>
#include<qstringlist.h>
#include "qmessagebox.h"
#include "qdatetime.h"
#include "qpainter.h"
#include "qelapsedtimer.h"
#include <qgraphicsitem.h>
#include <cstdlib>
#include <malloc.h>
#include <cstring>
#include <cmath>
#include <QVector>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void Widget::SerialUpdate();


private slots:
    void HistorySelect();
    void InputSD();
    void Read_Data();

    void on_openportBut_clicked();

    void on_PB_CLR_clicked();

    void on_PB_Forget_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QSerialPort *serial;
    QStringList his_list;
    int his_index;
};

#endif // WIDGET_H

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->LE_input->setEnabled(false);
    SerialUpdate();

    QDir dir = QDir::current();
    QFile file(dir.filePath("_SD_MEM.txt"));

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(NULL, tr("Path"), tr("Can not find log text and create it"));
        file.open(QIODevice::WriteOnly);
        file.close();
        return;
    }

    QTextStream * out = new QTextStream(&file);//文本流
    QStringList tempOption = out->readAll().split("\r\n");//每行以\r\n区分 win文本
    his_index=tempOption.at(0).toInt()-1;

    if(his_index<0)
        his_index=0;

    tempOption.removeAt(0);
    his_list=tempOption;
    file.close();

    connect(ui->LE_input,SIGNAL(textEdited(const QString&)),this, SLOT(HistorySelect ()));
    connect(ui->LE_input, SIGNAL( returnPressed()), this, SLOT(InputSD()));



}

Widget::~Widget()
{
    delete ui;
}

void Widget::SerialUpdate()
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->PortBox->addItem(serial.portName());
            serial.close();
        }
    }

}

void Widget::HistorySelect()
{
    QString str=this->ui->LE_input->text();

    if(str.length()==0 || his_list.length()==0)
        return;

    if(str.at(str.length()-1) == '/')
    {
        his_index--;
        if(his_index<0)
            his_index=0;
        ui->LE_input->setText(his_list.at(his_index));
    }
    else if(str.at(str.length()-1) == '\\')
    {
        his_index++;
        if(his_index>=his_list.length())
            his_index=his_list.length()-1;
        ui->LE_input->setText(his_list.at(his_index));
    }
    else;

}


void Widget::InputSD()
{

    QString str=this->ui->LE_input->text();
    QByteArray ba = str.toLatin1(); // must
    ba.append('\n');

    QString str1 = ui->PTE_show->toPlainText();
    str1+=(str+"\n");
    ui->PTE_show->clear();
    ui->PTE_show->appendPlainText(str1);

    serial->write(ba);

    ui->LE_input->setText("");
    his_list.append((str));
    his_index=his_list.length();

}

void Widget::on_openportBut_clicked()
{
    if(ui->openportBut->text()==tr("打开串口"))
    {
        //串口初始化
        serial = new QSerialPort;
        serial->setPortName(ui->PortBox->currentText());
        serial->setBaudRate(ui->BaudBox->currentText().toInt());
        if(!serial->open(QIODevice::ReadWrite))
        {
            QMessageBox::about(NULL, tr("串口打开错误"), tr("<font color='red'>无法打开当前串口</font>"));
            serial->close();
            return;
        }

        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        ui->PortBox->setEnabled(false);
        ui->BaudBox->setEnabled(false);
        ui->openportBut->setText(tr("关闭串口"));

        ui->LE_input->setEnabled(true);

        QObject::connect(serial, &QSerialPort::readyRead, this, &Widget::Read_Data);

    }
    else
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();
        ui->PortBox->setEnabled(true);
        ui->BaudBox->setEnabled(true);
        ui->openportBut->setText(tr("打开串口"));
        ui->LE_input->setEnabled(false);
    }

}

void Widget::Read_Data()
{
    QByteArray buf;
    buf = serial->readAll();
    if(!buf.isEmpty())
    {
        QString str = ui->PTE_show->toPlainText();
        str+=tr(buf);
        ui->PTE_show->clear();
        ui->PTE_show->appendPlainText(str);
    }
    buf.clear();

}

void Widget::on_PB_CLR_clicked()
{
    ui->PTE_show->clear();
}

void Widget::on_PB_Forget_clicked()
{
    his_list.clear();
}

void Widget::on_pushButton_clicked()
{
    QDir dir = QDir::current();
    QFile file(dir.filePath("_SD_MEM.txt"));

    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(NULL, tr("Path"), tr("ERROR"));
    }
    else
    {
        QString str = his_list.join("\r\n");
        QString v;
        v.sprintf("%d\r\n",his_list.length());
        str=v+str;
        QTextStream in(&file);
        in<<str<<"\r\n";

        file.close();
    }

    if(!(ui->openportBut->text()==tr("打开串口")))
    {
        serial->clear();
        serial->close();
        serial->deleteLater();
    }


    QApplication* app;
    app->exit(0);
}

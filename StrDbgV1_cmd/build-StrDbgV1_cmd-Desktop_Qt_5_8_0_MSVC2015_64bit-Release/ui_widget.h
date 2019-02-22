/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *PortBox;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *BaudBox;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *openportBut;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *verticalLayout_3;
    QPlainTextEdit *PTE_show;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *LE_input;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *PB_CLR;
    QSpacerItem *verticalSpacer_8;
    QPushButton *PB_Forget;
    QSpacerItem *verticalSpacer_9;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(947, 378);
        horizontalLayoutWidget = new QWidget(Widget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 921, 361));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        PortBox = new QComboBox(horizontalLayoutWidget);
        PortBox->setObjectName(QStringLiteral("PortBox"));

        horizontalLayout_2->addWidget(PortBox);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        BaudBox = new QComboBox(horizontalLayoutWidget);
        BaudBox->setObjectName(QStringLiteral("BaudBox"));
        BaudBox->setEnabled(true);
        BaudBox->setEditable(true);
        BaudBox->setDuplicatesEnabled(true);

        horizontalLayout_3->addWidget(BaudBox);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));

        verticalLayout->addLayout(horizontalLayout_4);

        openportBut = new QPushButton(horizontalLayoutWidget);
        openportBut->setObjectName(QStringLiteral("openportBut"));

        verticalLayout->addWidget(openportBut);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        PTE_show = new QPlainTextEdit(horizontalLayoutWidget);
        PTE_show->setObjectName(QStringLiteral("PTE_show"));

        verticalLayout_3->addWidget(PTE_show);

        verticalSpacer_3 = new QSpacerItem(10, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_3);

        LE_input = new QLineEdit(horizontalLayoutWidget);
        LE_input->setObjectName(QStringLiteral("LE_input"));

        verticalLayout_3->addWidget(LE_input);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        PB_CLR = new QPushButton(horizontalLayoutWidget);
        PB_CLR->setObjectName(QStringLiteral("PB_CLR"));

        verticalLayout_2->addWidget(PB_CLR);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_8);

        PB_Forget = new QPushButton(horizontalLayoutWidget);
        PB_Forget->setObjectName(QStringLiteral("PB_Forget"));

        verticalLayout_2->addWidget(PB_Forget);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_9);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(Widget);

        BaudBox->setCurrentIndex(10);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "\344\270\262\345\217\243\345\217\267:", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "\346\263\242\347\211\271\347\216\207:", Q_NULLPTR));
        BaudBox->clear();
        BaudBox->insertItems(0, QStringList()
         << QApplication::translate("Widget", "110", Q_NULLPTR)
         << QApplication::translate("Widget", "300", Q_NULLPTR)
         << QApplication::translate("Widget", "600", Q_NULLPTR)
         << QApplication::translate("Widget", "1200", Q_NULLPTR)
         << QApplication::translate("Widget", "2400", Q_NULLPTR)
         << QApplication::translate("Widget", "4800", Q_NULLPTR)
         << QApplication::translate("Widget", "9600", Q_NULLPTR)
         << QApplication::translate("Widget", "19200", Q_NULLPTR)
         << QApplication::translate("Widget", "38400", Q_NULLPTR)
         << QApplication::translate("Widget", "57600", Q_NULLPTR)
         << QApplication::translate("Widget", "115200", Q_NULLPTR)
        );
        BaudBox->setCurrentText(QApplication::translate("Widget", "115200", Q_NULLPTR));
        openportBut->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
        PB_CLR->setText(QApplication::translate("Widget", "\346\270\205\351\231\244\346\230\276\347\244\272", Q_NULLPTR));
        PB_Forget->setText(QApplication::translate("Widget", "\346\270\205\347\251\272\350\256\260\345\275\225", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Widget", "\351\200\200\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

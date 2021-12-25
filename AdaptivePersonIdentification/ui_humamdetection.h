/********************************************************************************
** Form generated from reading UI file 'humamdetection.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HUMAMDETECTION_H
#define UI_HUMAMDETECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_humandetection
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *modelDir_PB;
    QSpacerItem *verticalSpacer;
    QPushButton *dataDir_PB;
    QSpacerItem *verticalSpacer_2;
    QLabel *personName_LB;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *modelDir_LE;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *dataDir_LE;
    QSpacerItem *verticalSpacer_4;
    QLineEdit *personName_LE;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *run_PB;
    QPushButton *abort_pb;

    void setupUi(QDialog *humandetection)
    {
        if (humandetection->objectName().isEmpty())
            humandetection->setObjectName(QString::fromUtf8("humandetection"));
        humandetection->resize(400, 300);
        verticalLayoutWidget = new QWidget(humandetection);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 40, 111, 151));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        modelDir_PB = new QPushButton(verticalLayoutWidget);
        modelDir_PB->setObjectName(QString::fromUtf8("modelDir_PB"));

        verticalLayout->addWidget(modelDir_PB);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        dataDir_PB = new QPushButton(verticalLayoutWidget);
        dataDir_PB->setObjectName(QString::fromUtf8("dataDir_PB"));

        verticalLayout->addWidget(dataDir_PB);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        personName_LB = new QLabel(verticalLayoutWidget);
        personName_LB->setObjectName(QString::fromUtf8("personName_LB"));

        verticalLayout->addWidget(personName_LB);

        verticalLayoutWidget_2 = new QWidget(humandetection);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(130, 40, 251, 151));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        modelDir_LE = new QLineEdit(verticalLayoutWidget_2);
        modelDir_LE->setObjectName(QString::fromUtf8("modelDir_LE"));
        modelDir_LE->setEnabled(false);

        verticalLayout_2->addWidget(modelDir_LE);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        dataDir_LE = new QLineEdit(verticalLayoutWidget_2);
        dataDir_LE->setObjectName(QString::fromUtf8("dataDir_LE"));
        dataDir_LE->setEnabled(false);

        verticalLayout_2->addWidget(dataDir_LE);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        personName_LE = new QLineEdit(verticalLayoutWidget_2);
        personName_LE->setObjectName(QString::fromUtf8("personName_LE"));

        verticalLayout_2->addWidget(personName_LE);

        horizontalLayoutWidget = new QWidget(humandetection);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(180, 240, 194, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        run_PB = new QPushButton(horizontalLayoutWidget);
        run_PB->setObjectName(QString::fromUtf8("run_PB"));

        horizontalLayout->addWidget(run_PB);

        abort_pb = new QPushButton(horizontalLayoutWidget);
        abort_pb->setObjectName(QString::fromUtf8("abort_pb"));

        horizontalLayout->addWidget(abort_pb);


        retranslateUi(humandetection);

        QMetaObject::connectSlotsByName(humandetection);
    } // setupUi

    void retranslateUi(QDialog *humandetection)
    {
        humandetection->setWindowTitle(QCoreApplication::translate("humandetection", "Dialog", nullptr));
        modelDir_PB->setText(QCoreApplication::translate("humandetection", "Model Dir", nullptr));
        dataDir_PB->setText(QCoreApplication::translate("humandetection", "Data Dir", nullptr));
        personName_LB->setText(QCoreApplication::translate("humandetection", "Video Input", nullptr));
        personName_LE->setText(QCoreApplication::translate("humandetection", "0", nullptr));
        run_PB->setText(QCoreApplication::translate("humandetection", "Run", nullptr));
        abort_pb->setText(QCoreApplication::translate("humandetection", "Abort", nullptr));
    } // retranslateUi

};

namespace Ui {
    class humandetection: public Ui_humandetection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HUMAMDETECTION_H

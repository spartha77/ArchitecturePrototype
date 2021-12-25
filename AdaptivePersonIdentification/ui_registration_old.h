/********************************************************************************
** Form generated from reading UI file 'registration.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_registration
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *modelDir_PB;
    QSpacerItem *verticalSpacer;
    QPushButton *dataDir_PB;
    QSpacerItem *verticalSpacer_5;
    QPushButton *imageDir_PB;
    QSpacerItem *verticalSpacer_2;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *modelDir_LE;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *dataDir_LE;
    QSpacerItem *verticalSpacer_6;
    QLineEdit *imageDir_LE;
    QSpacerItem *verticalSpacer_4;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *run_PB;
    QPushButton *abort_pb;
    QGroupBox *mode_GB;
    QRadioButton *batchMode_RB;
    QRadioButton *personName_RB;
    QLineEdit *personName_LE;

    void setupUi(QDialog *registration)
    {
        if (registration->objectName().isEmpty())
            registration->setObjectName(QString::fromUtf8("registration"));
        registration->resize(424, 418);
        verticalLayoutWidget = new QWidget(registration);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 50, 111, 151));
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

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        imageDir_PB = new QPushButton(verticalLayoutWidget);
        imageDir_PB->setObjectName(QString::fromUtf8("imageDir_PB"));

        verticalLayout->addWidget(imageDir_PB);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        verticalLayoutWidget_2 = new QWidget(registration);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(140, 50, 251, 151));
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

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_6);

        imageDir_LE = new QLineEdit(verticalLayoutWidget_2);
        imageDir_LE->setObjectName(QString::fromUtf8("imageDir_LE"));
        imageDir_LE->setEnabled(false);

        verticalLayout_2->addWidget(imageDir_LE);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        horizontalLayoutWidget = new QWidget(registration);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(190, 360, 229, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        run_PB = new QPushButton(horizontalLayoutWidget);
        run_PB->setObjectName(QString::fromUtf8("run_PB"));

        horizontalLayout->addWidget(run_PB);

        abort_pb = new QPushButton(horizontalLayoutWidget);
        abort_pb->setObjectName(QString::fromUtf8("abort_pb"));

        horizontalLayout->addWidget(abort_pb);

        mode_GB = new QGroupBox(registration);
        mode_GB->setObjectName(QString::fromUtf8("mode_GB"));
        mode_GB->setGeometry(QRect(10, 210, 401, 131));
        batchMode_RB = new QRadioButton(mode_GB);
        batchMode_RB->setObjectName(QString::fromUtf8("batchMode_RB"));
        batchMode_RB->setGeometry(QRect(20, 40, 112, 23));
        batchMode_RB->setChecked(true);
        personName_RB = new QRadioButton(mode_GB);
        personName_RB->setObjectName(QString::fromUtf8("personName_RB"));
        personName_RB->setGeometry(QRect(170, 40, 201, 23));
        personName_LE = new QLineEdit(mode_GB);
        personName_LE->setObjectName(QString::fromUtf8("personName_LE"));
        personName_LE->setGeometry(QRect(190, 80, 171, 25));
        mode_GB->raise();
        verticalLayoutWidget->raise();
        verticalLayoutWidget_2->raise();
        horizontalLayoutWidget->raise();

        retranslateUi(registration);

        QMetaObject::connectSlotsByName(registration);
    } // setupUi

    void retranslateUi(QDialog *registration)
    {
        registration->setWindowTitle(QCoreApplication::translate("registration", "Dialog", nullptr));
        modelDir_PB->setText(QCoreApplication::translate("registration", "Model Dir", nullptr));
        dataDir_PB->setText(QCoreApplication::translate("registration", "Data Dir", nullptr));
        imageDir_PB->setText(QCoreApplication::translate("registration", "Image Dir", nullptr));
        run_PB->setText(QCoreApplication::translate("registration", "Run", nullptr));
        abort_pb->setText(QCoreApplication::translate("registration", "Abort", nullptr));
        mode_GB->setTitle(QCoreApplication::translate("registration", "Mode", nullptr));
        batchMode_RB->setText(QCoreApplication::translate("registration", "Batch Mode", nullptr));
        personName_RB->setText(QCoreApplication::translate("registration", "Person Name to Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registration: public Ui_registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H

/********************************************************************************
** Form generated from reading UI file 'registration.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
    QRadioButton *liveRegister_RB;
    QLineEdit *livePersonName_LE;

    void setupUi(QDialog *registration)
    {
        if (registration->objectName().isEmpty())
            registration->setObjectName(QStringLiteral("registration"));
        registration->resize(644, 418);
        verticalLayoutWidget = new QWidget(registration);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 50, 111, 151));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        modelDir_PB = new QPushButton(verticalLayoutWidget);
        modelDir_PB->setObjectName(QStringLiteral("modelDir_PB"));

        verticalLayout->addWidget(modelDir_PB);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        dataDir_PB = new QPushButton(verticalLayoutWidget);
        dataDir_PB->setObjectName(QStringLiteral("dataDir_PB"));

        verticalLayout->addWidget(dataDir_PB);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        imageDir_PB = new QPushButton(verticalLayoutWidget);
        imageDir_PB->setObjectName(QStringLiteral("imageDir_PB"));

        verticalLayout->addWidget(imageDir_PB);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        verticalLayoutWidget_2 = new QWidget(registration);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(140, 50, 461, 151));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        modelDir_LE = new QLineEdit(verticalLayoutWidget_2);
        modelDir_LE->setObjectName(QStringLiteral("modelDir_LE"));
        modelDir_LE->setEnabled(false);

        verticalLayout_2->addWidget(modelDir_LE);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        dataDir_LE = new QLineEdit(verticalLayoutWidget_2);
        dataDir_LE->setObjectName(QStringLiteral("dataDir_LE"));
        dataDir_LE->setEnabled(false);

        verticalLayout_2->addWidget(dataDir_LE);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_6);

        imageDir_LE = new QLineEdit(verticalLayoutWidget_2);
        imageDir_LE->setObjectName(QStringLiteral("imageDir_LE"));
        imageDir_LE->setEnabled(false);

        verticalLayout_2->addWidget(imageDir_LE);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        horizontalLayoutWidget = new QWidget(registration);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(373, 360, 229, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        run_PB = new QPushButton(horizontalLayoutWidget);
        run_PB->setObjectName(QStringLiteral("run_PB"));

        horizontalLayout->addWidget(run_PB);

        abort_pb = new QPushButton(horizontalLayoutWidget);
        abort_pb->setObjectName(QStringLiteral("abort_pb"));

        horizontalLayout->addWidget(abort_pb);

        mode_GB = new QGroupBox(registration);
        mode_GB->setObjectName(QStringLiteral("mode_GB"));
        mode_GB->setGeometry(QRect(10, 210, 601, 131));
        batchMode_RB = new QRadioButton(mode_GB);
        batchMode_RB->setObjectName(QStringLiteral("batchMode_RB"));
        batchMode_RB->setGeometry(QRect(15, 40, 141, 23));
        QFont font;
        font.setPointSize(9);
        batchMode_RB->setFont(font);
        batchMode_RB->setChecked(true);
        personName_RB = new QRadioButton(mode_GB);
        personName_RB->setObjectName(QStringLiteral("personName_RB"));
        personName_RB->setGeometry(QRect(168, 40, 241, 23));
        personName_RB->setFont(font);
        personName_LE = new QLineEdit(mode_GB);
        personName_LE->setObjectName(QStringLiteral("personName_LE"));
        personName_LE->setGeometry(QRect(184, 80, 171, 25));
        liveRegister_RB = new QRadioButton(mode_GB);
        liveRegister_RB->setObjectName(QStringLiteral("liveRegister_RB"));
        liveRegister_RB->setGeometry(QRect(400, 40, 121, 23));
        liveRegister_RB->setFont(font);
        livePersonName_LE = new QLineEdit(mode_GB);
        livePersonName_LE->setObjectName(QStringLiteral("livePersonName_LE"));
        livePersonName_LE->setGeometry(QRect(410, 80, 171, 25));
        mode_GB->raise();
        verticalLayoutWidget->raise();
        verticalLayoutWidget_2->raise();
        horizontalLayoutWidget->raise();

        retranslateUi(registration);

        QMetaObject::connectSlotsByName(registration);
    } // setupUi

    void retranslateUi(QDialog *registration)
    {
        registration->setWindowTitle(QApplication::translate("registration", "Dialog", Q_NULLPTR));
        modelDir_PB->setText(QApplication::translate("registration", "Model Dir", Q_NULLPTR));
        dataDir_PB->setText(QApplication::translate("registration", "Data Dir", Q_NULLPTR));
        imageDir_PB->setText(QApplication::translate("registration", "Image Dir", Q_NULLPTR));
        run_PB->setText(QApplication::translate("registration", "Run", Q_NULLPTR));
        abort_pb->setText(QApplication::translate("registration", "Abort", Q_NULLPTR));
        mode_GB->setTitle(QApplication::translate("registration", "Mode", Q_NULLPTR));
        batchMode_RB->setText(QApplication::translate("registration", "Batch Mode (offiline)", Q_NULLPTR));
        personName_RB->setText(QApplication::translate("registration", "Person Name to Register(offline)", Q_NULLPTR));
        liveRegister_RB->setText(QApplication::translate("registration", "Live Registration", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class registration: public Ui_registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H

/********************************************************************************
** Form generated from reading UI file 'identify.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IDENTIFY_H
#define UI_IDENTIFY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_identify
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

    void setupUi(QDialog *identify)
    {
        if (identify->objectName().isEmpty())
            identify->setObjectName(QStringLiteral("identify"));
        identify->resize(400, 300);
        verticalLayoutWidget = new QWidget(identify);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 40, 111, 151));
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

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        personName_LB = new QLabel(verticalLayoutWidget);
        personName_LB->setObjectName(QStringLiteral("personName_LB"));

        verticalLayout->addWidget(personName_LB);

        verticalLayoutWidget_2 = new QWidget(identify);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(130, 40, 251, 151));
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

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        personName_LE = new QLineEdit(verticalLayoutWidget_2);
        personName_LE->setObjectName(QStringLiteral("personName_LE"));

        verticalLayout_2->addWidget(personName_LE);

        horizontalLayoutWidget = new QWidget(identify);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(180, 240, 194, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        run_PB = new QPushButton(horizontalLayoutWidget);
        run_PB->setObjectName(QStringLiteral("run_PB"));

        horizontalLayout->addWidget(run_PB);

        abort_pb = new QPushButton(horizontalLayoutWidget);
        abort_pb->setObjectName(QStringLiteral("abort_pb"));

        horizontalLayout->addWidget(abort_pb);


        retranslateUi(identify);

        QMetaObject::connectSlotsByName(identify);
    } // setupUi

    void retranslateUi(QDialog *identify)
    {
        identify->setWindowTitle(QApplication::translate("identify", "Dialog", Q_NULLPTR));
        modelDir_PB->setText(QApplication::translate("identify", "Model Dir", Q_NULLPTR));
        dataDir_PB->setText(QApplication::translate("identify", "Data Dir", Q_NULLPTR));
        personName_LB->setText(QApplication::translate("identify", "Video Input", Q_NULLPTR));
        personName_LE->setText(QApplication::translate("identify", "0", Q_NULLPTR));
        run_PB->setText(QApplication::translate("identify", "Run", Q_NULLPTR));
        abort_pb->setText(QApplication::translate("identify", "Abort", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class identify: public Ui_identify {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IDENTIFY_H

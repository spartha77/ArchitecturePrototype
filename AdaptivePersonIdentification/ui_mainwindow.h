/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRegister;
    QAction *actionAdaptivePersonIdentify;
    QAction *actionHumanDetection;
    QAction *actionBodyIdentification;
    QAction *actionFaceDetection;
    QAction *actionFaceIdentification;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *BackgroundImage;
    QMenuBar *menuBar;
    QMenu *menuFeatures;
    QMenu *menuIdentify;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(658, 332);
        MainWindow->setAutoFillBackground(true);
        actionRegister = new QAction(MainWindow);
        actionRegister->setObjectName(QString::fromUtf8("actionRegister"));
        actionAdaptivePersonIdentify = new QAction(MainWindow);
        actionAdaptivePersonIdentify->setObjectName(QString::fromUtf8("actionAdaptivePersonIdentify"));
        actionHumanDetection = new QAction(MainWindow);
        actionHumanDetection->setObjectName(QString::fromUtf8("actionHumanDetection"));
        actionBodyIdentification = new QAction(MainWindow);
        actionBodyIdentification->setObjectName(QString::fromUtf8("actionBodyIdentification"));
        actionFaceDetection = new QAction(MainWindow);
        actionFaceDetection->setObjectName(QString::fromUtf8("actionFaceDetection"));
        actionFaceIdentification = new QAction(MainWindow);
        actionFaceIdentification->setObjectName(QString::fromUtf8("actionFaceIdentification"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        BackgroundImage = new QLabel(centralWidget);
        BackgroundImage->setObjectName(QString::fromUtf8("BackgroundImage"));

        verticalLayout->addWidget(BackgroundImage);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 658, 21));
        menuFeatures = new QMenu(menuBar);
        menuFeatures->setObjectName(QString::fromUtf8("menuFeatures"));
        menuIdentify = new QMenu(menuFeatures);
        menuIdentify->setObjectName(QString::fromUtf8("menuIdentify"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFeatures->menuAction());
        menuFeatures->addAction(actionRegister);
        menuFeatures->addAction(menuIdentify->menuAction());
        menuIdentify->addAction(actionAdaptivePersonIdentify);
        menuIdentify->addAction(actionHumanDetection);
        menuIdentify->addAction(actionBodyIdentification);
        menuIdentify->addAction(actionFaceDetection);
        menuIdentify->addAction(actionFaceIdentification);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionRegister->setText(QCoreApplication::translate("MainWindow", "Register", nullptr));
        actionAdaptivePersonIdentify->setText(QCoreApplication::translate("MainWindow", "Adaptive person identify", nullptr));
        actionHumanDetection->setText(QCoreApplication::translate("MainWindow", "Human Detection", nullptr));
        actionBodyIdentification->setText(QCoreApplication::translate("MainWindow", "Body Identification", nullptr));
        actionFaceDetection->setText(QCoreApplication::translate("MainWindow", "Face Detection", nullptr));
        actionFaceIdentification->setText(QCoreApplication::translate("MainWindow", "Face Identification", nullptr));
        BackgroundImage->setText(QString());
        menuFeatures->setTitle(QCoreApplication::translate("MainWindow", "Skills", nullptr));
        menuIdentify->setTitle(QCoreApplication::translate("MainWindow", "Identify", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

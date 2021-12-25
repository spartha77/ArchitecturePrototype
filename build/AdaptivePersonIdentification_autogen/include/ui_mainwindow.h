/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(658, 332);
        MainWindow->setAutoFillBackground(true);
        actionRegister = new QAction(MainWindow);
        actionRegister->setObjectName(QStringLiteral("actionRegister"));
        actionAdaptivePersonIdentify = new QAction(MainWindow);
        actionAdaptivePersonIdentify->setObjectName(QStringLiteral("actionAdaptivePersonIdentify"));
        actionHumanDetection = new QAction(MainWindow);
        actionHumanDetection->setObjectName(QStringLiteral("actionHumanDetection"));
        actionBodyIdentification = new QAction(MainWindow);
        actionBodyIdentification->setObjectName(QStringLiteral("actionBodyIdentification"));
        actionFaceDetection = new QAction(MainWindow);
        actionFaceDetection->setObjectName(QStringLiteral("actionFaceDetection"));
        actionFaceIdentification = new QAction(MainWindow);
        actionFaceIdentification->setObjectName(QStringLiteral("actionFaceIdentification"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        BackgroundImage = new QLabel(centralWidget);
        BackgroundImage->setObjectName(QStringLiteral("BackgroundImage"));

        verticalLayout->addWidget(BackgroundImage);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 658, 21));
        menuFeatures = new QMenu(menuBar);
        menuFeatures->setObjectName(QStringLiteral("menuFeatures"));
        menuIdentify = new QMenu(menuFeatures);
        menuIdentify->setObjectName(QStringLiteral("menuIdentify"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionRegister->setText(QApplication::translate("MainWindow", "Register", Q_NULLPTR));
        actionAdaptivePersonIdentify->setText(QApplication::translate("MainWindow", "Adaptive person identify", Q_NULLPTR));
        actionHumanDetection->setText(QApplication::translate("MainWindow", "Human Detection", Q_NULLPTR));
        actionBodyIdentification->setText(QApplication::translate("MainWindow", "Body Identification", Q_NULLPTR));
        actionFaceDetection->setText(QApplication::translate("MainWindow", "Face Detection", Q_NULLPTR));
        actionFaceIdentification->setText(QApplication::translate("MainWindow", "Face Identification", Q_NULLPTR));
        BackgroundImage->setText(QString());
        menuFeatures->setTitle(QApplication::translate("MainWindow", "Skills", Q_NULLPTR));
        menuIdentify->setTitle(QApplication::translate("MainWindow", "Identify", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

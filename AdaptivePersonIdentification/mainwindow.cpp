#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registration.h"
#include "identify.h"
//#include "humamdetection.h"
//#include "facedetection.h"
//#include "bodyidentification.h"
//#include "faceidentification.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/resource/image/my_logo.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    palette.setColor(this->menuBar()->backgroundRole(), Qt::blue);
    palette.setColor(this->menuBar()->foregroundRole(), Qt::red);
    this->menuBar()->setPalette(palette);

    displayLabel = new QLabel(this);
    displayLabel->move(100,100);

}

MainWindow::MainWindow(MainWindow& MainWindow_obj)
{
    this->pixmapImage = MainWindow_obj.pixmapImage;
}

void MainWindow:: operator =(MainWindow& MainWindow_obj)
{
    this->pixmapImage = MainWindow_obj.pixmapImage;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRegister_triggered()
{
    registration register_obj(this);
    register_obj.setModal(true);
    register_obj.setWindowTitle("Register");
    register_obj.exec();
}

void MainWindow::on_actionAdaptivePersonIdentify_triggered()
{
    identify adaptivePersonIdentify_obj(this);
    adaptivePersonIdentify_obj.setModal(true);
    adaptivePersonIdentify_obj.setWindowTitle("Adaptive Person Identify");
    adaptivePersonIdentify_obj.m_SkillType = SkillType::IDENTIFY_PERSON;
    adaptivePersonIdentify_obj.exec();
}

void MainWindow::on_actionHumanDetection_triggered()
{
    identify humanDetection_obj(this);
    humanDetection_obj.setModal(true);
    humanDetection_obj.setWindowTitle("Human Detection");
    humanDetection_obj.m_SkillType = SkillType::HUMAN_DETECTION;
    humanDetection_obj.exec();

}

void MainWindow::on_actionBodyIdentification_triggered()
{
    identify bodyIdentification_obj(this);
    bodyIdentification_obj.setModal(true);
    bodyIdentification_obj.setWindowTitle("Body Identification");
    bodyIdentification_obj.m_SkillType = SkillType::BODY_ID;
    bodyIdentification_obj.exec();
}

void MainWindow::on_actionFaceDetection_triggered()
{
    identify faceDetection_obj(this);
    faceDetection_obj.setModal(true);
    faceDetection_obj.setWindowTitle("Face Detection");
    faceDetection_obj.m_SkillType = SkillType::FACE_DETECTION;
    faceDetection_obj.exec();
}

void MainWindow::on_actionFaceIdentification_triggered()
{
    identify faceIdentification_obj(this);
    faceIdentification_obj.setModal(true);
    faceIdentification_obj.setWindowTitle("Face Identification");
    faceIdentification_obj.m_SkillType = SkillType::FACE_IDENTIFICATION;
    faceIdentification_obj.exec();
}


void MainWindow::showImage()
{
    QPalette palette;
    QBrush backgroundColour(QColor(255,255,255, 255));
    backgroundColour.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Background,backgroundColour);
    this->setPalette(palette);

    QSize mainWindowSize = this->size();
    displayLabel->setStyleSheet("QLabel { background-color : Red; color : blue; }");
    displayLabel->setAlignment(Qt::AlignCenter);
    displayLabel->setFixedSize(mainWindowSize.width()*0.8, mainWindowSize.height()*0.8);
    displayLabel->setScaledContents(true);
    displayLabel->move(mainWindowSize.width()*0.1,mainWindowSize.height()*0.1);
    displayLabel->setPixmap(this->pixmapImage);
    displayLabel->show();

}

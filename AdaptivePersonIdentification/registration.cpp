#include "registration.h"
#include "ui_registration.h"
#include <CommandManager.h>
//#include <CommandReturnsNoOutputData.h>
#include <RegisterPersonCommandExecutor.h>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <memory>

QImage getQImage(cv::Mat &timage){

    static QVector<QRgb> colorTable;

    if (colorTable.isEmpty()){
        for (int i = 0; i < 256; i++){
            colorTable.push_back(qRgb(i, i, i));
        }
    }

    if (timage.type() == CV_8UC3){
        QImage temp = QImage((const unsigned char*)(timage.data), timage.cols, timage.rows, timage.step, QImage::Format_RGB888);
        return temp.rgbSwapped();
    }
    else if (timage.type() == CV_8UC1){
        QImage temp = QImage((const unsigned char*)(timage.data), timage.cols, timage.rows, timage.step, QImage::Format_Indexed8);
        temp.setColorTable(colorTable);
        return temp;
    }
}

void registration::OnImageNotified(cv::Mat* notifiedImage)
{

    QImage matQimage = getQImage(*notifiedImage);
    QPixmap pixmap(QPixmap::fromImage(matQimage));
    this->MainWindow_obs->pixmapImage = pixmap;
    emit imageReceived();
    cv::waitKey(5);
}

std::function <void (cv::Mat* mat)> registration::GetImageNotifiedFunction()
{
    return [this](cv::Mat* mat){ return this->OnImageNotified(mat);};
}


registration::registration(MainWindow* MainWindow_obj,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registration)
{
    ui->setupUi(this);
    this->MainWindow_obs = MainWindow_obj;
    connect(this,SIGNAL(imageReceived()),this->MainWindow_obs,SLOT(showImage()));
    connect(ui->abort_pb, SIGNAL(clicked()), this, SLOT(close()));
    run_PB_status();

}

registration::~registration()
{
    delete ui;
}


void registration::run_PB_status()
{
    if(ui->batchMode_RB->isChecked())
    {
        if(ui->modelDir_LE->text().isEmpty() || ui->dataDir_LE->text().isEmpty() || ui->imageDir_LE->text().isEmpty() )
        {

            ui->run_PB->setDisabled(true);

        }
        else
        {

            ui->run_PB->setDisabled(false);
        }
    }
    else if(ui->personName_RB->isChecked())
    {
        if(ui->modelDir_LE->text().isEmpty() || ui->dataDir_LE->text().isEmpty() || ui->personName_LE->text().isEmpty()|| ui->imageDir_LE->text().isEmpty() )
        {

            ui->run_PB->setDisabled(true);

        }
        else
        {

            ui->run_PB->setDisabled(false);
        }
    }
    else
    {
        if(ui->modelDir_LE->text().isEmpty() || ui->dataDir_LE->text().isEmpty() || ui->livePersonName_LE->text().isEmpty()|| ui->imageDir_LE->text().isEmpty() )
        {

            ui->run_PB->setDisabled(true);

        }
        else
        {

            ui->run_PB->setDisabled(false);
        }
    }
}

void registration::on_modelDir_PB_clicked()
{
    QString model_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    ui->modelDir_LE->setText(model_dir);

}

void registration::on_dataDir_PB_clicked()
{
    QString data_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    ui->dataDir_LE->setText(data_dir);

}

void registration::on_imageDir_PB_clicked()
{
    QString data_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
        "/home",
        QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks);

    ui->imageDir_LE->setText(data_dir);

}
void registration::on_run_PB_clicked()
{
   //this->close();
   AdaptiveHumanTracker::RegisterPersonCommandExecutorInputData registerCmdInputData;
   registerCmdInputData.modelDirectoryPath =ui->modelDir_LE->text().toStdString();
   registerCmdInputData.dataDirectoryPath = ui->dataDir_LE->text().toStdString();
   

   auto onNotifyCb = GetImageNotifiedFunction();
   m_executor = std::unique_ptr<RegisterPersonCommandExecutor>(new RegisterPersonCommandExecutor(onNotifyCb, false));
   //auto execMethod = executor.GetSkillExecutionMethod();
   //using execType = decltype(execMethod);

   if (ui->batchMode_RB->isChecked())
   {
       QDir dir(ui->imageDir_LE->text());
       QFileInfoList list = dir.entryInfoList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
       foreach(QFileInfo finfo, list) {
       if (finfo.isDir()) {                      
           registerCmdInputData.imageDirectoryPath = ui->imageDir_LE->text().toStdString() + "/" + finfo.fileName().toStdString();
           registerCmdInputData.registeredName = finfo.fileName().toStdString();
           registerCmdInputData.registrationMode = AdaptiveHumanTracker::FaceRegistrationMode::OFFLINE;
           std::unique_ptr<NullData> otNullData = AdaptiveHumanTracker::SkillsManager<AdaptiveHumanTracker::RegisterPersonCommandExecutorInputData, NullData>::GetInstance()->Execute<RegisterPersonCommandExecutor>(registerCmdInputData, *m_executor);
        }
     }

   }
   else if(ui->personName_RB->isChecked())
   {
       registerCmdInputData.registeredName = ui->personName_LE->text().toStdString();
       registerCmdInputData.imageDirectoryPath = ui->imageDir_LE->text().toStdString() + "/" + registerCmdInputData.registeredName;
       registerCmdInputData.registrationMode = AdaptiveHumanTracker::FaceRegistrationMode::OFFLINE;

       const QFileInfo outputDir(QString::fromStdString(registerCmdInputData.imageDirectoryPath));
       //std::unique_ptr<NullData> otNullData = AdaptiveHumanTracker::SkillsManager<RegisterPersonCommandExecutorInputData, NullData>::GetInstance()->Execute<execType>(registerCmdInputData, execMethod);
       if ((outputDir.exists()) || (outputDir.isDir()))
       {
           std::unique_ptr<NullData> otNullData = AdaptiveHumanTracker::SkillsManager<AdaptiveHumanTracker::RegisterPersonCommandExecutorInputData, NullData>::GetInstance()->Execute<RegisterPersonCommandExecutor>(registerCmdInputData, *m_executor);
       }
       else
       {
           QMessageBox::critical(this, tr("Adaptive Person Identification"),
                                          tr("Mismatch in Person name and Image directory path. Please provide correct name to register"),
                                          QMessageBox::Ok);
       }

   }
   else
   {
       registerCmdInputData.registeredName = ui->livePersonName_LE->text().toStdString();
       registerCmdInputData.imageDirectoryPath = ui->imageDir_LE->text().toStdString() + "/" + registerCmdInputData.registeredName;
       QString qt_image_directory_path = QString::fromStdString(registerCmdInputData.imageDirectoryPath);
       if (!QDir(qt_image_directory_path).exists())
       {
           QDir().mkdir(qt_image_directory_path);
       }
       registerCmdInputData.registrationMode = AdaptiveHumanTracker::FaceRegistrationMode::ONLINE;
       std::unique_ptr<NullData> otNullData = AdaptiveHumanTracker::SkillsManager<AdaptiveHumanTracker::RegisterPersonCommandExecutorInputData, NullData>::GetInstance()->Execute<RegisterPersonCommandExecutor>(registerCmdInputData, *m_executor);

   }

   m_executor.reset();

   this->MainWindow_obs->displayLabel->setVisible(false);

   QPixmap bkgnd(":/resource/image/my_logo.jpg");
   bkgnd = bkgnd.scaled(this->size());

   QPalette palette;
   palette.setBrush(QPalette::Background, bkgnd);
   this->MainWindow_obs->setPalette(palette);

}

void registration::on_abort_pb_clicked()
{

}

void registration::on_personName_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

void registration::on_dataDir_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

void registration::on_modelDir_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

void registration::on_batchMode_RB_clicked()
{
   /*if(ui->modelDir_LE->text().isEmpty() || ui->dataDir_LE->text().isEmpty())
   {

       ui->run_PB->setDisabled(true);

   }
   else
   {
       ui->run_PB->setEnabled(true);
   }*/
   run_PB_status();
   ui->personName_LE->setDisabled(true);
   ui->livePersonName_LE->setDisabled(true);

}

void registration::on_personName_RB_clicked()
{
    run_PB_status();
    ui->personName_LE->setEnabled(true);
    ui->livePersonName_LE->setDisabled(true);
}

void registration::on_imageDir_LE_textChanged(const QString &arg1)
{
     run_PB_status();
}

void registration::on_liveRegister_RB_clicked()
{
    run_PB_status();
    ui->livePersonName_LE->setEnabled(true);
    ui->personName_LE->setDisabled(true);

}

void registration::on_livePersonName_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

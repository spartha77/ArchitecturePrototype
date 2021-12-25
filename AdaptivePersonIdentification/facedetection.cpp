//#include <CommandManager.h>
//#include <CommandNullReturnData.h>
//#include <facedetectionCommandExecutor.h>
#include "facedetection.h"
#include "ui_facedetection.h"
#include <QFileDialog>

facedetection::facedetection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::facedetection)
{
    ui->setupUi(this);
    connect(ui->abort_pb, SIGNAL(clicked()), this, SLOT(close()));
    run_PB_status();
}

facedetection::~facedetection()
{
    delete ui;
}

void facedetection::run_PB_status()
{
    if(ui->modelDir_LE->text().isEmpty() || ui->dataDir_LE->text().isEmpty() || ui->personName_LE->text().isEmpty() )
    {

        ui->run_PB->setDisabled(true);


    }
    else
    {

        ui->run_PB->setDisabled(false);
    }
}

void facedetection::on_modelDir_PB_clicked()
{
    QString model_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    ui->modelDir_LE->setText(model_dir);

}

void facedetection::on_dataDir_PB_clicked()
{
    QString data_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    ui->dataDir_LE->setText(data_dir);
}

void facedetection::on_run_PB_clicked()
{
/*
    FaceDetectionCommandExecutorInputData FaceDetectionCmdInputData;

    FaceDetectionCmdInputData.modelDirectoryPath = ui->modelDir_LE->text().toStdString();
    FaceDetectionCmdInputData.dataDirectoryPath = ui->dataDir_LE->text().toStdString();

    FaceDetectionCommandExecutor executor;
    // Final test 
    std::unique_ptr<NullData> otNullData = CommandManager::GetInstance()->Execute< CommandNullReturnData, FaceDetectionCommandExecutor, FaceDetectionCommandExecutorInputData, NullData>(FaceDetectionCmdInputData, executor);
*/
}

void facedetection::on_personName_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

void facedetection::on_dataDir_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

void facedetection::on_modelDir_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

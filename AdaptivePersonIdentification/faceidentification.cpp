//#include <CommandManager.h>
//#include <CommandNullReturnData.h>
//#include <FaceIdentificationCommandExecutor.h>
#include "faceidentification.h"
#include "ui_faceidentification.h"
#include <QFileDialog>

faceidentification::faceidentification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::faceidentification)
{
    ui->setupUi(this);
    connect(ui->abort_pb, SIGNAL(clicked()), this, SLOT(close()));
    run_PB_status();
}

faceidentification::~faceidentification()
{
    delete ui;
}

void faceidentification::run_PB_status()
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

void faceidentification::on_modelDir_PB_clicked()
{
    QString model_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    ui->modelDir_LE->setText(model_dir);

}

void faceidentification::on_dataDir_PB_clicked()
{
    QString data_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    ui->dataDir_LE->setText(data_dir);
}

void faceidentification::on_run_PB_clicked()
{
/*
    FaceIdentificationCommandExecutorInputData FaceIdentificationCmdInputData;

    FaceIdentificationCmdInputData.modelDirectoryPath = ui->modelDir_LE->text().toStdString();
    FaceIdentificationCmdInputData.dataDirectoryPath = ui->dataDir_LE->text().toStdString();

    FaceIdentificationCommandExecutor executor;
    // Final test 
    std::unique_ptr<NullData> otNullData = CommandManager::GetInstance()->Execute< CommandNullReturnData, FaceIdentificationCommandExecutor, FaceIdentificationCommandExecutorInputData, NullData>(FaceIdentificationCmdInputData, executor);
*/
}

void faceidentification::on_personName_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

void faceidentification::on_dataDir_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

void faceidentification::on_modelDir_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

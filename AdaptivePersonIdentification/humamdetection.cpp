//#include <CommandManager.h>
//#include <CommandNullReturnData.h>
//#include <HumanDetectionCommandExecutor.h>
#include "humamdetection.h"
#include "ui_humamdetection.h"
#include <QFileDialog>

humandetection::humandetection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::humandetection)
{
    ui->setupUi(this);
    connect(ui->abort_pb, SIGNAL(clicked()), this, SLOT(close()));
    run_PB_status();
}

humandetection::~humandetection()
{
    delete ui;
}

void humandetection::run_PB_status()
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

void humandetection::on_modelDir_PB_clicked()
{
    QString model_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    ui->modelDir_LE->setText(model_dir);

}

void humandetection::on_dataDir_PB_clicked()
{
    QString data_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    ui->dataDir_LE->setText(data_dir);
}

void humandetection::on_run_PB_clicked()
{
/*
        HumanDetectionCommandExecutorInputData HumanDetectionCmdInputData;

        HumanDetectionCmdInputData.modelDirectoryPath = ui->modelDir_LE->text().toStdString();
        HumanDetectionCmdInputData.dataDirectoryPath = ui->dataDir_LE->text().toStdString();

        HumanDetectionCommandExecutor executor;
        // Final test 
        std::unique_ptr<NullData> otNullData = CommandManager::GetInstance()->Execute< CommandNullReturnData, HumanDetectionCommandExecutor, HumanDetectionCommandExecutorInputData, NullData>(HumanDetectionCmdInputData, executor);
*/
}

void humandetection::on_personName_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

void humandetection::on_dataDir_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

void humandetection::on_modelDir_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

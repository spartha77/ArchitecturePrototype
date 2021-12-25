//#include <CommandManager.h>
//#include <CommandNullReturnData.h>
//#include <BodyIdCommandExecutor.h>
#include "bodyidentification.h"
#include "ui_bodyidentification.h"
#include <QFileDialog>

bodyidentification::bodyidentification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bodyidentification)
{
    ui->setupUi(this);
    connect(ui->abort_pb, SIGNAL(clicked()), this, SLOT(close()));
    run_PB_status();
}

bodyidentification::~bodyidentification()
{
    delete ui;
}

void bodyidentification::run_PB_status()
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

void bodyidentification::on_modelDir_PB_clicked()
{
    QString model_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    ui->modelDir_LE->setText(model_dir);

}

void bodyidentification::on_dataDir_PB_clicked()
{
    QString data_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    ui->dataDir_LE->setText(data_dir);
}

void bodyidentification::on_run_PB_clicked()
{
/*
    BodyIdCommandExecutorInputData BodyIdCmdInputData;

    BodyIdCmdInputData.modelDirectoryPath = ui->modelDir_LE->text().toStdString();
    BodyIdCmdInputData.dataDirectoryPath = ui->dataDir_LE->text().toStdString();

    BodyIdCommandExecutor executor;
    // Final test 
    std::unique_ptr<NullData> otNullData = CommandManager::GetInstance()->Execute< CommandNullReturnData, BodyIdCommandExecutor, BodyIdCommandExecutorInputData, NullData>(BodyIdCmdInputData, executor);
*/
}

void bodyidentification::on_personName_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

void bodyidentification::on_dataDir_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

void bodyidentification::on_modelDir_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

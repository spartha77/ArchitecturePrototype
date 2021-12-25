#include <CommandManager.h>
//#include <CommandReturnsNoOutputData.h>
#include <IdentifyPersonCommandExecutor.h>
#include <HumanDetectionCommandExecutor.h>
#include <BodyIdCommandExecutor.h>
#include <FaceDetectionCommandExecutor.h>
#include <FaceIdentificationCommandExecutor.h>
#include "identify.h"
#include "ui_identify.h"
#include <QFileDialog>
#include <QCloseEvent>


identify::identify(MainWindow* MainWindow_obj,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::identify)
{
    ui->setupUi(this);
    this->MainWindow_obs = MainWindow_obj;
    connect(this,SIGNAL(imageReceived()),this->MainWindow_obs,SLOT(showImage()));
    connect(ui->abort_pb, SIGNAL(clicked()), this, SLOT(on_abort_pb_clicked()));
    run_PB_status();
}

identify::~identify()
{
    delete ui;
}

void identify::run_PB_status()
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

void identify::on_modelDir_PB_clicked()
{
    QString model_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    ui->modelDir_LE->setText(model_dir);

}

void identify::on_dataDir_PB_clicked()
{
    QString data_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    ui->dataDir_LE->setText(data_dir);
}

void identify::abort()
{
    if (m_commandRunningStatus == false)
        return;

    switch (this->m_SkillType)
    {
    case SkillType::IDENTIFY_PERSON:
        AdaptiveHumanTracker::SkillsManager<IdentifyPersonCommandExecutorInputData, NullData>::GetInstance()->Terminate();
        break;
    case SkillType::HUMAN_DETECTION:
        AdaptiveHumanTracker::SkillsManager<HumanDetectionCommandExecutorInputData, NullData>::GetInstance()->Terminate();
        break;
    case SkillType::BODY_ID:
        AdaptiveHumanTracker::SkillsManager<BodyIdCommandExecutorInputData, NullData>::GetInstance()->Terminate();
        break;
    case SkillType::FACE_DETECTION:
        AdaptiveHumanTracker::SkillsManager<FaceDetectionCommandExecutorInputData, NullData>::GetInstance()->Terminate();
        break;
    case SkillType::FACE_IDENTIFICATION:
        AdaptiveHumanTracker::SkillsManager<FaceIdentificationCommandExecutorInputData, NullData>::GetInstance()->Terminate();
        break;
    }
}
void identify::on_abort_pb_clicked()
{
    abort();
}

void identify::closeEvent(QCloseEvent* closeEvent)
{
    abort();
    closeEvent->accept();
}
void identify::on_run_PB_clicked()
{
    RAIIObject raiiObject([this]() 
        {
            this->m_commandRunningStatus = false; 

            if (m_IdentifyPersonExecutor)
                m_IdentifyPersonExecutor.reset();
            else if (m_BodyIdExeutor)
                m_BodyIdExeutor.reset();
            else if (m_HumanDetectionExeutor)
                m_HumanDetectionExeutor.reset();
            else if (m_FaceDetectionExeutor)
                m_FaceDetectionExeutor.reset();
            else if (m_FaceIdentificationExeutor)
                m_FaceIdentificationExeutor.reset();
        });

    m_commandRunningStatus = true;
    //this->close();
    if(this->m_SkillType == SkillType::IDENTIFY_PERSON)
    {
        IdentifyPersonCommandExecutorInputData IdentifyCmdInputData;

        IdentifyCmdInputData.modelDirectoryPath = ui->modelDir_LE->text().toStdString();
        IdentifyCmdInputData.dataDirectoryPath = ui->dataDir_LE->text().toStdString();

        auto onNotifyCb = GetImageNotifiedFunction();
        //IdentifyPersonCommandExecutor executor(onNotifyCb,false);
        m_IdentifyPersonExecutor = std::unique_ptr<IdentifyPersonCommandExecutor>(new IdentifyPersonCommandExecutor(onNotifyCb, false));
        // Final test
        //auto execMethod = executor.GetSkillExecutionMethod();
        //using execType = decltype(execMethod);
        std::unique_ptr<NullData> otNullData = AdaptiveHumanTracker::SkillsManager<IdentifyPersonCommandExecutorInputData, NullData>::GetInstance()->Execute<IdentifyPersonCommandExecutor>(IdentifyCmdInputData, *m_IdentifyPersonExecutor);

    }

    if (this->m_SkillType == SkillType::HUMAN_DETECTION)
    {
        HumanDetectionCommandExecutorInputData HumanDetectionCmdInputData;

        HumanDetectionCmdInputData.modelDirectoryPath = ui->modelDir_LE->text().toStdString();
        HumanDetectionCmdInputData.dataDirectoryPath = ui->dataDir_LE->text().toStdString();

        auto onNotifyCb = GetImageNotifiedFunction();
        //HumanDetectionCommandExecutor executor(onNotifyCb,false);
        m_HumanDetectionExeutor = std::unique_ptr<HumanDetectionCommandExecutor>(new HumanDetectionCommandExecutor(onNotifyCb, false));
        // Final test
        //auto execMethod = executor.GetSkillExecutionMethod();
        //using execType = decltype(execMethod);
        std::unique_ptr<NullData> otNullData = AdaptiveHumanTracker::SkillsManager<HumanDetectionCommandExecutorInputData, NullData>::GetInstance()->Execute<HumanDetectionCommandExecutor>(HumanDetectionCmdInputData, *m_HumanDetectionExeutor);
    }
    
    if (this->m_SkillType == SkillType::BODY_ID)
    {
        BodyIdCommandExecutorInputData BodyIdCmdInputData;

        BodyIdCmdInputData.modelDirectoryPath = ui->modelDir_LE->text().toStdString();
        BodyIdCmdInputData.dataDirectoryPath = ui->dataDir_LE->text().toStdString();

        auto onNotifyCb = GetImageNotifiedFunction();
        //BodyIdCommandExecutor executor(onNotifyCb,false);
        m_BodyIdExeutor = std::unique_ptr<BodyIdCommandExecutor>(new BodyIdCommandExecutor(onNotifyCb, false));
        // Final test
        //auto execMethod = executor.GetSkillExecutionMethod();
        //using execType = decltype(execMethod);
        std::unique_ptr<NullData> otNullData = AdaptiveHumanTracker::SkillsManager<BodyIdCommandExecutorInputData, NullData>::GetInstance()->Execute<BodyIdCommandExecutor>(BodyIdCmdInputData, *m_BodyIdExeutor);
    }
    if (this->m_SkillType == SkillType::FACE_DETECTION)
    {
        FaceDetectionCommandExecutorInputData FaceDetectionCmdInputData;

        FaceDetectionCmdInputData.modelDirectoryPath = ui->modelDir_LE->text().toStdString();
        FaceDetectionCmdInputData.dataDirectoryPath = ui->dataDir_LE->text().toStdString();

        auto onNotifyCb = GetImageNotifiedFunction();
        //FaceDetectionCommandExecutor executor(onNotifyCb,false);
        m_FaceDetectionExeutor = std::unique_ptr<FaceDetectionCommandExecutor>(new FaceDetectionCommandExecutor(onNotifyCb, false));
        // Final test
        //auto execMethod = executor.GetSkillExecutionMethod();
        //using execType = decltype(execMethod);
        std::unique_ptr<NullData> otNullData = AdaptiveHumanTracker::SkillsManager<FaceDetectionCommandExecutorInputData, NullData>::GetInstance()->Execute<FaceDetectionCommandExecutor>(FaceDetectionCmdInputData, *m_FaceDetectionExeutor);
    }
    if (this->m_SkillType == SkillType::FACE_IDENTIFICATION)
    {
        FaceIdentificationCommandExecutorInputData FaceIdentificationCmdInputData;

        FaceIdentificationCmdInputData.modelDirectoryPath = ui->modelDir_LE->text().toStdString();
        FaceIdentificationCmdInputData.dataDirectoryPath = ui->dataDir_LE->text().toStdString();

        auto onNotifyCb = GetImageNotifiedFunction();
        //FaceIdentificationCommandExecutor executor(onNotifyCb,false);
        m_FaceIdentificationExeutor = std::unique_ptr<FaceIdentificationCommandExecutor>(new FaceIdentificationCommandExecutor(onNotifyCb, false));
        //m_FaceIdentificationExeutor = new FaceIdentificationCommandExecutor(onNotifyCb, false);
        // Final test
        //auto exec//Method = executor.GetSkillExecutionMethod();
        //using execType = decltype(execMethod);
        std::unique_ptr<NullData> otNullData = AdaptiveHumanTracker::SkillsManager<FaceIdentificationCommandExecutorInputData, NullData>::GetInstance()->Execute<FaceIdentificationCommandExecutor>(FaceIdentificationCmdInputData, *m_FaceIdentificationExeutor);
    }

    


}

void identify::on_personName_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

void identify::on_dataDir_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

void identify::on_modelDir_LE_textChanged(const QString &arg1)
{
    run_PB_status();
}

void identify::OnImageNotified(cv::Mat* notifiedImage)
{

    QImage matQimage = this->getQImage(*notifiedImage);
    QPixmap pixmap(QPixmap::fromImage(matQimage));
    this->MainWindow_obs->pixmapImage = pixmap;
    emit imageReceived();
    cv::waitKey(1);
}

std::function <void (cv::Mat* mat)> identify::GetImageNotifiedFunction()
{
    return [this](cv::Mat* mat) mutable { return this->OnImageNotified(mat);};
}

QImage identify::getQImage(cv::Mat &timage){

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

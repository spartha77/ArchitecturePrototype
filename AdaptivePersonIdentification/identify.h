#pragma once
#ifndef IDENTIFY_H
#define IDENTIFY_H

#include <QDialog>
#include "mainwindow.h"

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

namespace Ui {
class identify;
}
class IdentifyPersonCommandExecutor;
class HumanDetectionCommandExecutor;
class BodyIdCommandExecutor;
class FaceDetectionCommandExecutor;
class FaceIdentificationCommandExecutor;

enum class SkillType
{
    IDENTIFY_PERSON,
    HUMAN_DETECTION,
    BODY_ID,
    FACE_DETECTION,
    FACE_IDENTIFICATION,
    REGISTRATION
};
class RAIIObject
{
private:
    std::function<void()> m_FuncReleaseAll;
public:
    RAIIObject(std::function<void()> func) { m_FuncReleaseAll = func; };
    ~RAIIObject() { m_FuncReleaseAll(); };
};
class identify : public QDialog
{
    Q_OBJECT

    MainWindow* MainWindow_obs;
    std::unique_ptr<IdentifyPersonCommandExecutor> m_IdentifyPersonExecutor;
    std::unique_ptr<HumanDetectionCommandExecutor> m_HumanDetectionExeutor;
    std::unique_ptr<BodyIdCommandExecutor> m_BodyIdExeutor;
    std::unique_ptr<FaceDetectionCommandExecutor> m_FaceDetectionExeutor;
    std::unique_ptr <FaceIdentificationCommandExecutor> m_FaceIdentificationExeutor;
    bool m_commandRunningStatus = false;

public:
    SkillType m_SkillType;;
    explicit identify(MainWindow* MainWindow_obj,QWidget *parent = 0);
    ~identify();

signals:
    void imageReceived();

private slots:
    void on_modelDir_PB_clicked();

    void on_dataDir_PB_clicked();

    void on_personName_LE_textChanged(const QString &arg1);

    void on_run_PB_clicked();

    void on_abort_pb_clicked();

    void run_PB_status();

    void on_dataDir_LE_textChanged(const QString &arg1);

    void on_modelDir_LE_textChanged(const QString &arg1);

    void OnImageNotified(cv::Mat* notifiedImage);

    std::function <void (cv::Mat* mat)> GetImageNotifiedFunction();

    QImage getQImage(cv::Mat &timage);

    void closeEvent(QCloseEvent* eventt) override;

    void abort();

private:
    Ui::identify *ui;
};

#endif // IDENTIFY_H

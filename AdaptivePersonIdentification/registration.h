#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include "mainwindow.h"

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

namespace Ui {
class registration;
}
class RegisterPersonCommandExecutor;
class registration : public QDialog
{
    Q_OBJECT

    MainWindow* MainWindow_obs;
    std::unique_ptr< RegisterPersonCommandExecutor> m_executor;

public:
    explicit registration(MainWindow* MainWindow_obj,QWidget *parent = 0);
    ~registration();
    //void getNotifiedData();

signals:
    void imageReceived();

private slots:
    void on_modelDir_PB_clicked();

    void on_dataDir_PB_clicked();

    void on_imageDir_PB_clicked();

    void on_run_PB_clicked();

    void on_abort_pb_clicked();

    void run_PB_status();

    void on_personName_LE_textChanged(const QString &arg1);

    void on_dataDir_LE_textChanged(const QString &arg1);

    void on_modelDir_LE_textChanged(const QString &arg1);

    void OnImageNotified(cv::Mat* notifiedImage);

    std::function <void (cv::Mat* mat)> GetImageNotifiedFunction();

    void on_batchMode_RB_clicked();

    void on_personName_RB_clicked();

    void on_imageDir_LE_textChanged(const QString &arg1);

    void on_liveRegister_RB_clicked();

    void on_livePersonName_LE_textChanged(const QString &arg1);


private:
    Ui::registration *ui;

};

#endif // REGISTRATION_H

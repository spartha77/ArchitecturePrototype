#pragma once
#ifndef FACEDETECTION_H
#define FACEDETECTION_H

#include <QDialog>

namespace Ui {
class facedetection;
}

class facedetection : public QDialog
{
    Q_OBJECT

public:
    //int selectedFeature;
    explicit facedetection(QWidget *parent = 0);
    ~facedetection();

private slots:
    void on_modelDir_PB_clicked();

    void on_dataDir_PB_clicked();

    void on_personName_LE_textChanged(const QString &arg1);

    void on_run_PB_clicked();

    void run_PB_status();

    void on_dataDir_LE_textChanged(const QString &arg1);

    void on_modelDir_LE_textChanged(const QString &arg1);

private:
    Ui::facedetection *ui;
};

#endif // FACEDETECTION_H

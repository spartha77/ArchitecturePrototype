#pragma once
#ifndef HUMANDETECTION_H
#define HUMANDETECTION_H

#include <QDialog>

namespace Ui {
class humandetection;
}

class humandetection : public QDialog
{
    Q_OBJECT

public:
    int m_SkillType;
    explicit humandetection(QWidget *parent = 0);
    ~humandetection();

private slots:
    void on_modelDir_PB_clicked();

    void on_dataDir_PB_clicked();

    void on_personName_LE_textChanged(const QString &arg1);

    void on_run_PB_clicked();

    void run_PB_status();

    void on_dataDir_LE_textChanged(const QString &arg1);

    void on_modelDir_LE_textChanged(const QString &arg1);

private:
    Ui::humandetection *ui;
};

#endif // HUMANDETECTION_H

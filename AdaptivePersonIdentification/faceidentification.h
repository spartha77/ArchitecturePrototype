#ifndef FACEIDENTIFICATION_H
#define FACEIDENTIFICATION_H

#include <QDialog>

namespace Ui {
class faceidentification;
}

class faceidentification : public QDialog
{
    Q_OBJECT

public:
    explicit faceidentification(QWidget *parent = 0);
    ~faceidentification();

private slots:
    void on_modelDir_PB_clicked();

    void on_dataDir_PB_clicked();

    void on_personName_LE_textChanged(const QString &arg1);

    void on_run_PB_clicked();

    void run_PB_status();

    void on_dataDir_LE_textChanged(const QString &arg1);

    void on_modelDir_LE_textChanged(const QString &arg1);

private:
    Ui::faceidentification *ui;
};

#endif // FACEIDENTIFICATION_H

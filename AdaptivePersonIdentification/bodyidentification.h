#ifndef BODYIDENTIFICATION_H
#define BODYIDENTIFICATION_H

#include <QDialog>

namespace Ui {
class bodyidentification;
}

class bodyidentification : public QDialog
{
    Q_OBJECT

public:
    explicit bodyidentification(QWidget *parent = 0);
    ~bodyidentification();

private slots:
    void on_modelDir_PB_clicked();

    void on_dataDir_PB_clicked();

    void on_personName_LE_textChanged(const QString &arg1);

    void on_run_PB_clicked();

    void run_PB_status();

    void on_dataDir_LE_textChanged(const QString &arg1);

    void on_modelDir_LE_textChanged(const QString &arg1);

private:
    Ui::bodyidentification *ui;
};

#endif // BODYIDENTIFICATION_H

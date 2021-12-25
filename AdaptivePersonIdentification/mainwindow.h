#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QLabel* displayLabel;
    QPixmap pixmapImage;

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(MainWindow& MainWindow_obj);
    void operator =(MainWindow& MainWindow_obj);
    ~MainWindow();

private slots:
    void on_actionRegister_triggered();

    void on_actionAdaptivePersonIdentify_triggered();

    void on_actionHumanDetection_triggered();

    void on_actionFaceIdentification_triggered();

    void on_actionBodyIdentification_triggered();

    void on_actionFaceDetection_triggered();

    void showImage();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

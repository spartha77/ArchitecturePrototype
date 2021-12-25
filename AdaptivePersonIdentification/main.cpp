#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/resource/image/my_logo2.jpg"));
    MainWindow widget;
    widget.setWindowTitle("Adaptive Person Identification");
    widget.showMaximized();
    return app.exec();
}

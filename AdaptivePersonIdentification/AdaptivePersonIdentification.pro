#-------------------------------------------------
#
# Project created by QtCreator 2020-02-07T08:33:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AdaptivePersonIdentification
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    registration.cpp \
    identify.cpp

HEADERS  += mainwindow.h \
    registration.h \
    identify.h

FORMS    += mainwindow.ui \
    registration.ui \
    identify.ui

RESOURCES += \
    resource.qrc

INCLUDEPATH += /opt/intel/openvino_2019.1.133/opencv/include
LIBS += -L/opt/intel/openvino_2019.1.133/opencv/lib \
    /opt/intel/openvino_2019.1.133/opencv/lib/libopencv_calib3d.so.4.1 \
    /opt/intel/openvino_2019.1.133/opencv/lib/libopencv_core.so.4.1 \
    /opt/intel/openvino_2019.1.133/opencv/lib/libopencv_dnn.so.4.1 \
    /opt/intel/openvino_2019.1.133/opencv/lib/libopencv_features2d.so.4.1 \
    /opt/intel/openvino_2019.1.133/opencv/lib/libopencv_flann.so.4.1 \
    /opt/intel/openvino_2019.1.133/opencv/lib/libopencv_gapi.so.4.1 \
    /opt/intel/openvino_2019.1.133/opencv/lib/libopencv_highgui.so.4.1 \
    /opt/intel/openvino_2019.1.133/opencv/lib/libopencv_imgcodecs.so.4.1 \
    /opt/intel/openvino_2019.1.133/opencv/lib/libopencv_imgproc.so.4.1 \
    /opt/intel/openvino_2019.1.133/opencv/lib/libopencv_video.so.4.1 \
    /opt/intel/openvino_2019.1.133/opencv/lib/libopencv_videoio.so.4.1 \

/********************************************************************************
** Form generated from reading UI file 'pclKinect.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PCLKINECT_H
#define UI_PCLKINECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_KinectViewer
{
public:
    QWidget *centralwidget;
    QVTKWidget *qvtkWidget;
    QPushButton *btnRunCamera;
    QVTKWidget *qvtkWidget_2;
    QPushButton *btnResetCameraViewer1;
    QLabel *labelViewer1;
    QLabel *labelViewer2;
    QDoubleSpinBox *valuePosXViewer1;
    QLabel *labelPosXVewer1;
    QLabel *labelPosYVewer1;
    QLabel *labelPosZVewer1;
    QDoubleSpinBox *valuePosYViewer1;
    QDoubleSpinBox *valuePosZViewer1;
    QLabel *labelViewYVewer1;
    QDoubleSpinBox *valueViewYViewer1;
    QDoubleSpinBox *valueViewZViewer1;
    QLabel *labelViewXVewer1;
    QLabel *labelViewZVewer1;
    QDoubleSpinBox *valueViewXViewer1;
    QPushButton *btnGetParametersCameraViewer1;
    QLabel *labelViewZVewer2;
    QLabel *labelPosXVewer2;
    QDoubleSpinBox *valuePosYViewer2;
    QLabel *labelPosZVewer2;
    QDoubleSpinBox *valueViewYViewer2;
    QDoubleSpinBox *valuePosXViewer2;
    QPushButton *btnGetParametersCameraViewer2;
    QLabel *labelPosYVewer2;
    QDoubleSpinBox *valueViewZViewer2;
    QLabel *labelViewYVewer2;
    QLabel *labelViewXVewer2;
    QDoubleSpinBox *valueViewXViewer2;
    QDoubleSpinBox *valuePosZViewer2;
    QPushButton *btnResetCameraViewer2;
    QPushButton *btnViewer1to2;
    QPushButton *btnViewer2to1;
    QDoubleSpinBox *dilateSizeValue;
    QLabel *labelSize;
    QPushButton *btnCaptureCloud;
    QPushButton *btnDilateCloud;
    QPushButton *btnErodeCloud;
    QDoubleSpinBox *erodeSizeValue;
    QLabel *labelSize_2;
    QPushButton *btnInitVisualizers;

    void setupUi(QMainWindow *KinectViewer)
    {
        if (KinectViewer->objectName().isEmpty())
            KinectViewer->setObjectName(QString::fromUtf8("KinectViewer"));
        KinectViewer->resize(1000, 700);
        KinectViewer->setMinimumSize(QSize(0, 0));
        KinectViewer->setMaximumSize(QSize(5000, 5000));
        centralwidget = new QWidget(KinectViewer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        qvtkWidget = new QVTKWidget(centralwidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(40, 120, 400, 400));
        btnRunCamera = new QPushButton(centralwidget);
        btnRunCamera->setObjectName(QString::fromUtf8("btnRunCamera"));
        btnRunCamera->setGeometry(QRect(40, 560, 110, 50));
        btnRunCamera->setCheckable(true);
        qvtkWidget_2 = new QVTKWidget(centralwidget);
        qvtkWidget_2->setObjectName(QString::fromUtf8("qvtkWidget_2"));
        qvtkWidget_2->setGeometry(QRect(570, 120, 400, 400));
        btnResetCameraViewer1 = new QPushButton(centralwidget);
        btnResetCameraViewer1->setObjectName(QString::fromUtf8("btnResetCameraViewer1"));
        btnResetCameraViewer1->setGeometry(QRect(40, 40, 110, 30));
        labelViewer1 = new QLabel(centralwidget);
        labelViewer1->setObjectName(QString::fromUtf8("labelViewer1"));
        labelViewer1->setGeometry(QRect(40, 10, 81, 16));
        QFont font;
        font.setPointSize(14);
        labelViewer1->setFont(font);
        labelViewer2 = new QLabel(centralwidget);
        labelViewer2->setObjectName(QString::fromUtf8("labelViewer2"));
        labelViewer2->setGeometry(QRect(570, 10, 81, 16));
        labelViewer2->setFont(font);
        valuePosXViewer1 = new QDoubleSpinBox(centralwidget);
        valuePosXViewer1->setObjectName(QString::fromUtf8("valuePosXViewer1"));
        valuePosXViewer1->setGeometry(QRect(210, 20, 66, 24));
        valuePosXViewer1->setMinimum(-99);
        labelPosXVewer1 = new QLabel(centralwidget);
        labelPosXVewer1->setObjectName(QString::fromUtf8("labelPosXVewer1"));
        labelPosXVewer1->setGeometry(QRect(170, 20, 41, 16));
        labelPosYVewer1 = new QLabel(centralwidget);
        labelPosYVewer1->setObjectName(QString::fromUtf8("labelPosYVewer1"));
        labelPosYVewer1->setGeometry(QRect(170, 50, 41, 16));
        labelPosZVewer1 = new QLabel(centralwidget);
        labelPosZVewer1->setObjectName(QString::fromUtf8("labelPosZVewer1"));
        labelPosZVewer1->setGeometry(QRect(170, 80, 41, 16));
        valuePosYViewer1 = new QDoubleSpinBox(centralwidget);
        valuePosYViewer1->setObjectName(QString::fromUtf8("valuePosYViewer1"));
        valuePosYViewer1->setGeometry(QRect(210, 50, 66, 24));
        valuePosYViewer1->setMinimum(-99);
        valuePosZViewer1 = new QDoubleSpinBox(centralwidget);
        valuePosZViewer1->setObjectName(QString::fromUtf8("valuePosZViewer1"));
        valuePosZViewer1->setGeometry(QRect(210, 80, 66, 24));
        valuePosZViewer1->setMinimum(-99);
        labelViewYVewer1 = new QLabel(centralwidget);
        labelViewYVewer1->setObjectName(QString::fromUtf8("labelViewYVewer1"));
        labelViewYVewer1->setGeometry(QRect(290, 50, 51, 20));
        valueViewYViewer1 = new QDoubleSpinBox(centralwidget);
        valueViewYViewer1->setObjectName(QString::fromUtf8("valueViewYViewer1"));
        valueViewYViewer1->setGeometry(QRect(340, 50, 66, 24));
        valueViewYViewer1->setMinimum(-99);
        valueViewZViewer1 = new QDoubleSpinBox(centralwidget);
        valueViewZViewer1->setObjectName(QString::fromUtf8("valueViewZViewer1"));
        valueViewZViewer1->setGeometry(QRect(340, 80, 66, 24));
        valueViewZViewer1->setMinimum(-99);
        labelViewXVewer1 = new QLabel(centralwidget);
        labelViewXVewer1->setObjectName(QString::fromUtf8("labelViewXVewer1"));
        labelViewXVewer1->setGeometry(QRect(290, 20, 51, 20));
        labelViewZVewer1 = new QLabel(centralwidget);
        labelViewZVewer1->setObjectName(QString::fromUtf8("labelViewZVewer1"));
        labelViewZVewer1->setGeometry(QRect(290, 80, 51, 20));
        valueViewXViewer1 = new QDoubleSpinBox(centralwidget);
        valueViewXViewer1->setObjectName(QString::fromUtf8("valueViewXViewer1"));
        valueViewXViewer1->setGeometry(QRect(340, 20, 66, 24));
        valueViewXViewer1->setMinimum(-99);
        btnGetParametersCameraViewer1 = new QPushButton(centralwidget);
        btnGetParametersCameraViewer1->setObjectName(QString::fromUtf8("btnGetParametersCameraViewer1"));
        btnGetParametersCameraViewer1->setGeometry(QRect(40, 80, 110, 30));
        labelViewZVewer2 = new QLabel(centralwidget);
        labelViewZVewer2->setObjectName(QString::fromUtf8("labelViewZVewer2"));
        labelViewZVewer2->setGeometry(QRect(820, 80, 51, 20));
        labelPosXVewer2 = new QLabel(centralwidget);
        labelPosXVewer2->setObjectName(QString::fromUtf8("labelPosXVewer2"));
        labelPosXVewer2->setGeometry(QRect(700, 20, 41, 16));
        valuePosYViewer2 = new QDoubleSpinBox(centralwidget);
        valuePosYViewer2->setObjectName(QString::fromUtf8("valuePosYViewer2"));
        valuePosYViewer2->setGeometry(QRect(740, 50, 66, 24));
        valuePosYViewer2->setMinimum(-99);
        labelPosZVewer2 = new QLabel(centralwidget);
        labelPosZVewer2->setObjectName(QString::fromUtf8("labelPosZVewer2"));
        labelPosZVewer2->setGeometry(QRect(700, 80, 41, 16));
        valueViewYViewer2 = new QDoubleSpinBox(centralwidget);
        valueViewYViewer2->setObjectName(QString::fromUtf8("valueViewYViewer2"));
        valueViewYViewer2->setGeometry(QRect(870, 50, 66, 24));
        valueViewYViewer2->setMinimum(-99);
        valuePosXViewer2 = new QDoubleSpinBox(centralwidget);
        valuePosXViewer2->setObjectName(QString::fromUtf8("valuePosXViewer2"));
        valuePosXViewer2->setGeometry(QRect(740, 20, 66, 24));
        valuePosXViewer2->setMinimum(-99);
        btnGetParametersCameraViewer2 = new QPushButton(centralwidget);
        btnGetParametersCameraViewer2->setObjectName(QString::fromUtf8("btnGetParametersCameraViewer2"));
        btnGetParametersCameraViewer2->setGeometry(QRect(570, 80, 110, 30));
        labelPosYVewer2 = new QLabel(centralwidget);
        labelPosYVewer2->setObjectName(QString::fromUtf8("labelPosYVewer2"));
        labelPosYVewer2->setGeometry(QRect(700, 50, 41, 16));
        valueViewZViewer2 = new QDoubleSpinBox(centralwidget);
        valueViewZViewer2->setObjectName(QString::fromUtf8("valueViewZViewer2"));
        valueViewZViewer2->setGeometry(QRect(870, 80, 66, 24));
        valueViewZViewer2->setMinimum(-99);
        labelViewYVewer2 = new QLabel(centralwidget);
        labelViewYVewer2->setObjectName(QString::fromUtf8("labelViewYVewer2"));
        labelViewYVewer2->setGeometry(QRect(820, 50, 51, 20));
        labelViewXVewer2 = new QLabel(centralwidget);
        labelViewXVewer2->setObjectName(QString::fromUtf8("labelViewXVewer2"));
        labelViewXVewer2->setGeometry(QRect(820, 20, 51, 20));
        valueViewXViewer2 = new QDoubleSpinBox(centralwidget);
        valueViewXViewer2->setObjectName(QString::fromUtf8("valueViewXViewer2"));
        valueViewXViewer2->setGeometry(QRect(870, 20, 66, 24));
        valueViewXViewer2->setMinimum(-99);
        valuePosZViewer2 = new QDoubleSpinBox(centralwidget);
        valuePosZViewer2->setObjectName(QString::fromUtf8("valuePosZViewer2"));
        valuePosZViewer2->setGeometry(QRect(740, 80, 66, 24));
        valuePosZViewer2->setMinimum(-99);
        btnResetCameraViewer2 = new QPushButton(centralwidget);
        btnResetCameraViewer2->setObjectName(QString::fromUtf8("btnResetCameraViewer2"));
        btnResetCameraViewer2->setGeometry(QRect(570, 40, 110, 30));
        btnViewer1to2 = new QPushButton(centralwidget);
        btnViewer1to2->setObjectName(QString::fromUtf8("btnViewer1to2"));
        btnViewer1to2->setGeometry(QRect(480, 20, 40, 30));
        btnViewer2to1 = new QPushButton(centralwidget);
        btnViewer2to1->setObjectName(QString::fromUtf8("btnViewer2to1"));
        btnViewer2to1->setGeometry(QRect(480, 70, 40, 30));
        dilateSizeValue = new QDoubleSpinBox(centralwidget);
        dilateSizeValue->setObjectName(QString::fromUtf8("dilateSizeValue"));
        dilateSizeValue->setGeometry(QRect(780, 560, 66, 24));
        dilateSizeValue->setDecimals(4);
        dilateSizeValue->setMaximum(20);
        dilateSizeValue->setSingleStep(0.01);
        dilateSizeValue->setValue(0.01);
        labelSize = new QLabel(centralwidget);
        labelSize->setObjectName(QString::fromUtf8("labelSize"));
        labelSize->setGeometry(QRect(700, 560, 71, 20));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        labelSize->setFont(font1);
        btnCaptureCloud = new QPushButton(centralwidget);
        btnCaptureCloud->setObjectName(QString::fromUtf8("btnCaptureCloud"));
        btnCaptureCloud->setGeometry(QRect(170, 560, 110, 50));
        btnCaptureCloud->setCheckable(false);
        btnDilateCloud = new QPushButton(centralwidget);
        btnDilateCloud->setObjectName(QString::fromUtf8("btnDilateCloud"));
        btnDilateCloud->setGeometry(QRect(570, 560, 110, 50));
        btnDilateCloud->setCheckable(true);
        btnErodeCloud = new QPushButton(centralwidget);
        btnErodeCloud->setObjectName(QString::fromUtf8("btnErodeCloud"));
        btnErodeCloud->setGeometry(QRect(570, 630, 110, 50));
        btnErodeCloud->setCheckable(true);
        erodeSizeValue = new QDoubleSpinBox(centralwidget);
        erodeSizeValue->setObjectName(QString::fromUtf8("erodeSizeValue"));
        erodeSizeValue->setGeometry(QRect(780, 630, 66, 24));
        erodeSizeValue->setDecimals(4);
        erodeSizeValue->setMaximum(20);
        erodeSizeValue->setSingleStep(0.01);
        erodeSizeValue->setValue(0.01);
        labelSize_2 = new QLabel(centralwidget);
        labelSize_2->setObjectName(QString::fromUtf8("labelSize_2"));
        labelSize_2->setGeometry(QRect(700, 630, 71, 20));
        labelSize_2->setFont(font1);
        btnInitVisualizers = new QPushButton(centralwidget);
        btnInitVisualizers->setObjectName(QString::fromUtf8("btnInitVisualizers"));
        btnInitVisualizers->setGeometry(QRect(40, 630, 110, 50));
        btnInitVisualizers->setCheckable(false);
        KinectViewer->setCentralWidget(centralwidget);

        retranslateUi(KinectViewer);

        QMetaObject::connectSlotsByName(KinectViewer);
    } // setupUi

    void retranslateUi(QMainWindow *KinectViewer)
    {
        KinectViewer->setWindowTitle(QApplication::translate("KinectViewer", "KinectViewer", 0, QApplication::UnicodeUTF8));
        btnRunCamera->setText(QApplication::translate("KinectViewer", "Run Camera", 0, QApplication::UnicodeUTF8));
        btnResetCameraViewer1->setText(QApplication::translate("KinectViewer", "Set parameters", 0, QApplication::UnicodeUTF8));
        labelViewer1->setText(QApplication::translate("KinectViewer", "Viewer 1", 0, QApplication::UnicodeUTF8));
        labelViewer2->setText(QApplication::translate("KinectViewer", "Viewer 2", 0, QApplication::UnicodeUTF8));
        labelPosXVewer1->setText(QApplication::translate("KinectViewer", "pos x:", 0, QApplication::UnicodeUTF8));
        labelPosYVewer1->setText(QApplication::translate("KinectViewer", "pos y:", 0, QApplication::UnicodeUTF8));
        labelPosZVewer1->setText(QApplication::translate("KinectViewer", "pos z:", 0, QApplication::UnicodeUTF8));
        labelViewYVewer1->setText(QApplication::translate("KinectViewer", "view y:", 0, QApplication::UnicodeUTF8));
        labelViewXVewer1->setText(QApplication::translate("KinectViewer", "view x:", 0, QApplication::UnicodeUTF8));
        labelViewZVewer1->setText(QApplication::translate("KinectViewer", "view z:", 0, QApplication::UnicodeUTF8));
        btnGetParametersCameraViewer1->setText(QApplication::translate("KinectViewer", "Get parameters", 0, QApplication::UnicodeUTF8));
        labelViewZVewer2->setText(QApplication::translate("KinectViewer", "view z:", 0, QApplication::UnicodeUTF8));
        labelPosXVewer2->setText(QApplication::translate("KinectViewer", "pos x:", 0, QApplication::UnicodeUTF8));
        labelPosZVewer2->setText(QApplication::translate("KinectViewer", "pos z:", 0, QApplication::UnicodeUTF8));
        btnGetParametersCameraViewer2->setText(QApplication::translate("KinectViewer", "Get parameters", 0, QApplication::UnicodeUTF8));
        labelPosYVewer2->setText(QApplication::translate("KinectViewer", "pos y:", 0, QApplication::UnicodeUTF8));
        labelViewYVewer2->setText(QApplication::translate("KinectViewer", "view y:", 0, QApplication::UnicodeUTF8));
        labelViewXVewer2->setText(QApplication::translate("KinectViewer", "view x:", 0, QApplication::UnicodeUTF8));
        btnResetCameraViewer2->setText(QApplication::translate("KinectViewer", "Set parameters", 0, QApplication::UnicodeUTF8));
        btnViewer1to2->setText(QApplication::translate("KinectViewer", "=>", 0, QApplication::UnicodeUTF8));
        btnViewer2to1->setText(QApplication::translate("KinectViewer", "<=", 0, QApplication::UnicodeUTF8));
        labelSize->setText(QApplication::translate("KinectViewer", "Dilate size:", 0, QApplication::UnicodeUTF8));
        btnCaptureCloud->setText(QApplication::translate("KinectViewer", "Capture Cloud", 0, QApplication::UnicodeUTF8));
        btnDilateCloud->setText(QApplication::translate("KinectViewer", "Dilate Cloud", 0, QApplication::UnicodeUTF8));
        btnErodeCloud->setText(QApplication::translate("KinectViewer", "Erode Cloud", 0, QApplication::UnicodeUTF8));
        labelSize_2->setText(QApplication::translate("KinectViewer", "Erode size:", 0, QApplication::UnicodeUTF8));
        btnInitVisualizers->setText(QApplication::translate("KinectViewer", "Init visualizers", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KinectViewer: public Ui_KinectViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCLKINECT_H

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
    QLabel *labelViewer1;
    QLabel *labelViewer2;
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
    QPushButton *btnTriangulateCloud;
    QDoubleSpinBox *triRadiusSearch;
    QLabel *labelRadiusSearch;
    QDoubleSpinBox *triMaxNeighbors;
    QLabel *labelMaxNeighbors;
    QPushButton *btnLoadPointCloud;
    QPushButton *btnSavePointCloud;

    void setupUi(QMainWindow *KinectViewer)
    {
        if (KinectViewer->objectName().isEmpty())
            KinectViewer->setObjectName(QString::fromUtf8("KinectViewer"));
        KinectViewer->resize(960, 700);
        KinectViewer->setMinimumSize(QSize(0, 0));
        KinectViewer->setMaximumSize(QSize(5000, 5000));
        centralwidget = new QWidget(KinectViewer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        qvtkWidget = new QVTKWidget(centralwidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(40, 30, 400, 400));
        btnRunCamera = new QPushButton(centralwidget);
        btnRunCamera->setObjectName(QString::fromUtf8("btnRunCamera"));
        btnRunCamera->setGeometry(QRect(30, 460, 110, 50));
        btnRunCamera->setCheckable(true);
        qvtkWidget_2 = new QVTKWidget(centralwidget);
        qvtkWidget_2->setObjectName(QString::fromUtf8("qvtkWidget_2"));
        qvtkWidget_2->setGeometry(QRect(520, 30, 400, 400));
        labelViewer1 = new QLabel(centralwidget);
        labelViewer1->setObjectName(QString::fromUtf8("labelViewer1"));
        labelViewer1->setGeometry(QRect(40, 10, 81, 16));
        QFont font;
        font.setPointSize(14);
        labelViewer1->setFont(font);
        labelViewer2 = new QLabel(centralwidget);
        labelViewer2->setObjectName(QString::fromUtf8("labelViewer2"));
        labelViewer2->setGeometry(QRect(520, 10, 81, 16));
        labelViewer2->setFont(font);
        btnViewer1to2 = new QPushButton(centralwidget);
        btnViewer1to2->setObjectName(QString::fromUtf8("btnViewer1to2"));
        btnViewer1to2->setGeometry(QRect(460, 200, 40, 30));
        btnViewer2to1 = new QPushButton(centralwidget);
        btnViewer2to1->setObjectName(QString::fromUtf8("btnViewer2to1"));
        btnViewer2to1->setGeometry(QRect(460, 240, 40, 30));
        dilateSizeValue = new QDoubleSpinBox(centralwidget);
        dilateSizeValue->setObjectName(QString::fromUtf8("dilateSizeValue"));
        dilateSizeValue->setGeometry(QRect(770, 460, 66, 24));
        dilateSizeValue->setDecimals(4);
        dilateSizeValue->setMaximum(20);
        dilateSizeValue->setSingleStep(0.01);
        dilateSizeValue->setValue(0.01);
        labelSize = new QLabel(centralwidget);
        labelSize->setObjectName(QString::fromUtf8("labelSize"));
        labelSize->setGeometry(QRect(690, 460, 71, 20));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        labelSize->setFont(font1);
        btnCaptureCloud = new QPushButton(centralwidget);
        btnCaptureCloud->setObjectName(QString::fromUtf8("btnCaptureCloud"));
        btnCaptureCloud->setGeometry(QRect(160, 460, 110, 50));
        btnCaptureCloud->setCheckable(false);
        btnDilateCloud = new QPushButton(centralwidget);
        btnDilateCloud->setObjectName(QString::fromUtf8("btnDilateCloud"));
        btnDilateCloud->setGeometry(QRect(560, 460, 110, 50));
        btnDilateCloud->setCheckable(true);
        btnErodeCloud = new QPushButton(centralwidget);
        btnErodeCloud->setObjectName(QString::fromUtf8("btnErodeCloud"));
        btnErodeCloud->setGeometry(QRect(560, 530, 110, 50));
        btnErodeCloud->setCheckable(true);
        erodeSizeValue = new QDoubleSpinBox(centralwidget);
        erodeSizeValue->setObjectName(QString::fromUtf8("erodeSizeValue"));
        erodeSizeValue->setGeometry(QRect(770, 530, 66, 24));
        erodeSizeValue->setDecimals(4);
        erodeSizeValue->setMaximum(20);
        erodeSizeValue->setSingleStep(0.01);
        erodeSizeValue->setValue(0.01);
        labelSize_2 = new QLabel(centralwidget);
        labelSize_2->setObjectName(QString::fromUtf8("labelSize_2"));
        labelSize_2->setGeometry(QRect(690, 530, 71, 20));
        labelSize_2->setFont(font1);
        btnInitVisualizers = new QPushButton(centralwidget);
        btnInitVisualizers->setObjectName(QString::fromUtf8("btnInitVisualizers"));
        btnInitVisualizers->setGeometry(QRect(30, 530, 110, 50));
        btnInitVisualizers->setCheckable(false);
        btnTriangulateCloud = new QPushButton(centralwidget);
        btnTriangulateCloud->setObjectName(QString::fromUtf8("btnTriangulateCloud"));
        btnTriangulateCloud->setGeometry(QRect(560, 600, 110, 50));
        btnTriangulateCloud->setCheckable(true);
        triRadiusSearch = new QDoubleSpinBox(centralwidget);
        triRadiusSearch->setObjectName(QString::fromUtf8("triRadiusSearch"));
        triRadiusSearch->setGeometry(QRect(810, 600, 66, 24));
        triRadiusSearch->setDecimals(4);
        triRadiusSearch->setMaximum(20);
        triRadiusSearch->setSingleStep(0.001);
        triRadiusSearch->setValue(0.025);
        labelRadiusSearch = new QLabel(centralwidget);
        labelRadiusSearch->setObjectName(QString::fromUtf8("labelRadiusSearch"));
        labelRadiusSearch->setGeometry(QRect(710, 600, 91, 20));
        labelRadiusSearch->setFont(font1);
        triMaxNeighbors = new QDoubleSpinBox(centralwidget);
        triMaxNeighbors->setObjectName(QString::fromUtf8("triMaxNeighbors"));
        triMaxNeighbors->setGeometry(QRect(810, 630, 66, 24));
        triMaxNeighbors->setDecimals(0);
        triMaxNeighbors->setMaximum(10000);
        triMaxNeighbors->setSingleStep(10);
        triMaxNeighbors->setValue(100);
        labelMaxNeighbors = new QLabel(centralwidget);
        labelMaxNeighbors->setObjectName(QString::fromUtf8("labelMaxNeighbors"));
        labelMaxNeighbors->setGeometry(QRect(710, 630, 91, 20));
        labelMaxNeighbors->setFont(font1);
        btnLoadPointCloud = new QPushButton(centralwidget);
        btnLoadPointCloud->setObjectName(QString::fromUtf8("btnLoadPointCloud"));
        btnLoadPointCloud->setGeometry(QRect(160, 530, 110, 50));
        btnLoadPointCloud->setCheckable(false);
        btnSavePointCloud = new QPushButton(centralwidget);
        btnSavePointCloud->setObjectName(QString::fromUtf8("btnSavePointCloud"));
        btnSavePointCloud->setGeometry(QRect(30, 600, 110, 50));
        btnSavePointCloud->setCheckable(false);
        KinectViewer->setCentralWidget(centralwidget);

        retranslateUi(KinectViewer);

        QMetaObject::connectSlotsByName(KinectViewer);
    } // setupUi

    void retranslateUi(QMainWindow *KinectViewer)
    {
        KinectViewer->setWindowTitle(QApplication::translate("KinectViewer", "KinectViewer", 0, QApplication::UnicodeUTF8));
        btnRunCamera->setText(QApplication::translate("KinectViewer", "Run Camera", 0, QApplication::UnicodeUTF8));
        labelViewer1->setText(QApplication::translate("KinectViewer", "Viewer 1", 0, QApplication::UnicodeUTF8));
        labelViewer2->setText(QApplication::translate("KinectViewer", "Viewer 2", 0, QApplication::UnicodeUTF8));
        btnViewer1to2->setText(QApplication::translate("KinectViewer", "=>", 0, QApplication::UnicodeUTF8));
        btnViewer2to1->setText(QApplication::translate("KinectViewer", "<=", 0, QApplication::UnicodeUTF8));
        labelSize->setText(QApplication::translate("KinectViewer", "Dilate size:", 0, QApplication::UnicodeUTF8));
        btnCaptureCloud->setText(QApplication::translate("KinectViewer", "Capture Cloud", 0, QApplication::UnicodeUTF8));
        btnDilateCloud->setText(QApplication::translate("KinectViewer", "Dilate Cloud", 0, QApplication::UnicodeUTF8));
        btnErodeCloud->setText(QApplication::translate("KinectViewer", "Erode Cloud", 0, QApplication::UnicodeUTF8));
        labelSize_2->setText(QApplication::translate("KinectViewer", "Erode size:", 0, QApplication::UnicodeUTF8));
        btnInitVisualizers->setText(QApplication::translate("KinectViewer", "Init visualizers", 0, QApplication::UnicodeUTF8));
        btnTriangulateCloud->setText(QApplication::translate("KinectViewer", "Triangulate Cloud", 0, QApplication::UnicodeUTF8));
        labelRadiusSearch->setText(QApplication::translate("KinectViewer", "Radius search:", 0, QApplication::UnicodeUTF8));
        labelMaxNeighbors->setText(QApplication::translate("KinectViewer", "Max neighbors:", 0, QApplication::UnicodeUTF8));
        btnLoadPointCloud->setText(QApplication::translate("KinectViewer", "Load Point Cloud", 0, QApplication::UnicodeUTF8));
        btnSavePointCloud->setText(QApplication::translate("KinectViewer", "Save Point Cloud", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KinectViewer: public Ui_KinectViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCLKINECT_H

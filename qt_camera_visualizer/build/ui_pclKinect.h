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
    QPushButton *btnStopStream;
    QVTKWidget *qvtkWidget_2;
    QPushButton *btnResetCameraViewer1;
    QLabel *labelViewer1;
    QLabel *labelViewer2;
    QPushButton *btnResetCameraViewer2;
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

    void setupUi(QMainWindow *KinectViewer)
    {
        if (KinectViewer->objectName().isEmpty())
            KinectViewer->setObjectName(QString::fromUtf8("KinectViewer"));
        KinectViewer->resize(900, 650);
        KinectViewer->setMinimumSize(QSize(0, 0));
        KinectViewer->setMaximumSize(QSize(5000, 5000));
        centralwidget = new QWidget(KinectViewer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        qvtkWidget = new QVTKWidget(centralwidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(40, 120, 400, 400));
        btnStopStream = new QPushButton(centralwidget);
        btnStopStream->setObjectName(QString::fromUtf8("btnStopStream"));
        btnStopStream->setGeometry(QRect(40, 560, 110, 50));
        btnStopStream->setCheckable(true);
        qvtkWidget_2 = new QVTKWidget(centralwidget);
        qvtkWidget_2->setObjectName(QString::fromUtf8("qvtkWidget_2"));
        qvtkWidget_2->setGeometry(QRect(480, 120, 400, 400));
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
        labelViewer2->setGeometry(QRect(480, 10, 81, 16));
        labelViewer2->setFont(font);
        btnResetCameraViewer2 = new QPushButton(centralwidget);
        btnResetCameraViewer2->setObjectName(QString::fromUtf8("btnResetCameraViewer2"));
        btnResetCameraViewer2->setGeometry(QRect(480, 72, 110, 30));
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
        KinectViewer->setCentralWidget(centralwidget);

        retranslateUi(KinectViewer);

        QMetaObject::connectSlotsByName(KinectViewer);
    } // setupUi

    void retranslateUi(QMainWindow *KinectViewer)
    {
        KinectViewer->setWindowTitle(QApplication::translate("KinectViewer", "KinectViewer", 0, QApplication::UnicodeUTF8));
        btnStopStream->setText(QApplication::translate("KinectViewer", "Stream running", 0, QApplication::UnicodeUTF8));
        btnResetCameraViewer1->setText(QApplication::translate("KinectViewer", "Reset camera", 0, QApplication::UnicodeUTF8));
        labelViewer1->setText(QApplication::translate("KinectViewer", "Viewer 1", 0, QApplication::UnicodeUTF8));
        labelViewer2->setText(QApplication::translate("KinectViewer", "Viewer 2", 0, QApplication::UnicodeUTF8));
        btnResetCameraViewer2->setText(QApplication::translate("KinectViewer", "Reset camera", 0, QApplication::UnicodeUTF8));
        labelPosXVewer1->setText(QApplication::translate("KinectViewer", "pos x:", 0, QApplication::UnicodeUTF8));
        labelPosYVewer1->setText(QApplication::translate("KinectViewer", "pos y:", 0, QApplication::UnicodeUTF8));
        labelPosZVewer1->setText(QApplication::translate("KinectViewer", "pos z:", 0, QApplication::UnicodeUTF8));
        labelViewYVewer1->setText(QApplication::translate("KinectViewer", "view y:", 0, QApplication::UnicodeUTF8));
        labelViewXVewer1->setText(QApplication::translate("KinectViewer", "view x:", 0, QApplication::UnicodeUTF8));
        labelViewZVewer1->setText(QApplication::translate("KinectViewer", "view z:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KinectViewer: public Ui_KinectViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCLKINECT_H

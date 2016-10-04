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
#include <QtGui/QHeaderView>
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

    void setupUi(QMainWindow *KinectViewer)
    {
        if (KinectViewer->objectName().isEmpty())
            KinectViewer->setObjectName(QString::fromUtf8("KinectViewer"));
        KinectViewer->resize(900, 580);
        KinectViewer->setMinimumSize(QSize(0, 0));
        KinectViewer->setMaximumSize(QSize(5000, 5000));
        centralwidget = new QWidget(KinectViewer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        qvtkWidget = new QVTKWidget(centralwidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(40, 40, 400, 400));
        btnStopStream = new QPushButton(centralwidget);
        btnStopStream->setObjectName(QString::fromUtf8("btnStopStream"));
        btnStopStream->setGeometry(QRect(40, 480, 110, 50));
        btnStopStream->setCheckable(true);
        qvtkWidget_2 = new QVTKWidget(centralwidget);
        qvtkWidget_2->setObjectName(QString::fromUtf8("qvtkWidget_2"));
        qvtkWidget_2->setGeometry(QRect(480, 40, 400, 400));
        KinectViewer->setCentralWidget(centralwidget);

        retranslateUi(KinectViewer);

        QMetaObject::connectSlotsByName(KinectViewer);
    } // setupUi

    void retranslateUi(QMainWindow *KinectViewer)
    {
        KinectViewer->setWindowTitle(QApplication::translate("KinectViewer", "KinectViewer", 0, QApplication::UnicodeUTF8));
        btnStopStream->setText(QApplication::translate("KinectViewer", "Stream running", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KinectViewer: public Ui_KinectViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCLKINECT_H

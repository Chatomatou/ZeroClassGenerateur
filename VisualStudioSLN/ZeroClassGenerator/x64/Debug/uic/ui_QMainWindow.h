/********************************************************************************
** Form generated from reading UI file 'QMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMAINWINDOW_H
#define UI_QMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QMainWindowClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QMainWindowClass)
    {
        if (QMainWindowClass->objectName().isEmpty())
            QMainWindowClass->setObjectName(QString::fromUtf8("QMainWindowClass"));
        QMainWindowClass->resize(600, 400);
        menuBar = new QMenuBar(QMainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QMainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QMainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QMainWindowClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QMainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QMainWindowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QMainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QMainWindowClass->setStatusBar(statusBar);

        retranslateUi(QMainWindowClass);

        QMetaObject::connectSlotsByName(QMainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *QMainWindowClass)
    {
        QMainWindowClass->setWindowTitle(QCoreApplication::translate("QMainWindowClass", "QMainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QMainWindowClass: public Ui_QMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMAINWINDOW_H

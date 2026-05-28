/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QLabel *statusLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1100, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(10, 10, 800, 540));
        graphicsView->setMinimumSize(QSize(800, 500));
        graphicsView->setStyleSheet(QString::fromUtf8("background-color: #F5F5DC;"));
        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(10, 555, 1080, 30));
        statusLabel->setFrameShape(QFrame::Shape::Box);
        statusLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\321\207\320\260 \320\272\320\276\320\274\320\274\320\270\320\262\320\276\321\217\320\266\321\221\321\200\320\260 - \320\234\320\265\321\202\320\276\320\264 \320\262\320\265\321\202\320\262\320\265\320\271 \320\270 \320\263\321\200\320\260\320\275\320\270\321\206", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\202\320\276\320\262 \320\272 \321\200\320\260\320\261\320\276\321\202\320\265. \320\230\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\271\321\202\320\265 \320\272\320\275\320\276\320\277\320\272\320\270 \321\201\320\277\321\200\320\260\320\262\320\260 \320\264\320\273\321\217 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

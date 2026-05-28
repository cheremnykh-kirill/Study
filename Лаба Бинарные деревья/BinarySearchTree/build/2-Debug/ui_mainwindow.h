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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *buttonLayout;
    QPushButton *insertButton;
    QPushButton *deleteButton;
    QPushButton *searchButton;
    QPushButton *findMinButton;
    QPushButton *balanceButton;
    QHBoxLayout *traversalLayout;
    QPushButton *preOrderButton;
    QPushButton *inOrderButton;
    QPushButton *postOrderButton;
    QHBoxLayout *printLayout;
    QPushButton *horizontalPrintButton;
    QPushButton *verticalPrintButton;
    QGraphicsView *graphicsView;
    QLabel *statusLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        insertButton = new QPushButton(centralwidget);
        insertButton->setObjectName("insertButton");
        insertButton->setMinimumSize(QSize(100, 0));

        buttonLayout->addWidget(insertButton);

        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setMinimumSize(QSize(100, 0));

        buttonLayout->addWidget(deleteButton);

        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName("searchButton");
        searchButton->setMinimumSize(QSize(100, 0));

        buttonLayout->addWidget(searchButton);

        findMinButton = new QPushButton(centralwidget);
        findMinButton->setObjectName("findMinButton");
        findMinButton->setMinimumSize(QSize(100, 0));

        buttonLayout->addWidget(findMinButton);

        balanceButton = new QPushButton(centralwidget);
        balanceButton->setObjectName("balanceButton");
        balanceButton->setMinimumSize(QSize(100, 0));

        buttonLayout->addWidget(balanceButton);


        verticalLayout->addLayout(buttonLayout);

        traversalLayout = new QHBoxLayout();
        traversalLayout->setObjectName("traversalLayout");
        preOrderButton = new QPushButton(centralwidget);
        preOrderButton->setObjectName("preOrderButton");
        preOrderButton->setMinimumSize(QSize(100, 0));

        traversalLayout->addWidget(preOrderButton);

        inOrderButton = new QPushButton(centralwidget);
        inOrderButton->setObjectName("inOrderButton");
        inOrderButton->setMinimumSize(QSize(100, 0));

        traversalLayout->addWidget(inOrderButton);

        postOrderButton = new QPushButton(centralwidget);
        postOrderButton->setObjectName("postOrderButton");
        postOrderButton->setMinimumSize(QSize(100, 0));

        traversalLayout->addWidget(postOrderButton);


        verticalLayout->addLayout(traversalLayout);

        printLayout = new QHBoxLayout();
        printLayout->setObjectName("printLayout");
        horizontalPrintButton = new QPushButton(centralwidget);
        horizontalPrintButton->setObjectName("horizontalPrintButton");
        horizontalPrintButton->setMinimumSize(QSize(150, 0));
        horizontalPrintButton->setCheckable(true);

        printLayout->addWidget(horizontalPrintButton);

        verticalPrintButton = new QPushButton(centralwidget);
        verticalPrintButton->setObjectName("verticalPrintButton");
        verticalPrintButton->setMinimumSize(QSize(150, 0));
        verticalPrintButton->setCheckable(true);

        printLayout->addWidget(verticalPrintButton);


        verticalLayout->addLayout(printLayout);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setMinimumSize(QSize(800, 400));

        verticalLayout->addWidget(graphicsView);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setMinimumSize(QSize(0, 30));
        statusLabel->setFrameShape(QFrame::Shape::Box);
        statusLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(statusLabel);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\221\320\270\320\275\320\260\321\200\320\275\320\276\320\265 \320\264\320\265\321\200\320\265\320\262\320\276 \320\277\320\276\320\270\321\201\320\272\320\260", nullptr));
        insertButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        findMinButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270 \320\274\320\270\320\275\320\270\320\274\321\203\320\274", nullptr));
        balanceButton->setText(QCoreApplication::translate("MainWindow", "\320\221\320\260\320\273\320\260\320\275\321\201\320\270\321\200\320\276\320\262\320\272\320\260", nullptr));
        preOrderButton->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\321\217\320\274\320\276\320\271 \320\276\320\261\321\205\320\276\320\264", nullptr));
        inOrderButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\270\320\274\320\274\320\265\321\202\321\200\320\270\321\207\320\275\321\213\320\271 \320\276\320\261\321\205\320\276\320\264", nullptr));
        postOrderButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\200\320\260\321\202\320\275\321\213\320\271 \320\276\320\261\321\205\320\276\320\264", nullptr));
        horizontalPrintButton->setText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\200\320\270\320\267\320\276\320\275\321\202\320\260\320\273\321\214\320\275\320\260\321\217 \320\277\320\265\321\207\320\260\321\202\321\214", nullptr));
        verticalPrintButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\321\202\320\270\320\272\320\260\320\273\321\214\320\275\320\260\321\217 \320\277\320\265\321\207\320\260\321\202\321\214", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\202\320\276\320\262 \320\272 \321\200\320\260\320\261\320\276\321\202\320\265. \320\224\320\276\320\261\320\260\320\262\321\214\321\202\320\265 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\321\213 \320\262 \320\264\320\265\321\200\320\265\320\262\320\276.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

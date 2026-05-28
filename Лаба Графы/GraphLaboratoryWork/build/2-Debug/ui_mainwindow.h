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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainVerticalLayout;
    QHBoxLayout *editButtonsLayout;
    QPushButton *addVertexButton;
    QPushButton *removeVertexButton;
    QPushButton *addEdgeButton;
    QPushButton *removeEdgeButton;
    QPushButton *editWeightButton;
    QPushButton *editMatrixButton;
    QHBoxLayout *algoButtonsLayout;
    QPushButton *bfsButton;
    QPushButton *dfsButton;
    QPushButton *dijkstraButton;
    QPushButton *floydButton;
    QPushButton *resetViewButton;
    QHBoxLayout *contentLayout;
    QGraphicsView *graphicsView;
    QTableWidget *matrixTable;
    QLabel *statusLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1100, 750);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainVerticalLayout = new QVBoxLayout(centralwidget);
        mainVerticalLayout->setObjectName("mainVerticalLayout");
        editButtonsLayout = new QHBoxLayout();
        editButtonsLayout->setObjectName("editButtonsLayout");
        addVertexButton = new QPushButton(centralwidget);
        addVertexButton->setObjectName("addVertexButton");

        editButtonsLayout->addWidget(addVertexButton);

        removeVertexButton = new QPushButton(centralwidget);
        removeVertexButton->setObjectName("removeVertexButton");

        editButtonsLayout->addWidget(removeVertexButton);

        addEdgeButton = new QPushButton(centralwidget);
        addEdgeButton->setObjectName("addEdgeButton");

        editButtonsLayout->addWidget(addEdgeButton);

        removeEdgeButton = new QPushButton(centralwidget);
        removeEdgeButton->setObjectName("removeEdgeButton");

        editButtonsLayout->addWidget(removeEdgeButton);

        editWeightButton = new QPushButton(centralwidget);
        editWeightButton->setObjectName("editWeightButton");

        editButtonsLayout->addWidget(editWeightButton);

        editMatrixButton = new QPushButton(centralwidget);
        editMatrixButton->setObjectName("editMatrixButton");

        editButtonsLayout->addWidget(editMatrixButton);


        mainVerticalLayout->addLayout(editButtonsLayout);

        algoButtonsLayout = new QHBoxLayout();
        algoButtonsLayout->setObjectName("algoButtonsLayout");
        bfsButton = new QPushButton(centralwidget);
        bfsButton->setObjectName("bfsButton");

        algoButtonsLayout->addWidget(bfsButton);

        dfsButton = new QPushButton(centralwidget);
        dfsButton->setObjectName("dfsButton");

        algoButtonsLayout->addWidget(dfsButton);

        dijkstraButton = new QPushButton(centralwidget);
        dijkstraButton->setObjectName("dijkstraButton");

        algoButtonsLayout->addWidget(dijkstraButton);

        floydButton = new QPushButton(centralwidget);
        floydButton->setObjectName("floydButton");

        algoButtonsLayout->addWidget(floydButton);

        resetViewButton = new QPushButton(centralwidget);
        resetViewButton->setObjectName("resetViewButton");

        algoButtonsLayout->addWidget(resetViewButton);


        mainVerticalLayout->addLayout(algoButtonsLayout);

        contentLayout = new QHBoxLayout();
        contentLayout->setObjectName("contentLayout");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setMinimumSize(QSize(750, 500));

        contentLayout->addWidget(graphicsView);

        matrixTable = new QTableWidget(centralwidget);
        matrixTable->setObjectName("matrixTable");
        matrixTable->setMinimumSize(QSize(300, 300));
        matrixTable->setMaximumSize(QSize(350, 350));

        contentLayout->addWidget(matrixTable);


        mainVerticalLayout->addLayout(contentLayout);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setMinimumSize(QSize(0, 40));
        statusLabel->setFrameShape(QFrame::Shape::Box);
        statusLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        mainVerticalLayout->addWidget(statusLabel);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204 - \320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274\321\213 - \320\222\320\260\321\200\320\270\320\260\320\275\321\202 \321\201 \320\262\320\265\321\200\321\210\320\270\320\275\321\213 5", nullptr));
        addVertexButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\262\320\265\321\200\321\210\320\270\320\275\321\203", nullptr));
        removeVertexButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\320\265\321\200\321\210\320\270\320\275\321\203", nullptr));
        addEdgeButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\200\320\265\320\261\321\200\320\276", nullptr));
        removeEdgeButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\200\320\265\320\261\321\200\320\276", nullptr));
        editWeightButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\262\320\265\321\201", nullptr));
        editMatrixButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \320\274\320\260\321\202\321\200\320\270\321\206\321\203", nullptr));
        bfsButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #87CEEB; font-weight: bold;", nullptr));
        bfsButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\205\320\276\320\264 \320\262 \321\210\320\270\321\200\320\270\320\275\321\203 (BFS)", nullptr));
        dfsButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #90EE90; font-weight: bold;", nullptr));
        dfsButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\205\320\276\320\264 \320\262 \320\263\320\273\321\203\320\261\320\270\320\275\321\203 (DFS)", nullptr));
        dijkstraButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #FFB6C1; font-weight: bold;", nullptr));
        dijkstraButton->setText(QCoreApplication::translate("MainWindow", "\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274 \320\224\320\265\320\271\320\272\321\201\321\202\321\200\321\213", nullptr));
        floydButton->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #DDA0DD; font-weight: bold;", nullptr));
        floydButton->setText(QCoreApplication::translate("MainWindow", "\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274 \320\244\320\273\320\276\320\271\320\264\320\260", nullptr));
        resetViewButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\261\321\200\320\276\321\201 \320\262\320\270\320\264\320\260", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\202\320\276\320\262 \320\272 \321\200\320\260\320\261\320\276\321\202\320\265. \320\235\320\260\320\266\320\274\320\270\321\202\320\265 \320\272\320\275\320\276\320\277\320\272\321\203 \320\260\320\273\320\263\320\276\321\200\320\270\321\202\320\274\320\260 \320\264\320\273\321\217 \320\275\320\260\321\207\320\260\320\273\320\260.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

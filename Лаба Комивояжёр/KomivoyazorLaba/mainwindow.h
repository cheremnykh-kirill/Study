#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QVector>
#include <QSet>
#include <QMap>
#include <climits>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onSceneClicked(const QPointF& pos);
    int findVertexAtPosition(double x, double y, double radius = 20);

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    void on_addNode_clicked();
    void on_addEdge_clicked();
    void on_solve_clicked();
    void on_clear_clicked();
    void animateNextStep();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    QTextEdit *outputText;

    struct Edge {
        int from;
        int to;
        int weight;
    };

    bool isAddingVertexMode;
    bool isAddingEdgeMode;
    bool isRemovingVertexMode;
    bool isRemovingEdgeMode;
    int selectedStartVertex;

    QVector<QPair<QPointF, int>> nodes;
    QVector<Edge> edges;
    QVector<QVector<int>> adjMatrix;
    int nodeCount;
    int nextVertexId;

    QVector<int> bestPath;
    int currentAnimStep;
    QVector<QGraphicsEllipseItem*> nodeItems;
    QVector<QGraphicsLineItem*> edgeItems;
    QVector<QGraphicsTextItem*> labelItems;

    void setupDefaultGraph();
    void updateAdjacencyMatrix();
    void drawGraph();
    void highlightPath(int step);
    void resetColors();
    void updateStatusMessage(const QString& message);
    int getNextFreeId();

    int tspBranchAndBound(QVector<int> &bestPath);
    void tspRecursive(QVector<int> &currentPath, QVector<bool> &visited,
                      int currentCost, int &bestCost, QVector<int> &bestPath,
                      int level);
    int calculateLowerBound(QVector<int> &path, QVector<bool> &visited, int level);
};

#endif // MAINWINDOW_H

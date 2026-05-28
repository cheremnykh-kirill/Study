#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsPolygonItem>
#include <QMessageBox>
#include <QInputDialog>
#include <QTimer>
#include <QQueue>
#include <QStack>
#include <QVector>
#include <QMap>
#include <QPair>
#include <QSet>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <cmath>

// Структура для ребра графа
struct Edge {
    int from;
    int to;
    int weight;

    Edge(int f, int t, int w) {
        from = f;
        to = t;
        weight = w;
    }
};

// Структура для вершины графа
struct Vertex {
    int id;
    double x;
    double y;

    Vertex(int vertexId, double posX, double posY) {
        id = vertexId;
        x = posX;
        y = posY;
    }
};

// Класс графа
class Graph {
private:
    QVector<Vertex> vertices;
    QVector<Edge> edges;
    int** adjacencyMatrix;
    int** distanceMatrix;
    int** pathMatrix;
    int maxVertices;
    int nextVertexId;

public:
    Graph(int maxV);
    ~Graph();

    void addVertex(int id, double x, double y);
    void addVertex(double x, double y);
    void removeVertex(int id);
    bool hasVertex(int id);
    QVector<Vertex> getVertices();
    int getVertexCount();
    Vertex getVertex(int id);
    int getNextVertexId() { return nextVertexId; }
    void resetNextVertexId() { nextVertexId = 1; }

    void addEdge(int from, int to, int weight);
    void removeEdge(int from, int to);
    void updateEdgeWeight(int from, int to, int newWeight);
    bool hasEdge(int from, int to);
    int getEdgeWeight(int from, int to);
    QVector<Edge> getEdges();
    QVector<Edge> getEdgesFrom(int vertexId);

    void updateAdjacencyMatrix();
    int** getAdjacencyMatrix();
    void setAdjacencyMatrixValue(int from, int to, int value);
    int getAdjacencyMatrixValue(int from, int to);

    QVector<int> breadthFirstSearch(int startVertex);
    QVector<int> depthFirstSearch(int startVertex);
    QVector<int> dijkstra(int startVertex, QVector<int>& distances);
    void floydWarshall(int**& distMatrix, int**& pathMat);
    QString getPathString(int from, int to, int** pathMat);

    int getMinDistanceVertex(QVector<int>& distances, QVector<bool>& visited);
    void initializeMatrices();
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int findVertexAtPosition(double x, double y, double radius = 30);
    void onSceneClicked(const QPointF& pos);  // Теперь public

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    void on_addVertexButton_clicked();
    void on_removeVertexButton_clicked();
    void on_addEdgeButton_clicked();
    void on_removeEdgeButton_clicked();
    void on_editWeightButton_clicked();
    void on_editMatrixButton_clicked();
    void on_bfsButton_clicked();
    void on_dfsButton_clicked();
    void on_dijkstraButton_clicked();
    void on_floydButton_clicked();
    void on_resetViewButton_clicked();
    void updateAnimation();

private:
    Ui::MainWindow *ui;
    Graph* graph;
    QGraphicsScene* scene;

    QTimer* animationTimer;
    QVector<int> animationPath;
    QVector<QPair<int, int>> animationEdges;
    int currentAnimationStep;
    bool isAnimating;

    bool isAddingEdgeMode;
    int selectedStartVertex;

    void drawGraph();
    void drawVertex(int id, double x, double y, QColor color, bool highlight = false);
    void drawEdge(int from, int to, int weight, QColor color, int penWidth = 2);
    void drawArrow(double fromX, double fromY, double toX, double toY, QColor color);
    void clearScene();

    void startAnimation(QVector<int> path, QVector<QPair<int, int>> highlightEdges);
    void stopAnimation();
    void highlightVertex(int id, QColor color);
    void highlightEdge(int from, int to, QColor color);
    void resetAllHighlights();

    void setupDefaultGraph();
    double calculateDistance(double x1, double y1, double x2, double y2);
    QPointF getEdgeMidpoint(Vertex from, Vertex to, double offset);
    void updateStatusMessage(const QString& message);
    void refreshMatrixTable();
};

#endif // MAINWINDOW_H

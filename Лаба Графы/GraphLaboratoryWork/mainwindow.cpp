#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QTableWidget>
#include <QHeaderView>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>

// ==================== Реализация класса Graph ====================

Graph::Graph(int maxV) {
    maxVertices = maxV;
    nextVertexId = 1;

    adjacencyMatrix = new int*[maxVertices + 1];
    distanceMatrix = new int*[maxVertices + 1];
    pathMatrix = new int*[maxVertices + 1];

    for (int i = 0; i <= maxVertices; i++) {
        adjacencyMatrix[i] = new int[maxVertices + 1];
        distanceMatrix[i] = new int[maxVertices + 1];
        pathMatrix[i] = new int[maxVertices + 1];

        for (int j = 0; j <= maxVertices; j++) {
            adjacencyMatrix[i][j] = 0;
            distanceMatrix[i][j] = 0;
            pathMatrix[i][j] = 0;
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i <= maxVertices; i++) {
        delete[] adjacencyMatrix[i];
        delete[] distanceMatrix[i];
        delete[] pathMatrix[i];
    }
    delete[] adjacencyMatrix;
    delete[] distanceMatrix;
    delete[] pathMatrix;
}

void Graph::addVertex(double x, double y) {
    while (hasVertex(nextVertexId)) {
        nextVertexId++;
        if (nextVertexId > maxVertices) {
            nextVertexId = 1;
        }
    }
    addVertex(nextVertexId, x, y);
    nextVertexId++;
    if (nextVertexId > maxVertices) {
        nextVertexId = 1;
    }
}

void Graph::addVertex(int id, double x, double y) {
    if (hasVertex(id) || id > maxVertices) {
        return;
    }
    vertices.append(Vertex(id, x, y));
}

void Graph::removeVertex(int id) {
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].id == id) {
            vertices.removeAt(i);
            break;
        }
    }

    QVector<Edge> newEdges;
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].from != id && edges[i].to != id) {
            newEdges.append(edges[i]);
        }
    }
    edges = newEdges;
    updateAdjacencyMatrix();
}

bool Graph::hasVertex(int id) {
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].id == id) {
            return true;
        }
    }
    return false;
}

QVector<Vertex> Graph::getVertices() {
    return vertices;
}

int Graph::getVertexCount() {
    return vertices.size();
}

Vertex Graph::getVertex(int id) {
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].id == id) {
            return vertices[i];
        }
    }
    return Vertex(-1, 0, 0);
}

void Graph::addEdge(int from, int to, int weight) {
    if (!hasVertex(from) || !hasVertex(to) || hasEdge(from, to)) {
        return;
    }
    edges.append(Edge(from, to, weight));
    updateAdjacencyMatrix();
}

void Graph::removeEdge(int from, int to) {
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].from == from && edges[i].to == to) {
            edges.removeAt(i);
            break;
        }
    }
    updateAdjacencyMatrix();
}

void Graph::updateEdgeWeight(int from, int to, int newWeight) {
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].from == from && edges[i].to == to) {
            edges[i].weight = newWeight;
            break;
        }
    }
    updateAdjacencyMatrix();
}

bool Graph::hasEdge(int from, int to) {
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].from == from && edges[i].to == to) {
            return true;
        }
    }
    return false;
}

int Graph::getEdgeWeight(int from, int to) {
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].from == from && edges[i].to == to) {
            return edges[i].weight;
        }
    }
    return 0;
}

QVector<Edge> Graph::getEdges() {
    return edges;
}

QVector<Edge> Graph::getEdgesFrom(int vertexId) {
    QVector<Edge> result;
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].from == vertexId) {
            result.append(edges[i]);
        }
    }
    return result;
}

void Graph::updateAdjacencyMatrix() {
    for (int i = 1; i <= maxVertices; i++) {
        for (int j = 1; j <= maxVertices; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }
    for (int i = 0; i < edges.size(); i++) {
        adjacencyMatrix[edges[i].from][edges[i].to] = edges[i].weight;
    }
}

int** Graph::getAdjacencyMatrix() {
    return adjacencyMatrix;
}

void Graph::setAdjacencyMatrixValue(int from, int to, int value) {
    adjacencyMatrix[from][to] = value;
    if (value > 0) {
        if (hasEdge(from, to)) {
            updateEdgeWeight(from, to, value);
        } else {
            addEdge(from, to, value);
        }
    } else {
        if (hasEdge(from, to)) {
            removeEdge(from, to);
        }
    }
}

int Graph::getAdjacencyMatrixValue(int from, int to) {
    return adjacencyMatrix[from][to];
}

void Graph::initializeMatrices() {
    int INF = 999999;
    for (int i = 1; i <= maxVertices; i++) {
        for (int j = 1; j <= maxVertices; j++) {
            if (i == j) {
                distanceMatrix[i][j] = 0;
                pathMatrix[i][j] = 0;
            } else if (adjacencyMatrix[i][j] > 0) {
                distanceMatrix[i][j] = adjacencyMatrix[i][j];
                pathMatrix[i][j] = i;
            } else {
                distanceMatrix[i][j] = INF;
                pathMatrix[i][j] = 0;
            }
        }
    }
}

// BFS
QVector<int> Graph::breadthFirstSearch(int startVertex) {
    QVector<int> result;
    QVector<bool> visited(maxVertices + 1, false);
    QQueue<int> queue;

    visited[startVertex] = true;
    queue.enqueue(startVertex);

    while (!queue.isEmpty()) {
        int current = queue.dequeue();
        result.append(current);

        QVector<Edge> outgoingEdges = getEdgesFrom(current);

        for (int i = 0; i < outgoingEdges.size(); i++) {
            for (int j = i + 1; j < outgoingEdges.size(); j++) {
                if (outgoingEdges[i].to > outgoingEdges[j].to) {
                    Edge temp = outgoingEdges[i];
                    outgoingEdges[i] = outgoingEdges[j];
                    outgoingEdges[j] = temp;
                }
            }
        }

        for (int i = 0; i < outgoingEdges.size(); i++) {
            int neighbor = outgoingEdges[i].to;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.enqueue(neighbor);
            }
        }
    }
    return result;
}

// DFS
QVector<int> Graph::depthFirstSearch(int startVertex) {
    QVector<int> result;
    QVector<bool> visited(maxVertices + 1, false);
    QStack<int> stack;

    stack.push(startVertex);

    while (!stack.isEmpty()) {
        int current = stack.pop();

        if (!visited[current]) {
            visited[current] = true;
            result.append(current);

            QVector<Edge> outgoingEdges = getEdgesFrom(current);

            for (int i = 0; i < outgoingEdges.size(); i++) {
                for (int j = i + 1; j < outgoingEdges.size(); j++) {
                    if (outgoingEdges[i].to < outgoingEdges[j].to) {
                        Edge temp = outgoingEdges[i];
                        outgoingEdges[i] = outgoingEdges[j];
                        outgoingEdges[j] = temp;
                    }
                }
            }

            for (int i = 0; i < outgoingEdges.size(); i++) {
                int neighbor = outgoingEdges[i].to;
                if (!visited[neighbor]) {
                    stack.push(neighbor);
                }
            }
        }
    }
    return result;
}

int Graph::getMinDistanceVertex(QVector<int>& distances, QVector<bool>& visited) {
    int minDistance = 999999;
    int minVertex = -1;

    for (int i = 1; i <= maxVertices; i++) {
        if (!visited[i] && distances[i] < minDistance) {
            minDistance = distances[i];
            minVertex = i;
        }
    }
    return minVertex;
}

// Дейкстра
QVector<int> Graph::dijkstra(int startVertex, QVector<int>& distances) {
    QVector<int> parent(maxVertices + 1, -1);
    QVector<bool> visited(maxVertices + 1, false);

    distances.resize(maxVertices + 1);
    for (int i = 1; i <= maxVertices; i++) {
        distances[i] = 999999;
    }
    distances[startVertex] = 0;

    for (int count = 0; count < maxVertices; count++) {
        int u = getMinDistanceVertex(distances, visited);
        if (u == -1) break;

        visited[u] = true;
        QVector<Edge> outgoingEdges = getEdgesFrom(u);

        for (int i = 0; i < outgoingEdges.size(); i++) {
            int v = outgoingEdges[i].to;
            int weight = outgoingEdges[i].weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                parent[v] = u;
            }
        }
    }
    return parent;
}

// Флойд-Уоршелл
void Graph::floydWarshall(int**& distMatrix, int**& pathMat) {
    initializeMatrices();
    int INF = 999999;

    int** D = new int*[maxVertices + 1];
    int** P = new int*[maxVertices + 1];

    for (int i = 0; i <= maxVertices; i++) {
        D[i] = new int[maxVertices + 1];
        P[i] = new int[maxVertices + 1];

        for (int j = 0; j <= maxVertices; j++) {
            D[i][j] = distanceMatrix[i][j];
            P[i][j] = pathMatrix[i][j];
        }
    }

    for (int k = 1; k <= maxVertices; k++) {
        for (int i = 1; i <= maxVertices; i++) {
            for (int j = 1; j <= maxVertices; j++) {
                if (D[i][k] != INF && D[k][j] != INF) {
                    if (D[i][k] + D[k][j] < D[i][j]) {
                        D[i][j] = D[i][k] + D[k][j];
                        P[i][j] = P[k][j];
                    }
                }
            }
        }
    }

    distMatrix = D;
    pathMat = P;
}

QString Graph::getPathString(int from, int to, int** pathMat) {
    QString result = "";
    QVector<int> path;

    int current = to;
    path.append(current);

    while (current != from && current != 0) {
        current = pathMat[from][current];
        if (current != 0) {
            path.prepend(current);
        }
    }

    if (current == 0) {
        return "Путь не существует";
    }

    for (int i = 0; i < path.size(); i++) {
        result += QString::number(path[i]);
        if (i < path.size() - 1) {
            result += " -> ";
        }
    }
    return result;
}

// ==================== Реализация MainWindow ====================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graph = new Graph(10);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 800, 600);

    // Устанавливаем фильтр событий для graphicsView
    ui->graphicsView->viewport()->installEventFilter(this);

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &MainWindow::updateAnimation);
    isAnimating = false;
    currentAnimationStep = 0;

    isAddingEdgeMode = false;
    selectedStartVertex = -1;

    ui->matrixTable->setRowCount(10);
    ui->matrixTable->setColumnCount(10);
    QStringList headers;
    for (int i = 1; i <= 10; i++) {
        headers << QString::number(i);
    }
    ui->matrixTable->setHorizontalHeaderLabels(headers);
    ui->matrixTable->setVerticalHeaderLabels(headers);

    for (int i = 0; i < 10; i++) {
        ui->matrixTable->setColumnWidth(i, 50);
        ui->matrixTable->setRowHeight(i, 30);
    }

    setupDefaultGraph();
    drawGraph();
    refreshMatrixTable();

    setWindowTitle("Граф - Интерактивное добавление вершин и рёбер");
    updateStatusMessage("Готов к работе. Кликните по сцене для добавления вершины, или нажмите кнопку 'Добавить ребро'");
}

MainWindow::~MainWindow() {
    delete graph;
    delete ui;
}

// Фильтр событий для обработки кликов по graphicsView
bool MainWindow::eventFilter(QObject* watched, QEvent* event) {
    if (watched == ui->graphicsView->viewport() && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QPointF scenePos = ui->graphicsView->mapToScene(mouseEvent->pos());
            onSceneClicked(scenePos);
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

int MainWindow::findVertexAtPosition(double x, double y, double radius) {
    QVector<Vertex> vertices = graph->getVertices();
    for (int i = 0; i < vertices.size(); i++) {
        double dx = vertices[i].x - x;
        double dy = vertices[i].y - y;
        if (sqrt(dx*dx + dy*dy) <= radius) {
            return vertices[i].id;
        }
    }
    return -1;
}

void MainWindow::onSceneClicked(const QPointF& pos) {
    if (isAddingEdgeMode) {
        int clickedVertex = findVertexAtPosition(pos.x(), pos.y());
        if (clickedVertex != -1) {
            if (selectedStartVertex == -1) {
                selectedStartVertex = clickedVertex;
                updateStatusMessage("Выбрана начальная вершина " + QString::number(selectedStartVertex) +
                                    ". Теперь выберите конечную вершину.");
                drawGraph();
                highlightVertex(selectedStartVertex, QColor(255, 200, 100));
            } else {
                if (selectedStartVertex == clickedVertex) {
                    updateStatusMessage("Нельзя создать петлю! Выберите другую вершину.");
                    return;
                }

                if (graph->hasEdge(selectedStartVertex, clickedVertex)) {
                    updateStatusMessage("Ребро уже существует!");
                    isAddingEdgeMode = false;
                    selectedStartVertex = -1;
                    drawGraph();
                    return;
                }

                bool ok;
                int weight = QInputDialog::getInt(this, "Вес ребра",
                                                  "Введите вес ребра от " +
                                                      QString::number(selectedStartVertex) +
                                                      " до " + QString::number(clickedVertex) + ":",
                                                  1, 1, 999, 1, &ok);
                if (ok) {
                    graph->addEdge(selectedStartVertex, clickedVertex, weight);
                    drawGraph();
                    refreshMatrixTable();
                    updateStatusMessage("Ребро " + QString::number(selectedStartVertex) +
                                        " → " + QString::number(clickedVertex) +
                                        " с весом " + QString::number(weight) + " добавлено.");
                } else {
                    updateStatusMessage("Добавление ребра отменено.");
                }
                isAddingEdgeMode = false;
                selectedStartVertex = -1;
                drawGraph();
            }
        } else {
            if (selectedStartVertex == -1) {
                updateStatusMessage("Кликните на вершине, чтобы выбрать начальную вершину.");
            } else {
                updateStatusMessage("Кликните на вершине, чтобы выбрать конечную вершину.");
            }
        }
    } else {
        int newId = graph->getNextVertexId();
        if (newId > 10) {
            updateStatusMessage("Достигнуто максимальное количество вершин (10)");
            QMessageBox::warning(this, "Ошибка", "Максимальное количество вершин - 10!");
            return;
        }
        graph->addVertex(pos.x(), pos.y());
        drawGraph();
        refreshMatrixTable();
        updateStatusMessage("Добавлена вершина " + QString::number(newId) +
                            " в позиции (" + QString::number(pos.x(), 'f', 0) +
                            ", " + QString::number(pos.y(), 'f', 0) + ")");
    }
}

void MainWindow::setupDefaultGraph() {
    graph->addVertex(1, 400, 50);
    graph->addVertex(2, 600, 200);
    graph->addVertex(3, 200, 200);
    graph->addVertex(4, 400, 350);
    graph->addVertex(5, 200, 350);
    graph->addVertex(6, 600, 350);

    graph->addEdge(1, 3, 13);
    graph->addEdge(1, 4, 15);
    graph->addEdge(2, 1, 28);
    graph->addEdge(2, 4, 20);
    graph->addEdge(3, 5, 30);
    graph->addEdge(4, 5, 39);
    graph->addEdge(4, 6, 31);
    graph->addEdge(5, 2, 21);
    graph->addEdge(5, 4, 39);
    graph->addEdge(6, 1, 18);
}

void MainWindow::clearScene() {
    scene->clear();
}

void MainWindow::drawGraph() {
    clearScene();

    QVector<Edge> edges = graph->getEdges();
    for (int i = 0; i < edges.size(); i++) {
        drawEdge(edges[i].from, edges[i].to, edges[i].weight, Qt::black);
    }

    QVector<Vertex> vertices = graph->getVertices();
    for (int i = 0; i < vertices.size(); i++) {
        drawVertex(vertices[i].id, vertices[i].x, vertices[i].y, QColor(173, 216, 230));
    }
}

void MainWindow::drawVertex(int id, double x, double y, QColor color, bool highlight) {
    double radius = 25;
    QColor fillColor = highlight ? QColor(255, 200, 100) : color;

    QGraphicsEllipseItem* circle = scene->addEllipse(x - radius, y - radius,
                                                     radius * 2, radius * 2,
                                                     QPen(Qt::black, 2),
                                                     QBrush(fillColor));

    QGraphicsTextItem* text = scene->addText(QString::number(id));
    text->setPos(x - 8, y - 12);
    QFont font = text->font();
    font.setBold(true);
    font.setPointSize(14);
    text->setFont(font);
}

void MainWindow::drawArrow(double fromX, double fromY, double toX, double toY, QColor color) {
    double arrowSize = 15;
    double angle = atan2(toY - fromY, toX - fromX);

    double x1 = toX - arrowSize * cos(angle - 0.5);
    double y1 = toY - arrowSize * sin(angle - 0.5);
    double x2 = toX - arrowSize * cos(angle + 0.5);
    double y2 = toY - arrowSize * sin(angle + 0.5);

    QPolygonF arrowHead;
    arrowHead << QPointF(toX, toY)
              << QPointF(x1, y1)
              << QPointF(x2, y2);

    scene->addPolygon(arrowHead, QPen(color), QBrush(color));
}

void MainWindow::drawEdge(int from, int to, int weight, QColor color, int penWidth) {
    Vertex vFrom = graph->getVertex(from);
    Vertex vTo = graph->getVertex(to);

    if (vFrom.id == -1 || vTo.id == -1) return;

    double radius = 25;
    double angle = atan2(vTo.y - vFrom.y, vTo.x - vFrom.x);

    double startX = vFrom.x + radius * cos(angle);
    double startY = vFrom.y + radius * sin(angle);
    double endX = vTo.x - radius * cos(angle);
    double endY = vTo.y - radius * sin(angle);

    QPen pen(color);
    pen.setWidth(penWidth);
    scene->addLine(startX, startY, endX, endY, pen);

    drawArrow((startX + endX) / 2, (startY + endY) / 2, endX, endY, color);

    double midX = (startX + endX) / 2;
    double midY = (startY + endY) / 2;
    double offsetX = -15 * sin(angle);
    double offsetY = 15 * cos(angle);

    QGraphicsTextItem* weightText = scene->addText(QString::number(weight));
    weightText->setPos(midX + offsetX - 10, midY + offsetY - 10);
    weightText->setDefaultTextColor(color);
    QFont weightFont = weightText->font();
    weightFont.setPointSize(12);
    weightText->setFont(weightFont);
}

void MainWindow::highlightVertex(int id, QColor color) {
    Vertex v = graph->getVertex(id);
    if (v.id != -1) {
        drawVertex(v.id, v.x, v.y, color, true);
    }
}

void MainWindow::highlightEdge(int from, int to, QColor color) {
    int weight = graph->getEdgeWeight(from, to);
    if (weight > 0) {
        drawEdge(from, to, weight, color, 3);
    }
}

void MainWindow::resetAllHighlights() {
    drawGraph();
}

void MainWindow::startAnimation(QVector<int> path, QVector<QPair<int, int>> highlightEdges) {
    stopAnimation();
    animationPath = path;
    animationEdges = highlightEdges;
    currentAnimationStep = 0;
    isAnimating = true;
    animationTimer->start(1000);
}

void MainWindow::stopAnimation() {
    animationTimer->stop();
    isAnimating = false;
    resetAllHighlights();
}

void MainWindow::updateAnimation() {
    if (!isAnimating) return;

    drawGraph();

    if (currentAnimationStep < animationPath.size()) {
        int currentVertex = animationPath[currentAnimationStep];
        highlightVertex(currentVertex, QColor(255, 200, 100));

        for (int i = 0; i < currentAnimationStep; i++) {
            highlightVertex(animationPath[i], QColor(144, 238, 144));
        }

        if (currentAnimationStep < animationEdges.size()) {
            highlightEdge(animationEdges[currentAnimationStep].first,
                          animationEdges[currentAnimationStep].second,
                          QColor(255, 0, 0));
        }

        for (int i = 0; i < currentAnimationStep && i < animationEdges.size(); i++) {
            highlightEdge(animationEdges[i].first,
                          animationEdges[i].second,
                          QColor(0, 0, 255));
        }

        currentAnimationStep++;
    } else {
        stopAnimation();
        QMessageBox::information(this, "Анимация завершена",
                                 "Алгоритм выполнен. Пройденные вершины отмечены зелёным.");
    }
}

double MainWindow::calculateDistance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

QPointF MainWindow::getEdgeMidpoint(Vertex from, Vertex to, double offset) {
    double midX = (from.x + to.x) / 2;
    double midY = (from.y + to.y) / 2;
    return QPointF(midX, midY);
}

void MainWindow::refreshMatrixTable() {
    int** matrix = graph->getAdjacencyMatrix();
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int value = matrix[i + 1][j + 1];
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(value));
            item->setTextAlignment(Qt::AlignCenter);
            ui->matrixTable->setItem(i, j, item);
        }
    }
}

void MainWindow::updateStatusMessage(const QString& message) {
    ui->statusLabel->setText(message);
    qDebug() << message;
}

void MainWindow::on_addVertexButton_clicked() {
    isAddingEdgeMode = false;
    selectedStartVertex = -1;
    updateStatusMessage("Режим добавления вершин. Кликните по сцене, чтобы добавить вершину.");
}

void MainWindow::on_addEdgeButton_clicked() {
    isAddingEdgeMode = true;
    selectedStartVertex = -1;
    updateStatusMessage("Режим добавления рёбер. Кликните на начальной вершине, затем на конечной.");
}

void MainWindow::on_removeVertexButton_clicked() {
    bool ok;
    int id = QInputDialog::getInt(this, "Удаление вершины",
                                  "Введите номер вершины для удаления:",
                                  1, 1, 10, 1, &ok);

    if (ok) {
        if (!graph->hasVertex(id)) {
            QMessageBox::warning(this, "Ошибка", "Вершина не существует!");
            return;
        }
        graph->removeVertex(id);
        drawGraph();
        refreshMatrixTable();
        updateStatusMessage("Вершина " + QString::number(id) + " удалена.");
    }
}

void MainWindow::on_removeEdgeButton_clicked() {
    bool ok;
    int from = QInputDialog::getInt(this, "Удаление ребра",
                                    "Введите начальную вершину:",
                                    1, 1, 10, 1, &ok);
    if (!ok) return;

    int to = QInputDialog::getInt(this, "Удаление ребра",
                                  "Введите конечную вершину:",
                                  1, 1, 10, 1, &ok);
    if (!ok) return;

    if (!graph->hasEdge(from, to)) {
        QMessageBox::warning(this, "Ошибка", "Такого ребра не существует!");
        return;
    }

    graph->removeEdge(from, to);
    drawGraph();
    refreshMatrixTable();
    updateStatusMessage("Ребро " + QString::number(from) + " → " + QString::number(to) + " удалено.");
}

void MainWindow::on_editWeightButton_clicked() {
    bool ok;
    int from = QInputDialog::getInt(this, "Изменение веса",
                                    "Введите начальную вершину:",
                                    1, 1, 10, 1, &ok);
    if (!ok) return;

    int to = QInputDialog::getInt(this, "Изменение веса",
                                  "Введите конечную вершину:",
                                  1, 1, 10, 1, &ok);
    if (!ok) return;

    if (!graph->hasEdge(from, to)) {
        QMessageBox::warning(this, "Ошибка", "Такого ребра не существует!");
        return;
    }

    int oldWeight = graph->getEdgeWeight(from, to);
    int newWeight = QInputDialog::getInt(this, "Изменение веса",
                                         "Введите новый вес ребра (старый: " +
                                             QString::number(oldWeight) + "):",
                                         oldWeight, 1, 999, 1, &ok);
    if (!ok) return;

    graph->updateEdgeWeight(from, to, newWeight);
    drawGraph();
    refreshMatrixTable();
    updateStatusMessage("Вес ребра " + QString::number(from) + " → " +
                        QString::number(to) + " изменён на " + QString::number(newWeight));
}

void MainWindow::on_editMatrixButton_clicked() {
    refreshMatrixTable();
}

void MainWindow::on_bfsButton_clicked() {
    bool ok;
    int startVertex = QInputDialog::getInt(this, "Обход в ширину",
                                           "Введите начальную вершину (по варианту - 5):",
                                           5, 1, 10, 1, &ok);

    if (ok) {
        if (!graph->hasVertex(startVertex)) {
            QMessageBox::warning(this, "Ошибка", "Такой вершины не существует!");
            return;
        }

        QVector<int> bfsResult = graph->breadthFirstSearch(startVertex);

        QVector<QPair<int, int>> edges;
        for (int i = 0; i < bfsResult.size() - 1; i++) {
            if (graph->hasEdge(bfsResult[i], bfsResult[i + 1])) {
                edges.append(QPair<int, int>(bfsResult[i], bfsResult[i + 1]));
            } else {
                edges.append(QPair<int, int>(-1, -1));
            }
        }

        QString resultStr = "Обход в ширину (BFS): ";
        for (int i = 0; i < bfsResult.size(); i++) {
            resultStr += QString::number(bfsResult[i]);
            if (i < bfsResult.size() - 1) {
                resultStr += " -> ";
            }
        }

        ui->statusLabel->setText(resultStr);
        startAnimation(bfsResult, edges);
    }
}

void MainWindow::on_dfsButton_clicked() {
    bool ok;
    int startVertex = QInputDialog::getInt(this, "Обход в глубину",
                                           "Введите начальную вершину (по варианту - 5):",
                                           5, 1, 10, 1, &ok);

    if (ok) {
        if (!graph->hasVertex(startVertex)) {
            QMessageBox::warning(this, "Ошибка", "Такой вершины не существует!");
            return;
        }

        QVector<int> dfsResult = graph->depthFirstSearch(startVertex);

        QVector<QPair<int, int>> edges;
        for (int i = 0; i < dfsResult.size() - 1; i++) {
            if (graph->hasEdge(dfsResult[i], dfsResult[i + 1])) {
                edges.append(QPair<int, int>(dfsResult[i], dfsResult[i + 1]));
            } else {
                edges.append(QPair<int, int>(-1, -1));
            }
        }

        QString resultStr = "Обход в глубину (DFS): ";
        for (int i = 0; i < dfsResult.size(); i++) {
            resultStr += QString::number(dfsResult[i]);
            if (i < dfsResult.size() - 1) {
                resultStr += " -> ";
            }
        }

        ui->statusLabel->setText(resultStr);
        startAnimation(dfsResult, edges);
    }
}

void MainWindow::on_dijkstraButton_clicked() {
    bool ok;
    int startVertex = QInputDialog::getInt(this, "Алгоритм Дейкстры",
                                           "Введите начальную вершину (по варианту - 5):",
                                           5, 1, 10, 1, &ok);

    if (ok) {
        if (!graph->hasVertex(startVertex)) {
            QMessageBox::warning(this, "Ошибка", "Такой вершины не существует!");
            return;
        }

        QVector<int> distances;
        QVector<int> parents = graph->dijkstra(startVertex, distances);

        QString resultStr = "Алгоритм Дейкстры от вершины " + QString::number(startVertex) + ":\n\n";

        for (int i = 1; i <= 10; i++) {
            if (graph->hasVertex(i) && i != startVertex) {
                resultStr += "До вершины " + QString::number(i) + ": ";
                if (distances[i] == 999999) {
                    resultStr += "недостижима\n";
                } else {
                    resultStr += "расстояние = " + QString::number(distances[i]) + "\n";

                    QString path = QString::number(i);
                    int current = i;
                    while (parents[current] != -1 && parents[current] != startVertex) {
                        path = QString::number(parents[current]) + " -> " + path;
                        current = parents[current];
                    }
                    if (parents[current] != -1) {
                        path = QString::number(startVertex) + " -> " + path;
                    }
                    resultStr += "Путь: " + path + "\n\n";
                }
            }
        }

        QMessageBox::information(this, "Результат Дейкстры", resultStr);

        int farthestVertex = -1;
        int maxDist = -1;
        for (int i = 1; i <= 10; i++) {
            if (graph->hasVertex(i) && distances[i] != 999999 && distances[i] > maxDist) {
                maxDist = distances[i];
                farthestVertex = i;
            }
        }

        if (farthestVertex != -1) {
            QVector<int> pathVertices;
            QVector<QPair<int, int>> pathEdges;

            int current = farthestVertex;
            pathVertices.prepend(current);

            while (parents[current] != -1) {
                int parent = parents[current];
                pathVertices.prepend(parent);
                pathEdges.prepend(QPair<int, int>(parent, current));
                current = parent;
            }

            startAnimation(pathVertices, pathEdges);
        }
    }
}

void MainWindow::on_floydButton_clicked() {
    int** distMatrix;
    int** pathMat;

    graph->floydWarshall(distMatrix, pathMat);

    QString resultStr = "Алгоритм Флойда-Уоршелла\n\n";

    resultStr += "Матрица кратчайших расстояний D:\n";
    resultStr += "    ";
    for (int j = 1; j <= 10; j++) {
        if (graph->hasVertex(j)) {
            resultStr += QString::number(j) + "     ";
        }
    }
    resultStr += "\n";

    for (int i = 1; i <= 10; i++) {
        if (graph->hasVertex(i)) {
            resultStr += QString::number(i) + "   ";
            for (int j = 1; j <= 10; j++) {
                if (graph->hasVertex(j)) {
                    if (distMatrix[i][j] == 999999) {
                        resultStr += "INF   ";
                    } else {
                        QString num = QString::number(distMatrix[i][j]);
                        while (num.length() < 5) {
                            num += " ";
                        }
                        resultStr += num + " ";
                    }
                }
            }
            resultStr += "\n";
        }
    }

    resultStr += "\nМатрица путей P:\n";
    resultStr += "    ";
    for (int j = 1; j <= 10; j++) {
        if (graph->hasVertex(j)) {
            resultStr += QString::number(j) + "     ";
        }
    }
    resultStr += "\n";

    for (int i = 1; i <= 10; i++) {
        if (graph->hasVertex(i)) {
            resultStr += QString::number(i) + "   ";
            for (int j = 1; j <= 10; j++) {
                if (graph->hasVertex(j)) {
                    QString num = QString::number(pathMat[i][j]);
                    while (num.length() < 5) {
                        num += " ";
                    }
                    resultStr += num + " ";
                }
            }
            resultStr += "\n";
        }
    }

    resultStr += "\nКратчайшие пути от вершины 5 (по варианту):\n";
    int startV = 5;
    if (graph->hasVertex(startV)) {
        for (int i = 1; i <= 10; i++) {
            if (graph->hasVertex(i) && i != startV) {
                if (distMatrix[startV][i] != 999999) {
                    QString path = graph->getPathString(startV, i, pathMat);
                    resultStr += "От " + QString::number(startV) + " до " +
                                 QString::number(i) + ": расстояние = " +
                                 QString::number(distMatrix[startV][i]) +
                                 ", путь: " + path + "\n";
                } else {
                    resultStr += "От " + QString::number(startV) + " до " +
                                 QString::number(i) + ": путь не существует\n";
                }
            }
        }
    }

    QMessageBox::information(this, "Результат Флойда", resultStr);

    QVector<int> animationVertices;
    QVector<QPair<int, int>> animationEdgesList;

    int maxPathVertex = -1;
    int maxPathLength = -1;

    for (int i = 1; i <= 10; i++) {
        if (graph->hasVertex(i) && i != startV && distMatrix[startV][i] != 999999) {
            if (distMatrix[startV][i] > maxPathLength) {
                maxPathLength = distMatrix[startV][i];
                maxPathVertex = i;
            }
        }
    }

    if (maxPathVertex != -1) {
        int current = maxPathVertex;
        animationVertices.prepend(current);

        while (current != startV && current != 0) {
            int prev = pathMat[startV][current];
            if (prev != 0) {
                animationVertices.prepend(prev);
                animationEdgesList.prepend(QPair<int, int>(prev, current));
                current = prev;
            } else {
                break;
            }
        }

        startAnimation(animationVertices, animationEdgesList);
    }

    for (int i = 0; i <= 10; i++) {
        delete[] distMatrix[i];
        delete[] pathMat[i];
    }
    delete[] distMatrix;
    delete[] pathMat;
}

void MainWindow::on_resetViewButton_clicked() {
    stopAnimation();
    drawGraph();
    updateStatusMessage("Вид сброшен.");
}

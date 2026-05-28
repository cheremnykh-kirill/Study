#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QPen>
#include <QBrush>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QDebug>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 800, 500);

    // Устанавливаем фильтр событий для обработки кликов
    ui->graphicsView->viewport()->installEventFilter(this);

    nodeCount = 0;
    currentAnimStep = 0;
    nextVertexId = 0;

    // Режимы
    isAddingVertexMode = true;
    isAddingEdgeMode = false;
    isRemovingVertexMode = false;
    isRemovingEdgeMode = false;
    selectedStartVertex = -1;

    // Создаём текстовое поле для вывода
    outputText = new QTextEdit(this);
    outputText->setGeometry(820, 20, 250, 300);
    outputText->setReadOnly(true);

    // Кнопка для переключения в режим добавления вершин
    QPushButton *addVertexModeBtn = new QPushButton("Режим: Добавить вершину (активен)", this);
    addVertexModeBtn->setGeometry(820, 330, 250, 30);
    addVertexModeBtn->setStyleSheet("background-color: #90EE90; font-weight: bold;");
    connect(addVertexModeBtn, &QPushButton::clicked, [this, addVertexModeBtn]() {
        isAddingVertexMode = true;
        isAddingEdgeMode = false;
        isRemovingVertexMode = false;
        isRemovingEdgeMode = false;
        selectedStartVertex = -1;
        addVertexModeBtn->setStyleSheet("background-color: #90EE90; font-weight: bold;");
        updateStatusMessage("Режим: добавление вершин. Кликните по сцене для добавления вершины.");
    });

    // Кнопка для переключения в режим добавления рёбер
    QPushButton *addEdgeModeBtn = new QPushButton("Режим: Добавить ребро", this);
    addEdgeModeBtn->setGeometry(820, 365, 250, 30);
    connect(addEdgeModeBtn, &QPushButton::clicked, [this, addEdgeModeBtn, addVertexModeBtn]() {
        isAddingVertexMode = false;
        isAddingEdgeMode = true;
        isRemovingVertexMode = false;
        isRemovingEdgeMode = false;
        selectedStartVertex = -1;
        addVertexModeBtn->setStyleSheet("");
        addEdgeModeBtn->setStyleSheet("background-color: #90EE90; font-weight: bold;");
        updateStatusMessage("Режим: добавление рёбер. Кликните на начальной вершине, затем на конечной.");
    });

    // Кнопка для переключения в режим удаления вершин
    QPushButton *removeVertexModeBtn = new QPushButton("Режим: Удалить вершину", this);
    removeVertexModeBtn->setGeometry(820, 400, 250, 30);
    connect(removeVertexModeBtn, &QPushButton::clicked, [this, removeVertexModeBtn, addVertexModeBtn]() {
        isAddingVertexMode = false;
        isAddingEdgeMode = false;
        isRemovingVertexMode = true;
        isRemovingEdgeMode = false;
        selectedStartVertex = -1;
        addVertexModeBtn->setStyleSheet("");
        removeVertexModeBtn->setStyleSheet("background-color: #90EE90; font-weight: bold;");
        updateStatusMessage("Режим: удаление вершин. Кликните на вершине для удаления.");
    });

    // Кнопка для переключения в режим удаления рёбер
    QPushButton *removeEdgeModeBtn = new QPushButton("Режим: Удалить ребро", this);
    removeEdgeModeBtn->setGeometry(820, 435, 250, 30);
    connect(removeEdgeModeBtn, &QPushButton::clicked, [this, removeEdgeModeBtn, addVertexModeBtn]() {
        isAddingVertexMode = false;
        isAddingEdgeMode = false;
        isRemovingVertexMode = false;
        isRemovingEdgeMode = true;
        selectedStartVertex = -1;
        addVertexModeBtn->setStyleSheet("");
        removeEdgeModeBtn->setStyleSheet("background-color: #90EE90; font-weight: bold;");
        updateStatusMessage("Режим: удаление рёбер. Кликните на ребре для удаления.");
    });

    // Кнопка "Решить TSP"
    QPushButton *solveBtn = new QPushButton("Решить TSP", this);
    solveBtn->setGeometry(820, 475, 250, 30);
    solveBtn->setStyleSheet("background-color: #FFB6C1; font-weight: bold;");
    connect(solveBtn, &QPushButton::clicked, this, &MainWindow::on_solve_clicked);

    // Кнопка "Очистить всё"
    QPushButton *clearBtn = new QPushButton("Очистить всё", this);
    clearBtn->setGeometry(820, 510, 250, 30);
    clearBtn->setStyleSheet("background-color: #FFA500; font-weight: bold;");
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::on_clear_clicked);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::animateNextStep);

    // Добавляем тестовый граф для демонстрации
    setupDefaultGraph();

    updateStatusMessage("Готов к работе. Режим: добавление вершин. Кликните по сцене.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupDefaultGraph()
{
    // Добавляем тестовые вершины
    nodes.append(qMakePair(QPointF(400, 80), 0));
    nodes.append(qMakePair(QPointF(150, 150), 1));
    nodes.append(qMakePair(QPointF(650, 150), 2));
    nodes.append(qMakePair(QPointF(150, 350), 3));
    nodes.append(qMakePair(QPointF(650, 350), 4));
    nodes.append(qMakePair(QPointF(400, 420), 5));
    nodeCount = 6;
    nextVertexId = 6;

    // Инициализируем матрицу смежности
    adjMatrix.resize(nodeCount);
    for (int i = 0; i < nodeCount; i++) {
        adjMatrix[i].resize(nodeCount);
        for (int j = 0; j < nodeCount; j++) {
            adjMatrix[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }

    // Добавляем рёбра
    auto addEdgeToMatrix = [this](int from, int to, int weight) {
        adjMatrix[from][to] = weight;
        adjMatrix[to][from] = weight;
    };

    addEdgeToMatrix(0, 1, 10);
    addEdgeToMatrix(0, 2, 15);
    addEdgeToMatrix(0, 3, 20);
    addEdgeToMatrix(0, 5, 50);
    addEdgeToMatrix(1, 2, 35);
    addEdgeToMatrix(1, 4, 25);
    addEdgeToMatrix(1, 5, 45);
    addEdgeToMatrix(2, 3, 30);
    addEdgeToMatrix(2, 4, 20);
    addEdgeToMatrix(3, 4, 15);
    addEdgeToMatrix(3, 5, 40);
    addEdgeToMatrix(4, 5, 10);

    // Заполняем список рёбер
    edges.clear();
    for (int i = 0; i < nodeCount; i++) {
        for (int j = i + 1; j < nodeCount; j++) {
            if (adjMatrix[i][j] != INT_MAX && adjMatrix[i][j] != 0) {
                Edge e;
                e.from = i;
                e.to = j;
                e.weight = adjMatrix[i][j];
                edges.append(e);
            }
        }
    }

    drawGraph();
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui->graphicsView->viewport() && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (mouseEvent && mouseEvent->button() == Qt::LeftButton) {
            onSceneClicked(ui->graphicsView->mapToScene(mouseEvent->pos()));
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

int MainWindow::findVertexAtPosition(double x, double y, double radius)
{
    for (int i = 0; i < nodes.size(); i++) {
        double dx = nodes[i].first.x() - x;
        double dy = nodes[i].first.y() - y;
        if (sqrt(dx*dx + dy*dy) <= radius) {
            return nodes[i].second;
        }
    }
    return -1;
}

void MainWindow::onSceneClicked(const QPointF& pos)
{
    if (isAddingVertexMode) {
        // Добавление вершины
        int newId = getNextFreeId();
        nodes.append(qMakePair(pos, newId));
        nodeCount++;
        nextVertexId = newId + 1;

        // Расширяем матрицу смежности
        adjMatrix.resize(nodeCount);
        for (int i = 0; i < nodeCount; i++) {
            adjMatrix[i].resize(nodeCount);
            if (i == nodeCount - 1) {
                for (int j = 0; j < nodeCount; j++) {
                    adjMatrix[i][j] = (i == j) ? 0 : INT_MAX;
                }
            }
        }

        drawGraph();
        updateStatusMessage("Добавлена вершина " + QString::number(newId));

    } else if (isAddingEdgeMode) {
        // Добавление ребра
        int clickedVertex = findVertexAtPosition(pos.x(), pos.y());
        if (clickedVertex != -1) {
            if (selectedStartVertex == -1) {
                selectedStartVertex = clickedVertex;
                updateStatusMessage("Выбрана начальная вершина " + QString::number(selectedStartVertex) +
                                    ". Теперь выберите конечную вершину.");
                drawGraph();
                // Подсвечиваем выбранную вершину
                for (int i = 0; i < nodeItems.size(); i++) {
                    if (nodes[i].second == selectedStartVertex) {
                        nodeItems[i]->setBrush(QBrush(QColor(255, 200, 100)));
                        break;
                    }
                }
            } else {
                if (selectedStartVertex == clickedVertex) {
                    updateStatusMessage("Нельзя создать петлю! Выберите другую вершину.");
                    selectedStartVertex = -1;
                    drawGraph();
                    return;
                }

                bool ok;
                int weight = QInputDialog::getInt(this, "Вес ребра",
                                                  "Введите вес ребра от " +
                                                      QString::number(selectedStartVertex) +
                                                      " до " + QString::number(clickedVertex) + ":",
                                                  10, 1, 999, 1, &ok);
                if (ok) {
                    int fromIdx = -1, toIdx = -1;
                    for (int i = 0; i < nodes.size(); i++) {
                        if (nodes[i].second == selectedStartVertex) fromIdx = i;
                        if (nodes[i].second == clickedVertex) toIdx = i;
                    }
                    if (fromIdx != -1 && toIdx != -1) {
                        adjMatrix[fromIdx][toIdx] = weight;
                        adjMatrix[toIdx][fromIdx] = weight;

                        Edge e;
                        e.from = fromIdx;
                        e.to = toIdx;
                        e.weight = weight;
                        edges.append(e);

                        drawGraph();
                        updateStatusMessage("Ребро " + QString::number(selectedStartVertex) +
                                            " — " + QString::number(clickedVertex) +
                                            " с весом " + QString::number(weight) + " добавлено.");
                    }
                } else {
                    updateStatusMessage("Добавление ребра отменено.");
                }
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

    } else if (isRemovingVertexMode) {
        // Удаление вершины
        int clickedVertex = findVertexAtPosition(pos.x(), pos.y());
        if (clickedVertex != -1) {
            // Удаляем все рёбра, связанные с вершиной
            QVector<Edge> newEdges;
            for (const Edge& e : edges) {
                int fromId = nodes[e.from].second;
                int toId = nodes[e.to].second;
                if (fromId != clickedVertex && toId != clickedVertex) {
                    newEdges.append(e);
                }
            }
            edges = newEdges;

            // Удаляем вершину
            int indexToRemove = -1;
            for (int i = 0; i < nodes.size(); i++) {
                if (nodes[i].second == clickedVertex) {
                    indexToRemove = i;
                    break;
                }
            }
            if (indexToRemove != -1) {
                nodes.removeAt(indexToRemove);
                nodeCount--;
            }

            // Перестраиваем матрицу смежности
            updateAdjacencyMatrix();
            drawGraph();
            updateStatusMessage("Вершина " + QString::number(clickedVertex) + " удалена.");
        } else {
            updateStatusMessage("Кликните на вершине, которую хотите удалить.");
        }

    } else if (isRemovingEdgeMode) {
        // Удаление ребра
        double minDist = 20.0;
        int edgeToRemove = -1;
        for (int i = 0; i < edges.size(); i++) {
            QPointF p1 = nodes[edges[i].from].first;
            QPointF p2 = nodes[edges[i].to].first;
            double dx = p2.x() - p1.x();
            double dy = p2.y() - p1.y();
            double len = sqrt(dx*dx + dy*dy);
            if (len < 0.001) continue;
            double t = ((pos.x() - p1.x()) * dx + (pos.y() - p1.y()) * dy) / (len * len);
            t = std::max(0.0, std::min(1.0, t));
            double projX = p1.x() + t * dx;
            double projY = p1.y() + t * dy;
            double dist = sqrt((pos.x() - projX)*(pos.x() - projX) + (pos.y() - projY)*(pos.y() - projY));
            if (dist < minDist) {
                minDist = dist;
                edgeToRemove = i;
            }
        }
        if (edgeToRemove != -1) {
            int fromIdx = edges[edgeToRemove].from;
            int toIdx = edges[edgeToRemove].to;
            adjMatrix[fromIdx][toIdx] = INT_MAX;
            adjMatrix[toIdx][fromIdx] = INT_MAX;
            edges.removeAt(edgeToRemove);
            drawGraph();
            updateStatusMessage("Ребро удалено.");
        } else {
            updateStatusMessage("Кликните на ребре, которое хотите удалить.");
        }
    }
}

int MainWindow::getNextFreeId()
{
    QSet<int> existingIds;
    for (const auto& node : nodes) {
        existingIds.insert(node.second);
    }
    int id = 0;
    while (existingIds.contains(id)) {
        id++;
    }
    return id;
}

void MainWindow::updateAdjacencyMatrix()
{
    adjMatrix.resize(nodeCount);
    for (int i = 0; i < nodeCount; i++) {
        adjMatrix[i].resize(nodeCount);
        for (int j = 0; j < nodeCount; j++) {
            adjMatrix[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }

    for (const Edge& e : edges) {
        adjMatrix[e.from][e.to] = e.weight;
        adjMatrix[e.to][e.from] = e.weight;
    }
}

void MainWindow::drawGraph()
{
    scene->clear();
    nodeItems.clear();
    edgeItems.clear();
    labelItems.clear();

    // Рисуем рёбра
    for (int i = 0; i < edges.size(); i++) {
        QPointF p1 = nodes[edges[i].from].first;
        QPointF p2 = nodes[edges[i].to].first;
        QGraphicsLineItem *line = scene->addLine(p1.x(), p1.y(), p2.x(), p2.y(),
                                                 QPen(Qt::black, 2));
        edgeItems.append(line);

        double mx = (p1.x() + p2.x()) / 2;
        double my = (p1.y() + p2.y()) / 2;
        QGraphicsTextItem *text = scene->addText(QString::number(edges[i].weight));
        text->setPos(mx - 10, my - 20);
        text->setDefaultTextColor(Qt::red);
        QFont font = text->font();
        font.setPointSize(11);
        font.setBold(true);
        text->setFont(font);
        labelItems.append(text);
    }

    // Рисуем вершины
    for (int i = 0; i < nodes.size(); i++) {
        QPointF p = nodes[i].first;
        QGraphicsEllipseItem *node = scene->addEllipse(p.x()-18, p.y()-18, 36, 36,
                                                       QPen(Qt::black, 2),
                                                       QBrush(Qt::cyan));
        nodeItems.append(node);

        QGraphicsTextItem *text = scene->addText(QString::number(nodes[i].second));
        text->setPos(p.x()-8, p.y()-12);
        QFont font = text->font();
        font.setBold(true);
        font.setPointSize(14);
        text->setFont(font);
        labelItems.append(text);
    }
}

void MainWindow::resetColors()
{
    for (int i = 0; i < nodeItems.size(); i++) {
        nodeItems[i]->setBrush(QBrush(Qt::cyan));
    }
    for (int i = 0; i < edgeItems.size(); i++) {
        edgeItems[i]->setPen(QPen(Qt::black, 2));
    }
}

void MainWindow::highlightPath(int step)
{
    resetColors();

    if (step >= bestPath.size()) return;

    // Находим индексы вершин в массиве nodes по их ID
    QMap<int, int> idToIndex;
    for (int i = 0; i < nodes.size(); i++) {
        idToIndex[nodes[i].second] = i;
    }

    // Подсвечиваем текущую вершину
    if (idToIndex.contains(bestPath[step])) {
        int idx = idToIndex[bestPath[step]];
        nodeItems[idx]->setBrush(QBrush(QColor(255, 200, 100)));
    }

    // Подсвечиваем пройденные вершины и рёбра
    for (int i = 0; i < step; i++) {
        int fromId = bestPath[i];
        int toId = bestPath[i+1];

        if (idToIndex.contains(fromId)) {
            nodeItems[idToIndex[fromId]]->setBrush(QBrush(Qt::green));
        }

        // Подсвечиваем ребро
        for (int j = 0; j < edges.size(); j++) {
            int edgeFromId = nodes[edges[j].from].second;
            int edgeToId = nodes[edges[j].to].second;
            if ((edgeFromId == fromId && edgeToId == toId) ||
                (edgeFromId == toId && edgeToId == fromId)) {
                edgeItems[j]->setPen(QPen(Qt::green, 3));
                break;
            }
        }
    }
}

void MainWindow::animateNextStep()
{
    if (currentAnimStep < bestPath.size()) {
        highlightPath(currentAnimStep);
        outputText->append("Шаг " + QString::number(currentAnimStep) +
                           ": вершина " + QString::number(bestPath[currentAnimStep]));
        currentAnimStep++;
    } else {
        timer->stop();
        resetColors();
        // Финальная подсветка всего пути зелёным
        QMap<int, int> idToIndex;
        for (int i = 0; i < nodes.size(); i++) {
            idToIndex[nodes[i].second] = i;
        }
        for (int i = 0; i < bestPath.size(); i++) {
            if (idToIndex.contains(bestPath[i])) {
                nodeItems[idToIndex[bestPath[i]]]->setBrush(QBrush(Qt::green));
            }
        }
        outputText->append("Готово! Полный путь пройден.");
    }
}

void MainWindow::on_solve_clicked()
{
    if (nodeCount < 3) {
        QMessageBox::warning(this, "Ошибка", "Нужно хотя бы 3 вершины для решения TSP");
        return;
    }

    outputText->clear();
    bestPath.clear();

    int bestCost = tspBranchAndBound(bestPath);

    if (bestCost == INT_MAX) {
        outputText->setText("Решение не найдено! Граф может быть несвязным.");
        return;
    }

    outputText->append("Лучший путь найден!");
    outputText->append("Стоимость: " + QString::number(bestCost));

    QString pathStr = "Путь: ";
    for (int i = 0; i < bestPath.size(); i++) {
        pathStr += QString::number(bestPath[i]);
        if (i < bestPath.size()-1) pathStr += " -> ";
    }
    outputText->append(pathStr);

    currentAnimStep = 0;
    timer->start(1000);
    updateStatusMessage("Запущена анимация найденного маршрута.");
}

int MainWindow::tspBranchAndBound(QVector<int> &bestPath)
{
    int bestCost = INT_MAX;
    QVector<int> currentPath;
    QVector<bool> visited(nodeCount, false);

    currentPath.append(0);
    visited[0] = true;

    tspRecursive(currentPath, visited, 0, bestCost, bestPath, 1);

    return bestCost;
}

void MainWindow::tspRecursive(QVector<int> &currentPath, QVector<bool> &visited,
                              int currentCost, int &bestCost, QVector<int> &bestPath,
                              int level)
{
    if (level == nodeCount) {
        int last = currentPath.last();
        if (adjMatrix[last][0] != INT_MAX) {
            int totalCost = currentCost + adjMatrix[last][0];
            if (totalCost < bestCost) {
                bestCost = totalCost;
                bestPath = currentPath;
                bestPath.append(0);
            }
        }
        return;
    }

    int bound = calculateLowerBound(currentPath, visited, level);
    if (bound >= bestCost) return;

    int lastNode = currentPath.last();

    for (int i = 0; i < nodeCount; i++) {
        if (!visited[i] && adjMatrix[lastNode][i] != INT_MAX) {
            visited[i] = true;
            currentPath.append(i);

            tspRecursive(currentPath, visited,
                         currentCost + adjMatrix[lastNode][i],
                         bestCost, bestPath, level + 1);

            visited[i] = false;
            currentPath.removeLast();
        }
    }
}

int MainWindow::calculateLowerBound(QVector<int> &path, QVector<bool> &visited, int level)
{
    int bound = 0;

    for (int i = 0; i < path.size() - 1; i++) {
        bound += adjMatrix[path[i]][path[i+1]];
    }

    for (int i = 0; i < nodeCount; i++) {
        if (!visited[i]) {
            int minEdge = INT_MAX;
            for (int j = 0; j < nodeCount; j++) {
                if (i != j && adjMatrix[i][j] < minEdge) {
                    minEdge = adjMatrix[i][j];
                }
            }
            if (minEdge != INT_MAX) {
                bound += minEdge;
            }
        }
    }

    return bound;
}

void MainWindow::on_clear_clicked()
{
    timer->stop();
    scene->clear();
    nodes.clear();
    edges.clear();
    adjMatrix.clear();
    bestPath.clear();
    nodeCount = 0;
    nextVertexId = 0;
    currentAnimStep = 0;
    selectedStartVertex = -1;
    nodeItems.clear();
    edgeItems.clear();
    labelItems.clear();
    outputText->clear();
    updateStatusMessage("Всё очищено. Теперь можно добавлять новые вершины.");
}

void MainWindow::updateStatusMessage(const QString& message)
{
    ui->statusLabel->setText(message);
    qDebug() << message;
}

void MainWindow::on_addNode_clicked()
{
    isAddingVertexMode = true;
    isAddingEdgeMode = false;
    isRemovingVertexMode = false;
    isRemovingEdgeMode = false;
    selectedStartVertex = -1;
    updateStatusMessage("Режим: добавление вершин. Кликните по сцене.");
}

void MainWindow::on_addEdge_clicked()
{
    isAddingVertexMode = false;
    isAddingEdgeMode = true;
    isRemovingVertexMode = false;
    isRemovingEdgeMode = false;
    selectedStartVertex = -1;
    updateStatusMessage("Режим: добавление рёбер. Кликните на начальной вершине, затем на конечной.");
}

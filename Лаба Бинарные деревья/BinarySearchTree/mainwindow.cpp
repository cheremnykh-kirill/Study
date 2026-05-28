#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QMap>

// ==================== Методы BinarySearchTree ====================

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

void BinarySearchTree::destroyTree(TreeNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void BinarySearchTree::insert(double value) {
    root = insertNode(root, value);
}

TreeNode* BinarySearchTree::insertNode(TreeNode* node, double value) {
    if (node == nullptr) {
        return new TreeNode(value);
    }

    if (value < node->data) {
        node->left = insertNode(node->left, value);
    }
    else if (value > node->data) {
        node->right = insertNode(node->right, value);
    }

    return node;
}

void BinarySearchTree::remove(double value) {
    root = deleteNode(root, value);
}

TreeNode* BinarySearchTree::deleteNode(TreeNode* node, double value) {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->data) {
        node->left = deleteNode(node->left, value);
    }
    else if (value > node->data) {
        node->right = deleteNode(node->right, value);
    }
    else {
        if (node->left == nullptr) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }

        TreeNode* temp = findMinNode(node->right);
        node->data = temp->data;
        node->right = deleteNode(node->right, temp->data);
    }

    return node;
}

TreeNode* BinarySearchTree::findMinNode(TreeNode* node) {
    TreeNode* current = node;
    while (current != nullptr && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

bool BinarySearchTree::search(double value) {
    return searchNode(root, value) != nullptr;
}

TreeNode* BinarySearchTree::searchNode(TreeNode* node, double value) {
    if (node == nullptr || node->data == value) {
        return node;
    }

    if (value < node->data) {
        return searchNode(node->left, value);
    }
    return searchNode(node->right, value);
}

double BinarySearchTree::findMin() {
    if (root == nullptr) {
        return 0.0;
    }
    TreeNode* minNode = findMinNode(root);
    return minNode->data;
}

QString BinarySearchTree::getPreOrder(QVector<double>& path) {
    QString result = "";
    path.clear();
    preOrderTraversal(root, result, path);
    return result;
}

void BinarySearchTree::preOrderTraversal(TreeNode* node, QString& result, QVector<double>& path) {
    if (node != nullptr) {
        result += QString::number(node->data, 'f', 2) + " ";
        path.append(node->data);
        preOrderTraversal(node->left, result, path);
        preOrderTraversal(node->right, result, path);
    }
}

QString BinarySearchTree::getInOrder(QVector<double>& path) {
    QString result = "";
    path.clear();
    inOrderTraversal(root, result, path);
    return result;
}

void BinarySearchTree::inOrderTraversal(TreeNode* node, QString& result, QVector<double>& path) {
    if (node != nullptr) {
        inOrderTraversal(node->left, result, path);
        result += QString::number(node->data, 'f', 2) + " ";
        path.append(node->data);
        inOrderTraversal(node->right, result, path);
    }
}

QString BinarySearchTree::getPostOrder(QVector<double>& path) {
    QString result = "";
    path.clear();
    postOrderTraversal(root, result, path);
    return result;
}

void BinarySearchTree::postOrderTraversal(TreeNode* node, QString& result, QVector<double>& path) {
    if (node != nullptr) {
        postOrderTraversal(node->left, result, path);
        postOrderTraversal(node->right, result, path);
        result += QString::number(node->data, 'f', 2) + " ";
        path.append(node->data);
    }
}

int BinarySearchTree::getHeight(TreeNode* node) {
    if (node == nullptr) return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int BinarySearchTree::getNodeCount(TreeNode* node) {
    if (node == nullptr) return 0;
    return getNodeCount(node->left) + getNodeCount(node->right) + 1;
}

void BinarySearchTree::fillArrayInOrder(TreeNode* node, double* arr, int& index) {
    if (node != nullptr) {
        fillArrayInOrder(node->left, arr, index);
        arr[index] = node->data;
        index++;
        fillArrayInOrder(node->right, arr, index);
    }
}

TreeNode* BinarySearchTree::buildBalancedTree(double* arr, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start + end) / 2;
    TreeNode* node = new TreeNode(arr[mid]);
    node->left = buildBalancedTree(arr, start, mid - 1);
    node->right = buildBalancedTree(arr, mid + 1, end);
    return node;
}

void BinarySearchTree::balance() {
    int size = getNodeCount(root);
    if (size == 0) return;

    double* arr = new double[size];
    int index = 0;
    fillArrayInOrder(root, arr, index);
    destroyTree(root);
    root = buildBalancedTree(arr, 0, size - 1);
    delete[] arr;
}

TreeNode* BinarySearchTree::getRoot() {
    return root;
}

int BinarySearchTree::getTreeHeight() {
    return getHeight(root);
}

int BinarySearchTree::getTreeSize() {
    return getNodeCount(root);
}

// ==================== Методы MainWindow ====================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tree = new BinarySearchTree();
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 800, 600);

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &MainWindow::on_animationTimerTimeout);
    isAnimating = false;
    currentAnimationStep = 0;

    setWindowTitle("Бинарное дерево поиска (double) - Вариант 25");
    ui->horizontalPrintButton->setCheckable(true);
    ui->verticalPrintButton->setCheckable(true);
    ui->horizontalPrintButton->setChecked(true);

    // Добавим несколько тестовых значений для демонстрации
    tree->insert(50);
    tree->insert(30);
    tree->insert(70);
    tree->insert(20);
    tree->insert(40);
    tree->insert(60);
    tree->insert(80);
    drawTreeHorizontal();
}

MainWindow::~MainWindow()
{
    stopAnimation();
    delete tree;
    delete ui;
}

void MainWindow::clearScene() {
    scene->clear();
}


// ==================== ГОРИЗОНТАЛЬНАЯ ПЕЧАТЬ (корень слева, дети справа) ====================

void MainWindow::drawTreeHorizontal() {
    clearScene();

    if (tree->getRoot() != nullptr) {
        // Горизонтальное дерево: корень слева, левый потомок сверху, правый снизу
        double startX = 50;
        double startY = 300;  // Центр по вертикали
        double offsetX = 100;  // Расстояние по горизонтали между уровнями
        double offsetY = 60;   // Расстояние по вертикали между узлами

        drawNodeHorizontal(tree->getRoot(), startX, startY, offsetX, offsetY);
    }
}

void MainWindow::drawNodeHorizontal(TreeNode* node, double x, double y, double offsetX, double offsetY) {
    if (node == nullptr) return;

    double radius = 25;

    // Рисуем круг для узла
    QGraphicsEllipseItem* circle = scene->addEllipse(x - radius, y - radius,
                                                     radius * 2, radius * 2,
                                                     QPen(Qt::black, 2),
                                                     QBrush(QColor(173, 216, 230)));

    // Рисуем значение узла
    QGraphicsTextItem* text = scene->addText(QString::number(node->data, 'f', 2));
    text->setPos(x - 18, y - 10);
    QFont font = text->font();
    font.setPointSize(12);
    font.setBold(true);
    text->setFont(font);

    // Левый потомок (рисуем ВВЕРХ-ВНИЗ от текущего узла)
    if (node->left != nullptr) {
        double childX = x + offsetX;
        double childY = y - offsetY;

        // Линия от текущего узла к левому потомку
        scene->addLine(x + radius, y, childX - radius, childY, QPen(Qt::black, 2));

        // Рекурсивно рисуем левое поддерево
        drawNodeHorizontal(node->left, childX, childY, offsetX * 0.8, offsetY * 0.8);
    }

    // Правый потомок (рисуем ВНИЗ от текущего узла)
    if (node->right != nullptr) {
        double childX = x + offsetX;
        double childY = y + offsetY;

        // Линия от текущего узла к правому потомку
        scene->addLine(x + radius, y, childX - radius, childY, QPen(Qt::black, 2));

        // Рекурсивно рисуем правое поддерево
        drawNodeHorizontal(node->right, childX, childY, offsetX * 0.8, offsetY * 0.8);
    }
}

// ==================== ВЕРТИКАЛЬНАЯ ПЕЧАТЬ (корень вверху, дети внизу) ====================

void MainWindow::drawTreeVertical() {
    clearScene();

    if (tree->getRoot() != nullptr) {
        // Вертикальное дерево: корень вверху, дети внизу
        double startX = 400;
        double startY = 50;
        double offsetX = 200;
        double offsetY = 80;

        drawNodeVertical(tree->getRoot(), startX, startY, offsetX, offsetY);
    }
}

void MainWindow::drawNodeVertical(TreeNode* node, double x, double y, double offsetX, double offsetY) {
    if (node == nullptr) return;

    double radius = 25;

    // Рисуем круг для узла
    QGraphicsEllipseItem* circle = scene->addEllipse(x - radius, y - radius,
                                                     radius * 2, radius * 2,
                                                     QPen(Qt::black, 2),
                                                     QBrush(QColor(144, 238, 144)));

    // Рисуем значение узла
    QGraphicsTextItem* text = scene->addText(QString::number(node->data, 'f', 2));
    text->setPos(x - 18, y - 10);
    QFont font = text->font();
    font.setPointSize(12);
    font.setBold(true);
    text->setFont(font);

    // Левый потомок (рисуем ВЛЕВО-ВНИЗ)
    if (node->left != nullptr) {
        double childX = x - offsetX;
        double childY = y + offsetY;

        scene->addLine(x - radius + 5, y + radius - 5, childX + radius - 5, childY - radius + 5, QPen(Qt::black, 2));

        drawNodeVertical(node->left, childX, childY, offsetX * 0.7, offsetY);
    }

    // Правый потомок (рисуем ВПРАВО-ВНИЗ)
    if (node->right != nullptr) {
        double childX = x + offsetX;
        double childY = y + offsetY;

        scene->addLine(x + radius - 5, y + radius - 5, childX - radius + 5, childY - radius + 5, QPen(Qt::black, 2));

        drawNodeVertical(node->right, childX, childY, offsetX * 0.7, offsetY);
    }
}

// ==================== АНИМАЦИЯ ПОДСВЕТКИ ====================

void MainWindow::startAnimation(const QVector<double>& path) {
    stopAnimation();
    animationPath = path;
    currentAnimationStep = 0;
    isAnimating = true;
    animationTimer->start(800);  // 0.8 секунды между шагами
}

void MainWindow::stopAnimation() {
    if (animationTimer->isActive()) {
        animationTimer->stop();
    }
    isAnimating = false;
    // Перерисовываем дерево без подсветки (используем isChecked, а не isEnabled!)
    if (ui->horizontalPrintButton->isChecked()) {
        drawTreeHorizontal();
    } else {
        drawTreeVertical();
    }
}

void MainWindow::on_animationTimerTimeout() {
    if (!isAnimating || currentAnimationStep >= animationPath.size()) {
        stopAnimation();
        ui->statusLabel->setText("Анимация завершена.");
        return;
    }

    double currentValue = animationPath[currentAnimationStep];
    ui->statusLabel->setText("Шаг " + QString::number(currentAnimationStep + 1) +
                             ": вершина " + QString::number(currentValue, 'f', 2));

    // Перерисовываем дерево с подсветкой текущего узла
    clearScene();

    // Используем isChecked для определения выбранного режима печати
    if (ui->horizontalPrintButton->isChecked()) {
        drawTreeWithHighlight(animationPath, currentAnimationStep);
    } else {
        drawTreeWithHighlightVertical(animationPath, currentAnimationStep);
    }

    currentAnimationStep++;
}

void MainWindow::drawTreeWithHighlight(const QVector<double>& path, int currentStep) {
    if (tree->getRoot() == nullptr) return;

    double startX = 50;
    double startY = 300;
    double offsetX = 100;
    double offsetY = 60;

    drawNodeWithHighlight(tree->getRoot(), startX, startY, offsetX, offsetY, path, currentStep);
}

void MainWindow::drawTreeWithHighlightVertical(const QVector<double>& path, int currentStep) {
    if (tree->getRoot() == nullptr) return;

    double startX = 400;
    double startY = 50;
    double offsetX = 200;
    double offsetY = 80;

    drawNodeWithHighlightVertical(tree->getRoot(), startX, startY, offsetX, offsetY, path, currentStep);
}

void MainWindow::drawNodeWithHighlight(TreeNode* node, double x, double y, double offsetX, double offsetY,
                                       const QVector<double>& path, int currentStep) {
    if (node == nullptr) return;

    double radius = 25;
    QColor nodeColor;

    // Определяем цвет узла
    bool isVisited = false;
    bool isCurrent = false;

    for (int i = 0; i <= currentStep && i < path.size(); i++) {
        if (qAbs(node->data - path[i]) < 0.0001) {
            isVisited = true;
            if (i == currentStep) {
                isCurrent = true;
            }
            break;
        }
    }

    if (isCurrent) {
        nodeColor = QColor(255, 200, 100);  // Текущий узел — оранжевый
    } else if (isVisited) {
        nodeColor = QColor(144, 238, 144);  // Пройденные узлы — зелёный
    } else {
        nodeColor = QColor(173, 216, 230);  // Непосещённые — голубой
    }

    QGraphicsEllipseItem* circle = scene->addEllipse(x - radius, y - radius,
                                                     radius * 2, radius * 2,
                                                     QPen(Qt::black, 2),
                                                     QBrush(nodeColor));

    QGraphicsTextItem* text = scene->addText(QString::number(node->data, 'f', 2));
    text->setPos(x - 18, y - 10);
    QFont font = text->font();
    font.setPointSize(12);
    font.setBold(true);
    text->setFont(font);

    // Левый потомок (вверх)
    if (node->left != nullptr) {
        double childX = x + offsetX;
        double childY = y - offsetY;
        scene->addLine(x + radius, y, childX - radius, childY, QPen(Qt::black, 2));
        drawNodeWithHighlight(node->left, childX, childY, offsetX * 0.8, offsetY * 0.8, path, currentStep);
    }

    // Правый потомок (вниз)
    if (node->right != nullptr) {
        double childX = x + offsetX;
        double childY = y + offsetY;
        scene->addLine(x + radius, y, childX - radius, childY, QPen(Qt::black, 2));
        drawNodeWithHighlight(node->right, childX, childY, offsetX * 0.8, offsetY * 0.8, path, currentStep);
    }
}

void MainWindow::drawNodeWithHighlightVertical(TreeNode* node, double x, double y, double offsetX, double offsetY,
                                               const QVector<double>& path, int currentStep) {
    if (node == nullptr) return;

    double radius = 25;
    QColor nodeColor;

    bool isVisited = false;
    bool isCurrent = false;

    for (int i = 0; i <= currentStep && i < path.size(); i++) {
        if (qAbs(node->data - path[i]) < 0.0001) {
            isVisited = true;
            if (i == currentStep) {
                isCurrent = true;
            }
            break;
        }
    }

    if (isCurrent) {
        nodeColor = QColor(255, 200, 100);  // Текущий узел — оранжевый
    } else if (isVisited) {
        nodeColor = QColor(144, 238, 144);  // Пройденные узлы — зелёный
    } else {
        nodeColor = QColor(173, 216, 230);  // Непосещённые — голубой
    }

    QGraphicsEllipseItem* circle = scene->addEllipse(x - radius, y - radius,
                                                     radius * 2, radius * 2,
                                                     QPen(Qt::black, 2),
                                                     QBrush(nodeColor));

    QGraphicsTextItem* text = scene->addText(QString::number(node->data, 'f', 2));
    text->setPos(x - 18, y - 10);
    QFont font = text->font();
    font.setPointSize(12);
    font.setBold(true);
    text->setFont(font);

    // Левый потомок (влево-вниз)
    if (node->left != nullptr) {
        double childX = x - offsetX;
        double childY = y + offsetY;
        scene->addLine(x - radius + 5, y + radius - 5, childX + radius - 5, childY - radius + 5, QPen(Qt::black, 2));
        drawNodeWithHighlightVertical(node->left, childX, childY, offsetX * 0.7, offsetY, path, currentStep);
    }

    // Правый потомок (вправо-вниз)
    if (node->right != nullptr) {
        double childX = x + offsetX;
        double childY = y + offsetY;
        scene->addLine(x + radius - 5, y + radius - 5, childX - radius + 5, childY - radius + 5, QPen(Qt::black, 2));
        drawNodeWithHighlightVertical(node->right, childX, childY, offsetX * 0.7, offsetY, path, currentStep);
    }
}

// ==================== ОБРАБОТЧИКИ КНОПОК ====================

// ... остальные обработчики кнопок (insert, delete, search, findMin, balance) остаются без изменений ...

void MainWindow::on_preOrderButton_clicked() {
    QVector<double> path;
    QString result = tree->getPreOrder(path);

    if (result.isEmpty()) {
        QMessageBox::information(this, "Прямой обход (NLR)", "Дерево пустое.");
    } else {
        QMessageBox::information(this, "Прямой обход (NLR)",
                                 "Прямой обход (корень-левое-правое):\n" + result);
        startAnimation(path);
    }
}

void MainWindow::on_inOrderButton_clicked() {
    QVector<double> path;
    QString result = tree->getInOrder(path);

    if (result.isEmpty()) {
        QMessageBox::information(this, "Симметричный обход (LNR)", "Дерево пустое.");
    } else {
        QMessageBox::information(this, "Симметричный обход (LNR)",
                                 "Симметричный обход (левое-корень-правое):\n" + result);
        startAnimation(path);
    }
}

void MainWindow::on_postOrderButton_clicked() {
    QVector<double> path;
    QString result = tree->getPostOrder(path);

    if (result.isEmpty()) {
        QMessageBox::information(this, "Обратный обход (LRN)", "Дерево пустое.");
    } else {
        QMessageBox::information(this, "Обратный обход (LRN)",
                                 "Обратный обход (левое-правое-корень):\n" + result);
        startAnimation(path);
    }
}

void MainWindow::on_horizontalPrintButton_clicked() {
    drawTreeHorizontal();
    ui->horizontalPrintButton->setChecked(true);
    ui->verticalPrintButton->setChecked(false);
    ui->statusLabel->setText("Отображена горизонтальная печать дерева.");
}

void MainWindow::on_verticalPrintButton_clicked() {
    drawTreeVertical();
    ui->horizontalPrintButton->setChecked(false);
    ui->verticalPrintButton->setChecked(true);
    ui->statusLabel->setText("Отображена вертикальная печать дерева.");
}

// ==================== ОБРАБОТЧИКИ КНОПОК ====================

void MainWindow::on_insertButton_clicked() {
    bool ok;
    double value = QInputDialog::getDouble(this, "Вставка элемента",
                                           "Введите число (double):",
                                           0.0, -1000000.0, 1000000.0, 2, &ok);

    if (ok) {
        tree->insert(value);
        if (ui->horizontalPrintButton->isChecked()) {
            drawTreeHorizontal();
        } else {
            drawTreeVertical();
        }
        ui->statusLabel->setText("Элемент " + QString::number(value, 'f', 2) + " добавлен в дерево.");
    }
}

void MainWindow::on_deleteButton_clicked() {
    bool ok;
    double value = QInputDialog::getDouble(this, "Удаление элемента",
                                           "Введите число для удаления:",
                                           0.0, -1000000.0, 1000000.0, 2, &ok);

    if (ok) {
        if (tree->search(value)) {
            tree->remove(value);
            if (ui->horizontalPrintButton->isChecked()) {
                drawTreeHorizontal();
            } else {
                drawTreeVertical();
            }
            ui->statusLabel->setText("Элемент " + QString::number(value, 'f', 2) + " удалён из дерева.");
        } else {
            QMessageBox::warning(this, "Ошибка", "Элемент не найден в дереве!");
        }
    }
}

void MainWindow::on_searchButton_clicked() {
    bool ok;
    double value = QInputDialog::getDouble(this, "Поиск элемента",
                                           "Введите число для поиска:",
                                           0.0, -1000000.0, 1000000.0, 2, &ok);

    if (ok) {
        if (tree->search(value)) {
            QMessageBox::information(this, "Результат поиска",
                                     "Элемент " + QString::number(value, 'f', 2) + " найден в дереве!");
        } else {
            QMessageBox::information(this, "Результат поиска",
                                     "Элемент " + QString::number(value, 'f', 2) + " не найден в дереве.");
        }
    }
}

void MainWindow::on_findMinButton_clicked() {
    if (tree->getRoot() == nullptr) {
        QMessageBox::warning(this, "Ошибка", "Дерево пустое!");
        return;
    }

    double minValue = tree->findMin();
    QString message = "Минимальный элемент в дереве: " + QString::number(minValue, 'f', 2);
    ui->statusLabel->setText(message);
    QMessageBox::information(this, "Минимальный элемент", message);
}

void MainWindow::on_balanceButton_clicked() {
    if (tree->getRoot() == nullptr) {
        QMessageBox::warning(this, "Ошибка", "Дерево пустое! Нечего балансировать.");
        return;
    }

    tree->balance();
    if (ui->horizontalPrintButton->isChecked()) {
        drawTreeHorizontal();
    } else {
        drawTreeVertical();
    }
    ui->statusLabel->setText("Дерево сбалансировано.");
    QMessageBox::information(this, "Балансировка", "Дерево успешно сбалансировано!");
}

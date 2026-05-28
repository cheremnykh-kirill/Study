#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QMessageBox>
#include <QInputDialog>
#include <QTimer>
#include <QVector>
#include <QMap>
#include <cmath>

// Структура узла дерева
struct TreeNode {
    double data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(double value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Класс бинарного дерева поиска
class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insertNode(TreeNode* node, double value);
    TreeNode* deleteNode(TreeNode* node, double value);
    TreeNode* findMinNode(TreeNode* node);
    TreeNode* searchNode(TreeNode* node, double value);
    void destroyTree(TreeNode* node);
    int getHeight(TreeNode* node);
    int getNodeCount(TreeNode* node);
    void preOrderTraversal(TreeNode* node, QString& result, QVector<double>& path);
    void inOrderTraversal(TreeNode* node, QString& result, QVector<double>& path);
    void postOrderTraversal(TreeNode* node, QString& result, QVector<double>& path);
    TreeNode* buildBalancedTree(double* arr, int start, int end);
    void fillArrayInOrder(TreeNode* node, double* arr, int& index);

public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(double value);
    void remove(double value);
    bool search(double value);
    double findMin();

    QString getPreOrder(QVector<double>& path);
    QString getInOrder(QVector<double>& path);
    QString getPostOrder(QVector<double>& path);

    void balance();
    TreeNode* getRoot();
    int getTreeHeight();
    int getTreeSize();
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

private slots:
    void on_insertButton_clicked();
    void on_deleteButton_clicked();
    void on_searchButton_clicked();
    void on_findMinButton_clicked();
    void on_balanceButton_clicked();
    void on_preOrderButton_clicked();
    void on_inOrderButton_clicked();
    void on_postOrderButton_clicked();
    void on_horizontalPrintButton_clicked();
    void on_verticalPrintButton_clicked();
    void on_animationTimerTimeout();

private:
    Ui::MainWindow *ui;
    BinarySearchTree* tree;
    QGraphicsScene* scene;
    QTimer* animationTimer;
    QVector<double> animationPath;
    int currentAnimationStep;
    bool isAnimating;

    // Методы для визуализации
    void drawTreeHorizontal();
    void drawTreeVertical();
    void drawNodeHorizontal(TreeNode* node, double x, double y, double offsetX, double offsetY);
    void drawNodeVertical(TreeNode* node, double x, double y, double offsetX, double offsetY);
    void clearScene();

    // Методы для анимации с подсветкой
    void drawTreeWithHighlight(const QVector<double>& path, int currentStep);
    void drawTreeWithHighlightVertical(const QVector<double>& path, int currentStep);
    void drawNodeWithHighlight(TreeNode* node, double x, double y, double offsetX, double offsetY,
                               const QVector<double>& path, int currentStep);
    void drawNodeWithHighlightVertical(TreeNode* node, double x, double y, double offsetX, double offsetY,
                                       const QVector<double>& path, int currentStep);

    void startAnimation(const QVector<double>& path);
    void stopAnimation();
};

#endif // MAINWINDOW_H

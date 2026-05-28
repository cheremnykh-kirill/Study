#include <iostream>
#include <clocale>
using namespace std;
const int MAX_DISKS = 10;  // Максимальное количество дисков
int towers[3][MAX_DISKS];  // Башни: [номер_башни][уровень]
int heights[3];            // Высота каждой башни
int totalDisks;            // Общее количество дисков


void initTowers(int n) {
    totalDisks = n;
    for (int i = 0; i < 3; i++) {
        heights[i] = 0;
        for (int j = 0; j < MAX_DISKS; j++) {
            towers[i][j] = 0;
        }
    }
    heights[0] = n;
    for (int i = 0; i < n; i++) {
        towers[0][i] = n - i;
    }
}


int getDiskSize(int tower, int level) {
    if (level < 0 || level >= heights[tower]) {
        return 0;
    }
    return towers[tower][level];
}


void moveDisk(int from, int to) {
    int disk = towers[from][heights[from] - 1];
    towers[from][heights[from] - 1] = 0;
    heights[from]--;
    towers[to][heights[to]] = disk;
    heights[to]++;
}


void drawTowers(int moveNumber) {
    int p = totalDisks;                    // центр 1-й башни
    int q = p + totalDisks * 2 + 3;        // центр 2-й башни
    int z = q + totalDisks * 2 + 3;        // центр 3-й башни
    int centers[3] = { p, q, z };
    int height = totalDisks;                // высота = количество дисков
    int totalWidth = z + totalDisks;        // общая ширина
    cout << "\nХод N: " << moveNumber << "\n";
    cout << string(50, '=') << "\n\n";
    for (int level = height - 1; level >= 0; level--) {
        for (int j = 0; j <= totalWidth; j++) {
            bool drawn = false;
            for (int t = 0; t < 3; t++) {
                int diskSize = getDiskSize(t, level);
                if (diskSize > 0) {
                    int diskStart = centers[t] - diskSize + 1;  // Начало диска
                    int diskEnd = centers[t] + diskSize - 1;    // Конец диска

                    if (j >= diskStart && j <= diskEnd) {
                        cout << "=";
                        drawn = true;
                        break;
                    }
                }
            }
            if (!drawn) {
                if (j == p || j == q || j == z) {
                    cout << "*";
                }
                else {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    for (int k = 0; k <= totalWidth; k++) {
        bool inGap = false;
        if (k > p + totalDisks && k < q - totalDisks) {
            inGap = true;
        }
        if (k > q + totalDisks && k < z - totalDisks) {
            inGap = true;
        }
        if (inGap) {
            cout << " ";
        }
        else {
            cout << "=";
        }
    }
    cout << endl << endl;
}


void hanWithVisual(int n, int start, int target, int auxiliary, int& moveCount) {
    if (n <= 0) {
        return;
    }
    hanWithVisual(n - 1, start, auxiliary, target, moveCount);
    moveCount++;
    cout << endl << "Перемещаем диск " << n << ": " << start << " -> " << target << endl;
    moveDisk(start - 1, target - 1);
    drawTowers(moveCount);
    hanWithVisual(n - 1, auxiliary, target, start, moveCount);
}


int main() {
    setlocale(LC_ALL, "RU");
    int n;
    cout << "ХАНОЙСКАЯ БАШНЯ" << endl;
    cout << string(40, '-') << endl;
    cout << "Введите количество дисков (1-7): ";
    cin >> n;
    if (n <= 0 || n > 7) {
        cout << "Ошибка! Введите число от 1 до 7!" << endl;
        return 1;
    }
    initTowers(n);
    cout << endl << "Начальное состояние: " << endl;
    drawTowers(0);
    int moveCount = 0;
    hanWithVisual(n, 1, 3, 2, moveCount);
    cout << endl << string(50, '-') << endl;
    cout << "Игра завершена!" << endl;
    cout << "Всего ходов: " << moveCount << endl;
    return 0;
}
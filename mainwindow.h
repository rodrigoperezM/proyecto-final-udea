
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem *pacmanItem;
    int pacmanX;
    int pacmanY;
    int spriteWidth;
    int spriteHeight;
    int cellSize;
    std::vector<QString> laberinto;
    int score;
    int lives;
    int enemiesRemaining;
    QLabel *scoreLabel;
    QLabel *livesLabel;
    QLabel *enemiesLabel;

    void drawLaberinto();
    void movePacman(int dx, int dy);
    void collectPoint(int x, int y);
    void checkCollision();
    void updateScore();
    void updateLives();
    void updateEnemiesRemaining();
    void checkGameOver();
};

#endif // MAINWINDOW_H


/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QLabel>
#include <QTimer>

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
    void deactivatePowerMode();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem *pacmanItem;
    QLabel *scoreLabel;
    QLabel *livesLabel;
    QLabel *enemiesLabel;
    std::vector<QString> laberinto;
    int pacmanX;
    int pacmanY;
    int spriteWidth;
    int spriteHeight;
    int cellSize;
    int score;
    int lives;
    int enemiesRemaining;
    bool gameOver;
    bool powerMode; // Nuevo estado para modo de poder
    QTimer *powerTimer; // Temporizador para modo de poder
    int totalPoints;
    bool pacmanMouthOpen; // Nueva variable de estado para la boca de Pac-Man

    void drawLaberinto();
    void movePacman(int dx, int dy);
    void collectPoint(int x, int y);
    void checkCollision();
    void handlePacmanCaught();
    void updateScore();
    void updateLives();
    void updateEnemiesRemaining();
    void checkGameOver();
    void resetPacmanPosition();
    void resetGame();
    void restartGame();
    void handlePowerPoint(int x, int y); // Nueva función para manejar puntos de poder
    void activatePowerMode(); // Nueva función para activar el modo de poder
};

#endif // MAINWINDOW_H*/

/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QLabel>
#include <QTimer>
#include <QList>

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
    void deactivatePowerMode();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem *pacmanItem;
    QLabel *scoreLabel;
    QLabel *livesLabel;
    QLabel *enemiesLabel;
    std::vector<QString> laberinto;
    int pacmanX;
    int pacmanY;
    int spriteWidth;
    int spriteHeight;
    int cellSize;
    int score;
    int lives;
    int enemiesRemaining;
    bool gameOver;
    bool powerMode;
    QTimer *powerTimer;
    int totalPoints;
    bool pacmanMouthOpen;

    QPixmap pacmanImageOpen;
    QPixmap pacmanImageClosed;
    QPixmap pacmanImageUp;
    QPixmap pacmanImageDown;
    QPixmap pacmanImageLeft;
    QPixmap pacmanImageRight;

    void drawLaberinto();
    void movePacman(int dx, int dy);
    void collectPoint(int x, int y);
    void checkCollision();
    void handlePacmanCaught();
    void updateScore();
    void updateLives();
    void updateEnemiesRemaining();
    void checkGameOver();
    void resetPacmanPosition();
    void resetGame();
    void restartGame();
    void handlePowerPoint(int x, int y);
    void activatePowerMode();
};

#endif // MAINWINDOW_H*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QLabel>
#include <QTimer>
#include <QMediaPlayer> // Incluir QMediaPlayer
#include <QList>

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
    void deactivatePowerMode();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem *pacmanItem;
    QLabel *scoreLabel;
    QLabel *livesLabel;
    QLabel *enemiesLabel;
    std::vector<QString> laberinto;
    int pacmanX;
    int pacmanY;
    int spriteWidth;
    int spriteHeight;
    int cellSize;
    int score;
    int lives;
    int enemiesRemaining;
    bool gameOver;
    bool powerMode;
    QTimer *powerTimer;
    int totalPoints;
    bool pacmanMouthOpen;




    QPixmap pacmanImageOpen;
    QPixmap pacmanImageClosed;
    QPixmap pacmanImageUp;
    QPixmap pacmanImageDown;
    QPixmap pacmanImageLeft;
    QPixmap pacmanImageRight;

    QMediaPlayer *chompSound; // Cambiar a QMediaPlayer

    void drawLaberinto();
    void movePacman(int dx, int dy);
    void collectPoint(int x, int y);
    void checkCollision();
    void handlePacmanCaught();
    void updateScore();
    void updateLives();
    void updateEnemiesRemaining();
    void checkGameOver();
    void resetPacmanPosition();
    void resetGame();
    void restartGame();
    void handlePowerPoint(int x, int y);
    void activatePowerMode();
};

#endif // MAINWINDOW_H





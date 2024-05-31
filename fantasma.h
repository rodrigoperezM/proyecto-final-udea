#ifndef FANTASMA_H
#define FANTASMA_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>

enum class GhostType { Blinky, Clyde };

class Fantasma : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Fantasma(int cellSize, const std::vector<QString> &laberinto, QGraphicsScene *scene, const QPixmap &pixmap, GhostType type);

    void setPacmanPosition(int x, int y);
    void setScore(int score);
    void setPowerMode(bool powerMode); // Nueva función para establecer el modo de poder

signals:
    void pacmanCaught();

private slots:
    void move();

private:
    int cellSize;
    std::vector<QString> laberinto;
    int pacmanX;
    int pacmanY;
    int score;
    GhostType type;
    QTimer *moveTimer;
    bool powerMode; // Estado para el modo de poder

    void changeDirection();
};

#endif // FANTASMA_H


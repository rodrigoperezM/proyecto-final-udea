
#ifndef FANTASMA_H
#define FANTASMA_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <vector>
#include <QString>

class Fantasma : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Fantasma(int cellSize, const std::vector<QString>& laberinto, QGraphicsScene *scene, const QPixmap &sprite);

    QTimer* getTimer() const { return timer; }

public slots:
    void move();

private:
    int cellSize;
    const std::vector<QString>& laberinto;
    QGraphicsScene *scene;
    QTimer *timer;

    void moveRandomly();
    bool canMoveTo(int newX, int newY);
};

#endif // FANTASMA_H

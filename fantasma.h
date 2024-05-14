
#ifndef FANTASMA_H
#define FANTASMA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include "direction.h" // Incluir el archivo que contiene la definición de Direction

class Fantasma : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Fantasma(int width, int height, int cellSize, QGraphicsScene *scene, QObject *parent = nullptr);
    void move();
private:
    int spriteWidth;
    int spriteHeight;
    int cellSize;
    QGraphicsScene *scene;
    Direction direccion;
    QTimer *timer;

    bool isColliding() const;
    Direction randomDirection() const;
public:
    QTimer *getTimer() const { return timer; }

};

#endif // FANTASMA_H

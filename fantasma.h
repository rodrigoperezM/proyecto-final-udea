/*#ifndef FANTASMA_H
#define FANTASMA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include "direction.h"

//enum class Direction { Up, Down, Left, Right };

class Fantasma : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Fantasma(int width, int height, int cellSize, QObject *parent = nullptr);
    ~Fantasma() {}

private:
    int spriteWidth;
    int spriteHeight;
    int cellSize;
    QPointF posicion;
    Direction direccion;

    void move();
    bool isColliding() const;
    Direction randomDirection() const;
};

#endif // FANTASMA_H*/

/*#ifndef FANTASMA_H
#define FANTASMA_H

#include "direction.h" // Asegúrate de incluir la definición de Direction si es necesario
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Fantasma : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Fantasma(int width, int height, int cellSize, QGraphicsScene *scene, QObject *parent = nullptr);
    void move(); // Declaración de la función move()
private:
    int spriteWidth;
    int spriteHeight;
    int cellSize;
    QGraphicsScene *scene;
    bool isColliding() const;
    Direction randomDirection() const;

};

#endif // FANTASMA_H*/

/*#ifndef FANTASMA_H
#define FANTASMA_H

#include "direction.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer> // Incluir QTimer para utilizar temporizadores

class Fantasma : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
//public:
    //Fantasma(int width, int height, int cellSize, QGraphicsScene *scene, QObject *parent = nullptr);
private:
    int spriteWidth;
    int spriteHeight;
    int cellSize;
    QGraphicsScene *scene;
    Direction direccion;
    QTimer *timer; // Temporizador para el movimiento del fantasma

    //void move();
    bool isColliding() const;
    Direction randomDirection() const;

public:
    QTimer* getTimer() const { return timer; }
public:
    Fantasma(int width, int height, int cellSize, QGraphicsScene *scene, QObject *parent = nullptr);
    void move(); // Mover el fantasma


};

#endif // FANTASMA_H*/

/*#ifndef FANTASMA_H
#define FANTASMA_H

#include "direction.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>

class Fantasma : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Fantasma(int width, int height, int cellSize, QGraphicsScene *scene, QObject *parent = nullptr);
    QTimer* getTimer() const { return timer; }
private:
    int spriteWidth;
    int spriteHeight;
    int cellSize;
    QGraphicsScene *scene;
    Direction direccion;
    QTimer *timer;
    void move();
    bool isColliding() const;
    Direction randomDirection() const;
};

#endif // FANTASMA_H*/

/*#ifndef FANTASMA_H
#define FANTASMA_H

#include "direction.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>

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
};

#endif // FANTASMA_H*/

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

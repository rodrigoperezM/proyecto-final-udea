/*#include "fantasma.h"
#include "mainwindow.h" // Incluir mainwindow.h para acceder a Direction
#include <QGraphicsScene>
#include <QRandomGenerator>

#include <QTimer> // Incluir QTimer para utilizar temporizadores

Fantasma::Fantasma(int width, int height, int cellSize, QObject *parent)
    : QObject(parent), spriteWidth(width), spriteHeight(height), cellSize(cellSize)
{
    setPixmap(QPixmap(":/fantasma.png")); // Asignar una imagen al objeto

    // Inicializar un temporizador para manejar el movimiento del fantasma
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(1000); // Mover el fantasma cada segundo
}

void Fantasma::move()
{
    // Generar una dirección aleatoria si el fantasma está en una colisión
    if (isColliding()) {
        direccion = randomDirection();
        return;
    }

    // Determinar la nueva posición del fantasma en base a la dirección actual
    QPointF newPos = posicion;
    switch (direccion) {
    case Direction::Up:
        newPos.ry() -= cellSize;
        break;
    case Direction::Down:
        newPos.ry() += cellSize;
        break;
    case Direction::Left:
        newPos.rx() -= cellSize;
        break;
    case Direction::Right:
        newPos.rx() += cellSize;
        break;
    }

    // Actualizar la posición del fantasma
    setPos(newPos);
    posicion = newPos;
}

bool Fantasma::isColliding() const
{
    // Verificar si el fantasma está colisionando con otros elementos en la escena después de moverse
    QList<QGraphicsItem *> collidingItems = scene()->items(QPolygonF(mapToScene(boundingRect())));
    collidingItems.removeOne(const_cast<Fantasma *>(this)); // Remover el propio objeto de la lista de elementos colisionados
    return !collidingItems.isEmpty();
}

Direction Fantasma::randomDirection() const
{
    // Generar una dirección aleatoria
    int directionInt = QRandomGenerator::global()->bounded(0, 8); // 0 a 7 (ocho direcciones posibles)
    return static_cast<Direction>(directionInt);
}*/

/*#include "fantasma.h"
#include "mainwindow.h" // Solo si es necesario para acceder a Direction
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QTimer>

Fantasma::Fantasma(int width, int height, int cellSize, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), spriteWidth(width), spriteHeight(height), cellSize(cellSize)
{
    setPixmap(QPixmap(":/fantasma.png")); // Cargar la imagen del fantasma

    // Inicializar la posición y dirección del fantasma
    posicion = QPointF(0, 0); // Posición inicial (puede ser modificada según tu necesidad)
    direccion = Direction::Right; // Dirección inicial (puede ser modificada según tu necesidad)

    // Configurar un temporizador para mover el fantasma periódicamente
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(1000); // Mover el fantasma cada segundo
}

void Fantasma::move()
{
    // Determinar la nueva posición del fantasma en base a la dirección actual
    QPointF newPos = posicion;
    switch (direccion) {
    case Direction::Up:
        newPos.ry() -= cellSize;
        break;
    case Direction::Down:
        newPos.ry() += cellSize;
        break;
    case Direction::Left:
        newPos.rx() -= cellSize;
        break;
    case Direction::Right:
        newPos.rx() += cellSize;
        break;
    }

    // Verificar si la nueva posición está dentro de la escena y no colisiona con otros elementos
    if (scene()->sceneRect().contains(newPos) && !isColliding()) {
        setPos(newPos); // Actualizar la posición del fantasma
        posicion = newPos; // Actualizar la posición almacenada del fantasma
    } else {
        // Si la nueva posición está fuera de la escena o colisiona, cambiar la dirección aleatoriamente
        direccion = randomDirection();
    }
}*/

/*#include "fantasma.h"
#include <QTimer>
#include <QRandomGenerator>
#include "mainwindow.h" // Solo si es necesario para acceder a Direction
#include <QGraphicsScene>
#include "direction.h"

Fantasma::Fantasma(int width, int height, int cellSize, QGraphicsScene *scene, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), spriteWidth(width), spriteHeight(height), cellSize(cellSize), scene(scene)
{
    setPixmap(QPixmap(":/fantasma.png")); // Asignar una imagen al objeto

    // Inicializar un temporizador para manejar el movimiento del fantasma
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(500); // Mover el fantasma cada medio segundo
}

void Fantasma::move()
{
    // Obtener una dirección aleatoria para el movimiento
    int randomDirection = QRandomGenerator::global()->bounded(0, 4); // 0 a 3 (arriba, abajo, izquierda, derecha)
    QPointF newPos = pos();

    // Determinar la nueva posición del fantasma en base a la dirección aleatoria
    switch (randomDirection) {
    case 0: // Arriba
        newPos.ry() -= cellSize;
        break;
    case 1: // Abajo
        newPos.ry() += cellSize;
        break;
    case 2: // Izquierda
        newPos.rx() -= cellSize;
        break;
    case 3: // Derecha
        newPos.rx() += cellSize;
        break;
    }

    // Verificar si la nueva posición es válida (no hay colisión con las paredes)
    if (scene->collidingItems(this).isEmpty()) {
        setPos(newPos); // Actualizar la posición del fantasma
    }
}


bool Fantasma::isColliding() const
{
    // Verificar si el fantasma colisiona con otros elementos en la escena
    QList<QGraphicsItem *> collidingItems = (scene->collidingItems(this));
    return !collidingItems.isEmpty();
}

Direction Fantasma::randomDirection() const
{
    // Generar una dirección aleatoria
    int directionInt = QRandomGenerator::global()->bounded(0, 4); // 0 a 3 (cuatro direcciones posibles)
    return static_cast<Direction>(directionInt);
}*/

/*#include "fantasma.h"
#include "direction.h"
#include <QTimer>
#include <QRandomGenerator>

Fantasma::Fantasma(int width, int height, int cellSize, QGraphicsScene *scene, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), spriteWidth(width), spriteHeight(height),
      cellSize(cellSize), scene(scene)
{
    setPixmap(QPixmap(":/fantasma.png")); // Asignar una imagen al objeto

    // Inicializar un temporizador para manejar el movimiento del fantasma
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(1000); // Mover el fantasma cada segundo
}

void Fantasma::move()
{
    // Determinar la nueva posición del fantasma en base a la dirección actual
    QPointF newPos = pos();
    Direction newDirection = randomDirection(); // Obtener una nueva dirección aleatoria
    switch (newDirection) {
    case Direction::Up:
        newPos.ry() -= cellSize;
        break;
    case Direction::Down:
        newPos.ry() += cellSize;
        break;
    case Direction::Left:
        newPos.rx() -= cellSize;
        break;
    case Direction::Right:
        newPos.rx() += cellSize;
        break;
    }

    // Verificar si la nueva posición es válida (no hay colisión)
    if (scene->collidingItems(this).isEmpty()) {
        // Si la nueva posición es válida, actualizar la posición del fantasma
        setPos(newPos);
    }
}

Direction Fantasma::randomDirection() const
{
    // Obtener una dirección aleatoria
    int dir = QRandomGenerator::global()->bounded(0, 4); // 0 a 3 (arriba, abajo, izquierda, derecha)
    return static_cast<Direction>(dir);
}*/

/*#include "fantasma.h"
#include "direction.h"
#include <QRandomGenerator>
#include <QTimer>

Fantasma::Fantasma(int width, int height, int cellSize, QGraphicsScene *scene, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), spriteWidth(width), spriteHeight(height), cellSize(cellSize), scene(scene)
{
    setPixmap(QPixmap(":/fantasma.png"));

    // Inicializar el temporizador y conectarlo a la función move()
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Fantasma::move);
    timer->start(1000); // Mover el fantasma cada segundo
}

void Fantasma::move()
{
    // Obtener una dirección aleatoria
    direccion = randomDirection();

    // Calcular la nueva posición del fantasma según la dirección aleatoria
    QPointF newPos = pos();
    switch (direccion) {
    case Direction::Up:
        newPos.ry() -= cellSize;
        break;
    case Direction::Down:
        newPos.ry() += cellSize;
        break;
    case Direction::Left:
        newPos.rx() -= cellSize;
        break;
    case Direction::Right:
        newPos.rx() += cellSize;
        break;
    }
    // Verificar si la nueva posición está dentro del laberinto y no hay colisión
        if (scene->sceneRect().contains(newPos) && !isColliding()) {
            // Actualizar la posición del fantasma
            setPos(newPos);
        } else {
            // Si hay colisión o la nueva posición está fuera del laberinto, cambiar de dirección
            direccion = randomDirection();
        }

        // Actualizar la escena para reflejar el movimiento del fantasma
        scene()->update();
    }


bool Fantasma::isColliding() const
{
    // Verificar si el fantasma está colisionando con algún otro elemento en la escena
    QList<QGraphicsItem*> collidingItems = scene->items();
    for (QGraphicsItem *item : collidingItems) {
        if (item != this) {
            if (collidesWithItem(item)) {
                return true;
            }
        }
    }
    return false;
}

Direction Fantasma::randomDirection() const
{
    // Generar una dirección aleatoria para el movimiento del fantasma
    int random = QRandomGenerator::global()->bounded(0, 4); // 0 a 3 (arriba, abajo, izquierda, derecha)
    return static_cast<Direction>(random);
}*/

/*#include "fantasma.h"
#include "direction.h"
#include <QRandomGenerator>
#include <QTimer>

Fantasma::Fantasma(int width, int height, int cellSize, QGraphicsScene *scene, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), spriteWidth(width), spriteHeight(height), cellSize(cellSize), scene(scene)
{
    setPixmap(QPixmap(":/fantasma.png"));

    // Inicializar el temporizador y conectarlo a la función move()
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Fantasma::move);
    timer->start(1000); // Mover el fantasma cada segundo

    // Configurar una dirección inicial aleatoria
    direccion = randomDirection();
}



void Fantasma::move()
{
    // Obtener una dirección aleatoria
    direccion = randomDirection();

    // Calcular la nueva posición del fantasma según la dirección aleatoria
    QPointF newPos = pos();
    switch (direccion) {
    case Direction::Up:
        newPos.ry() -= cellSize;
        break;
    case Direction::Down:
        newPos.ry() += cellSize;
        break;
    case Direction::Left:
        newPos.rx() -= cellSize;
        break;
    case Direction::Right:
        newPos.rx() += cellSize;
        break;
    }

    // Verificar si la nueva posición está dentro del laberinto y no hay colisión
    if (scene->sceneRect().contains(newPos) && !isColliding()) {
        // Actualizar la posición del fantasma
        setPos(newPos);
    } else {
        // Si hay colisión o la nueva posición está fuera del laberinto, cambiar de dirección
        direccion = randomDirection();
    }

    // Actualizar la escena para reflejar el movimiento del fantasma
    scene->update();
}


bool Fantasma::isColliding() const
{
    // Verificar si el fantasma está colisionando con algún otro elemento en la escena
    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    for (QGraphicsItem *item : collidingItemsList) {
        if (item != this) {
            return true;
        }
    }
    return false;
}


Direction Fantasma::randomDirection() const
{
    // Generar una dirección aleatoria para el movimiento del fantasma
    int random = QRandomGenerator::global()->bounded(0, 4); // 0 a 3 (arriba, abajo, izquierda, derecha)
    return static_cast<Direction>(random);
}*/

/*#include "fantasma.h"
#include "direction.h"
#include <QRandomGenerator>
#include <QTimer>

Fantasma::Fantasma(int width, int height, int cellSize, QGraphicsScene *scene, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), spriteWidth(width), spriteHeight(height), cellSize(cellSize), scene(scene)
{
    setPixmap(QPixmap(":/fantasma.png"));

    // Inicializar el temporizador y conectarlo a la función move()
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Fantasma::move);
    timer->start(1000); // Mover el fantasma cada segundo
}

void Fantasma::move()
{
    // Obtener una dirección aleatoria
    direccion = randomDirection();

    // Calcular la nueva posición del fantasma según la dirección aleatoria
    QPointF newPos = pos();
    switch (direccion) {
    case Direction::Up:
        newPos.ry() -= cellSize;
        break;
    case Direction::Down:
        newPos.ry() += cellSize;
        break;
    case Direction::Left:
        newPos.rx() -= cellSize;
        break;
    case Direction::Right:
        newPos.rx() += cellSize;
        break;
    }

    // Verificar si la nueva posición está dentro del laberinto y no hay colisión
    if (scene->sceneRect().contains(newPos) && !isColliding()) {
        // Actualizar la posición del fantasma
        setPos(newPos);
    } else {
        // Si hay colisión o la nueva posición está fuera del laberinto, cambiar de dirección
        direccion = randomDirection();
    }

    // Actualizar la escena para reflejar el movimiento del fantasma
    scene->update();
}

bool Fantasma::isColliding() const
{
    // Verificar si el fantasma está colisionando con algún otro elemento en la escena
    QList<QGraphicsItem*> collidingItems = scene->items();
    for (QGraphicsItem *item : collidingItems) {
        if (item != this) {
            if (collidesWithItem(item)) {
                return true;
            }
        }
    }
    return false;
}

Direction Fantasma::randomDirection() const
{
    // Generar una dirección aleatoria para el movimiento del fantasma
    int random = QRandomGenerator::global()->bounded(0, 4); // 0 a 3 (arriba, abajo, izquierda, derecha)
    return static_cast<Direction>(random);
}*/
#include "fantasma.h"
#include "direction.h"
#include <QRandomGenerator>
#include <QTimer>

Fantasma::Fantasma(int width, int height, int cellSize, QGraphicsScene *scene, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), spriteWidth(width), spriteHeight(height), cellSize(cellSize), scene(scene)
{
    setPixmap(QPixmap(":/fantasma.png"));

    // Inicializar el temporizador y conectarlo a la función move()
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Fantasma::move);
    timer->start(1000); // Mover el fantasma cada segundo
}

void Fantasma::move()
{
    // Obtener una dirección aleatoria
    direccion = randomDirection();

    // Calcular la nueva posición del fantasma según la dirección aleatoria
    QPointF newPos = pos();
    switch (direccion) {
    case Direction::Up:
        newPos.ry() -= cellSize;
        break;
    case Direction::Down:
        newPos.ry() += cellSize;
        break;
    case Direction::Left:
        newPos.rx() -= cellSize;
        break;
    case Direction::Right:
        newPos.rx() += cellSize;
        break;
    }
    // Verificar si la nueva posición está dentro del laberinto y no hay colisión
    if (scene->sceneRect().contains(newPos) && !isColliding()) {
        // Actualizar la posición del fantasma
        setPos(newPos);
    } else {
        // Si hay colisión o la nueva posición está fuera del laberinto, cambiar de dirección
        direccion = randomDirection();
    }

    // Actualizar la escena para reflejar el movimiento del fantasma
    scene->update();
}

bool Fantasma::isColliding() const
{
    // Verificar si el fantasma está colisionando con algún otro elemento en la escena
    QList<QGraphicsItem*> collidingItems = scene->collidingItems(this);
    for (QGraphicsItem *item : collidingItems) {
        if (item != this) {
            if (collidesWithItem(item)) {
                return true;
            }
        }
    }
    return false;
}

Direction Fantasma::randomDirection() const
{
    // Generar una dirección aleatoria para el movimiento del fantasma
    int random = QRandomGenerator::global()->bounded(0, 4); // 0 a 3 (arriba, abajo, izquierda, derecha)
    return static_cast<Direction>(random);
}

/*#include "pacman.h"
#include <QKeyEvent>

Pacman::Pacman(int width, int height, int cellSize, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), spriteWidth(width), spriteHeight(height), cellSize(cellSize)
{
    setPixmap(QPixmap(":/pacman.png")); // Suponiendo que pacman.png está en el directorio de recursos
    setZValue(1); // Asegura que el Pacman esté delante de otras entidades en la escena
    currentDirection = Direction::Right;
    pacmanPos = QPointF(cellSize / 2.0, cellSize / 2.0);
    setPos(pacmanPos);
}

void Pacman::move(Direction direction)
{
    QPointF newPos = pacmanPos;

    // Calcular la nueva posición del Pacman según la dirección
    switch (direction) {
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
    if (!checkCollision(newPos)) {
        // Actualizar la posición del Pacman
        setPos(newPos);
        pacmanPos = newPos;
        currentDirection = direction;
    }
}

bool Pacman::checkCollision(const QPointF &newPos) const
{
    // Verificar si la nueva posición colisiona con las paredes del laberinto
    // Por simplicidad, asumimos que las paredes son los caracteres '#'
    int row = newPos.y() / cellSize;
    int col = newPos.x() / cellSize;
    return (row < 0 || row >= 20 || col < 0 || col >= 20); // Ajusta los límites según el tamaño del laberinto
}*/

#include "pacman.h"
#include <QKeyEvent>
#include <qDebug>

Pacman::Pacman(int width, int height, int cellSize, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), spriteWidth(width), spriteHeight(height), cellSize(cellSize)
{
    setPixmap(QPixmap(":/spritesheet.png")); // Cargar el spritesheet
    setZValue(1); // Asegurar que Pacman esté delante de otras entidades en la escena
    currentDirection = Direction::Right;
    pacmanPos = QPointF(cellSize / 2.0, cellSize / 2.0);
    setPos(pacmanPos);
}

void Pacman::move(Direction direction)
{
    QPointF newPos = pacmanPos;

    // Calcular la nueva posición de Pacman según la dirección
    switch (direction) {
    case Direction::Up:
        newPos.ry() -= cellSize;
        qDebug() << "Moving Up: New position" << newPos;
        break;
    case Direction::Down:
        newPos.ry() += cellSize;
        qDebug() << "Moving Down: New position" << newPos;
        break;
    case Direction::Left:
        newPos.rx() -= cellSize;
        qDebug() << "Moving Left: New position" << newPos;
        break;
    case Direction::Right:
        newPos.rx() += cellSize;
        qDebug() << "Moving Right: New position" << newPos;
        break;
    }

    // Verificar si la nueva posición es válida (no hay colisión)
    if (!checkCollision(newPos)) {
        // Actualizar la posición de Pacman
        setPos(newPos);
        pacmanPos = newPos;
        currentDirection = direction;
        qDebug() << "Pacman moved successfully to position" << newPos;
    } else {
        qDebug() << "Collision detected, Pacman cannot move to position" << newPos;
    }
}


bool Pacman::checkCollision(const QPointF &newPos) const
{
    // Verificar si la nueva posición colisiona con las paredes del laberinto
    // Por simplicidad, asumimos que las paredes son los caracteres '#'
    int row = newPos.y() / cellSize;
    int col = newPos.x() / cellSize;
    return (row < 0 || row >= 20 || col < 0 || col >= 20); // Ajustar los límites según el tamaño del laberinto
}

void Pacman::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Key pressed: " << event->key(); // Imprime la tecla presionada para depuración

    switch (event->key()) {
    case Qt::Key_Up:
        move(Direction::Up);
        break;
    case Qt::Key_Down:
        move(Direction::Down);
        break;
    case Qt::Key_Left:
        move(Direction::Left);
        break;
    case Qt::Key_Right:
        move(Direction::Right);
        break;
    default:
        break;
    }
}



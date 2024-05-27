/*#include "pacman.h"
#include <QKeyEvent>
//#include <qDebug>

Pacman::Pacman(int width, int height, int cellSize, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), spriteWidth(width), spriteHeight(height), cellSize(cellSize)
{
    setPixmap(QPixmap(":/spritesheet.png")); // Cargar el spritesheet
    setZValue(1); // Asegurar que Pacman esté delante de otras entidades en la escena
    currentDirection = Direction::Right;
    pacmanPos = QPointF(cellSize / 2.0, cellSize / 2.0);
    setPos(pacmanPos);
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

}*/



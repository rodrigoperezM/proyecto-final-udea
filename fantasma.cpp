
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

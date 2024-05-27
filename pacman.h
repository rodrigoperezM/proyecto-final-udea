
/*#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent> // Necesitamos incluir QKeyEvent para poder usarlo

enum class Direction { Up, Down, Left, Right }; // Definición de Direction

class Pacman : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Pacman(int width, int height, int cellSize, QObject *parent = nullptr);
    //void move(Direction direction);
    bool checkCollision(const QPointF &newPos) const;

private:
    int spriteWidth;
    int spriteHeight;
    int cellSize;
    Direction currentDirection;
    QPointF pacmanPos;
protected:
    void keyPressEvent(QKeyEvent *event) override;

};

#endif // PACMAN_H*/




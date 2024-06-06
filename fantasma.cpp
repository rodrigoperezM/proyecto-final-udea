#include "fantasma.h"
#include <cstdlib>

Fantasma::Fantasma(int cellSize, const std::vector<QString> &laberinto, QGraphicsScene *scene, const QPixmap &pixmap, GhostType type)
    : QGraphicsPixmapItem(pixmap), cellSize(cellSize), laberinto(laberinto), pacmanX(0), pacmanY(0), score(0), type(type), powerMode(false) {
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Fantasma::move);
    moveTimer->start(500);
}

void Fantasma::setPacmanPosition(int x, int y) {
    pacmanX = x;
    pacmanY = y;
}

void Fantasma::setScore(int score) {
    this->score = score;
}

void Fantasma::setPowerMode(bool powerMode) {
    this->powerMode = powerMode;
}

void Fantasma::move() {
    int ghostX = x() / cellSize;
    int ghostY = y() / cellSize;

    if (powerMode) {
        // Mueve fantasma en dirección opuesta a Pacman
        if (ghostX <= pacmanX / cellSize) {
            ghostX--;
        } else if (ghostX >= pacmanX / cellSize) {
            ghostX++;
        }

        if (ghostY <= pacmanY / cellSize) {
            ghostY--;
        } else if (ghostY >= pacmanY / cellSize) {
            ghostY++;
        }
    } else {
        // Mueve fantasma hacia Pacman
        if (ghostX < pacmanX / cellSize) {
            ghostX++;
        } else if (ghostX > pacmanX / cellSize) {
            ghostX--;
        }

        if (ghostY < pacmanY / cellSize) {
            ghostY++;
        } else if (ghostY > pacmanY / cellSize) {
            ghostY--;
        }
    }

    if (laberinto[ghostY][ghostX] != '#') {
        setPos(ghostX * cellSize, ghostY * cellSize);
    }

    if (ghostX == pacmanX / cellSize && ghostY == pacmanY / cellSize) {
        emit pacmanCaught();
    }
}

/*void Fantasma::changeDirection() {
    // Cambia dirección aleatoriamente
}*/



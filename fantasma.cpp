
#include "fantasma.h"
#include <cstdlib>
#include <ctime>

Fantasma::Fantasma(int cellSize, const std::vector<QString>& laberinto, QGraphicsScene *scene, const QPixmap &sprite)
    : cellSize(cellSize), laberinto(laberinto), scene(scene) {
    setPixmap(sprite.scaled(cellSize, cellSize));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Fantasma::move);
    timer->start(1000); // Move every second
    srand(time(nullptr)); // Inicializar la semilla del generador de números aleatorios
}

void Fantasma::move() {
    moveRandomly();
}

void Fantasma::moveRandomly() {
    // Obtener una dirección de movimiento aleatoria
    int dx = rand() % 3 - 1; // -1, 0 o 1
    int dy = rand() % 3 - 1; // -1, 0 o 1

    // Calcular la nueva posición
    int newX = x() + dx * cellSize;
    int newY = y() + dy * cellSize;

    // Verificar si el movimiento es válido (no chocar con las paredes)
    if (canMoveTo(newX, newY)) {
        setPos(newX, newY);
    }
}

bool Fantasma::canMoveTo(int newX, int newY) {
    int col = newX / cellSize;
    int row = newY / cellSize;

    // Verificar límites del laberinto y paredes
    if (row >= 0 && row < laberinto.size() && col >= 0 && col < laberinto[0].size() && laberinto[row][col] != '#') {
        return true;
    }
    return false;
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include "fantasma.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    spriteWidth(32),
    spriteHeight(32),
    cellSize(40)
{
    ui->setupUi(this);

    // Inicializar la escena y la vista
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Inicializar el laberinto como un laberinto simple de 20x30
    laberinto = {
        "##################",
        "#.......#........#",
        "#..###...#..##.###",
        "#........#.......#",
        "#...##...#####.###",
        "#..........#...#.#",
        "#########...#....#",
        "#............#..##",
        "#..##....###.....#",
        "##...##....#.#..##",
        "######..####.##.##",
        "#............#...#",
        "#.##.##..###..####",
        "##################",
    };
    // Dibujar el laberinto en la escena
    drawLaberinto();

    // Cargar y recortar el spritesheet
    QPixmap spritesheet(":/spritesheet.png");
    //QList<QPixmap> sprites = recortarSpritesheet(spritesheet, spriteWidth, spriteHeight);
    sprites = recortarSpritesheet(spritesheet, spriteWidth, spriteHeight);

    // Colocar las imágenes en el laberinto
    colocarImagen(sprites[0], 10, 5); // fruta
    colocarImagen(sprites[1], 2, 3); // fruta
    colocarImagen(sprites[2], 5, 11); // fruta
    colocarImagen(sprites[3], 11, 16); //fruta
    colocarImagen(sprites[4], 1, 13); //llave

    // Crear y agregar los fantasmas a la escena
    colocarImagen(sprites[5], 12, 2); // Fantasma 5
    colocarImagen(sprites[6], 7, 7); // Fantasma 6
    colocarImagen(sprites[7], 1, 5); //pacman
    colocarImagen(sprites[8], 4, 1); // fantasma
    colocarImagen(sprites[9], 4, 15); // fantasma
    colocarImagen(sprites[10], 7, 16); // fantasma

    Fantasma *fantasma1 = new Fantasma(spriteWidth, spriteHeight, cellSize, scene);
    Fantasma *fantasma2 = new Fantasma(spriteWidth, spriteHeight, cellSize, scene);
    scene->addItem(fantasma1);
    scene->addItem(fantasma2);

    // Conectar el temporizador de cada fantasma a su función move()
    connect(fantasma1->getTimer(), &QTimer::timeout, fantasma1, &Fantasma::move);
    connect(fantasma2->getTimer(), &QTimer::timeout, fantasma2, &Fantasma::move);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        movePacman(Direction::Left);
        break;
    case Qt::Key_Right:
        movePacman(Direction::Right);
        break;
    case Qt::Key_Up:
        movePacman(Direction::Up);
        break;
    case Qt::Key_Down:
        movePacman(Direction::Down);
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
    scene->update(); // Actualizar la escena después del movimiento del jugador
}

void MainWindow::movePacman(Direction direction)
{
    // Buscar la posición actual de Pacman
    int row = 0, col = 0;
    for (row = 0; row < laberinto.size(); ++row) {
        col = QString::fromStdString(laberinto[row]).indexOf('P');
        if (col != -1) break;
    }

    // Calcular la nueva posición según la dirección
    switch (direction) {
    case Direction::Left:
        if (col > 0 && laberinto[row][col - 1] != '#') {
            laberinto[row][col] = ' '; // Limpiar la posición actual
            laberinto[row][col - 1] = 'P'; // Actualizar la nueva posición
        }
        break;
    case Direction::Right:
        if (col < laberinto[row].size() - 1 && laberinto[row][col + 1] != '#') {
            laberinto[row][col] = ' '; // Limpiar la posición actual
            laberinto[row][col + 1] = 'P'; // Actualizar la nueva posición
        }
        break;
    case Direction::Up:
        if (row > 0 && laberinto[row - 1][col] != '#') {
            laberinto[row][col] = ' '; // Limpiar la posición actual
            laberinto[row - 1][col] = 'P'; // Actualizar la nueva posición
        }
        break;
    case Direction::Down:
        if (row < laberinto.size() - 1 && laberinto[row + 1][col] != '#') {
            laberinto[row][col] = ' '; // Limpiar la posición actual
            laberinto[row + 1][col] = 'P'; // Actualizar la nueva posición
        }
        break;
    }

    // Actualizar la posición de Pacman en la escena
    QGraphicsItem *pacman = scene->items().at(7);
    int newX = pacman->x() + (direction == Direction::Right) - (direction == Direction::Left);
    int newY = pacman->y() + (direction == Direction::Down) - (direction == Direction::Up);
    pacman->setPos(newX, newY);
}

void MainWindow::moveFantasma(Fantasma *fantasma)
{
    // Implementar la lógica para mover al fantasma
    // Por ahora, moveremos aleatoriamente
    int randomDirection = qrand() % 4; // 0: arriba, 1: derecha, 2: abajo, 3: izquierda

    int dx = 0, dy = 0;
    switch (randomDirection) {
    case 0: // Arriba
        dy = -1;
        break;
    case 1: // Derecha
        dx = 1;
        break;
    case 2: // Abajo
        dy = 1;
        break;
    case 3: // Izquierda
        dx = -1;
        break;
    }

    // Obtener la posición actual del fantasma
    int x = fantasma->x() / cellSize;
    int y = fantasma->y() / cellSize;

    // Verificar si la próxima posición está dentro del laberinto y no es una pared
    if (x + dx >= 0 && x + dx < laberinto[0].size() && y + dy >= 0 && y + dy < laberinto.size() &&
            laberinto[y + dy][x + dx] != '#') {
        // Mover el fantasma
        fantasma->setPos((x + dx) * cellSize, (y + dy) * cellSize);
    }
}

void MainWindow::drawLaberinto()
{
    const int numRows = laberinto.size(); // Número de filas en el laberinto
    const int numCols = laberinto[0].size(); // Número de columnas en el laberinto

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            // Dibujar las paredes del laberinto
            if (laberinto[row][col] == '#') {
                scene->addRect(col * cellSize, row * cellSize, cellSize, cellSize, QPen(Qt::black), QBrush(Qt::blue));
            }
            // Dibujar puntos en ciertas posiciones
            else if (laberinto[row][col] == '.') {
                // Dibujar un pequeño círculo en el centro de la celda
                int x = col * cellSize + cellSize / 2 - 2; // centrado horizontalmente
                int y = row * cellSize + cellSize / 2 - 2; // centrado verticalmente
                scene->addEllipse(x, y, 4, 4, QPen(Qt::black), QBrush(Qt::black));
            }
        }
    }
}

void MainWindow::colocarImagen(const QPixmap &imagen, int fila, int columna)
{
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(imagen);
    item->setPos(columna * cellSize, fila * cellSize);
    scene->addItem(item);
    // Guardar una referencia al item en la lista
       spritesItems.append(item);
}

QList<QPixmap> MainWindow::recortarSpritesheet(const QPixmap &spritesheet, int newWidth, int newHeight)
{
    QList<QPixmap> sprites;
    int numRows = 3;
    int numCols = 4;
    int spriteWidth = spritesheet.width() / numCols;
    int spriteHeight = spritesheet.height() / numRows;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            QPixmap sprite = spritesheet.copy(col * spriteWidth, row * spriteHeight, spriteWidth, spriteHeight)
                             .scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            sprites.append(sprite);
        }
    }
    return sprites;
}


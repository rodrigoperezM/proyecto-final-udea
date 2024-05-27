
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fantasma.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pacmanX(1),
    pacmanY(1),
    spriteWidth(32),
    spriteHeight(32),
    cellSize(40),
    score(0),
    lives(3),  // Iniciar con 3 vidas
    enemiesRemaining(2)  // Número de enemigos iniciales
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Inicializar el laberinto
    laberinto = {
        "##################",
        "#.......#........#",
        "#...##...#..##..##",
        "#........#.......#",
        "#...##...#####.###",
        "#..........#...#.#",
        "#########...#....#",
        "#............#...#",
        "#..##....###.....#",
        "##...##....#.#..##",
        "#####...####.##.##",
        "#............#...#",
        "#..#.##..###..####",
        "##################",
    };

    // Dibujar el laberinto en la escena
    drawLaberinto();

    // Crear etiquetas para la puntuación, vidas y enemigos restantes
    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setGeometry(10, 10, 100, 30);
    livesLabel = new QLabel("Lives: 3", this);
    livesLabel->setGeometry(120, 10, 100, 30);
    enemiesLabel = new QLabel("Enemies: 2", this);
    enemiesLabel->setGeometry(230, 10, 100, 30);

    // Colocar Pac-Man en el laberinto
    QPixmap pacmanImage(":/pacman.png");
    pacmanItem = new QGraphicsPixmapItem(pacmanImage);
    pacmanItem->setPos(pacmanX * cellSize, pacmanY * cellSize);
    scene->addItem(pacmanItem);

    // Cargar imágenes de los fantasmas
    QPixmap ghostImage1(":/ghost1.png");
    QPixmap ghostImage2(":/ghost2.png");

    // Crear y agregar los fantasmas a la escena con sus imágenes
    Fantasma *fantasma1 = new Fantasma(cellSize, laberinto, scene, ghostImage1);
    Fantasma *fantasma2 = new Fantasma(cellSize, laberinto, scene, ghostImage2);
    fantasma1->setPos(5 * cellSize, 10 * cellSize);
    fantasma2->setPos(10 * cellSize, 5 * cellSize);
    scene->addItem(fantasma1);
    scene->addItem(fantasma2);

    // Iniciar los temporizadores de los fantasmas
    fantasma1->getTimer()->start();
    fantasma2->getTimer()->start();
}

MainWindow::~MainWindow()
{
    delete ui;
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
                QGraphicsEllipseItem *point = scene->addEllipse(x, y, 4, 4, QPen(Qt::black), QBrush(Qt::black));
                point->setData(0, "point"); // Etiquetar el punto
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_W:
            movePacman(0, -1);
            break;
        case Qt::Key_A:
            movePacman(-1, 0);
            break;
        case Qt::Key_S:
            movePacman(0, 1);
            break;
        case Qt::Key_D:
            movePacman(1, 0);
            break;
        default:
            QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::movePacman(int dx, int dy)
{
    int newPacmanX = pacmanX + dx;
    int newPacmanY = pacmanY + dy;

    // Verificar colisiones con las paredes
    if (newPacmanX >= 0 && newPacmanX < laberinto[0].size() &&
        newPacmanY >= 0 && newPacmanY < laberinto.size() &&
        laberinto[newPacmanY][newPacmanX] != '#')
    {
        pacmanX = newPacmanX;
        pacmanY = newPacmanY;
        pacmanItem->setPos(pacmanX * cellSize, pacmanY * cellSize);
        collectPoint(newPacmanX, newPacmanY);
        checkCollision();
    }
}

void MainWindow::collectPoint(int x, int y)
{
    if (laberinto[y][x] == '.') {
        laberinto[y][x] = ' '; // Eliminar el punto del laberinto
        updateScore();
        // Eliminar el punto gráfico del laberinto
        QList<QGraphicsItem *> items = scene->items(QRectF(x * cellSize, y * cellSize, cellSize, cellSize));
        for (QGraphicsItem *item : items) {
            if (item->data(0) == "point") {
                scene->removeItem(item); // Eliminar el punto gráfico
                delete item; // Liberar la memoria del punto
            }
        }
    }
}

void MainWindow::checkCollision()
{
    // Verificar colisión con los fantasmas
    QList<QGraphicsItem *> items = scene->collidingItems(pacmanItem);
    for (QGraphicsItem *item : items) {
        Fantasma *fantasma = dynamic_cast<Fantasma *>(item);
        if (fantasma) {
            lives--;  // Reducir una vida
            updateLives();
            if (lives <= 0) {
                checkGameOver();
            }
        }
    }
}

void MainWindow::updateScore()
{
    score += 10; // Incrementar la puntuación
    scoreLabel->setText("Score: " + QString::number(score));
}

void MainWindow::updateLives()
{
    livesLabel->setText("Lives: " + QString::number(lives));
}

void MainWindow::updateEnemiesRemaining()
{
    enemiesLabel->setText("Enemies: " + QString::number(enemiesRemaining));
}

void MainWindow::checkGameOver()
{
    // Verificar si el juego ha terminado
    if (lives <= 0) {
        QMessageBox::information(this, "Game Over", "Se acabaron las vidas. Juego terminado.");
        // Resetear o terminar el juego
    }
}

void MainWindow::on_pushButton_clicked()
{
    // Configurar las variables iniciales del juego
    score = 0;
    lives = 3;
    enemiesRemaining = 2;

    // Actualizar las etiquetas de puntuación, vidas y enemigos restantes
    updateScore();
    updateLives();
    updateEnemiesRemaining();

    // Crear y posicionar Pac-Man en el laberinto
    pacmanX = 1;
    pacmanY = 1;
    pacmanItem->setPos(pacmanX * cellSize, pacmanY * cellSize);

    // Redibujar el laberinto
    drawLaberinto();
}

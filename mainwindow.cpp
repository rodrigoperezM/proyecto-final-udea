#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fantasma.h"
#include <QMessageBox>
#include <QTimer>
#include <QMessageBox>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pacmanX(1),
    pacmanY(1),
    spriteWidth(32),
    spriteHeight(32),
    cellSize(40),
    score(0),
    lives(3),
    enemiesRemaining(2),
    gameOver(false),
    powerMode(false),
    pacmanMouthOpen(true) // Indicar que inicialmente la boca de Pac-Man está abierta
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    laberinto = {
        "##################",
        "#.......#.....*..#",
        "#...##...#..##..##",
        "#........#.......#",
        "#...##...#####.###",
        "#..........#...#.#",
        "#########...#....#",
        "#*...........#...#",
        "#..##....###...*.#",
        "##...##....#.#..##",
        "#####...####.##.##",
        "#............#...#",
        "#*.#.##..###..####",
        "##################",
    };

    drawLaberinto();

    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setGeometry(900, 10, 100, 30); // (x, y, ancho, alto)
    livesLabel = new QLabel("Lives: 3", this);
    livesLabel->setGeometry(900, 50, 100, 30); // Ajustado para estar debajo de scoreLabel
    enemiesLabel = new QLabel("Enemies: 2", this);
    enemiesLabel->setGeometry(900, 90, 100, 30); // Ajustado para estar debajo de livesLabel

    // Cargar las imágenes de Pac-Man con la boca abierta y cerrada
    pacmanImageOpen.load(":/pacman2.png");
    pacmanImageClosed.load(":/pacman1.png");

    // Cargar las imágenes de Pac-Man en diferentes direcciones
    pacmanImageUp.load(":/arriba.png");
    pacmanImageDown.load(":/abajo.png");
    pacmanImageLeft.load(":/izquierda.png");
    pacmanImageRight.load(":/pacman2.png");

    // Inicializar la variable de estado de la boca de Pac-Man
    pacmanMouthOpen = true;

    // Establecer la imagen de Pac-Man en la escena y guardar su referencia
    pacmanItem = new QGraphicsPixmapItem(pacmanImageOpen);
    pacmanItem->setPos(pacmanX * cellSize, pacmanY * cellSize);
    scene->addItem(pacmanItem);

    // Configurar el sonido de Pac-Man
    chompSound = new QMediaPlayer(this);
    chompSound->setMedia(QUrl("qrc:/pacmansonido.mp3"));
    chompSound->setVolume(50);

    // Reproducir el sonido al inicio del juego
    chompSound->play();

    // Crear y posicionar los fantasmas
    QPixmap ghostImage1(":/ghost1.png");
    QPixmap ghostImage2(":/ghost2.png");
    Fantasma *blinky = new Fantasma(cellSize, laberinto, scene, ghostImage1, GhostType::Blinky);
    Fantasma *clyde = new Fantasma(cellSize, laberinto, scene, ghostImage2, GhostType::Clyde);
    blinky->setPos(5 * cellSize, 10 * cellSize);
    clyde->setPos(10 * cellSize, 5 * cellSize);
    scene->addItem(blinky);
    scene->addItem(clyde);

    // Conectar las señales de pacmanCaught de los fantasmas al método handlePacmanCaught
    connect(blinky, &Fantasma::pacmanCaught, this, &MainWindow::handlePacmanCaught);
    connect(clyde, &Fantasma::pacmanCaught, this, &MainWindow::handlePacmanCaught);

    powerTimer = new QTimer(this);
    connect(powerTimer, &QTimer::timeout, this, &MainWindow::deactivatePowerMode);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::drawLaberinto() {
    totalPoints = 0;
    const int numRows = laberinto.size();
    const int numCols = laberinto[0].size();
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (laberinto[row][col] == '#') {
                scene->addRect(col * cellSize, row * cellSize, cellSize, cellSize, QPen(Qt::black), QBrush(Qt::blue));
            } else if (laberinto[row][col] == '.') {
                totalPoints++;
                int x = col * cellSize + cellSize / 2 - 2;
                int y = row * cellSize + cellSize / 2 - 2;
                QGraphicsEllipseItem *point = scene->addEllipse(x, y, 4, 4, QPen(Qt::black), QBrush(Qt::black));
                point->setData(0, "Punto");
            } else if (laberinto[row][col] == '*') {
                int x = col * cellSize + cellSize / 2 - 5;
                int y = row * cellSize + cellSize / 2 - 5;
                QGraphicsEllipseItem *powerPoint = scene->addEllipse(x, y, 10, 10, QPen(Qt::black), QBrush(Qt::yellow));
                powerPoint->setData(0, "Puntos de poder");
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // Verificar si el juego está en marcha
    if (!ui->pushButton->isEnabled()) {
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
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

/*void MainWindow::movePacman(int dx, int dy) {
    int newPacmanX = pacmanX + dx;
    int newPacmanY = pacmanY + dy;
    if (newPacmanX >= 0 && newPacmanX < static_cast<int>(laberinto[0].size()) && newPacmanY >= 0 && newPacmanY < static_cast<int

>(laberinto.size()) && laberinto[newPacmanY][newPacmanX] != '#') {
        pacmanX = newPacmanX;
        pacmanY = newPacmanY;

        // Cambiar la imagen de Pac-Man dependiendo de la dirección
        if (dx > 0) {
            pacmanItem->setPixmap(pacmanMouthOpen ? pacmanImageRight : pacmanImageClosed);
        } else if (dx < 0) {
            pacmanItem->setPixmap(pacmanMouthOpen ? pacmanImageLeft : pacmanImageClosed);
        } else if (dy > 0) {
            pacmanItem->setPixmap(pacmanMouthOpen ? pacmanImageDown : pacmanImageClosed);
        } else if (dy < 0) {
            pacmanItem->setPixmap(pacmanMouthOpen ? pacmanImageUp : pacmanImageClosed);
        }

        // Alternar el estado de la boca de Pac-Man
        pacmanMouthOpen = !pacmanMouthOpen;

        // Actualizar la posición de Pac-Man en la escena
        pacmanItem->setPos(pacmanX * cellSize, pacmanY * cellSize);

        // Verificar la recolección de puntos y colisiones
        collectPoint(newPacmanX, newPacmanY);
        checkCollision();

        // Actualizar la posición y puntuación de los fantasmas
        QList<QGraphicsItem *> items = scene->items();
        foreach (QGraphicsItem *item, items) {
            Fantasma *ghost = dynamic_cast<Fantasma *>(item);
            if (ghost) {
                ghost->setPacmanPosition(pacmanX * cellSize, pacmanY * cellSize);
                ghost->setScore(score);
            }
        }
    }
}*/

/*void MainWindow::movePacman(int dx, int dy) {
    int newPacmanX = pacmanX + dx;
    int newPacmanY = pacmanY + dy;
    if (newPacmanX >= 0 && newPacmanX < static_cast<int>(laberinto[0].size()) && newPacmanY >= 0 && newPacmanY < static_cast<int>(laberinto.size()) && laberinto[newPacmanY][newPacmanX] != '#') {
        pacmanX = newPacmanX;
        pacmanY = newPacmanY;

        // Cambiar la imagen de Pac-Man dependiendo de la dirección
        if (dx > 0) {
            pacmanItem->setPixmap(pacmanMouthOpen ? pacmanImageRight : pacmanImageClosed);
        } else if (dx < 0) {
            pacmanItem->setPixmap(pacmanMouthOpen ? pacmanImageLeft : pacmanImageClosed);
        } else if (dy > 0) {
            pacmanItem->setPixmap(pacmanMouthOpen ? pacmanImageDown : pacmanImageClosed);
        } else if (dy < 0) {
            pacmanItem->setPixmap(pacmanMouthOpen ? pacmanImageUp : pacmanImageClosed);
        }

        // Alternar el estado de la boca de Pac-Man
        pacmanMouthOpen = !pacmanMouthOpen;

        // Reproducir el sonido de masticar si se recolecta un punto
        collectPoint(newPacmanX, newPacmanY);

        // Actualizar la posición de Pac-Man en la escena
        pacmanItem->setPos(pacmanX * cellSize, pacmanY * cellSize);

        // Verificar colisiones con los fantasmas
        checkCollision();

        // Actualizar la posición y puntuación de los fantasmas
        QList<QGraphicsItem *> items = scene->items();
        foreach (QGraphicsItem *item, items) {
            Fantasma *ghost = dynamic_cast<Fantasma *>(item);
            if (ghost) {
                ghost->setPacmanPosition(pacmanX * cellSize, pacmanY * cellSize);
                ghost->setScore(score);
            }
        }
    }
}*/

void MainWindow::movePacman(int dx, int dy) {
    int newPacmanX = pacmanX + dx;
    int newPacmanY = pacmanY + dy;
    if (newPacmanX >= 0 && newPacmanX < static_cast<int>(laberinto[0].size()) && newPacmanY >= 0 && newPacmanY < static_cast<int>(laberinto.size()) && laberinto[newPacmanY][newPacmanX] != '#') {
        pacmanX = newPacmanX;
        pacmanY = newPacmanY;

        // Cambiar la imagen de Pac-Man dependiendo de la dirección
        if (dx > 0) {
            pacmanItem->setPixmap(pacmanMouthOpen ? pacmanImageRight : pacmanImageClosed);
        } else if (dx < 0) {
            pacmanItem->setPixmap(pacmanMouthOpen ? pacmanImageLeft : pacmanImageClosed);
        } else if (dy > 0) {
            pacmanItem->setPixmap(pacmanMouthOpen ? pacmanImageDown : pacmanImageClosed);
        } else if (dy < 0) {
            pacmanItem->setPixmap(pacmanMouthOpen ? pacmanImageUp : pacmanImageClosed);
        }

        // Alternar el estado de la boca de Pac-Man
        pacmanMouthOpen = !pacmanMouthOpen;

        // Reproducir el sonido de masticar
        chompSound->play();

        // Actualizar la posición de Pac-Man en la escena
        pacmanItem->setPos(pacmanX * cellSize, pacmanY * cellSize);

        // Verificar colisiones con los fantasmas
        checkCollision();

        // Actualizar la posición y puntuación de los fantasmas
        QList<QGraphicsItem *> items = scene->items();
        foreach (QGraphicsItem *item, items) {
            Fantasma *ghost = dynamic_cast<Fantasma *>(item);
            if (ghost) {
                ghost->setPacmanPosition(pacmanX * cellSize, pacmanY * cellSize);
                ghost->setScore(score);
            }
        }
    }
}



void MainWindow::collectPoint(int x, int y) {
    if (laberinto[y][x] == '.') {
        laberinto[y][x] = ' ';
        updateScore();
        totalPoints--;
        QList<QGraphicsItem *> items = scene->items(QRectF(x * cellSize, y * cellSize, cellSize, cellSize));
        for (QGraphicsItem *item : items) {
            if (item->data(0) == "Punto") {
                scene->removeItem(item);
                delete item;
            }
        }
        checkGameOver();
    } else if (laberinto[y][x] == '*') {
        handlePowerPoint(x, y);
    }
}

void MainWindow::handlePowerPoint(int x, int y) {
    activatePowerMode();
    laberinto[y][x] = ' ';
    score += 50;
    QList<QGraphicsItem *> items = scene->items(QRectF(x * cellSize, y * cellSize, cellSize, cellSize));
    for (QGraphicsItem *item : items) {
        if (item->data(0) == "Puntos de poder") {
            scene->removeItem(item);
            delete item;
        }
    }
    updateScore();
}

void MainWindow::activatePowerMode() {
    powerMode = true;
    powerTimer->start(5000);
    foreach (QGraphicsItem *item, scene->items()) {
        Fantasma *ghost = dynamic_cast<Fantasma *>(item);
        if (ghost) {
            ghost->setPowerMode(true);
        }
    }
}

void MainWindow::deactivatePowerMode() {
    powerMode = false;
    powerTimer->stop();
    foreach (QGraphicsItem *item, scene->items()) {
        Fantasma *ghost = dynamic_cast<Fantasma *>(item);
        if (ghost) {
            ghost->setPowerMode(false);
        }
    }
}

void MainWindow::checkCollision() {
    QList<QGraphicsItem *> items = scene->items(QRectF(pacmanX * cellSize, pacmanY * cellSize, cellSize, cellSize));
    for (QGraphicsItem *item : items) {
        Fantasma *ghost = dynamic_cast<Fantasma *>(item);
        if (ghost) {
            if (powerMode) {
                scene->removeItem(ghost);
                delete ghost;
                enemiesRemaining--;
                updateEnemiesRemaining();
            } else {
                handlePacmanCaught();
            }
        }
    }
}

void MainWindow::handlePacmanCaught() {
    if (gameOver) return; // Asegura de no ejecutar más lógica si el juego ya terminó

    lives--;
    if (lives < 0) lives = 0; // Asegura de que las vidas no sean negativas
    updateLives();
    if (lives <= 0) {
        gameOver = true;
        QMessageBox::information(this, "Game Over", "Pacman ha perdido todas las vidas!");
    } else {
        resetPacmanPosition();
    }
}

void MainWindow::updateScore() {
    scoreLabel->setText("Score: " + QString::number(score));
}

void MainWindow::updateLives() {
    livesLabel->setText("Vidas: " + QString::number(lives));
}

void MainWindow::updateEnemiesRemaining() {
    enemiesLabel->setText("Enemigos: " + QString::number(enemiesRemaining));
    checkGameOver();
}

void MainWindow::checkGameOver() {
    if (totalPoints == 0) {
        gameOver = true;
        QMessageBox::information(this, "Has ganado!", "Pacman se ha comido todos los puntos!");
    } else if (enemiesRemaining == 0) {
        gameOver = true;
        QMessageBox::information(this, "Has ganado!", "Pacman se ha comido todos los fantasmas!");
    }
}

void MainWindow::resetPacmanPosition() {
    pacmanX = 1;
    pacmanY = 1;
    pacmanItem->setPos(pacmanX * cellSize, pacmanY * cellSize);
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

    // Iniciar los temporizadores de los fantasmas
    // timerFantasma1->start();
    // timerFantasma2->start();

    // Deshabilitar el botón de inicio para evitar movimientos antes de comenzar el juego
    ui->pushButton->setEnabled(false);
}

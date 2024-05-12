/*#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Crear la escena y el QGraphicsView
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Inicializar el laberinto como un laberinto simple de 20x30
    laberinto = {
        "##############################",
        "#                            #",
        "# ############### ############",
        "# ############### ############",
        "#        # ####### #######    #",
        "#        # ####### #######    #",
        "#        # ####### #######    #",
        "# ######## ####### ####### ## #",
        "# ######## ####### ####### ## #",
        "#        #          #         #",
        "#        #          #         #",
        "## ###### ########### ###### ##",
        "#        #          #         #",
        "#        #          #         #",
        "# ######## ########## #########",
        "# ######## ########## #########",
        "#        #                    #",
        "#        #                    #",
        "##############################",
    };

    // Dibujar el laberinto en la escena
    drawLaberinto();
    cellSize = 40; // Tamaño de cada celda del laberinto

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
}

void MainWindow::loadSpritesheet()
{
    // Aquí cargas tu spritesheet
    // spritesheet = QPixmap(":/spritesheet.png");
    // Ajusta el ancho y alto del sprite según sea necesario
    // spriteWidth = ...;
    // spriteHeight = ...;
}

void MainWindow::createPacman()
{
    // Aquí creas el pixmap del pacman y lo agregas a la escena
    QRect pacmanRect(0, 0, spriteWidth, spriteHeight);
    QPixmap pacmanSprite = spritesheet.copy(pacmanRect);
    QGraphicsPixmapItem *pacmanItem = scene->addPixmap(pacmanSprite);
    scene->addItem(pacmanItem); // Se agrega a la escena

    // Posicionar el Pacman en el centro de la primera celda del laberinto
    pacmanPos = QPointF(cellSize / 2.0, cellSize / 2.0);
    pacmanItem->setPos(pacmanPos);
}

/*void MainWindow::drawLaberinto()
{
    const int numRows = 20; // Número de filas en la cuadrícula
    const int numCols = 30; // Número de columnas en la cuadrícula

    // Calcular el tamaño de cada celda en función del tamaño del QGraphicsView
    int cellWidth = view->width() / numCols;
    int cellHeight = view->height() / numRows;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            // Calcular las coordenadas de la esquina superior izquierda de la celda
            int x = col * cellWidth;
            int y = row * cellHeight;

            // Dibujar las líneas verticales y horizontales para formar las paredes del laberinto
            if (laberinto[row][col] == '#') {
                // Dibujar la línea superior de la celda
                scene->addLine(x, y, x + cellWidth, y, QPen(Qt::black));
                // Dibujar la línea inferior de la celda
                scene->addLine(x, y + cellHeight, x + cellWidth, y + cellHeight, QPen(Qt::black));
                // Dibujar la línea izquierda de la celda
                scene->addLine(x, y, x, y + cellHeight, QPen(Qt::black));
                // Dibujar la línea derecha de la celda
                scene->addLine(x + cellWidth, y, x + cellWidth, y + cellHeight, QPen(Qt::black));
            }
        }
    }
}*/
/*void MainWindow::drawLaberinto()
{
    const int numRows = 50; // Número de filas en el laberinto
    const int numCols = 70; // Número de columnas en el laberinto

    // Calcular el tamaño de cada celda en función del tamaño de la ventana
    int cellWidth = view->width() / numCols;
    int cellHeight = view->height() / numRows;

    // Ajustar el tamaño de las celdas para que sean más grandes
    cellWidth *= 2;
    cellHeight *= 2;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            // Calcular las coordenadas de la esquina superior izquierda de la celda
            int x = col * cellWidth;
            int y = row * cellHeight;

            // Dibujar las líneas verticales y horizontales para formar las paredes del laberinto
            if (laberinto[row][col] == '#') {
                // Dibujar la línea superior de la celda
                scene->addLine(x, y, x + cellWidth, y, QPen(Qt::black, 3)); // Ajustar el grosor de la línea según sea necesario
                // Dibujar la línea inferior de la celda
                scene->addLine(x, y + cellHeight, x + cellWidth, y + cellHeight, QPen(Qt::black, 3)); // Ajustar el grosor de la línea según sea necesario
                // Dibujar la línea izquierda de la celda
                scene->addLine(x, y, x, y + cellHeight, QPen(Qt::black, 3)); // Ajustar el grosor de la línea según sea necesario
                // Dibujar la línea derecha de la celda
                scene->addLine(x + cellWidth, y, x + cellWidth, y + cellHeight, QPen(Qt::black, 3)); // Ajustar el grosor de la línea según sea necesario
            }
        }
    }
}




void MainWindow::movePacman(Direction direction)
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
        QGraphicsItem *pacmanItem = scene->items().first();
        pacmanItem->setPos(newPos);
        pacmanPos = newPos;
    }
}

bool MainWindow::checkCollision(const QPointF &newPos)
{
    // Verificar si la nueva posición colisiona con las paredes del laberinto
    // Por simplicidad, asumimos que las paredes son los caracteres '#'
    int row = newPos.y() / cellSize;
    int col = newPos.x() / cellSize;
    if (row < 0 || row >= laberinto.size() || col < 0 || col >= laberinto[0].size())
        return true; // Fuera de los límites del laberinto
    return laberinto[row][col] == '#';
}
*/
/*#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    spriteWidth(32), // Ajusta el ancho del sprite según sea necesario
    spriteHeight(32), // Ajusta el alto del sprite según sea necesario
    cellSize(40) // Tamaño de cada celda del laberinto
{
    ui->setupUi(this);

    // Crear la escena y el QGraphicsView
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Inicializar el laberinto como un laberinto simple de 20x30
    laberinto = {
        "##################",
        "#        #       #",
        "#  ###   #  ## ###",
        "#        #       #",
        "#   ##   ##### ###",
        "#           #  # #",
        "#########   #    #",
        "#             # ##",
        "#  ##    ###     #",
        "##   ##    # #  ##",
        "######  #### ## ##",
        "#            #   #",
        "# ## ##  ### #####",
        "##################",

    };

    // Dibujar el laberinto en la escena
    drawLaberinto();

    // Crear el Pacman
    createPacman();
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
}

void MainWindow::loadSpritesheet()
{
    // Aquí puedes cargar tu spritesheet desde un archivo y ajustar el ancho y alto del sprite
    // spritesheet = QPixmap(":/spritesheet.png");
    // spriteWidth = ...;
    // spriteHeight = ...;
}

void MainWindow::createPacman()
{
    // Aquí creas el pixmap del pacman y lo agregas a la escena
    QPixmap pacmanSprite(":/pacman.png"); // Suponiendo que pacman.png está en el directorio de recursos
    QGraphicsPixmapItem *pacmanItem = scene->addPixmap(pacmanSprite);
    scene->addItem(pacmanItem); // Se agrega a la escena

    // Posicionar el Pacman en el centro de la primera celda del laberinto
    pacmanPos = QPointF(cellSize / 2.0, cellSize / 2.0);
    pacmanItem->setPos(pacmanPos);
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
        }
    }
}

//void MainWindow::movePacman(Direction direction)
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
        QGraphicsItem *pacmanItem = scene->items().first();
        pacmanItem->setPos(newPos);
        pacmanPos = newPos;
    }
}

bool MainWindow::checkCollision(const QPointF &newPos)
{
    // Verificar si la nueva posición colisiona con las paredes del laberinto
    // Por simplicidad, asumimos que las paredes son los caracteres '#'
    int row = newPos.y() / cellSize;
    int col = newPos.x() / cellSize;
    if (row < 0 || row >= laberinto.size() || col < 0 || col >= laberinto[0].size())
        return true; // Fuera de los límites del laberinto
    return laberinto[row][col] == '#';
}
*/
/*#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    spriteWidth(32), // Ajusta el ancho del sprite según sea necesario
    spriteHeight(32), // Ajusta el alto del sprite según sea necesario
    cellSize(40) // Tamaño de cada celda del laberinto
{
    ui->setupUi(this);

    // Crear la escena y el QGraphicsView
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Inicializar el laberinto como un laberinto simple de 20x30
    laberinto = {
        "##################",
        "#        #       #",
        "#  ###   #  ## ###",
        "#        #       #",
        "#   ##   ##### ###",
        "#           #  # #",
        "#########   #    #",
        "#             # ##",
        "#  ##    ###     #",
        "##   ##    # #  ##",
        "######  #### ## ##",
        "#            #   #",
        "# ## ##  ### #####",
        "##################",
    };

    // Dibujar el laberinto en la escena
    drawLaberinto();

    // Crear el Pacman
    pacman = new Pacman(spriteWidth, spriteHeight, cellSize, this); // Crear una instancia de Pacman
    scene->addItem(pacman); // Agregar Pacman a la escena
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        pacman->move(Direction::Left); // Mover Pacman a la izquierda
        break;
    case Qt::Key_Right:
        pacman->move(Direction::Right); // Mover Pacman a la derecha
        break;
    case Qt::Key_Up:
        pacman->move(Direction::Up); // Mover Pacman hacia arriba
        break;
    case Qt::Key_Down:
        pacman->move(Direction::Down); // Mover Pacman hacia abajo
        break;
    default:
        QMainWindow::keyPressEvent(event);
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
        }
    }
}

bool MainWindow::checkCollision(const QPointF &newPos)
{
    // Verificar si la nueva posición colisiona con las paredes del laberinto
    // Por simplicidad, asumimos que las paredes son los caracteres '#'
    int row = newPos.y() / cellSize;
    int col = newPos.x() / cellSize;
    if (row < 0 || row >= laberinto.size() || col < 0 || col >= laberinto[0].size())
        return true; // Fuera de los límites del laberinto
    return laberinto[row][col] == '#';
}*/
/*#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    spriteWidth(32), // Ancho del sprite
    spriteHeight(32), // Alto del sprite
    cellSize(40) // Tamaño de cada celda del laberinto
{
    ui->setupUi(this);

    // Crear la escena y el QGraphicsView
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Inicializar el laberinto como un laberinto simple de 20x30
    laberinto = {
        "##################",
        "#        #       #",
        "#  ###   #  ## ###",
        "#        #       #",
        "#   ##   ##### ###",
        "#           #  # #",
        "#########   #    #",
        "#             # ##",
        "#  ##    ###     #",
        "##   ##    # #  ##",
        "######  #### ## ##",
        "#            #   #",
        "# ## ##  ### #####",
        "##################",

    };

    // Dibujar el laberinto en la escena
    drawLaberinto();

    // Cargar el spritesheet y ajustar el ancho y alto del sprite
    loadSpritesheet();

    // Crear el Pacman
    createPacman();
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
}

/*void MainWindow::loadSpritesheet()
{
    // Cargar el spritesheet desde un archivo
    spritesheet = QPixmap(":/spritesheet.png");

    // Ajustar el ancho y alto del sprite según sea necesario
    spriteWidth = 620;
    spriteHeight = 620;
}*/
/*void MainWindow::loadSpritesheet()
{
    QPixmap spritesheet(":/spritesheet.png"); // Carga el spritesheet
    int numColumns = 4; // Número de columnas en el spritesheet
    int numRows = 3; // Número de filas en el spritesheet
    int spriteWidth = spritesheet.width() / numColumns; // Ancho de cada sprite
    int spriteHeight = spritesheet.height() / numRows; // Alto de cada sprite

    // Recorre cada fila y columna del spritesheet
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numColumns; ++col) {
            // Calcula la región del spritesheet para copiar
            QRect spriteRect(col * spriteWidth, row * spriteHeight, spriteWidth, spriteHeight);
            // Copia la región del spritesheet como una nueva imagen
            QPixmap sprite = spritesheet.copy(spriteRect);
            // Crea un QGraphicsPixmapItem para mostrar la imagen en la escena
            QGraphicsPixmapItem *spriteItem = scene->addPixmap(sprite);
            // Establece la posición del sprite en la escena
            spriteItem->setPos(col * spriteWidth, row * spriteHeight);
            // Establece la escala del sprite para ajustar su tamaño si es necesario
            spriteItem->setScale(0.5); // Ajusta según lo necesites
        }
    }
}


void MainWindow::createPacman()
{
    // Crear el pixmap del Pacman y establecer la porción del spritesheet que corresponde al Pacman
    QPixmap pacmanSprite = spritesheet.copy(0, 0, spriteWidth, spriteHeight);
    QGraphicsPixmapItem *pacmanItem = scene->addPixmap(pacmanSprite);
    scene->addItem(pacmanItem);

    // Posicionar el Pacman en el centro de la primera celda del laberinto
    pacmanPos = QPointF(cellSize / 2.0, cellSize / 2.0);
    pacmanItem->setPos(pacmanPos);
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
        }
    }
}

void MainWindow::movePacman(Direction direction)
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
        QGraphicsItem *pacmanItem = scene->items().first();
        pacmanItem->setPos(newPos);
        pacmanPos = newPos;
    }
}

bool MainWindow::checkCollision(const QPointF &newPos)
{
    // Verificar si la nueva posición colisiona con las paredes del laberinto
    // Por simplicidad, asumimos que las paredes son los caracteres '#'
    int row = newPos.y() / cellSize;
    int col = newPos.x() / cellSize;
    if (row < 0 || row >= laberinto.size() || col < 0 || col >= laberinto[0].size())
        return true; // Fuera de los límites del laberinto
    return laberinto[row][col] == '#';
}*/
/*#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    spriteWidth(05), // Ajusta el ancho del sprite según sea necesario
    spriteHeight(05), // Ajusta el alto del sprite según sea necesario
    cellSize(40) // Tamaño de cada celda del laberinto
{
    ui->setupUi(this);

    // Inicializar la escena y la vista
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Inicializar el laberinto como un laberinto simple de 20x30
    laberinto = {
        "##################",
        "#        #       #",
        "#  ###   #  ## ###",
        "#        #       #",
        "#   ##   ##### ###",
        "#           #  # #",
        "#########   #    #",
        "#             # ##",
        "#  ##    ###     #",
        "##   ##    # #  ##",
        "######  #### ## ##",
        "#            #   #",
        "# ## ##  ### #####",
        "##################",
    };

    // Dibujar el laberinto en la escena
    drawLaberinto();

    // Cargar y recortar el spritesheet
    QPixmap spritesheet(":/spritesheet.png");
    QList<QPixmap> sprites = recortarSpritesheet(spritesheet);

    // Colocar las imágenes en el laberinto
    colocarImagen(sprites[0], 10, 5); // fruta
    colocarImagen(sprites[1], 2, 3); // fruta
    colocarImagen(sprites[2], 5, 11); // fruta
    colocarImagen(sprites[3], 11, 16); //fruta
    colocarImagen(sprites[4], 1, 13); //llave
    colocarImagen(sprites[5], 12, 2); // Fantasma 5
    colocarImagen(sprites[6], 7, 7); // Fantasma 6
    colocarImagen(sprites[7], 1, 5); //pacman
    colocarImagen(sprites[8], 4, 1); // fantasma
    colocarImagen(sprites[9], 4, 15); // fantasma
    //colocarImagen(sprites[10], 7, 16); // fantasma
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
}

void MainWindow::movePacman(Direction direction)
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
        QGraphicsItem *pacmanItem = scene->items().first();
        pacmanItem->setPos(newPos);
        pacmanPos = newPos;
    }
}

void MainWindow::loadSpritesheet()
{
    // Aquí puedes cargar tu spritesheet desde un archivo y ajustar el ancho y alto del sprite
    // spritesheet = QPixmap(":/spritesheet.png");
    // spriteWidth = ...;
    // spriteHeight = ...;
}

void MainWindow::createPacman()
{
    // Aquí creas el pixmap del pacman y lo agregas a la escena
    QPixmap pacmanSprite(":/pacman.png"); // Suponiendo que pacman.png está en el directorio de recursos
    QGraphicsPixmapItem *pacmanItem = scene->addPixmap(pacmanSprite);
    scene->addItem(pacmanItem); // Se agrega a la escena

    // Posicionar el Pacman en el centro de la primera celda del laberinto
    pacmanPos = QPointF(cellSize / 2.0, cellSize / 2.0);
    pacmanItem->setPos(pacmanPos);
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
        }
    }
}

void MainWindow::colocarImagen(const QPixmap &imagen, int fila, int columna)
{
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(imagen);
    item->setPos(columna * cellSize, fila * cellSize);
    scene->addItem(item);
}

QList<QPixmap> MainWindow::recortarSpritesheet(const QPixmap &spritesheet)
{
    QList<QPixmap> sprites;
    int numRows = 3;
    int numCols = 4;
    int spriteWidth = spritesheet.width() / numCols;
    int spriteHeight = spritesheet.height() / numRows;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            QPixmap sprite = spritesheet.copy(col * spriteWidth, row * spriteHeight, spriteWidth, spriteHeight);
            sprites.append(sprite);
        }
    }
    return sprites;
}

bool MainWindow::checkCollision(const QPointF &newPos)
{
    // Verificar si la nueva posición colisiona con las paredes del laberinto
    // Por simplicidad, asumimos que las paredes son los caracteres '#'
    int row = newPos.y() / cellSize;
    int col = newPos.x() / cellSize;
    if (row < 0 || row >= laberinto.size() || col < 0 || col >= laberinto[0].size())
        return true; // Fuera de los límites del laberinto
    return laberinto[row][col] == '#';
}*/

// En mainwindow.cpp

/*#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    spriteWidth(32), // Ajusta el ancho del sprite según sea necesario
    spriteHeight(32), // Ajusta el alto del sprite según sea necesario
    cellSize(40) // Tamaño de cada celda del laberinto
{
    ui->setupUi(this);

    // Inicializar la escena y la vista
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Inicializar el laberinto como un laberinto simple de 20x30
    laberinto = {
        "##################",
        "#        #       #",
        "#  ###   #  ## ###",
        "#        #       #",
        "#   ##   ##### ###",
        "#           #  # #",
        "#########   #    #",
        "#             # ##",
        "#  ##    ###     #",
        "##   ##    # #  ##",
        "######  #### ## ##",
        "#            #   #",
        "# ## ##  ### #####",
        "##################",
    };

    // Dibujar el laberinto en la escena
    drawLaberinto();

    // Cargar y recortar el spritesheet
    QPixmap spritesheet(":/spritesheet.png");
    QList<QPixmap> sprites = recortarSpritesheet(spritesheet, spriteWidth, spriteHeight);

    // Colocar las imágenes en el laberinto
    colocarImagen(sprites[0], 10, 6); // fruta
    colocarImagen(sprites[1], 2, 2); // fruta
    colocarImagen(sprites[2], 5, 11); // fruta
    colocarImagen(sprites[3], 11, 16); //fruta
    colocarImagen(sprites[4], 1, 13); //llave
    colocarImagen(sprites[5], 12, 2); // Fantasma1
    colocarImagen(sprites[6], 7, 7); // Fantasma2
    colocarImagen(sprites[7], 1, 5); //pacman
    colocarImagen(sprites[8], 4, 1); // fantasm3
    colocarImagen(sprites[9], 4, 15); // fantasma4
    //colocarImagen(sprites[10], 7, 16); // fantasma
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
}

void MainWindow::movePacman(Direction direction)
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
        QGraphicsItem *pacmanItem = scene->items().first();
        pacmanItem->setPos(newPos);
        pacmanPos = newPos;
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
        }
    }
}

void MainWindow::colocarImagen(const QPixmap &imagen, int fila, int columna)
{
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(imagen);
    item->setPos(columna * cellSize, fila * cellSize);
    scene->addItem(item);
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

bool MainWindow::checkCollision(const QPointF &newPos)
{
    // Verificar si la nueva posición colisiona con las paredes del laberinto
    // Por simplicidad, asumimos que las paredes son los caracteres '#'
    int row = newPos.y() / cellSize;
    int col = newPos.x() / cellSize;
    if (row < 0 || row >= laberinto.size() || col < 0 || col >= laberinto[0].size())
        return true; // Fuera de los límites del laberinto
    return laberinto[row][col] == '#';
}*/

/*#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QDebug>
#include <QKeyEvent>
#include "fantasma.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    spriteWidth(32), // Ajusta el ancho del sprite según sea necesario
    spriteHeight(32), // Ajusta el alto del sprite según sea necesario
    cellSize(40) // Tamaño de cada celda del laberinto
{
    ui->setupUi(this);

    // Inicializar la escena y la vista
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Inicializar el laberinto como un laberinto simple de 20x30
    laberinto = {
        "##################",
        "#        #       #",
        "#  ###   #  ## ###",
        "#        #       #",
        "#   ##   ##### ###",
        "#           #  # #",
        "#########   #    #",
        "#             # ##",
        "#  ##    ###     #",
        "##   ##    # #  ##",
        "######  #### ## ##",
        "#            #   #",
        "# ## ##  ### #####",
        "##################",
    };



    // Cargar y recortar el spritesheet
    QPixmap spritesheet(":/spritesheet.png");
    QList<QPixmap> sprites = recortarSpritesheet(spritesheet, spriteWidth, spriteHeight);

    // Colocar las imágenes en el laberinto
    colocarImagen(sprites[0], 10, 5); // fruta
    colocarImagen(sprites[1], 2, 3); // fruta
    colocarImagen(sprites[2], 5, 11); // fruta
    colocarImagen(sprites[3], 11, 16); //fruta
    colocarImagen(sprites[4], 1, 13); //llave

    // Crear y agregar los fantasmas a la escena
    Fantasma *fantasma1 = new Fantasma(spriteWidth, spriteHeight, cellSize, scene);
    scene->addItem(fantasma1);

    Fantasma *fantasma2 = new Fantasma(spriteWidth, spriteHeight, cellSize, scene);
    scene->addItem(fantasma2);

    colocarImagen(sprites[5], 12, 2); // Fantasma 5
    colocarImagen(sprites[6], 7, 7); // Fantasma 6
    colocarImagen(sprites[7], 1, 5); //pacman
    colocarImagen(sprites[8], 4, 1); // fantasma
    colocarImagen(sprites[9], 4, 15); // fantasma
    colocarImagen(sprites[10], 7, 16); // fantasma
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
    // Lógica para mover al jugador
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
        }
    }
}*/

/*#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fantasma.h"
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QDebug>
#include <QKeyEvent>

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
        "#        #       #",
        "#  ###   #  ## ###",
        "#        #       #",
        "#   ##   ##### ###",
        "#           #  # #",
        "#########   #    #",
        "#             # ##",
        "#  ##    ###     #",
        "##   ##    # #  ##",
        "######  #### ## ##",
        "#            #   #",
        "# ## ##  ### #####",
        "##################",
    };

    // Dibujar el laberinto en la escena
    drawLaberinto();

    // Cargar y recortar el spritesheet
    QPixmap spritesheet(":/spritesheet.png");
    QList<QPixmap> sprites = recortarSpritesheet(spritesheet, spriteWidth, spriteHeight);

    // Colocar las imágenes en el laberinto
    colocarImagen(sprites[0], 10, 5); // fruta
    colocarImagen(sprites[1], 2, 3); // fruta
    colocarImagen(sprites[2], 5, 11); // fruta
    colocarImagen(sprites[3], 11, 16); //fruta
    colocarImagen(sprites[4], 1, 13); //llave

    // Crear y agregar los fantasmas a la escena
    Fantasma *fantasma1 = new Fantasma(spriteWidth, spriteHeight, cellSize, scene);
    scene->addItem(fantasma1);

    Fantasma *fantasma2 = new Fantasma(spriteWidth, spriteHeight, cellSize, scene);
    scene->addItem(fantasma2);

    colocarImagen(sprites[5], 12, 2); // Fantasma 5
    colocarImagen(sprites[6], 7, 7); // Fantasma 6
    colocarImagen(sprites[7], 1, 5); //pacman
    colocarImagen(sprites[8], 4, 1); // fantasma
    colocarImagen(sprites[9], 4, 15); // fantasma
    colocarImagen(sprites[10], 7, 16); // fantasma
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
    // Lógica para mover al jugador
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
        }
    }
}

void MainWindow::colocarImagen(const QPixmap &imagen, int fila, int columna)
{
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(imagen);
    item->setPos(columna * cellSize, fila * cellSize);
    scene->addItem(item);
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
}*/

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
        "#        #       #",
        "#  ###   #  ## ###",
        "#        #       #",
        "#   ##   ##### ###",
        "#           #  # #",
        "#########   #    #",
        "#             # ##",
        "#  ##    ###     #",
        "##   ##    # #  ##",
        "######  #### ## ##",
        "#            #   #",
        "# ## ##  ### #####",
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

/*void MainWindow::movePacman(Direction direction)
{
    // Obtener la posición actual de Pacman
    int row = 0, col = 0;
    for (row = 0; row < laberinto.size(); ++row) {
        col = QString::fromStdString(laberinto[row]).indexOf('P');
        if (col != -1) break;
    }

    // Actualizar la posición según la dirección
    switch (direction) {
    case Direction::Left:
        if (col > 0 && laberinto[row][col - 1] != '#') {
            laberinto[row][col] = ' ';
            laberinto[row][col - 1] = 'P';
        }
        break;
    case Direction::Right:
        if (col < laberinto[row].size() - 1 && laberinto[row][col + 1] != '#') {
            laberinto[row][col] = ' ';
            laberinto[row][col + 1] = 'P';
        }
        break;
    case Direction::Up:
        if (row > 0 && laberinto[row - 1][col] != '#') {
            laberinto[row][col] = ' ';
            laberinto[row - 1][col] = 'P';
        }
        break;
    case Direction::Down:
        if (row < laberinto.size() - 1 && laberinto[row + 1][col] != '#') {
            laberinto[row][col] = ' ';
            laberinto[row + 1][col] = 'P';
        }
        break;
    }

    // Actualizar la posición de Pacman en la escena
    QGraphicsItem *pacman = scene->items().at(0); // Suponiendo que Pacman es el primer elemento en la escena
    int newX = pacman->x() + (direction == Direction::Right) - (direction == Direction::Left);
    int newY = pacman->y() + (direction == Direction::Down) - (direction == Direction::Up);
    pacman->setPos(newX, newY);
}*/

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
    QGraphicsItem *pacman = scene->items().at(12);
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
        }
    }
}

void MainWindow::colocarImagen(const QPixmap &imagen, int fila, int columna)
{
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(imagen);
    item->setPos(columna * cellSize, fila * cellSize);
    scene->addItem(item);
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



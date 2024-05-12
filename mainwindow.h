/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class Direction { Up, Down, Left, Right };

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPixmap spritesheet;
    int spriteWidth;
    int spriteHeight;
    QPointF pacmanPos;
    int cellSize; // Tamaño de cada celda del laberinto
    //std::vector<std::vector<char>> laberinto; // Variable para almacenar el laberinto
    std::vector<std::string> laberinto;

    void loadSpritesheet();
    void createPacman();
    void drawLaberinto();
    void movePacman(Direction direction);
    bool checkCollision(const QPointF &newPos);
};

#endif // MAINWINDOW_H*/

/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <vector>
#include <string>
#include "pacman.h" // Incluir el archivo de encabezado de Pacman

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPixmap spritesheet;
    int spriteWidth;
    int spriteHeight;
    int cellSize; // Tamaño de cada celda del laberinto
    std::vector<std::string> laberinto;
    Pacman *pacman; // Instancia de Pacman

    void loadSpritesheet();
    void drawLaberinto();
    bool checkCollision(const QPointF &newPos);
};

#endif // MAINWINDOW_H*/

/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class Direction { Up, Down, Left, Right };

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPixmap spritesheet;
    int spriteWidth;
    int spriteHeight;
    QPointF pacmanPos; // Variable para almacenar la posición del Pacman
    int cellSize; // Tamaño de cada celda del laberinto
    std::vector<std::string> laberinto;

    void loadSpritesheet();
    void createPacman();
    void drawLaberinto();
    void movePacman(Direction direction);
    bool checkCollision(const QPointF &newPos);
};

#endif // MAINWINDOW_H*/

/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class Direction { Up, Down, Left, Right };

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPixmap spritesheet;
    int spriteWidth;
    int spriteHeight;
    QPointF pacmanPos;
    int cellSize; // Tamaño de cada celda del laberinto
    //std::vector<std::vector<char>> laberinto; // Variable para almacenar el laberinto
    std::vector<std::string> laberinto;

    void loadSpritesheet();
    void createPacman();
    void drawLaberinto();
    void movePacman(Direction direction);
    bool checkCollision(const QPointF &newPos);
    QList<QPixmap> recortarSpritesheet(const QPixmap &spritesheet);
    void colocarImagen(const QPixmap &imagen, int fila, int columna);
};

#endif // MAINWINDOW_H*/

/*// En mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QList>
#include "direction.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//enum class Direction { Up, Down, Left, Right };

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPixmap spritesheet;
    int spriteWidth;
    int spriteHeight;
    QPointF pacmanPos;
    int cellSize; // Tamaño de cada celda del laberinto
    //std::vector<std::vector<char>> laberinto; // Variable para almacenar el laberinto
    std::vector<std::string> laberinto;

    void loadSpritesheet();
    void createPacman();
    void drawLaberinto();
    void movePacman(Direction direction);
    bool checkCollision(const QPointF &newPos);
    QList<QPixmap> recortarSpritesheet(const QPixmap &spritesheet, int newWidth, int newHeight); // Mover la definición aquí
    void colocarImagen(const QPixmap &imagen, int fila, int columna);
};

#endif // MAINWINDOW_H*/

/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QList>
#include "direction.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPixmap spritesheet;
    int spriteWidth;
    int spriteHeight;
    QPointF pacmanPos;
    int cellSize;
    std::vector<std::string> laberinto;

    void loadSpritesheet();
    void createPacman();
    void drawLaberinto();
    void movePacman(Direction direction);
    bool checkCollision(const QPointF &newPos);
    QList<QPixmap> recortarSpritesheet(const QPixmap &spritesheet, int newWidth, int newHeight);
    void colocarImagen(const QPixmap &imagen, int fila, int columna);
};

#endif // MAINWINDOW_H*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QList>
#include <QTimer>
#include "direction.h"
#include "fantasma.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPixmap spritesheet;
    int spriteWidth;
    int spriteHeight;
    int cellSize;
    std::vector<std::string> laberinto;
    QTimer *fantasmaTimer;

    void drawLaberinto();
    void movePacman(Direction direction);
    void colocarImagen(const QPixmap &imagen, int fila, int columna);
    QList<QPixmap> recortarSpritesheet(const QPixmap &spritesheet, int newWidth, int newHeight);
QList<QPixmap> sprites; // Variable para almacenar los sprites recortados
private slots:
    void moveFantasma(Fantasma *fantasma);
};

#endif // MAINWINDOW_H





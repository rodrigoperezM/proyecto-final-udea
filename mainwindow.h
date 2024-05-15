
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

    void on_start_clicked();

private:
    QList<QGraphicsPixmapItem*> spritesItems;
};

#endif // MAINWINDOW_H






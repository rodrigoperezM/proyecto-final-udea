#include "StartScreen.h"

StartScreen::StartScreen(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    titleLabel = new QLabel("Pac-Man", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Arial", 50));

    startButton = new QPushButton("Start Game", this);
    startButton->setFont(QFont("Arial", 20));

    layout->addWidget(titleLabel);
    layout->addWidget(startButton);

    connect(startButton, &QPushButton::clicked, this, &StartScreen::onStartButtonClicked);
    // Establecer un tamaño fijo más pequeño para la pantalla de inicio
    setFixedSize(1000, 500); // Cambiar el tamaño según sea necesario
}

void StartScreen::onStartButtonClicked()
{
    emit startGame();
}

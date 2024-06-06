#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class StartScreen : public QWidget
{
    Q_OBJECT
public:
    explicit StartScreen(QWidget *parent = nullptr);

signals:
    void startGame();

private slots:
    void onStartButtonClicked();

private:
    QVBoxLayout *layout;
    QLabel *titleLabel;
    QPushButton *startButton;
};

#endif // STARTSCREEN_H

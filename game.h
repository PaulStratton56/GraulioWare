#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QStackedWidget>
#include <QRandomGenerator>
#include <QLineEdit>
#include <QVBoxLayout>
#include "arrowkeys.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class Game;
}
QT_END_NAMESPACE

class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();
private slots:
    void on_QuitButton_clicked();
    void on_StartButton_clicked();
    void on_again_clicked();
    void on_retry_clicked();
    void on_giveup_clicked();

    void widgetChanged(int index);
    void startMinigame();
    void loseMinigame();
    void globalTimeout();

    void startGame_Typing();
    void startGame_Avoid();
    void startGame_Arrows();

    QString getLetters(int length);
    void handleArrows();
    // void touched();
    void on_lineEdit_textChanged(const QString &arg1);

private:
    QTimer* globalTimer;
    bool toGame;
    Ui::Game *ui;
    int score;
    int lives;
    int minigameTime;
    // QLabel *liva;
    // QLabel *scora;
    // QLabel *lultext;
    // QLineEdit *shower;
    QOpenGLWidget *avoidGameDisplay;
    QVBoxLayout* avoidGame;
    ArrowKeys *arrowKeysWidget;
    QVBoxLayout* arrowGame;

};

#endif // GAME_H

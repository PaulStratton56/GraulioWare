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
    void timeoutCallback();

    void on_again_clicked();
    void navi(int index);
    void goNext();
    void reg();

    void on_retry_clicked();

    void on_giveup_clicked();
    QString generateRandomLetters(int length);

    void on_lineEdit_textChanged(const QString &arg1);
    //void touched() const;
private:
    QTimer* timer;
    bool vis;
    Ui::Game *ui;
    int score;
    int lives;
    QLabel *liva;
    QLabel *scora;
    QString word;
    QLabel *lultext;
    QLineEdit *shower;
    int old;
    QOpenGLWidget *opG;

};

#endif // GAME_H

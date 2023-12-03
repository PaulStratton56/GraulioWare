#include "game.h"
#include "ui_game.h"
#include "gameVars.h"
#include <QTimer>
#include <qdebug.h>
#include <cctype>
#include <QPoint>
#include <random>
#include <Qstring>
#include "openglwidget.h"
#include <QVBoxLayout>

// ========== CONSTRUCTOR/DESTRUCTOR ==========

Game::Game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    this->setFixedSize(1280, 720);

    globalTimer = new QTimer(this);

    avoidGameDisplay = new OpenGLWidget(this);
    avoidGameDisplay->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    avoidGameDisplay->setFixedSize(600, 400);

    avoidGame = new QVBoxLayout(ui->stackedWidget->widget(AVOIDANCE));
    avoidGame->addWidget(avoidGameDisplay, 0, Qt::AlignCenter);

    connect(avoidGameDisplay, &OpenGLWidget::squaresOverlapping, this, &Game::touched);
    connect(globalTimer, &QTimer::timeout, this, &Game::globalTimeout);
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, &Game::widgetChanged);
}


Game::~Game()
{
    delete globalTimer;
    delete ui;
    delete avoidGameDisplay;
    delete avoidGame;
}

// ========== GAME FLOW FUNCTIONS ==========

void Game::widgetChanged(int index){
    switch(index)
    {
    case(HUB):
        globalTimer->start(2*1000);
        ui->Lives->setText(QString("Lives: %1").arg(lives));
        ui->Score->setText(QString("Score: %1").arg(score));
        break;
    case(TYPING):
        startGame_Typing();
        break;
    case(ARROWS):
        startGame_Arrows();
        break;
    case(AVOIDANCE):
        startGame_Avoid();
        break;
    }
}

void Game::startMinigame(){
    toGame = false;
    // int minigame = (rand()%3) + 2;
    int minigame = TYPING;
    ui->stackedWidget->setCurrentIndex(minigame);
    qDebug() <<"timer started";
    globalTimer->start(minigameTime*1000);
}

void Game::loseMinigame(){
    toGame = true;
    lives -= 1;

    if(lives > 0) ui->stackedWidget->setCurrentIndex(HUB);
    else ui->stackedWidget->setCurrentIndex(LOSS);
}

void Game::winMinigame(){
    toGame = true;
    score += 100;

    if(score < 1000) ui->stackedWidget->setCurrentIndex(HUB);
    else ui->stackedWidget->setCurrentIndex(VICTORY);
}

void Game::globalTimeout(){
    qDebug() <<"timer ended";

    if(ui->stackedWidget->currentIndex() == AVOIDANCE) avoidGameDisplay->clearFocus();

    if(toGame) startMinigame();
    else loseMinigame();
}

// ========== MINIGAME START FUNCTIONS ==========

void Game::startGame_Typing()
{
    keyNumber = 0;
    QString letters(getLetters(LETTER_NUMBER));
    for(int i = 0; i < LETTER_NUMBER; i++)
    {
        if(rand()%2)
        {
            CapitalKey* newKey = new CapitalKey(this, ui->KeyLayout, letters[i].toLatin1());
            keys[i] = static_cast<Key*>(newKey);
        }
        else
        {
            LowerKey* newKey = new LowerKey(this, ui->KeyLayout, letters[i].toLatin1());
            keys[i] = static_cast<Key*>(newKey);
        }
    }
}

void Game::startGame_Avoid()
{
    avoidGameDisplay->setFocus();
}

void Game::startGame_Arrows()
{

}

// ========== HELPER FUNCTIONS ==========

QString Game::getLetters(int length)
{
    QString returnString(length,'_');
    for(int i = 0; i < length; i++)
    {
        QChar letter((rand() % (122 - 97 + 1)) + 97);
        returnString[i] = letter;

    }
    return returnString;
}

void Game::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "Key pressed! Key: " << event->text();
    if(ui->stackedWidget->currentIndex() == TYPING)
    {
        qDebug() << "In the Typing minigame.";
        if(dynamic_cast<CapitalKey*>(keys[keyNumber]) != nullptr)
        {
            qDebug() << "The current key is capital!";
            CapitalKey* currentKey = dynamic_cast<CapitalKey*>(keys[keyNumber]);
            qDebug() << "The current key is: " << currentKey->label->text();
            if(currentKey->label->text() == event->text())
            {
                currentKey->pressed();
                qDebug() << "You pressed a capital letter key!";
                keyNumber++;
            }
        }
        else
        {
            qDebug() << "The current key is lowercase!";
            LowerKey* currentKey = dynamic_cast<LowerKey*>(keys[keyNumber]);
            qDebug() << "The current key is: " << currentKey->label->text();
            if(currentKey->label->text() == event->text())
            {
                currentKey->pressed();
                qDebug() << "You pressed a lowercase letter key!";
                keyNumber++;
            }
        }
        if(keyNumber >= LETTER_NUMBER)
        {
            globalTimer->stop();
            winMinigame();
        }
    }
}

void Game::on_lineEdit_textChanged(const QString &arg1)
{

}

void Game::touched()
{

}

// ========== BUTTON FUNCTIONS ==========

void Game::on_QuitButton_clicked()
{
    close();
}

void Game::on_StartButton_clicked()
{
    qDebug() << "Beginning Game!";
    lives = STARTING_LIVES;
    score = 0;
    toGame = true;
    minigameTime = MINIGAME_START_TIME;

    ui->stackedWidget->setCurrentIndex(HUB);
}

void Game::on_again_clicked(){ Game::on_StartButton_clicked(); }
void Game::on_retry_clicked(){ Game::on_StartButton_clicked(); }
void Game::on_giveup_clicked(){ Game::on_QuitButton_clicked(); }

// ========== OTHER FUNCTIONS ==========

// void Game::on_lineEdit_textChanged(const QString &arg1)
// {
//     qDebug() <<arg1 << " "<< word;
//     QString temp1 = arg1;
//     QString temp2 = word;
//     qDebug() <<temp1  << temp2;
//     if(temp1 == temp2){
//         qDebug() << "are same";
//         timer->stop();
//         score += 100;
//         scora->setText("Score: " + QString::number(score));
//         ui->stackedWidget->setCurrentIndex(1);
//     }
// }

//void handleSquaresOverlapping(){

//}

// QString Game::generateRandomLetters(int length) {
//     QString randomString;
//     QRandomGenerator randomGenerator;

//     for (int i = 0; i < length; ++i) {
//         // Generate a random uppercase letter (A-Z) using ASCII values
//         QChar randomLetter = QChar('A' + (rand()%58));
//         randomString.append(randomLetter);
//     }

//     return randomString;
// }


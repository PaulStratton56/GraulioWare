#include "game.h"
#include "ui_game.h"
#include "gameVars.h"
#include <QTimer>
#include <qdebug.h>
#include <QPoint>
#include <QString>
#include "openglwidget.h"
#include <QVBoxLayout>
#include <QPoint>
#include "arrowkeys.h"

// ========== CONSTRUCTOR/DESTRUCTOR ==========

Game::Game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    this->setFixedSize(1167, 647);

    globalTimer = new QTimer(this);
    secondTimer = new QTimer(this);

    avoidGameDisplay = new OpenGLWidget(this);
    avoidGameDisplay->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    avoidGameDisplay->setFixedSize(400, 400);

    avoidGame = new QVBoxLayout(ui->stackedWidget->widget(AVOIDANCE));
    avoidGame->addWidget(avoidGameDisplay, 0, Qt::AlignCenter);

    arrowKeysWidget = new ArrowKeys(this);
    arrowKeysWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    arrowKeysWidget->setFixedSize(400, 400);

    arrowGame = new QVBoxLayout(ui->stackedWidget->widget(ARROWS));
    arrowGame->addWidget(arrowKeysWidget, 0, Qt::AlignCenter);

    connect(arrowKeysWidget, &ArrowKeys::allArrowsInputted, this, &Game::arrowWin);
    connect(arrowKeysWidget, &ArrowKeys::arrowFailure, this, &Game::arrowLoss);
    connect(avoidGameDisplay, &OpenGLWidget::squaresOverlapping, this, &Game::touched);
    connect(globalTimer, &QTimer::timeout, this, &Game::globalTimeout);
    connect(secondTimer, &QTimer::timeout, this, &Game::secondTimeout);
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, &Game::widgetChanged);
}


Game::~Game()
{
    delete globalTimer;
    delete secondTimer;
    delete ui;
    delete avoidGameDisplay;
    delete avoidGame;
    delete arrowKeysWidget;
    delete arrowGame;
}

// ========== GAME FLOW FUNCTIONS ==========

void Game::widgetChanged(int index){
    switch(index)
    {
    case(HUB):
        globalTimer->start(3*1000);
        ui->Lives->setText(QString("Lives\n%1").arg(lives));
        ui->Score->setText(QString("Score\n%1").arg(score));
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
    case(LOSS):
        ui->finalscore->setText(QString("Score\n%1").arg(score));
        if(survival) ui->gameOverTitle->setText(QString("!! OUT OF LIVES !!"));
        globalTimer->stop();
        break;
    case(VICTORY):
        globalTimer->stop();
        break;
    }

}

void Game::startMinigame(){
    toGame = false;
    minigameTime = std::max(4, (int)(MINIGAME_START_TIME - (2*(std::floor(score/DIFFICULTY_INTERVAL)))));
    ui->stackedWidget->setCurrentIndex(minigameNum);

    qDebug() <<"timer started";
    globalTimer->start(minigameTime*1000);

    timeLeft = minigameTime;
    secondTimer->start(1000);
}

void Game::loseMinigame(){//temporarily disabled losing
    toGame = true;
    globalTimer->stop();
    timeLeft = 0;
    secondTimer->stop();
    lives -= 1;
    ui->Result->setText(resultMessages[(rand() % 5) + 5]);
    minigameNum = (rand()%3) + 2;
    ui->NextGame->setText(QString("NEXT: " + printedState[minigameNum-2]));

    if(lives > 0) ui->stackedWidget->setCurrentIndex(HUB);
    else ui->stackedWidget->setCurrentIndex(LOSS);
}

void Game::winMinigame(){
    toGame = true;
    globalTimer->stop();
    timeLeft = 0;
    secondTimer->stop();
    score += POINTS_PER_GAME;
    if(score % DIFFICULTY_INTERVAL == 0 && score <= 20)
    {
        ui->Result->setText(QString("FASTER!!!"));
    }
    else
    {
        ui->Result->setText(resultMessages[(rand() % 5)]);
    }
    minigameNum = (rand()%3) + 2;
    ui->NextGame->setText(QString("NEXT: " + printedState[minigameNum-2]));

    if(score < WIN_SCORE || survival) ui->stackedWidget->setCurrentIndex(HUB);
    else ui->stackedWidget->setCurrentIndex(VICTORY);
}

void Game::globalTimeout(){
    qDebug() << "timer ended";

    if(toGame) startMinigame();
    else
    {
        if(ui->stackedWidget->currentIndex() == TYPING)
        {
            for(int i = keyNumber; i < LETTER_NUMBER; i++)
            {
                qDebug() << "Deleting key " << i;
                if(dynamic_cast<CapitalKey*>(keys[i]) != nullptr)
                {
                    CapitalKey* currentKey = dynamic_cast<CapitalKey*>(keys[i]);
                    currentKey->pressed();
                }
                else
                {
                    LowerKey* currentKey = dynamic_cast<LowerKey*>(keys[i]);
                    currentKey->pressed();
                }
                qDebug() << "Key " << i << " deleted.";
            }
            loseMinigame();
        }
        if(ui->stackedWidget->currentIndex() == AVOIDANCE)
        {
            avoidGameDisplay->moveTimer->stop();
            avoidGameDisplay->clearFocus();
            avoidGameDisplay->reset();
            winMinigame();
        }
        if(ui->stackedWidget->currentIndex() == ARROWS)
        {
            arrowKeysWidget->clearFocus();
            loseMinigame();
        }
    }
}

void Game::secondTimeout(){
    qDebug() << "second Passed!";
    timeLeft--;
    if(timeLeft > 0)
    {
        timerLabel->setText(QString("TIME LEFT: %1").arg(timeLeft));
        secondTimer->start(1000);
    }
    else
    {
        secondTimer->stop();
    }
}

// ========== MINIGAME START FUNCTIONS ==========

void Game::startGame_Typing()
{
    ui->TypingTimeLeft->setText(QString("TIME LEFT: %1").arg(minigameTime));
    ui->KeysRemaining->setText(QString("KEYS REMAINING: %1").arg(LETTER_NUMBER));
    timerLabel = ui->TypingTimeLeft;

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
    ui->AvoidTimer->setText(QString("TIME LEFT: %1").arg(minigameTime));
    timerLabel = ui->AvoidTimer;
    avoidGameDisplay->setFocus();
    avoidGameDisplay->moveTimer->start(5);
}

void Game::startGame_Arrows()
{
    ui->ArrowTimeLeft->setText(QString("TIME LEFT: %1").arg(minigameTime));
    timerLabel = ui->ArrowTimeLeft;
    arrowKeysWidget->start(5);
    arrowKeysWidget->setFocus();
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
            winMinigame();
        }
        else
        {
            ui->KeysRemaining->setText(QString("KEYS REMAINING: %1").arg(10-keyNumber));
        }
    }
}

void Game::touched()
{
    qDebug() << "Touching..";
    avoidGameDisplay->reset();
    avoidGameDisplay->moveTimer->stop();
    loseMinigame();
}

// ========== BUTTON FUNCTIONS ==========

void Game::on_QuitButton_clicked()
{
    close();
}

void Game::on_StartButton_clicked()
{
    qDebug() << "Beginning Game!";
    ui->Result->setText("Minigame incoming!!!");
    minigameNum = (rand()%3) + 2;
    ui->NextGame->setText(QString("NEXT: " + printedState[minigameNum-2]));
    lives = STARTING_LIVES;
    score = 0;
    toGame = true;
    minigameTime = MINIGAME_START_TIME;

    ui->stackedWidget->setCurrentIndex(HUB);
}

void Game::on_SurvivalButton_clicked()
{
    survival = true;
    Game::on_StartButton_clicked();
}

void Game::on_again_clicked(){ ui->stackedWidget->setCurrentIndex(START); }
void Game::on_retry_clicked(){ ui->stackedWidget->setCurrentIndex(START); }
void Game::on_giveup_clicked(){ Game::on_QuitButton_clicked(); }
void Game::on_quitter_clicked(){ Game::on_QuitButton_clicked(); }

// ========== OTHER FUNCTIONS ==========

void Game::arrowWin(){
    qDebug() << "All arrows hit!";
    winMinigame();
}

void Game::arrowLoss(){
    qDebug() << "Missed one...";
    loseMinigame();
}







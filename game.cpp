#include "game.h"
#include "ui_game.h"
#include <QTimer>
#include <qdebug.h>
#include <QPoint>
#include <random>
#include <Qstring>


Game::Game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    this->setFixedSize(1280, 720);
    lives = 0;
    score = 0;
    vis = true;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::reg);
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, &Game::navi);
    QWidget *gameNavig = ui->stackedWidget->widget(1);

    liva = gameNavig->findChild<QLabel*>("Lives");
    scora = gameNavig->findChild<QLabel*>("Score");
}


Game::~Game()
{
    delete timer;
    //delete nTimer;
    delete ui;
}

void Game::navi(int index){
    if(index == 1){
        timer->start(2*1000);
    }
}

void Game::on_QuitButton_clicked()
{
    close();
}
void Game::goNext(){
    vis = false;
    int num = rand()%4;
    if(num == 0){
        ui->stackedWidget->setCurrentIndex(2);
        qDebug() <<"timer started";
        timer->start(5*1000);
    }else   if(num == 1){
        ui->stackedWidget->setCurrentIndex(3);
        timer->start(5*1000);
        qDebug() <<"timer started";
    }else if(num == 2){
        ui->stackedWidget->setCurrentIndex(4);
        timer->start(5*1000);
        qDebug() <<"timer started";
    }else{
        ui->stackedWidget->setCurrentIndex(5);
        timer->start(5*1000);
        qDebug() <<"timer started";
    }
}

void Game::on_StartButton_clicked()
{
    lives = 3;
    score = 0;
    liva->setText("Lives: " + QString::number(lives));
    scora->setText("Score: " + QString::number(score));
    qDebug() << "startbuttopn lciokedasd";
    ui->stackedWidget->setCurrentIndex(1);
}

void Game::reg(){
    if(vis == false){
        timeoutCallback();
    }else{
        goNext();
    }
}
void Game::timeoutCallback(){
    vis = true;
    if(lives > 1){
        ui->stackedWidget->setCurrentIndex(1);
        lives -= 1;

    }else{
        if(score > 1000){
            ui->stackedWidget->setCurrentIndex(7);
        }else{
            ui->stackedWidget->setCurrentIndex(6);

        }
    }

}



void Game::on_again_clicked()
{
    Game::on_StartButton_clicked();
}


void Game::on_retry_clicked()
{
    Game::on_StartButton_clicked();
}


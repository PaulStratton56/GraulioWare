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
    vis = true; //navigation for game nav
    timer = new QTimer(this);
    old = older = 5;
    QString word = generateRandomLetters(5);

    QWidget *gameNavig = ui->stackedWidget->widget(1);
    QWidget *typOr = ui->stackedWidget->widget(2);

    shower = typOr->findChild<QLineEdit*>("lineEdit");
    lultext = typOr->findChild<QLabel*>("texter");
    liva = gameNavig->findChild<QLabel*>("Lives");
    scora = gameNavig->findChild<QLabel*>("Score");

    connect(timer, &QTimer::timeout, this, &Game::reg);
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, &Game::navi);
}


Game::~Game()
{
    delete timer;
    delete ui;
}

void Game::navi(int index){
    if(index == 1){
        timer->start(2*1000);
        qDebug() << "Timer started";
        shower->clear();
    }else if(index == 2){
        QString word = generateRandomLetters(5);
        lultext->setText(word);
    }
}

void Game::on_QuitButton_clicked()
{
    close();
}

void Game::goNext(){
    vis = false;
    int num = rand()%4;
    while(num == old || num == older){
        num = rand()%4;
    }
    if(num == 0){
        ui->stackedWidget->setCurrentIndex(2);
        qDebug() <<"timer started";
        timer->start(5*1000);
    }else if(num == 1){
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
    older = old;
    old = num;

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
    qDebug() <<"timer ended";
    if(vis == false){
        timeoutCallback();
    }else{
        goNext();
    }
}
void Game::timeoutCallback(){
    vis = true;
    if(lives > 1){
        //lives -= 1;
        liva->setText("Lives: " + QString::number(lives));
        ui->stackedWidget->setCurrentIndex(1);

    }else{
        if(score > 1000){
            timer->stop();
            ui->stackedWidget->setCurrentIndex(7);
        }else{
            timer->stop();
            ui->stackedWidget->setCurrentIndex(6);

        }
    }

}

QString Game::generateRandomLetters(int length) {
    QString randomString;
    QRandomGenerator randomGenerator;

    for (int i = 0; i < length; ++i) {
        // Generate a random uppercase letter (A-Z) using ASCII values
        QChar randomLetter = QChar('A' + (rand()%52));
        randomString.append(randomLetter);
    }

    return randomString;
}

void Game::on_again_clicked()
{
    Game::on_StartButton_clicked();
}


void Game::on_retry_clicked()
{
    Game::on_StartButton_clicked();
}


void Game::on_giveup_clicked()
{
    close();
}


void Game::on_lineEdit_textChanged(const QString &arg1)
{
    qDebug() <<arg1 << " "<< word;
    if(&arg1 == word){
        timer->stop();
        score += 100;
        ui->stackedWidget->setCurrentIndex(1);
    }
}


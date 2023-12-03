#include "game.h"
#include "ui_game.h"
#include <QTimer>
#include <qdebug.h>
#include <QPoint>
#include <random>
#include <Qstring>
#include "openglwidget.h"
#include <QVBoxLayout>

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
    old = 5;

    QWidget *gameNavig = ui->stackedWidget->widget(1);
    QWidget *typOr = ui->stackedWidget->widget(2);
    //QWidget *control = ui->stackedWidget->widget(4);

    QVBoxLayout *layout = new QVBoxLayout(ui->stackedWidget->widget(4));
    opG = new OpenGLWidget(this);
    layout->addWidget(opG, 0, Qt::AlignCenter);
    opG->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    opG->setFixedSize(600, 400);

    shower = typOr->findChild<QLineEdit*>("lineEdit");
    lultext = typOr->findChild<QLabel*>("texter");
    liva = gameNavig->findChild<QLabel*>("Lives");
    scora = gameNavig->findChild<QLabel*>("Score");

    //connect(opG, &OpenGLWidget::squaresOverlapping, this, &Game::touched);
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
        word = generateRandomLetters(5);
        lultext->setText(word);
    }else if(index == 4){
        opG->setFocus();
    }
}

void Game::on_QuitButton_clicked()
{
    close();
}

void Game::goNext(){
    vis = false;
    int num = rand()%3;
    while(num == old){
        num = rand()%3;
    }
    old = num;
    num = 2;//bugtesting
    ui->stackedWidget->setCurrentIndex(2+num);
    qDebug() <<"timer started";
    timer->start(20*1000);


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
    opG->clearFocus();
    if(vis == false){
        timeoutCallback();
    }else{
        goNext();
    }
}

//void handleSquaresOverlapping(){

//}
void Game::timeoutCallback(){//temporarily disabled losing
    vis = true;
    if(lives > 1){
        //lives -= 1;
        liva->setText("Lives: " + QString::number(lives));
        ui->stackedWidget->setCurrentIndex(1);

    }else{
        if(score > 1000){
            timer->stop();
            ui->stackedWidget->setCurrentIndex(6);
        }else{
            timer->stop();
            ui->stackedWidget->setCurrentIndex(5);

        }
    }

}

QString Game::generateRandomLetters(int length) {
    QString randomString;
    QRandomGenerator randomGenerator;

    for (int i = 0; i < length; ++i) {
        // Generate a random uppercase letter (A-Z) using ASCII values
        QChar randomLetter = QChar('A' + (rand()%58));
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
    QString temp1 = arg1;
    QString temp2 = word;
    qDebug() <<temp1  << temp2;
    if(temp1 == temp2){
        qDebug() << "are same";
        timer->stop();
        score += 100;
        scora->setText("Score: " + QString::number(score));
        ui->stackedWidget->setCurrentIndex(1);
    }
}


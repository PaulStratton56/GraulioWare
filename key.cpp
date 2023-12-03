#include "key.h"
#include <QDebug>
#include <QFont>

Key::Key(QWidget *parent, char letter) : QOpenGLWidget(parent)
{
    setFixedSize(50,50);
    label = new QLabel(this);
    label->setText(QString(letter));
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label->setGeometry(0,0, 50, 50);

    QFont font;
    font.setPointSize(25);
    font.setBold(true);
    font.setFamily("Comic Sans MS");
    label->setFont(font);


}

void Key::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Key::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

//Let's draw a key!
void Key::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.3f, 0.3f, 0.3f);

    glBegin(GL_QUADS);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();

    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_QUADS);
    glVertex2f(-0.8, 0.8);
    glVertex2f(0.8, 0.8);
    glVertex2f(0.8, -0.8);
    glVertex2f(-0.8, -0.8);
    glEnd();

    glLineWidth(3.0);

    glBegin(GL_LINES);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, -1.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(1.0, 1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();

    glLineWidth(1.0);


}

#include "key.h"
#include <gameVars.h>
#include <QLayout>
#include <QDebug>
#include <QFont>

// Key Definition
Key::Key(QWidget *parent, QLayout* layout, char letter) : QOpenGLWidget(parent)
{
    myLayout = layout;
    myLayout->addWidget(this);
    setFixedSize(KEY_SIZE,KEY_SIZE);
    label = new QLabel(this);
    QPalette labelPalette = label->palette();
    labelPalette.setColor(QPalette::WindowText, QColor(Qt::black));
    label->setPalette(labelPalette);
    label->setText(QString(letter));
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label->setGeometry(0,0, KEY_SIZE, KEY_SIZE);

    QFont font;
    font.setPointSize(KEY_SIZE/2);
    font.setBold(true);
    font.setFamily("Comic Sans MS");
    label->setFont(font);
}

Key::~Key()
{
    delete label;
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

// CapitalKey function implementation
void CapitalKey::pressed()
{
    qDebug() << "Key pressed event";
    myLayout->removeWidget(this);
    qDebug() << "self removed from widget. Deleting self!";
    delete this;
}

void CapitalKey::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.1f, 0.1f, 0.1f);

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

// LowerKey function implementation
void LowerKey::pressed()
{
    qDebug() << "Key pressed event";
    myLayout->removeWidget(this);
    qDebug() << "self removed from widget. Deleting self!";
    delete this;
}

void LowerKey::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.4f, 0.4f, 0.4f);

    glBegin(GL_QUADS);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();

    glColor3f(0.6f, 0.6f, 0.6f);

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







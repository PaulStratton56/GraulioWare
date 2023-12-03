#include "OpenGLWidget.h"
#include <QKeyEvent>
#include <QCoreApplication>

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), x_pos(0.0f), y_pos(0.0f) {
    // Initialize chasing_x and chasing_y at a fixed distance away
    float distance = 1.0f;
    chasing_x = x_pos + distance;
    chasing_y = y_pos + distance;
    // Set up the timer
    moveTimer = new QTimer(this);
    movementSpeed = .1;
    connect(moveTimer, &QTimer::timeout, this, &OpenGLWidget::moveChasingSquare);
    moveTimer->start(500);
}

OpenGLWidget::~OpenGLWidget() {
}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}


void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the first square
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(x_pos, y_pos);
    glVertex2f(x_pos + 0.1, y_pos);
    glVertex2f(x_pos + 0.1, y_pos + 0.1);
    glVertex2f(x_pos, y_pos + 0.1);
    glEnd();

    // Draw the second square (chasing square)
    glColor3f(1.0, 0.0, 0.0);  // You can set a different color for the chasing square
    glBegin(GL_QUADS);
    glVertex2f(chasing_x, chasing_y);
    glVertex2f(chasing_x + 0.1, chasing_y);
    glVertex2f(chasing_x + 0.1, chasing_y + 0.1);
    glVertex2f(chasing_x, chasing_y + 0.1);
    glEnd();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
        qDebug() << "left pressed";
        x_pos -= 0.1;
        break;
    case Qt::Key_Right:
        x_pos += 0.1;
        break;
    case Qt::Key_Up:
        y_pos += 0.1;
        break;
    case Qt::Key_Down:
        y_pos -= 0.1;
        break;
    default:
        break;
    }

    update();
}
void OpenGLWidget::moveChasingSquare() {
    // Calculate the direction towards the first square
    float dx = x_pos - chasing_x;
    float dy = y_pos - chasing_y;

    // Normalize the direction
    float length = sqrt(dx * dx + dy * dy);
    if (length > 0.0f) {
        dx /= length;
        dy /= length;
    }

    // Move the chasing square towards the first square
    chasing_x += movementSpeed * dx;
    chasing_y += movementSpeed * dy;

    if (areSquaresOverlapping()) {
        emit squaresOverlapping();
        // Add your code to handle the overlap condition
    }

    update();
}

bool OpenGLWidget::areSquaresOverlapping() const {
    float square1Right = x_pos + 0.1;  // Assuming square width and height are both 0.1
    float square1Top = y_pos + 0.1;

    float square2Right = chasing_x + 0.1;
    float square2Top = chasing_y + 0.1;

    // Check for non-overlapping conditions
    if (x_pos > square2Right || square1Right < chasing_x || y_pos > square2Top || square1Top < chasing_y) {
        return false;  // Squares do not overlap
    }

    return true;  // Squares overlap
}

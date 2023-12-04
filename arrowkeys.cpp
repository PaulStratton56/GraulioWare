#include "arrowkeys.h"
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>
#include <QStringList>
#include <cstdlib>

ArrowKeys::ArrowKeys(QWidget *parent) : QOpenGLWidget(parent)
{
    // arrowTimer = new QTimer(this);
    // connect(arrowTimer, &QTimer::timeout, this, &ArrowKeys::handleArrowTimeout);

}
ArrowKeys::~ArrowKeys(){
}
void ArrowKeys::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(57.0/255.0f, 0, 106.0/255.0f, 1.0);
}

void ArrowKeys::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void ArrowKeys::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the current arrow
    if (currentArrowIndex < arrowSequence.size()) {
        drawArrow(arrowSequence[currentArrowIndex]);
    }
}

void ArrowKeys::start(int numArrows)
{
    currentArrowIndex = 0;
    totalArrows = numArrows;
    arrowSequence.clear();
    generateArrowSequence();
    // arrowTimer->start(3000);
}


void ArrowKeys::keyPressEvent(QKeyEvent *event) {
    if(currentArrowIndex == totalArrows){ return; }
    if (event->key() == arrowSequence[currentArrowIndex]) {
        currentArrowIndex++;
        if (currentArrowIndex == totalArrows) {
            emit allArrowsInputted();
        }
    }
    else
    {
        emit arrowFailure();
        currentArrowIndex = totalArrows;
    }

    update();
}


void ArrowKeys::generateArrowSequence() {
    currentArrowIndex = 0;

    int prevArrow = rand() %4;
    int arrowNum = prevArrow;
    for (int i = 0; i < totalArrows; i++) {
        Qt::Key arrow = static_cast<Qt::Key>(Qt::Key_Left + arrowNum);
        arrowSequence.push_back(arrow);
        prevArrow = arrowNum;
        while(arrowNum == prevArrow){ arrowNum = rand() % 4; }
    }
}

// void ArrowKeys::handleArrowTimeout() {
//     // Arrows disappear after a certain time, generate a new sequence
//     generateArrowSequence();
// }

void ArrowKeys::drawArrow(Qt::Key arrow) {
    float size = 0.3;

    glLoadIdentity();
    // Set color based on arrow direction
    switch (arrow) {
    case Qt::Key_Left:
        glColor3f(1.0, 0.0, 0.0);  // Red for Left
        orientation = 90.0;
        break;
    case Qt::Key_Right:
        glColor3f(0.0, 1.0, 0.0);  // Green for Right
        orientation = 270.0;
        break;
    case Qt::Key_Up:
        glColor3f(0.3, 0.4, 1.0);  // Blue for Up
        orientation = 0.0;
        break;
    case Qt::Key_Down:
        glColor3f(1.0, 1.0, 0.0);  // Yellow for Down
        orientation = 180.0;
        break;
    default:
        break;
    }

    // Center the arrow on the screen
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(orientation, 0.0, 0.0, 1.0);

    glBegin(GL_TRIANGLES);
    glVertex2f(-size/1.4, -size);
    glVertex2f(size/1.4, -size);
    glVertex2f(0.0, size);
    glEnd();
}

#include "arrowkeys.h"
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>
#include <QStringList>
#include <cstdlib>

ArrowKeys::ArrowKeys(QWidget *parent)
    : QOpenGLWidget(parent), currentArrowIndex(0)
{
    generateArrowSequence();

    arrowTimer = new QTimer(this);
    connect(arrowTimer, &QTimer::timeout, this, &ArrowKeys::handleArrowTimeout);
    arrowTimer->start(3000);

}
ArrowKeys::~ArrowKeys(){
}
void ArrowKeys::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 0.0);
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



void ArrowKeys::keyPressEvent(QKeyEvent *event) {
    totalArrows = 5;
    if (currentArrowIndex < 5) {
        Qt::Key expectedKey = arrowSequence[currentArrowIndex];

        // Check if the pressed key matches the current arrow
        if (event->key() == expectedKey) {
            // Move to the next arrow
            currentArrowIndex++;

            // Check if all arrows are pressed
            if (currentArrowIndex == 4) {
                // All arrows are pressed, emit the signal
                emit allArrowsInputted();

                // Generate a new sequence
                generateArrowSequence();
            }
        }
    }

    update(); // Trigger a redraw
}


void ArrowKeys::generateArrowSequence() {
    arrowSequence.clear();
    currentArrowIndex = 0;

    // Generate a random arrow sequence (you can adjust this logic)
    for (int i = 0; i < 4; ++i) {
        Qt::Key arrow = static_cast<Qt::Key>(Qt::Key_Left + (rand() % 4));
        arrowSequence.push_back(arrow);
    }
}

void ArrowKeys::handleArrowTimeout() {
    // Arrows disappear after a certain time, generate a new sequence
    generateArrowSequence();
}

void ArrowKeys::drawArrow(Qt::Key arrow) {
    float size = 0.1;
    glRotatef(-orientation, 0.0, 0.0, 1.0);
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
        glColor3f(0.0, 0.0, 1.0);  // Blue for Up
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

    // Adjust the coordinates to create a left-pointing arrow
//    if (arrow == Qt::Key_Left) {
//        glVertex2f(-size, 0.0);
//        glVertex2f(size, -size);
//        glVertex2f(size, size);
//    } else {
//        // Use the original coordinates for other arrow directions
//        glVertex2f(-size, -size);
//        glVertex2f(size, -size);
//        glVertex2f(0.0, size);
//    }

    glBegin(GL_TRIANGLES);
    glVertex2f(-size, -size);
    glVertex2f(size, -size);
    glVertex2f(0.0, size);
    glEnd();
}

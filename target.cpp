#include "target.h"
#include <cmath>
#include <QDebug>


Target::Target(QWidget *parent) : QOpenGLWidget(parent)
{

}

void Target::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Target::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

//Let's draw a circle!
void Target::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //Set up the number of lines to draw.
    const int numSegments = 360;

    //This scaling allows for the target to always be a circle, no matter what viewport!
    float w = this->width();
    float h = this->height();
    bool scaleX = false;
    if(w > h){ scaleX = true; }
    float scalingFactor = std::min(w/h, h/w);

    bool isRed = false;

    for(int scale = 5; scale > 0; scale--)
    {
        //Set color to white and red, alternating
        if(isRed)
        {
            isRed = false;
            glColor3f(1.0f, 1.0f, 1.0f);
        }
        else
        {
            isRed = true;
            glColor3f(1.0f, 0.0f, 0.0f);
        }

        //Draw the circle, using math!
        //Center is (0,0), border of viewport is at 1.0
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0);
        for (int i = 0; i <= numSegments; i++)
        {
            float theta = i*(M_PI/180);
            float x = (1 * std::cos(theta)) * ((scaleX) ? scalingFactor : 1) * (scale/5.0);
            float y = (1 * std::sin(theta)) * ((scaleX) ? 1 : scalingFactor) * (scale/5.0);
            glVertex2f(x, y);
        }
        glEnd();
    }

}

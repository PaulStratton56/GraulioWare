#ifndef KEY_H
#define KEY_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QLabel>

//Might need to change privacy, depending on what's needed from QOpenGLWidgets.
class Key : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
    QLabel* label;

public:
    Key(QWidget *parent = nullptr, char letter = ' ');

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // KEY_H

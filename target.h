#ifndef TARGET_H
#define TARGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

//Might need to change privacy, depending on what's needed from QOpenGLWidgets.
class Target : private QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Target(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // TRIANGLE_H

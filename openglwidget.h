#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QTimer>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    QTimer* moveTimer;
    OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();
    void reset();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;
    bool areSquaresOverlapping() const;
private slots:
    void moveChasingSquare();
private:
    float x_pos;
    float y_pos;
    float chasing_x;  // Declare chasing_x as a member variable
    float chasing_y;  // Declare chasing_y as a member variable
    float movementSpeed;
signals:
    void squaresOverlapping();
};

#endif // OPENGLWIDGET_H

#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QTimer>

    class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void moveChasingSquare();
    bool areSquaresOverlapping() const;
private:
    float x_pos;
    float y_pos;
    float chasing_x;  // Declare chasing_x as a member variable
    float chasing_y;  // Declare chasing_y as a member variable
    float movementSpeed;
    QTimer* moveTimer;
signals:
    void squaresOverlapping() const;
};

#endif // OPENGLWIDGET_H

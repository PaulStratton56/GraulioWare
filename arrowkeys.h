#ifndef ARROWKEYS_H
#define ARROWKEYS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QTimer>
#include <QPoint>
#include <QLabel>
#include <QStringList>

class ArrowKeys : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    ArrowKeys(QWidget *parent = nullptr);
    ~ArrowKeys();
    void start(int numArrows = 5);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void generateArrowSequence();
    // void handleArrowTimeout();
    void drawArrow(Qt::Key arrow);
private:
    // QTimer *arrowTimer;
    QVector<Qt::Key> arrowSequence;
    int currentArrowIndex;
    int totalArrows;
    float orientation;
signals:
    void allArrowsInputted();
    void arrowFailure();


};

#endif // ARROWKEYS_H

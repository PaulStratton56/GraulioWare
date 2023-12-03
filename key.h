#ifndef KEY_H
#define KEY_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QLabel>
#include <QSpacerItem>
#include <cctype>

//Might need to change privacy, depending on what's needed from QOpenGLWidgets.
class Key : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    QLabel* label;
    Key(QWidget *parent = nullptr, QLayout* layout = nullptr, char letter = ' ');
    ~Key();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override = 0;
    virtual void pressed() = 0;
    QLayout* myLayout;
};


class CapitalKey : public Key
{
    Q_OBJECT

public:
    CapitalKey(QWidget *parent = nullptr, QLayout* layout = nullptr, char letter = ' ') : Key(parent, layout, std::toupper(letter)){}
    ~CapitalKey(){}
    void pressed();
    void paintGL();
};

class LowerKey : public Key
{
    Q_OBJECT

public:
    LowerKey(QWidget *parent = nullptr, QLayout* layout = nullptr, char letter = ' ') : Key(parent, layout, letter){}
    ~LowerKey(){}
    void pressed();
    void paintGL();
};

#endif // KEY_H

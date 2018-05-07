#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <QWidget>

class Controls : public QWidget
{
    Q_OBJECT
public:
    explicit Controls(QWidget *parent = nullptr);

signals:
    void fromChanged(int from);
    void toChanged(int to);

public slots:
};

#endif // CONTROLS_HPP

#ifndef TFILL_GUI_H
#define TFILL_GUI_H

#include <QWidget>
#include <QPainter>
#include "hexagon.hpp"

class Canvas : public QWidget {
	Q_OBJECT

public:
	Canvas(QWidget *parent = 0);
	~Canvas();

private slots:
	void timedDrawEventHandler();

private:
	void drawHexagonPath(PointPath &pos);
};

#endif

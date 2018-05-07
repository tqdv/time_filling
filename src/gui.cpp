#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <random>
#include "hexagon.hpp"
#include "gui.hpp"



#include <iostream>

Canvas::Canvas(QWidget *parent) : QWidget(parent) {
	QTimer *timer = new QTimer(this);
	timer->setInterval(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(timedDrawEventHandler()));
	timer->start();
} 

Canvas::~Canvas() { }

void Canvas::drawHexagonPath(PointPath &pos) {

	qDebug() << "before";

	QPainter painter;
	painter.begin(this);
	painter.setPen(Qt::green);
	painter.setRenderHint(QPainter::Antialiasing);

	qDebug() << "between";

	QPointF p1, p2;
	p1 = QPointF((qreal) pos[0].x, (qreal) pos[0].y);
	for (int j = 1; j < 7; j++) {
		p2 = QPointF((qreal) pos[j].x, (qreal) pos[j].y);
		painter.drawLine(p1, p2);
		p1 = std::move(p2);
	}
	//this->update();
	
	painter.end();
	qDebug() << "after";
}


/* To improve and move */
void Canvas::timedDrawEventHandler() {

	std::cout << "hi";

	std::random_device rd;
	std::minstd_rand gen;
	gen.seed(rd());
	HexagonPath path;
	PointPath pos;
	Point center = {5.0, 5.0};
	int from, to;
	bool status;

	from = gen() % 7;
	to = gen() % 7;

	status = hexagon_path(from, to, path);

	if (status) {
		status = hexagon_positions(path, center, 5.0, 0.0, pos);
		this->drawHexagonPath(pos);
	}
}


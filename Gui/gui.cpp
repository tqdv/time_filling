#include "gui.hpp"

#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QWidget>
#include <random>

#include "hexagon.hpp"

Canvas::Canvas (QWidget *parent) : QWidget (parent) {
	QTimer *timer = new QTimer (this);
	timer->setInterval (1000);
	//	connect(timer, &QTimer::timeout, this, &Canvas::recalculatePath);
	timer->start ();
}

Canvas::~Canvas () {}

void Canvas::setFrom (int from) {
	if (mFrom != from) {
		mFrom = from;
		recalculatePath ();
	}
}

void Canvas::setTo (int to) {
	if (mTo != to) {
		mTo = to;
		recalculatePath ();
	}
}

void Canvas::drawHexagonPath (PointPath &pos) {

	QPainter painter (this);
	painter.setPen (Qt::green);
	painter.setRenderHint (QPainter::Antialiasing);

	QPointF p1, p2;
	p1 = QPointF ((qreal) pos[0].x, (qreal) pos[0].y);
	for (int j = 1; j < 7; j++) {
		p2 = QPointF ((qreal) pos[j].x, (qreal) pos[j].y);
		painter.drawLine (p1, p2);
		p1 = std::move (p2);
	}
}

void Canvas::paintEvent (QPaintEvent *ev) {
	drawHexagonPath (mLastPath);
}

/* To improve */
void Canvas::recalculatePath () {

	std::random_device rd;
	std::minstd_rand gen;
	gen.seed (rd ());
	HexagonPath path;
	bool status;

	status = hexagon_path (mFrom, mTo, path);

	if (!status)
		return;

	Point center = {float(width () / 2.0), float(height () / 2.0)};
	status = hexagon_positions (
	   path, center, qMin (width (), height ()) / 2.0, 0.0, mLastPath);
	update ();
}

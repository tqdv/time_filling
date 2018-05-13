#include "gui.hpp"

#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QWidget>
#include <random>

#include "shapes.hpp"

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

void Canvas::drawHexagonPath (const PointPath &pos) {
	int n = pos.size ();
	if (n == 0) {
		return;
	}

	QPainter painter (this);
	painter.setPen (Qt::green);
	painter.setRenderHint (QPainter::Antialiasing);

	QPointF p1, p2;
	p1 = QPointF ((qreal) pos[0].x, (qreal) pos[0].y);
	for (int i = 1; i < n; ++i) {
		p2 = QPointF ((qreal) pos[i].x, (qreal) pos[i].y);
		painter.drawLine (p1, p2);
		p1 = std::move (p2);
	}
}

void Canvas::paintEvent (QPaintEvent *ev) {
	drawHexagonPath (mLastPath);
}

/* To improve */
void Canvas::recalculatePath () {
	Point center = {float(width () / 2.0), float(height () / 2.0)};
	float radius = qMin (width (), height ()) / 2.0;

	std::optional<PointPath> pos
	   = shape_positions ({hexagon, radius, 0.0}, mFrom, mTo, center);

	if (!pos.has_value ()) {
		return;
	}

	mLastPath = *pos;
	update ();
}

#ifndef TFILL_GUI_H
#define TFILL_GUI_H

#include <QPainter>
#include <QWidget>
#include "hexagon.hpp"

class Canvas : public QWidget {
	Q_OBJECT

	PointPath mLastPath;

	int mFrom;
	int mTo;

  public:
	Canvas (QWidget *parent = 0);
	~Canvas ();

  public slots:
	void setFrom (int from);
	void setTo (int to);

  private slots:
	void recalculatePath ();

  private:
	void drawHexagonPath (const PointPath &pos);
	void paintEvent (QPaintEvent *ev);
};

#endif

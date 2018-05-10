#include "controls.hpp"

#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>

Controls::Controls (QWidget *parent) : QWidget (parent) {
	QFormLayout *lay = new QFormLayout (this);

	QSpinBox *number = new QSpinBox (this);
	lay->addRow ("From", number);
	number->setRange (0, 6);
	connect (number,
	   static_cast<void (QSpinBox::*) (int)> (&QSpinBox::valueChanged), this,
	   &Controls::fromChanged);

	number = new QSpinBox (this);
	lay->addRow ("To", number);
	number->setRange (0, 6);
	connect (number,
	   static_cast<void (QSpinBox::*) (int)> (&QSpinBox::valueChanged), this,
	   &Controls::toChanged);
}

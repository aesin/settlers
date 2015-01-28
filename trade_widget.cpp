#include "trade_widget.h"
namespace settlers {
ResourceBox::ResourceBox(GameResource res): QWidget(), value(0) {
  QVBoxLayout * m_layout = new QVBoxLayout(this);
  QPushButton * m_inc = new QPushButton(this);
  QPushButton * m_dec = new QPushButton(this);
  QLabel * m_value_box = new QLabel(this);
  m_value_box->setNum(0);
  QObject::connect(m_inc, SIGNAL(clicked()), this, SLOT(IncreaseValue()));
  QObject::connect(m_dec, SIGNAL(clicked()), this, SLOT(DecreaseValue()));
  QObject::connect(this, SIGNAL(ValueChanged(int)), m_value_box, SLOT(setNum(int)));
  const std::vector<QColor> kResColors = {Qt::darkRed, Qt::darkGreen, Qt::gray, Qt::green, Qt::cyan}; // TODO: make pictures
  m_value_box->setAutoFillBackground(true);
  m_value_box->setPalette(QPalette(kResColors[res], kResColors[res]));
  m_layout->addWidget(m_inc);
  m_layout->addWidget(m_value_box);
  m_layout->addWidget(m_dec);
  setLayout(m_layout);
}

void ResourceBox::DecreaseValue()
{
  if (value > 0) {
    value--;
    ValueChanged(value);
  }
}

void ResourceBox::IncreaseValue()
{
  value++;
  ValueChanged(value);
}

}
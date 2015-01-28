#ifndef trade_widget_H
#define trade_widget_H
#include "objects.h"
#include "network.h"

#include <QtGui>
#include <QObject>
#include <QColor>

namespace settlers{
class ResourceBox : public QWidget {
  Q_OBJECT
public:
  ResourceBox(GameResource res);
  int GetValue() { return value; }
private:
  int value;
private slots:
  void IncreaseValue();
  void DecreaseValue();
signals:
  void ValueChanged(int new_value);
};

class TradeWidget : public QWidget {
  Q_OBJECT
private:
  void MakeTrade();

private slots:
  void MakeOffer() {};
  void AcceptOffer() {};
  void CancelTrade() {};
};
}
#endif

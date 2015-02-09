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
  ResourceBox(GameResource res, QWidget * parent = 0);
  int GetValue() { return value; }
  void SetValue(int new_value);
private:
  int value;
private slots:
  void IncreaseValue();
  void DecreaseValue();
signals:
  void ValueChanged(int new_value);
};

class ResourcePanel : public QWidget {
  Q_OBJECT
public:
  ResourcePanel(QWidget * parent = 0);
  const Resources& GetResources() { return m_resources; }
  void SetRecources(const Resources& new_res);
private:
  Resources m_resources;
  std::vector<ResourceBox*> m_res_boxes = std::vector<ResourceBox*>(RESOURCES_NUMBER, 0);
private slots:
  void ChangeValue(GameResource res, int new_value) { m_resources[res] = new_value; }
};

class TradeWidget : public QWidget {
  Q_OBJECT
public:
  TradeWidget();
private:
  void MakeTrade();

private slots:
  void MakeOffer() {};
  void AcceptOffer() {};
  void CancelTrade() {};
};
}
#endif

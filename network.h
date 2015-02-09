#ifndef network_H
#define network_H

#include <QtGui>
#include <QObject>

namespace settlers {
enum PackageType{GAME_EVENT, PACKAGE_ACCEPT, GAME_STATE, PACKAGE_TYPE_NUMBER};

class GamePackage{
  int sender_id;
  int destination;
  PackageType type;

};

class PackageHandler{
  Q_OBJECT
private:
  int cur_pack_size = 0;
  QByteArray cur_package;

private slots:
  void ReadData (QByteArray& data);
};


}
#endif // network_H

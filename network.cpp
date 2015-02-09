#include "network.h"

namespace settlers {


void PackageHandler::ReadData(QByteArray& data)
{
  while (data.size() > 0) {
    if (cur_pack_size == 0) {
      if (cur_package.size() == 2) {
	cur_pack_size = cur_package[0] * 256 + cur_package[1];
	cur_package.clear();
      }
      else {
	cur_package.push_back(data[0]);
	data.remove(0, 1);
      }
    }
    else {
      int bytes_to_copy = min(data.size(), cur_pack_size - cur_package.size());
      cur_package.push_back(data.left(bytes_to_copy));
      data.remove(0, bytes_to_copy);
      //TODO: deserialize
      cur_package.clear();
      cur_pack_size = 0;
    }
  }
}

}

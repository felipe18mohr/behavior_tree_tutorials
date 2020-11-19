#include "behaviortree_cpp_v3/bt_factory.h"

struct Point3D { double x, y, z; };

class MyLegacyMoveTo {
  public:
    bool go (Point3D goal) {
      printf("Goint to %f %f %f\n", goal.x, goal.y, goal.z);
      return true;
    }
};

namespace BT {
  template <> Point3D convertFromString(StringView key) {
    auto parts = BT::splitString(key, ';');
    
    if (parts.size() != 3)
      throw RuntimeError("invalid input");
    else {
      Point3D output;
      output.x = convertFromString<double>(parts[0]);
      output.y = convertFromString<double>(parts[1]);
      output.z = convertFromString<double>(parts[2]);
      return output;
    }
  }
}

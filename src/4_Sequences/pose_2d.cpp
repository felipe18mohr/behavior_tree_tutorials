#include "behaviortree_cpp_v3/bt_factory.h"

struct Pose2D {
  double x, y, theta;
};

namespace BT {
  
  template <> inline Pose2D convertFromString(StringView str) {
    auto parts = splitString(str, ';');
    if(parts.size() != 3)
      throw RuntimeError("Invalid Input");
    else{
      Pose2D output;
      output.x = convertFromString<double>(parts[0]);
      output.y = convertFromString<double>(parts[1]);
      output.theta = convertFromString<double>(parts[2]);
      return output;
    }
  }
}

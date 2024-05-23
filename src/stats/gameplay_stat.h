#ifndef GAMEPLAY_STAT_H
#define GAMEPLAY_STAT_H

#include <godot_cpp/classes/resource.hpp>

//using namespace godot;

namespace godot {

class GameplayStat : public Resource {
  GDCLASS(GameplayStat, Resource)

private:
  double base_value;

public:
  double get_base_value() const;
  void set_base_value(const double p_base_value);

protected:
  static void _bind_methods();
};

}

#endif

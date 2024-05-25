#include "modifier_magnitude.h"

void ModifierMagnitude::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_magnitude"), &ModifierMagnitude::get_magnitude);
}

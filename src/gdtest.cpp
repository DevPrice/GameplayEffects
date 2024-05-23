#include "gdtest.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GDTest::_bind_methods() {
}

GDTest::GDTest() {
    // Initialize any variables here.
    time_passed = 0.0;
}

GDTest::~GDTest() {
    // Add your cleanup here.
}

void GDTest::_process(double delta) {
    time_passed += delta;

    Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 0.f);

    set_position(new_position);
}

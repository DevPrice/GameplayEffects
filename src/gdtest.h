#ifndef GDTEXT_H
#define GDTEXT_H

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class GDTest : public Sprite2D {
    GDCLASS(GDTest, Sprite2D)

private:
    double time_passed;

protected:
    static void _bind_methods();

public:
    GDTest();
    ~GDTest();

    void _process(double delta) override;
};

}

#endif

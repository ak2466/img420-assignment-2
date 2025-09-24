// fading_sprite.h

#ifndef FADING_SPRITE_H
#define FADING_SPRITE_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {

class FadingSprite : public Sprite2D {
    GDCLASS(FadingSprite, Sprite2D);

private:
    bool is_fading;
    double fade_duration;
    double fade_timer;
    double rotation_angle;

protected:
    static void _bind_methods();

public:
    FadingSprite();
    ~FadingSprite();

    void _process(double delta) override;
    void start_fade();

    void set_fade_duration(const double p_fade_duration);
    double get_fade_duration() const;

    void set_rotation_angle(const double p_rotation_angle);
    double get_rotation_angle() const;
};

} // namespace godot

#endif // FADING_SPRITE_H
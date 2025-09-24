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
    bool is_animating;
    bool reverse_animation;
    double animation_duration;
    double animation_timer;
    double rotation_angle;

protected:
    static void _bind_methods();

public:
    FadingSprite();
    ~FadingSprite();

    void _process(double delta) override;
    void start_animation();

    void set_animation_duration(const double p_animation_duration);
    double get_animation_duration() const;

    void set_rotation_angle(const double p_rotation_angle);
    double get_rotation_angle() const;

    void set_reverse_animation(const bool p_reverse_animation);
    bool get_reverse_animation() const;
};

} // namespace godot

#endif // FADING_SPRITE_H
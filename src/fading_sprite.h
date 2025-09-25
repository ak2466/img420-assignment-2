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
    bool reverse_fade;

    float start_opacity;
    float end_opacity;
    float current_opacity;

    double animation_duration;
    double animation_timer;
    double rotation_angle;
    double start_rotation;
    double end_rotation;
    Vector2 max_size;
    Vector2 start_scale;
    Vector2 current_scale;
    Vector2 end_scale;

protected:
    static void _bind_methods();

public:
    FadingSprite();
    ~FadingSprite();

    void _physics_process(double delta) override;
    void _enter_tree() override;
    void start_animation();

    void set_animation_duration(const double p_animation_duration);
    double get_animation_duration() const;

    void set_rotation_angle(const double p_rotation_angle);
    double get_rotation_angle() const;

    void set_max_size(const Vector2 p_max_size);
    Vector2 get_max_size() const;

    void set_reverse_animation(const bool p_reverse_animation);
    bool get_reverse_animation() const;

        void set_reverse_fade(const bool p_reverse_fade);
    bool get_reverse_fade() const;
};

} // namespace godot

#endif // FADING_SPRITE_H
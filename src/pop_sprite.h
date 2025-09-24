// fading_sprite.h

#ifndef POP_SPRITE_H
#define POP_SPRITE_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

class PopSprite : public Sprite2D {
    GDCLASS(PopSprite, Sprite2D);

private:
    bool is_animating;
    bool reverse_animation;
    double animation_duration;
    double animation_timer;
    Vector2 max_size;

protected:
    static void _bind_methods();

public:
    PopSprite();
    ~PopSprite();

    void _process(double delta) override;
    void start_animation();

    void set_animation_duration(const double p_animation_duration);
    double get_animation_duration() const;

    void set_max_size(const Vector2 p_max_size);
    Vector2 get_max_size() const;

    void set_reverse_animation(const bool p_reverse_animation);
    bool get_reverse_animation() const;
};

} // namespace godot

#endif // FADING_SPRITE_H
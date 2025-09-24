// fading_sprite.cpp

#include "fading_sprite.h"
#include <godot_cpp/core/class_db.hpp>

const double PI = 3.141592653;

using namespace godot;

void FadingSprite::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_animation_duration"), &FadingSprite::get_animation_duration);
    ClassDB::bind_method(D_METHOD("set_animation_duration", "p_animation_duration"), &FadingSprite::set_animation_duration);

    ClassDB::bind_method(D_METHOD("get_rotation_angle"), &FadingSprite::get_rotation_angle);
    ClassDB::bind_method(D_METHOD("set_rotation_angle", "p_rotation_angle"), &FadingSprite::set_rotation_angle);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fade_duration", PROPERTY_HINT_RANGE, "0.1,5.0,0.01"), "set_fade_duration", "get_fade_duration");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotation_angle", PROPERTY_HINT_RANGE, "0.0,360.0,0.01"), "set_rotation_angle", "get_rotation_angle");

    ADD_SIGNAL(MethodInfo("animation_complete"));
    ClassDB::bind_method(D_METHOD("start_animation"), &FadingSprite::start_animation);
}

FadingSprite::FadingSprite() {
    is_animating = false;
    animation_duration = 1.0;
    animation_timer = 0.0;
    rotation_angle = 0.0;
}

FadingSprite::~FadingSprite() {
    // Cleanup if needed
}

void FadingSprite::_process(double delta) {

    // Define variables
    // Define animation completion ratio
    double completion_ratio = animation_timer / animation_duration;

    if (is_animating) {
        animation_timer += delta;

        double new_alpha = completion_ratio;

        if (completion_ratio >= 1.0) {
            completion_ratio = 1.0;
            is_animating = false;
            emit_signal("fade_complete");
        }

        Color current_color = get_modulate();
        current_color.a = new_alpha;
        set_modulate(current_color);

        godot::UtilityFunctions::print(godot::String("Completion ratio: ") + godot::String::num(completion_ratio));

        double remaining_rotation = rotation_angle * (1.0 - completion_ratio);
        double rotation_radians = remaining_rotation * (PI / 180);
        set_rotation(rotation_radians);
    }
}

void FadingSprite::set_animation_duration(const double p_animation_duration) {
    animation_duration = p_animation_duration;
}

double FadingSprite::get_animation_duration() const {
    return animation_duration;
}

void FadingSprite::start_animation() {
    is_animating = true;
    animation_timer = 0.0;
}

void FadingSprite::set_rotation_angle(const double p_rotation_angle) {
    rotation_angle = p_rotation_angle;
}

double FadingSprite::get_rotation_angle() const {
    return rotation_angle;
}
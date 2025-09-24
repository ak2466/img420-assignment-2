// fading_sprite.cpp

#include "fading_sprite.h"
#include <godot_cpp/core/class_db.hpp>

const double PI = 3.141592653;

using namespace godot;

void FadingSprite::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_fade_duration"), &FadingSprite::get_fade_duration);
    ClassDB::bind_method(D_METHOD("set_fade_duration", "p_fade_duration"), &FadingSprite::set_fade_duration);

    ClassDB::bind_method(D_METHOD("get_rotation_angle"), &FadingSprite::get_rotation_angle);
    ClassDB::bind_method(D_METHOD("set_rotation_angle", "p_rotation_angle"), &FadingSprite::set_rotation_angle);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fade_duration", PROPERTY_HINT_RANGE, "0.1,5.0,0.01"), "set_fade_duration", "get_fade_duration");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotation_angle", PROPERTY_HINT_RANGE, "0.1,5.0,0.01"), "set_rotation_angle", "get_rotation_angle");

    ADD_SIGNAL(MethodInfo("fade_complete"));
    ClassDB::bind_method(D_METHOD("start_fade"), &FadingSprite::start_fade);
}

FadingSprite::FadingSprite() {
    is_fading = false;
    fade_duration = 1.0;
    fade_timer = 0.0;
    rotation_angle = 0.0;
}

FadingSprite::~FadingSprite() {
    // Cleanup if needed
}

void FadingSprite::_process(double delta) {

    // Define variables
    double rotation_angle_radians;

    if (is_fading) {
        fade_timer += delta;

        double new_alpha = 1.0 - (fade_timer / fade_duration);

        if (new_alpha <= 0.0) {
            new_alpha = 0.0;
            is_fading = false;
            emit_signal("fade_complete");
        }

        godot::UtilityFunctions::print(godot::String("Current alpha: ") + godot::String::num(new_alpha));

        Color current_color = get_modulate();
        current_color.a = new_alpha;
        set_modulate(current_color);
    }

    rotation_angle_radians = rotation_angle * (PI / 180);
    set_rotation(rotation_angle_radians);
}

void FadingSprite::set_fade_duration(const double p_fade_duration) {
    fade_duration = p_fade_duration;
}

double FadingSprite::get_fade_duration() const {
    return fade_duration;
}

void FadingSprite::start_fade() {
    is_fading = true;
    fade_timer = 0.0;
}

void FadingSprite::set_rotation_angle(const double p_rotation_angle) {
    rotation_angle = p_rotation_angle;
}

double FadingSprite::get_rotation_angle() const {
    return rotation_angle;
}
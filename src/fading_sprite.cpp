// fading_sprite.cpp

#include "fading_sprite.h"
#include <godot_cpp/core/class_db.hpp>

const double PI = 3.141592653;

using namespace godot;

// Class bindings
void FadingSprite::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_animation_duration"), &FadingSprite::get_animation_duration);
    ClassDB::bind_method(D_METHOD("set_animation_duration", "p_animation_duration"), &FadingSprite::set_animation_duration);
    ClassDB::bind_method(D_METHOD("start_animation", "p_reverse_animation", "p_reverse_fade"), &FadingSprite::start_animation);

    ClassDB::bind_method(D_METHOD("get_rotation_angle"), &FadingSprite::get_rotation_angle);
    ClassDB::bind_method(D_METHOD("set_rotation_angle", "p_rotation_angle"), &FadingSprite::set_rotation_angle);

    ClassDB::bind_method(D_METHOD("get_max_size"), &FadingSprite::get_max_size);
    ClassDB::bind_method(D_METHOD("set_max_size", "p_rotation_angle"), &FadingSprite::set_max_size);

    ClassDB::bind_method(D_METHOD("get_reverse_animation"), &FadingSprite::get_reverse_animation);
    ClassDB::bind_method(D_METHOD("set_reverse_animation", "p_reverse_animation"), &FadingSprite::set_reverse_animation);

    ClassDB::bind_method(D_METHOD("get_reverse_fade"), &FadingSprite::get_reverse_fade);
    ClassDB::bind_method(D_METHOD("set_reverse_fade", "p_reverse_fade"), &FadingSprite::set_reverse_fade);

    // Add properties to editor
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "animation_duration", PROPERTY_HINT_RANGE, "0.1,5.0,0.01"), "set_animation_duration", "get_animation_duration");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotation_angle", PROPERTY_HINT_RANGE, "0.0,360.0,0.01"), "set_rotation_angle", "get_rotation_angle");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "max_size", PROPERTY_HINT_RANGE, "0.0,360.0,0.01"), "set_max_size", "get_max_size");

    // Add signal to editor
    ADD_SIGNAL(MethodInfo("animation_complete"));
}

FadingSprite::FadingSprite() {
    is_animating = false;
    reverse_animation = false;
    animation_duration = 1.0;
    animation_timer = 0.0;
    rotation_angle = 0.0;
}

FadingSprite::~FadingSprite() {
    // Cleanup if needed
}

void FadingSprite::_physics_process(double delta) {

    // Define variables
    // Define animation completion ratio
    double completion_ratio = -1.0;

    completion_ratio = animation_timer / animation_duration;

    // Check if is animating
    if (is_animating) {

        // Add delta (current diff in frames) to animation timer
        animation_timer += delta;

        // Check if completion ratio is over or under recommended range
        if (completion_ratio > 1.0 || completion_ratio < 0.0) {

            // Reset completion ratio (change this to accept 0.0 when reversed)
            completion_ratio = 1.0;

            // Turn is animating off to stop the loop
            is_animating = false;

            // Emit the fade complete signal
            emit_signal("animation_complete");
        }

        // Get current color
        Color current_color = get_modulate();

        current_opacity = start_opacity + ((end_opacity - start_opacity)) * completion_ratio;

        // Change its alpha
        current_color.a = current_opacity;

        // Set sprite to current color
        set_modulate(current_color);

        // Calculate remaining rotation amount
        double remaining_rotation = start_rotation + ((end_rotation - start_rotation) * completion_ratio);

        // Set the rotation
        set_rotation_degrees(remaining_rotation);

        current_scale.x = start_scale.x + ((end_scale.x - start_scale.x) * completion_ratio);
        current_scale.y = start_scale.y + ((end_scale.y - start_scale.y) * completion_ratio);

        set_scale(current_scale);
    }
}

// Setters and getters
void FadingSprite::set_animation_duration(const double p_animation_duration) {
    animation_duration = p_animation_duration;
}

double FadingSprite::get_animation_duration() const {
    return animation_duration;
}

void FadingSprite::start_animation(bool p_reverse_animation, bool p_reverse_fade) {
    reverse_animation = p_reverse_animation;
    reverse_fade = p_reverse_fade;

    // Handle reverse fade and reverse animation logic
    if(reverse_fade) {
        start_opacity = 0.0;
        end_opacity = get_modulate().a;
    }
    else {
        start_opacity = get_modulate().a;
        end_opacity = 0.0;
    }

    // Max size is multiplied by get scale to have it be relative to scale set in editor
    if(reverse_animation) {
        start_scale = max_size * get_scale();
        end_scale = get_scale();

        start_rotation = get_rotation_degrees();
        end_rotation = rotation_angle;
    }
    else {

        start_scale = get_scale();
        end_scale = max_size * get_scale();

        start_rotation = rotation_angle;
        end_rotation = get_rotation_degrees();
    }

    is_animating = true;
    animation_timer = 0.0;
}

void FadingSprite::set_rotation_angle(const double p_rotation_angle) {
    rotation_angle = p_rotation_angle;
}

double FadingSprite::get_rotation_angle() const {
    return rotation_angle;
}

void FadingSprite::set_reverse_animation(const bool p_reverse_animation) {
    reverse_animation = p_reverse_animation;
}

bool FadingSprite::get_reverse_animation() const {
    return reverse_animation;
}

void FadingSprite::set_reverse_fade(const bool p_reverse_fade) {
    reverse_fade = p_reverse_fade;
}

bool FadingSprite::get_reverse_fade() const {
    return reverse_fade;
}

void FadingSprite::set_max_size(const Vector2 p_max_size) {
    max_size = p_max_size;
}

Vector2 FadingSprite::get_max_size() const {
    return max_size;
}

// fading_sprite.cpp

#include "fading_sprite.h"
#include <godot_cpp/core/class_db.hpp>

const double PI = 3.141592653;

using namespace godot;

void FadingSprite::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_animation_duration"), &FadingSprite::get_animation_duration);
    ClassDB::bind_method(D_METHOD("set_animation_duration", "p_animation_duration"), &FadingSprite::set_animation_duration);
    ClassDB::bind_method(D_METHOD("start_animation"), &FadingSprite::start_animation);

    ClassDB::bind_method(D_METHOD("get_rotation_angle"), &FadingSprite::get_rotation_angle);
    ClassDB::bind_method(D_METHOD("set_rotation_angle", "p_rotation_angle"), &FadingSprite::set_rotation_angle);

    ClassDB::bind_method(D_METHOD("get_reverse_animation"), &FadingSprite::get_reverse_animation);
    ClassDB::bind_method(D_METHOD("set_reverse_animation", "p_reverse_animation"), &FadingSprite::set_reverse_animation);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "animation_duration", PROPERTY_HINT_RANGE, "0.1,5.0,0.01"), "set_animation_duration", "get_animation_duration");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotation_angle", PROPERTY_HINT_RANGE, "0.0,360.0,0.01"), "set_rotation_angle", "get_rotation_angle");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "reverse_animation", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT), "set_reverse_animation", "get_reverse_animation");

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

void FadingSprite::_process(double delta) {

    // Define variables
    // Define animation completion ratio
    double completion_ratio = -1.0;

    // Check if reverse animation is enabled
    if(reverse_animation)
    {
        // If it is, reverse the completion ratio 
        completion_ratio = 1.0 - (animation_timer / animation_duration);
    }

    // Otherwise
    else
    {
        // Calculate the completion_ratio normally
        completion_ratio = animation_timer / animation_duration;
    }



    // Check if is animating
    if (is_animating) {

        // Add delta (current diff in frames) to animation timer
        animation_timer += delta;

        // Set new alpha to the completion ratio
        double new_alpha = completion_ratio;

        // Check if completion ratio is over or under recommended range
        if (completion_ratio > 1.0 || completion_ratio < 0.0) {

            // Reset completion ratio (change this to accept 0.0 when reversed)
            completion_ratio = 1.0;

            // Turn is animating off to stop the loop
            is_animating = false;

            // Emit the fade complete signal
            emit_signal("fade_complete");
        }

        // Get current color
        Color current_color = get_modulate();

        // Change its alpha
        current_color.a = new_alpha;

        // Set sprite to current color
        set_modulate(current_color);

        // DEBUG: console log rotation angle
        //godot::UtilityFunctions::print(godot::String("Rotation angle: ") + godot::String::num(rotation_angle));

        // Calculate remaining rotation amount
        double remaining_rotation = rotation_angle * (1.0 - completion_ratio);

        // Convert it to radians
        double rotation_radians = remaining_rotation * (PI / 180);

        // Set the rotation
        set_rotation(rotation_radians);
    }
}

// Setters and getters
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

void FadingSprite::set_reverse_animation(const bool p_reverse_animation) {
    reverse_animation = p_reverse_animation;
}

bool FadingSprite::get_reverse_animation() const {
    return reverse_animation;
}
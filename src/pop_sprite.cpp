#include "pop_sprite.h"

using namespace godot;

void PopSprite::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_animation_duration"), &PopSprite::get_animation_duration);
    ClassDB::bind_method(D_METHOD("set_animation_duration", "p_animation_duration"), &PopSprite::set_animation_duration);
    ClassDB::bind_method(D_METHOD("start_animation"), &PopSprite::start_animation);

    ClassDB::bind_method(D_METHOD("get_max_size"), &PopSprite::get_max_size);
    ClassDB::bind_method(D_METHOD("set_max_size", "p_rotation_angle"), &PopSprite::set_max_size);

    ClassDB::bind_method(D_METHOD("get_reverse_animation"), &PopSprite::get_reverse_animation);
    ClassDB::bind_method(D_METHOD("set_reverse_animation", "p_reverse_animation"), &PopSprite::set_reverse_animation);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "animation_duration", PROPERTY_HINT_RANGE, "0.1,5.0,0.01"), "set_animation_duration", "get_animation_duration");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "max_size", PROPERTY_HINT_RANGE, "0.0,360.0,0.01"), "set_max_size", "get_max_size");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "reverse_animation", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT), "set_reverse_animation", "get_reverse_animation");

    ADD_SIGNAL(MethodInfo("animation_complete"));
}

PopSprite::PopSprite() {

}

PopSprite::~PopSprite() {
    // Cleanup if needed
}

void PopSprite::_process(double delta) {

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

    if(is_animating) {

        // Add delta (current diff in frames) to animation timer
        animation_timer += delta;

        // Check if completion ratio is over or under recommended range
        if (completion_ratio > 1.0 || completion_ratio < 0.0) {

            // Reset completion ratio (change this to accept 0.0 when reversed)
            completion_ratio = 1.0;

            // Turn is animating off to stop the loop
            is_animating = false;

            // Emit the animation complete signal
            //emit_signal("fade_complete");
        }
    }

    set_scale(max_size);

}

// Setters and getters
void PopSprite::set_animation_duration(const double p_animation_duration) {
    animation_duration = p_animation_duration;
}

double PopSprite::get_animation_duration() const {
    return animation_duration;
}

void PopSprite::start_animation() {
    is_animating = true;
    animation_timer = 0.0;
}

void PopSprite::set_reverse_animation(const bool p_reverse_animation) {
    reverse_animation = p_reverse_animation;
}

bool PopSprite::get_reverse_animation() const {
    return reverse_animation;
}

void PopSprite::set_max_size(const Vector2 p_max_size) {
    max_size = p_max_size;
}

Vector2 PopSprite::get_max_size() const {
    return max_size;
}
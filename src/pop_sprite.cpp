#include "pop_sprite.h"

using namespace godot;

void PopSprite::_bind_methods() {

}

PopSprite::PopSprite() {

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
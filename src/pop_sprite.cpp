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
    start_scale = Vector2(1.0, 1.0);

    // Calculate scale
    current_scale = Vector2(1.0, 1.0);
}

PopSprite::~PopSprite() {
    // Cleanup if needed
}

void PopSprite::_enter_tree() {

    if(reverse_animation) {
        start_scale = max_size;
        end_scale = get_scale();
    }
    else {

        start_scale = get_scale();
        end_scale = max_size;
    }

    godot::UtilityFunctions::print(godot::String("Start scale x: ") + godot::String::num(start_scale.x));
    godot::UtilityFunctions::print(godot::String("Start scale y: ") + godot::String::num(start_scale.y));
}

void PopSprite::_process(double delta) {

    // Define variables
    // Define animation completion ratio
    double completion_ratio = -1.0;

    completion_ratio = animation_timer / animation_duration;

    if(is_animating) {

        // Add delta (current diff in frames) to animation timer
        animation_timer += delta;

        // Check if completion ratio is over or under recommended range
        if (completion_ratio >= 1.0) {

            // Reset completion ratio (change this to accept 0.0 when reversed)
            completion_ratio = 1.0;

            // Turn is animating off to stop the loop
            is_animating = false;

            // Emit the animation complete signal
            emit_signal("fade_complete");
        }

        current_scale.x = start_scale.x + ((end_scale.x - start_scale.x) * completion_ratio);
        current_scale.y = start_scale.y + ((end_scale.y - start_scale.y) * completion_ratio);

        godot::UtilityFunctions::print(godot::String("Completion ratio") + godot::String::num(completion_ratio));
        godot::UtilityFunctions::print(godot::String("Current x: ") + godot::String::num(current_scale.x));
        godot::UtilityFunctions::print(godot::String("Current y: ") + godot::String::num(current_scale.y));

        set_scale(current_scale);
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

void PopSprite::set_max_size(const Vector2 p_max_size) {
    max_size = p_max_size;
}

Vector2 PopSprite::get_max_size() const {
    return max_size;
}
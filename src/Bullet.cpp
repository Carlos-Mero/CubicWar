#include "Bullets.h"
#include <godot_cpp/classes/visible_on_screen_notifier2d.hpp>
#include <godot_cpp/core/object.hpp>

using namespace godot;

void Bullet::_bind_methods() {
}

Bullet::Bullet() {
}

Bullet::~Bullet() {
}

// Default Bullet

Vector2 DefaultBullet::bspeed = Vector2(0, -1200);
double DefaultBullet::damage = 28.0;

void DefaultBullet::_bind_methods() {
	ClassDB::bind_method(
			D_METHOD("m_free"), &DefaultBullet::m_free);
	ADD_SIGNAL(MethodInfo("hit"));
}

DefaultBullet::DefaultBullet() {
}

DefaultBullet::~DefaultBullet() {
}

void DefaultBullet::_ready() {
	get_node<VisibleOnScreenNotifier2D>("VisibleOnScreenNotifier2D")
		->connect("screen_exited", Callable(this, "m_free"));
}

void DefaultBullet::m_free() {
	queue_free();
}

void DefaultBullet::_physics_process(double delta) {
	set_position(get_position() + bspeed * delta);
}

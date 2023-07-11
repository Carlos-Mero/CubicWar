#include "Bullets.h"
#include "Enemy.h"

#include <godot_cpp/classes/visible_on_screen_notifier2d.hpp>

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
	ClassDB::bind_method(
			D_METHOD("cast_damage_met", "target"), &DefaultBullet::cast_damage);
	ADD_SIGNAL(MethodInfo(
				"default_bullet_hit", PropertyInfo(Variant::VECTOR2, "st_pos")));
}

DefaultBullet::DefaultBullet() {
}

DefaultBullet::~DefaultBullet() {
}

void DefaultBullet::_ready() {
	get_node<VisibleOnScreenNotifier2D>("VisibleOnScreenNotifier2D")
		->connect("screen_exited", Callable(this, "m_free"));
	connect("body_entered", Callable(this, "cast_damage_met"));
}

void DefaultBullet::m_free() {
	queue_free();
}

void DefaultBullet::cast_damage(Enemy * target) {
	target->being_attacked(damage);
	emit_signal("default_bullet_hit", get_position());
	queue_free();
}

void DefaultBullet::_physics_process(double delta) {
	set_position(get_position() + bspeed * delta);
}

// EnemyBeeBullet

const double EnemyBeeBullet::damage = 70.0;
const double EnemyBeeBullet::speed_norm = 750.0;

void EnemyBeeBullet::_bind_methods() {
}

EnemyBeeBullet::EnemyBeeBullet() {
}

EnemyBeeBullet::~EnemyBeeBullet() {
}

void EnemyBeeBullet::_ready() {
	//TODO
}

void EnemyBeeBullet::_physics_process(double delta) {
	//TODO
}

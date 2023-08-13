#include "Enemy.h"
#include "Player.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

double Enemy::default_weapon_coldown = 0.7;
double Enemy::contact_damage = 100.0;

void Enemy::_bind_methods() {
	ClassDB::bind_method(D_METHOD("being_attacked", "damage"),
			&Enemy::being_attacked);
	ClassDB::bind_method(D_METHOD("set_health", "n_health"),
			&Enemy::set_health);
	ClassDB::bind_method(D_METHOD("get_health"), &Enemy::get_health);
	ClassDB::bind_method(
			D_METHOD("set_default_weapon_coldown", "n_coldown"),
			&Enemy::set_default_weapon_coldown);
	ClassDB::bind_method(
			D_METHOD("get_default_weapon_coldown"),
			&Enemy::get_default_weapon_coldown);
	ClassDB::bind_method(
			D_METHOD("cast_contact_damage", "target"),
			&Enemy::cast_contact_damage);
	ClassDB::add_property(
			"Enemy",
			PropertyInfo(Variant::FLOAT, "health"),
			"set_health", "get_health");
	ClassDB::add_property(
			"Enemy",
			PropertyInfo(Variant::FLOAT, "default_weapon_coldown"),
			"set_default_weapon_coldown", "get_default_weapon_coldown");
	ADD_SIGNAL(MethodInfo(
				"enemy_default_weapon_attack",
				PropertyInfo(Variant::VECTOR2, "enemy_pos")));
	ADD_SIGNAL(MethodInfo("enemy_died"));
}

Enemy::Enemy() {
	m_default_weapon_coldown = default_weapon_coldown;
}

Enemy::~Enemy() {
}

void Enemy::being_attacked(double damage) {
	health -= damage;
	if (health <= 0) {
		emit_signal("enemy_died");
		//TODO
		queue_free();
	}
}

void Enemy::cast_contact_damage(Node *target) {
	static_cast<Player *>(target)->being_attacked(contact_damage);
	being_attacked(contact_damage);
}

void Enemy::_ready() {

	connect("body_entered", Callable(this, "cast_contact_damage"));
	connect("enemy_default_weapon_attack", Callable(get_parent(), "enemy_bee_attack"));

}

void Enemy::_process(double delta) {
	m_default_weapon_coldown -= delta;
	if (m_default_weapon_coldown <= 0) {
		m_default_weapon_coldown += default_weapon_coldown;
		m_default_weapon_coldown += (rand() % 10 - 5) * 0.05;
		// emit_signal("enemy_default_weapon_attack", get_position());
	}
}

void Enemy::_physics_process(double delta) {
}

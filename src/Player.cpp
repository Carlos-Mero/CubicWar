#include "Player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Player::_bind_methods(){
	ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "new_speed"), &Player::set_speed);
	ClassDB::bind_method(D_METHOD("being_attacked", "damage"), &Player::being_attacked);
	ClassDB::bind_method(D_METHOD("died"), &Player::died);
	ClassDB::add_property("Player", PropertyInfo(Variant::VECTOR2, "speed"), "set_speed", "get_speed");
	ADD_SIGNAL(MethodInfo("player_being_attacked", PropertyInfo(Variant::FLOAT, "damage")));
	ADD_SIGNAL(MethodInfo("player_died"));
}

const double Player::max_speed = 400;
const double Player::default_weapon_coldown = 0.2;

Player::Player() {
}

Player::~Player() {
}

void Player::_ready() {
	stopped = true;
	health = 200.0;
	speed = Vector2(0,-100);
	weapon_coldown = default_weapon_coldown;
	connect("player_died", Callable(this, "died"));
	connect("player_being_attacked", Callable(this, "being_attacked"));
	//emit_signal("player_being_attacked", 400.0);
}

void Player::default_weapon_attack() {
	return;
}

void Player::died() {
	UtilityFunctions::print("The player is died");
	return;
}

void Player::being_attacked(const double damage) {
	health -= damage;
	if (health <= 0) {
		emit_signal("player_died");
	}
	UtilityFunctions::print("The player has been attacked!");
}

void Player::_process(double delta) {
	if (stopped) {
		return;
	}

	weapon_coldown -= delta;
	set_position(get_position() + speed * delta);

	if (weapon_coldown <= 0) {
		default_weapon_attack();
		weapon_coldown = default_weapon_coldown;
	}

}

#include "Player.h"
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>

using namespace godot;

void Player::_bind_methods(){
	ClassDB::bind_method(D_METHOD("set_processing_status", "n_status"), &Player::set_process_status);
	ClassDB::bind_method(D_METHOD("get_processing_status"), &Player::is_processing);
	ClassDB::bind_method(D_METHOD("being_attacked", "damage"), &Player::being_attacked);
	ClassDB::bind_method(D_METHOD("died"), &Player::died);
	ClassDB::add_property("Player", PropertyInfo(Variant::BOOL, "is_processing"), "set_processing_status", "get_processing_status");
	ADD_SIGNAL(MethodInfo("player_being_attacked", PropertyInfo(Variant::FLOAT, "damage")));
	ADD_SIGNAL(MethodInfo("player_died"));
}

const double Player::max_speed = 1050.0;
const double Player::default_weapon_coldown = 0.2;

Player::Player() {
}

Player::~Player() {
}

void Player::_ready() {
	//TODO
	processing_status = false;
	health = 200.0;
	weapon_coldown = default_weapon_coldown;
	_cubic_war = get_node<CubicWar>("/root/CubicWar");
	_animated_sprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");
	_collision_area_core = get_node<CollisionShape2D>("CollisionAreaCore");
	_collision_area_around = get_node<CollisionShape2D>("CollisionAreaAround");
	_collision_area_edge = get_node<CollisionShape2D>("CollisionAreaEdge");
	input = Input::get_singleton();
	connect("player_died", Callable(this, "died"));
	connect("player_being_attacked", Callable(this, "being_attacked"));
}

void Player::default_weapon_attack() {
	//TODO
	return;
}

void Player::died() {
	//TODO
	return;
}

void Player::being_attacked(const double damage) {
	health -= damage;
	if (health <= 0) {
		emit_signal("player_died");
	}
}

void Player::_process(double delta) {
	if (!processing_status) {
		return;
	}

	weapon_coldown -= delta;

	if (weapon_coldown <= 0) {
		default_weapon_attack();
		weapon_coldown += default_weapon_coldown;
	}

	if (get_velocity().x > 0) {
		if (_animated_sprite->get_frame() == 0 && !_animated_sprite->is_flipped_h()) {
			_animated_sprite->stop();
		} else {
			_animated_sprite->set_flip_h(false);
			_animated_sprite->play_backwards("TurningRightRev");
		}
	} else if (get_velocity().x < 0) {
		if (_animated_sprite->get_frame() == 0 && _animated_sprite->is_flipped_h()) {
			_animated_sprite->stop();
		} else {
			_animated_sprite->set_flip_h(true);
			_animated_sprite->play_backwards("TurningRightRev");
		}
	} else {
		_animated_sprite->play_backwards("Stand");
		_animated_sprite->set_frame(1);
	}

}

void Player::_physics_process(double delta) {
	if (!processing_status) {
		return;
	}

	set_velocity(input->get_last_mouse_velocity());
	if (get_velocity().length() > max_speed) {
		set_velocity(get_velocity().normalized() * max_speed);
	}

	move_and_slide();

	set_position(Vector2(
				Math::clamp(get_position().x, (real_t)0.0, _cubic_war->_scene_size.x),
				Math::clamp(get_position().y, (real_t)0.0, _cubic_war->_scene_size.y)));

}

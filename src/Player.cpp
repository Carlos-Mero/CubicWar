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
	ClassDB::bind_method(
			D_METHOD("set_processing_status", "n_status"),
			&Player::set_process_status);
	ClassDB::bind_method(
			D_METHOD("get_processing_status"),
			&Player::is_processing);
	ClassDB::bind_method(
			D_METHOD("being_attacked", "damage"),
			&Player::being_attacked);
	ClassDB::bind_method(D_METHOD("died"), &Player::died);
	ClassDB::bind_method(
			D_METHOD("disable_laser_detection"), &Player::disable_laser_detection);
	ClassDB::bind_method(
			D_METHOD("enable_laser_detection"), &Player::enable_laser_detection);
	ClassDB::add_property(
			"Player",
			PropertyInfo(Variant::BOOL, "is_processing"),
			"set_processing_status", "get_processing_status");
	ADD_SIGNAL(MethodInfo(
				"player_being_attacked",
				PropertyInfo(Variant::FLOAT, "damage")));
	ADD_SIGNAL(MethodInfo("player_died"));
	ADD_SIGNAL(MethodInfo(
				"player_attack",
				PropertyInfo(Variant::INT, "weapon_type"),
				PropertyInfo(Variant::VECTOR2, "current_pos")));
}

const double Player::max_speed = 1050.0;
const double Player::default_weapon_coldown = 0.17;
const double Player::laser_min_accumulate = 0.5;
const double Player::laser_max_accumulate = 2.4;
const double Player::laser_dps = 91;

Player::Player() {
	processing_status = true;
	//processing_status = false;
	health = 200.0;
	weapon_coldown = default_weapon_coldown;
	laser_accumulate = 0.0;
	current_weapon_type = WeaponType::DEFAULT_WEAPON;
}

Player::~Player() {
}

void Player::_ready() {
	//TODO
	_laser = get_node<AnimatedSprite2D>("Laser");
	_laser_range_right = get_node<CollisionPolygon2D>("Laser/Range/LaserRangeRight");
	_laser_range_left = get_node<CollisionPolygon2D>("Laser/Range/LaserRangeLeft");
	_animated_sprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");
	_collision_area_core = get_node<CollisionShape2D>("CollisionAreaCore");
	_collision_area_around = get_node<CollisionShape2D>("CollisionAreaAround");
	_collision_area_edge = get_node<CollisionShape2D>("CollisionAreaEdge");
	input = Input::get_singleton();

	connect("player_died", Callable(this, "died"));
	connect("player_being_attacked", Callable(this, "being_attacked"));

	_laser->connect("animation_finished", Callable(this, "disable_laser_detection"));

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


	// Weapon Attack
	weapon_coldown -= delta;
	if (weapon_coldown <= 0) {
		emit_signal("player_attack", (int)current_weapon_type, get_position());
		weapon_coldown += default_weapon_coldown;
	}

	if (input->is_action_just_pressed("laser_prepare")) {
		_laser->show();
		laser_accumulate = 0.0;
	}
	if (input->is_action_pressed("laser_prepare")) {
		laser_accumulate += delta;
		if (!_laser->is_playing()) {
			_laser->play("laser_prepare");
		}
	}
	if (input->is_action_just_released("laser_prepare")) {
		if (laser_accumulate >= laser_min_accumulate) {
			laser_accumulate =
				(laser_accumulate > laser_max_accumulate) ? laser_max_accumulate : laser_accumulate;
			laser_shoot();
		} else {
			_laser->hide();
		}
	} 

	// Movement Display
	if (get_velocity().x > 0) {
		if (_animated_sprite->get_frame() == 3 && !_animated_sprite->is_flipped_h()) 
		{
			_animated_sprite->stop();
		} else {
			_animated_sprite->set_flip_h(false);
			_animated_sprite->play("TurningRight");
		}
	} else if (get_velocity().x < 0) {
		if (_animated_sprite->get_frame() == 3 && _animated_sprite->is_flipped_h()) {
			_animated_sprite->stop();
		} else {
			_animated_sprite->set_flip_h(true);
			_animated_sprite->play("TurningRight");
		}
	} else {
		_animated_sprite->play("Stand");
		_animated_sprite->set_frame(0);
	}

}

void Player::_physics_process(double delta) {
	if (!processing_status) {
		return;
	}

	// Movement
	set_velocity(input->get_last_mouse_velocity());
	if (get_velocity().length() > max_speed) {
		set_velocity(get_velocity().normalized() * max_speed);
	}

	move_and_slide();

	set_position(Vector2(
				Math::clamp(get_position().x, (real_t)0.0, movement_limit.x),
				Math::clamp(get_position().y, (real_t)0.0, movement_limit.y)));

}

inline void Player::disable_laser_detection() {
	_laser_range_left->set_disabled(true);
	_laser_range_right->set_disabled(true);
}

inline void Player::enable_laser_detection() {
	_laser_range_left->set_disabled(false);
	_laser_range_right->set_disabled(false);
}

void Player::laser_shoot() {
	_laser->play("laser_attack");
	enable_laser_detection();
	//TODO
}

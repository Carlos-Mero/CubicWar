#ifndef PLAYER_H
#define PLAYER_H

#include "Enemy.h"

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/collision_polygon2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/wrapped.hpp>

namespace godot {

enum WeaponType : int{
	DEFAULT_WEAPON = 0,
	LASER = 1,
};

class Player : public CharacterBody2D {
	GDCLASS(Player, CharacterBody2D)

	private:
		static const double max_speed;
		static const double default_weapon_coldown;
		static const double laser_max_accumulate;
		static const double laser_min_accumulate;
		static const double laser_dps;

		bool processing_status;
		Vector2 movement_limit;
		double health;
		double weapon_coldown;
		WeaponType current_weapon_type;
		double laser_accumulate;

		AnimatedSprite2D * _laser;
		Area2D * _laser_range;
		CollisionPolygon2D * _laser_range_left;
		CollisionPolygon2D * _laser_range_right;
		AnimatedSprite2D * _animated_sprite;
		CollisionShape2D * _collision_area_core;
		CollisionShape2D * _collision_area_around;
		CollisionShape2D * _collision_area_edge;

	protected:
		static void _bind_methods();

	public:

		Input * input;
		Player();
		~Player();

		void being_attacked(const double damage);
		void died(Vector2 pos);

		void set_process_status(const bool n_status) {processing_status = n_status;}
		bool is_processing() const {return processing_status;}
		void set_weapon_type(const WeaponType wp) {current_weapon_type = wp;}
		WeaponType get_weapon_type() const {return current_weapon_type;}
		void set_movement_limit(const Vector2 size) {movement_limit = size;}
		Vector2 get_movement_limit() const {return movement_limit;}
		inline void disable_laser_detection();
		inline void enable_laser_detection();
		void laser_shoot();
		void cast_laser_damage(Enemy * target);

		void _ready() override;
		void _process(double delta) override;
		void _physics_process(double delta) override;
};

}

#endif

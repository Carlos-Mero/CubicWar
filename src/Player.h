#ifndef PLAYER_H
#define PLAYER_H

#include "CubicWar.h"

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/wrapped.hpp>

namespace godot {

class Player : public CharacterBody2D {
	GDCLASS(Player, CharacterBody2D)

	private:
		static const double max_speed;
		static const double default_weapon_coldown;

		bool processing_status;
		double health;
		double weapon_coldown;

		CubicWar * _cubic_war;
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

		void set_process_status(const bool n_status) {processing_status = n_status;}
		bool is_processing() const {return processing_status;}

		void default_weapon_attack();
		void being_attacked(const double damage);
		void died();

		void _ready() override;
		void _process(double delta) override;
		void _physics_process(double delta) override;
};

}

#endif

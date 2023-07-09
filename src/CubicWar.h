#ifndef CUBIC_WAR_H
#define CUBIC_WAR_H

#include "Player.h"

#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/resource_preloader.hpp>
#include <godot_cpp/classes/wrapped.hpp>

namespace godot {

class CubicWar : public Node2D {
	GDCLASS(CubicWar, Node2D)

	private:
		Vector2 player_init_pos;

		Input * input;
		DisplayServer * _display_server;
		ResourceLoader * _re_loader;
		ResourcePreloader * _pre_loader;
		Player * _player;

		Ref<PackedScene> default_bullet;

		Ref<PackedScene> enemy_bee;

	protected:
		static void _bind_methods();

	public:
		static Vector2 _scene_size;

		CubicWar();
		~CubicWar();

		void game_init();
		void game_restart();
		void game_stop();
		void player_attack(int type, Vector2 st_pos);
		void player_default_weapon_attack(Vector2 st_pos);
		void player_died();

		void _ready() override;
		void _process(double delta) override;
		void _physics_process(double delta) override;
};

}

#endif

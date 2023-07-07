#include "CubicWar.h"

#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/resource_preloader.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void CubicWar::_bind_methods() {
	ClassDB::bind_method(
			D_METHOD("player_attack_start", "weapon_type", "current_pos"),
			&CubicWar::player_attack);
	ClassDB::bind_method(
			D_METHOD("player_died"), &CubicWar::player_died);
	ADD_SIGNAL(MethodInfo("game_ready"));
}

CubicWar::CubicWar() {
}

CubicWar::~CubicWar() {
}

Vector2 CubicWar::_scene_size = Vector2(720, 1280);

void CubicWar::game_init() {
	_display_server->mouse_set_mode(DisplayServer::MOUSE_MODE_HIDDEN);
}

void CubicWar::player_attack(int type, Vector2 st_pos) {
	switch(type) {
		case 0:
			player_default_weapon_attack(st_pos);
			break;
		case 1:
			player_laser_attack(st_pos);
			break;
		default:
			UtilityFunctions::print("Error! Unknown WeaponType!");
			break;
	}
}

void CubicWar::player_default_weapon_attack(Vector2 st_pos) {
	Node *bullet = default_bullet->instantiate();
	bullet->set("position", st_pos);
	add_child(bullet);
}

void CubicWar::player_laser_attack(Vector2 st_pos) {
	//TODO
}

void CubicWar::player_died() {
	UtilityFunctions::print("You are died.");
}

void CubicWar::_ready() {

	player_init_pos = Vector2(360, 640);

	_re_loader = ResourceLoader::get_singleton();
	_pre_loader = get_node<ResourcePreloader>("ResourcePreloader");
	_display_server = DisplayServer::get_singleton();

	default_bullet = _re_loader->load("res://default_bullet.tscn");
	enemy_bee = _re_loader->load("res://enemy_bee.tscn");

	_pre_loader->add_resource("default_bullet", default_bullet);
	_pre_loader->add_resource("enemy_bee", enemy_bee);

}

void CubicWar::_physics_process(double delta) {

}

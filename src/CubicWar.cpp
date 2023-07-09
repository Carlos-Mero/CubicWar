#include "CubicWar.h"
#include "Player.h"

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
	ClassDB::bind_method(
			D_METHOD("game_restart_met"), &CubicWar::game_restart);
	ClassDB::bind_method(
			D_METHOD("game_stop_met"), &CubicWar::game_stop);
	ADD_SIGNAL(MethodInfo("game_ready"));
	ADD_SIGNAL(MethodInfo("game_restart"));
	ADD_SIGNAL(MethodInfo("game_stop"));
}

CubicWar::CubicWar() {
	player_init_pos = Vector2(360, 640);
}

CubicWar::~CubicWar() {
}

Vector2 CubicWar::_scene_size = Vector2(720, 1280);

void CubicWar::game_init() {
	_display_server->mouse_set_mode(DisplayServer::MOUSE_MODE_HIDDEN);
}

void CubicWar::player_attack(int type, Vector2 st_pos) {
	switch(type) {
		case DEFAULT_WEAPON:
			player_default_weapon_attack(st_pos);
			break;
		case LASER:
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

void CubicWar::player_died() {
	UtilityFunctions::print("You are died.");
}

void CubicWar::_ready() {

	input = Input::get_singleton();
	_re_loader = ResourceLoader::get_singleton();
	_pre_loader = get_node<ResourcePreloader>("ResourcePreloader");
	_display_server = DisplayServer::get_singleton();
	
	_player = get_node<Player>("Player");
	_player->set_movement_limit(_scene_size);

	default_bullet = _re_loader->load("res://default_bullet.tscn");
	enemy_bee = _re_loader->load("res://enemy_bee.tscn");

	_pre_loader->add_resource("default_bullet", default_bullet);
	_pre_loader->add_resource("enemy_bee", enemy_bee);

	connect("game_restart", Callable(this, "game_restart_met"));
	connect("game_stop", Callable(this, "game_stop_met"));

	_player->connect(
			"player_attack",
			Callable(this, "player_attack_start"));
	_player->connect("player_died", Callable(this, "player_died"));

}

void CubicWar::game_restart() {
	_player->set_process_status(true);
	//TODO
}

void CubicWar::game_stop() {
	_player->set_process_status(false);
	//TODO
}

void CubicWar::_process(double delta) {
	if (input->is_action_pressed("game_restart")) {
		emit_signal("game_restart");
	} else if (input->is_action_pressed("game_stop")) {
		emit_signal("game_stop");
	}
}

void CubicWar::_physics_process(double delta) {

}

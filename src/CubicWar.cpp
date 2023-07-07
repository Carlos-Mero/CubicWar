#include "CubicWar.h"
#include <godot_cpp/classes/display_server.hpp>

using namespace godot;

void CubicWar::_bind_methods() {
}

CubicWar::CubicWar() {
}

CubicWar::~CubicWar() {
}

void CubicWar::game_init() {
	_display_server->mouse_set_mode(DisplayServer::MOUSE_MODE_HIDDEN);
}

Vector2 CubicWar::_scene_size = Vector2(720, 1280);

void CubicWar::_ready() {
	_display_server = DisplayServer::get_singleton();
}

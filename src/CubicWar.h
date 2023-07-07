#ifndef CUBIC_WAR_H
#define CUBIC_WAR_H

#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>

namespace godot {

class CubicWar : public Node2D {
	GDCLASS(CubicWar, Node2D)

	private:
		DisplayServer * _display_server;

	protected:
		static void _bind_methods();

	public:
		static Vector2 _scene_size;

		CubicWar();
		~CubicWar();

		void game_init();
		void _ready() override;
};

}

#endif

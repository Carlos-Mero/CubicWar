#ifndef ENEMY_H
#define ENEMY_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>

namespace godot {

class Enemy : public CharacterBody2D {
	GDCLASS(Enemy, CharacterBody2D)

	private:

	protected:
		static void _bind_methods();

	public:
		Enemy();
		~Enemy();

		void _ready() override;
		void _process(double delta) override;
		void _physics_process(double delta) override;
};

}

#endif

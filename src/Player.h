#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>

namespace godot {

class Player : public AnimatedSprite2D {
	GDCLASS(Player, AnimatedSprite2D)

	private:
		static const double max_speed;
		static const double default_weapon_coldown;

		bool stopped;
		double health;
		Vector2 speed;
		double weapon_coldown;

	protected:
		static void _bind_methods();

	public:
		Player();
		~Player();

		void start_processing() {stopped = false;}
		void stop_processing() {stopped = true;}
		void set_speed(const Vector2 &new_speed) {speed = new_speed;}
		Vector2 get_speed() const {return speed;}

		void default_weapon_attack();
		void being_attacked(const double damage);
		void died();

		void _ready() override;
		void _process(double delta) override;
};

}

#endif

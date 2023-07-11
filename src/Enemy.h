#ifndef ENEMY_H
#define ENEMY_H

#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>

namespace godot {

class Enemy : public RigidBody2D {
	GDCLASS(Enemy, RigidBody2D)

	private:
		static double default_weapon_coldown;
		static double contact_damage;
		double health;
		double m_default_weapon_coldown;

	protected:
		static void _bind_methods();

	public:
		Enemy();
		~Enemy();

		void set_health(const double n_health) {health = n_health;}
		double get_health() {return health;}
		void set_default_weapon_coldown (const double n_coldown) {
			default_weapon_coldown = n_coldown;
		}
		double get_default_weapon_coldown() const {
			return default_weapon_coldown;
		}

		void being_attacked(double damage);
		void cast_contact_damage(Node *target);
		void _ready() override;
		void _process(double delta) override;
		void _physics_process(double delta) override;
};

}

#endif

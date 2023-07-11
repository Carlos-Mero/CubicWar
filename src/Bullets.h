#ifndef BULLETS_H
#define BULLETS_H

#include "Enemy.h"

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>

namespace godot {

class Bullet : public Area2D {
	GDCLASS(Bullet, Area2D)

	private:

	protected:
		static void _bind_methods();

	public:
		Bullet();
		~Bullet();
};

class DefaultBullet : public Area2D {
	GDCLASS(DefaultBullet, Area2D)

	private:
		static Vector2 bspeed;
		static double damage;

	protected:
		static void _bind_methods();

	public:
		void cast_damage(Enemy * target);

		DefaultBullet();
		~DefaultBullet();

		void _ready() override;
		void m_free();
		void _physics_process(double delta) override;
};

class EnemyBeeBullet : public Area2D {
	GDCLASS(EnemyBeeBullet, Area2D)

	private:
		static const double damage;
		static const double speed_norm;
		Vector2 bspeed;

	protected:
		static void _bind_methods();

	public:
		EnemyBeeBullet();
		~EnemyBeeBullet();

		void _ready() override;
		void _physics_process(double delta) override;

};

}

#endif

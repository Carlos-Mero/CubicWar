#ifndef BULLETS_H
#define BULLETS_H

#include <godot_cpp/classes/physics_body2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>

namespace godot {

class Bullet : public PhysicsBody2D {
	GDCLASS(Bullet, PhysicsBody2D)

	private:
		Vector2 bspeed;

	protected:
		static void _bind_methods();

	public:
		Bullet();
		~Bullet();

		void _ready() override;
		void _physics_process(double delta) override;

};

}

#endif

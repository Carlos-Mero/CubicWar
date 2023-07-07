#include "Bullets.h"

using namespace godot;

void Bullet::_bind_methods() {

}

Bullet::Bullet() {
}

Bullet::~Bullet() {
}

void Bullet::_ready() {
}

void Bullet::_physics_process(double delta) {
	move_and_collide(bspeed);
}

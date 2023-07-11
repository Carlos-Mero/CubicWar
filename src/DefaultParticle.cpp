#include "DefaultParticle.h"

using namespace godot;

void GPUParticles2D_GC::_bind_methods() {
}

GPUParticles2D_GC::GPUParticles2D_GC() {
}

GPUParticles2D_GC::~GPUParticles2D_GC() {
}

void GPUParticles2D_GC::_process(double delta) {
	if (!is_emitting()) {
		queue_free();
	}
}

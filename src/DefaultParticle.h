#ifndef DEFAULT_PARTICLE_H
#define DEFAULT_PARTICLE_H

#include <godot_cpp/classes/gpu_particles2d.hpp>

namespace godot {

class GPUParticles2D_GC : public GPUParticles2D {
	GDCLASS(GPUParticles2D_GC, GPUParticles2D)

	private:

	protected:
		static void _bind_methods();

	public:
		GPUParticles2D_GC();
		~GPUParticles2D_GC();

		void _process(double delta) override;
};

}

#endif

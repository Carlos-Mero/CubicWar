#include "register_types.h"

#include "CubicWar.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullets.h"
#include "DefaultParticle.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_modules(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

		ClassDB::register_class<CubicWar>();
    ClassDB::register_class<Player>();
		ClassDB::register_class<Enemy>();
		ClassDB::register_class<Bullet>();
		ClassDB::register_class<GPUParticles2D_GC>();
		ClassDB::register_class<DefaultBullet>();
		ClassDB::register_class<EnemyBeeBullet>();

}

void uninitialize_modules(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT cubic_war_modules_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_modules);
    init_obj.register_terminator(uninitialize_modules);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}
}

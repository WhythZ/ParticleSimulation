#ifndef _PARTICLE_H_

#include <SDL.h>

#include "../Infrastructure/Vector2f.h"
#include "ParticleType.h"

struct Particle
{
	ParticleType type = ParticleType::EMPTY;  //1字节，粒子类型枚举

	Particle(ParticleType _type) : type(_type) {};
};

#endif
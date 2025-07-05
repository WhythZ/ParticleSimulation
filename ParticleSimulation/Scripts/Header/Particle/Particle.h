#ifndef _PARTICLE_H_

#include <SDL.h>

#include "../Infrastructure/Vector2f.h"
#include "ParticleType.h"

struct Particle
{
	bool isUpdatedThisFrame = false;          //1字节，粒子是否在本帧被更新过，避免重复更新同一粒子
	ParticleType type = ParticleType::EMPTY;  //1字节，粒子类型枚举

	Particle(ParticleType _type) : type(_type) {};
};

#endif
#ifndef _PARTICLE_H_

#include <SDL.h>

#include "../Infrastructure/Vector2f.h"
#include "ParticleType.h"

struct Particle
{
	bool updatedInThisFrame;                  //1字节，粒子是否在当前帧更新过
	ParticleType type = ParticleType::EMPTY;  //1字节，粒子类型枚举
	SDL_Color color;		                  //4字节，粒子渲染颜色（RGBA）
	float lifeTime;                           //4字节，粒子生命周期（单位s）
	Vector2f velocity;                        //8字节，粒子速度向量
};

#endif
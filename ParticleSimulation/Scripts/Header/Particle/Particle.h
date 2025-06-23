#ifndef _PARTICLE_H_

#include <cstdint> //uint8_t

#include <SDL.h>

#include "../Infrastructure/Vector2f.h"

//指定底层类型uint8_t使得Particle类成员ParticleType仅占用1字节空间
enum class ParticleType : uint8_t
{
	EMPTY,      //空

	DIRT,       //土
	STONE,      //岩
	WOOD,       //木
	ICE,        //冰

	SAND,       //沙
	SNOW,       //雪
	GUNPOWDER,  //药
	SALT,       //盐

	WATER,      //水
	OIL,        //油
	ACID,       //酸
	LAVA,       //熔

	FIRE,       //火

	SMOKE,      //烟
	STEAM       //汽
};

struct Particle
{
	bool updatedInThisFrame;                  //1字节，粒子是否在当前帧更新过
	ParticleType type = ParticleType::EMPTY;  //1字节，粒子类型枚举
	SDL_Color color;		                  //4字节，粒子渲染颜色（RGBA）
	float lifeTime;                           //4字节，粒子生命周期（单位s）
	Vector2f velocity;                        //8字节，粒子速度向量
};

#endif
#ifndef _PARTICLE_TYPE_H_
#define _PARTICLE_TYPE_H_

//uint8_t
#include <cstdint>

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

#endif
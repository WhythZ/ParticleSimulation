#ifndef _PARTICLE_TYPE_H_
#define _PARTICLE_TYPE_H_

//uint8_t
#include <cstdint>

//指定底层类型uint8_t使得Particle类成员ParticleType仅占用1字节空间
enum class ParticleType : uint8_t
{
	EMPTY = 0,      //空

	DIRT = 1,       //泥土
	STONE = 2,      //岩石
	WOOD = 3,       //木头
	ICE = 4,        //冰

	SAND = 5,       //沙
	SNOW = 6,       //雪
	GUNPOWDER = 7,  //火药

	WATER = 8,      //水
	OIL = 9,        //油
	ACID = 10,      //酸液
	LAVA = 11,      //岩浆

	FIRE = 12,      //火

	SMOKE = 13,     //烟
	STEAM = 14,     //蒸汽

	COUNT = 15      //表示枚举数量
};

#endif
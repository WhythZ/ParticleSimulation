#ifndef _PARTICLE_TYPE_H_
#define _PARTICLE_TYPE_H_

//uint8_t
#include <cstdint>

//ָ���ײ�����uint8_tʹ��Particle���ԱParticleType��ռ��1�ֽڿռ�
enum class ParticleType : uint8_t
{
	EMPTY,      //��

	DIRT,       //��
	STONE,      //��
	WOOD,       //ľ
	ICE,        //��

	SAND,       //ɳ
	SNOW,       //ѩ
	GUNPOWDER,  //ҩ
	SALT,       //��

	WATER,      //ˮ
	OIL,        //��
	ACID,       //��
	LAVA,       //��

	FIRE,       //��

	SMOKE,      //��
	STEAM       //��
};

#endif
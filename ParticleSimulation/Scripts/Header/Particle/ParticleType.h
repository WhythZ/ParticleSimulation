#ifndef _PARTICLE_TYPE_H_
#define _PARTICLE_TYPE_H_

//uint8_t
#include <cstdint>

//ָ���ײ�����uint8_tʹ��Particle���ԱParticleType��ռ��1�ֽڿռ�
enum class ParticleType : uint8_t
{
	EMPTY = 0,      //��

	DIRT = 1,       //����
	STONE = 2,      //��ʯ
	WOOD = 3,       //ľͷ
	ICE = 4,        //��

	SAND = 5,       //ɳ
	SNOW = 6,       //ѩ
	GUNPOWDER = 7,  //��ҩ

	WATER = 8,      //ˮ
	OIL = 9,        //��
	ACID = 10,      //��Һ
	LAVA = 11,      //�ҽ�

	FIRE = 12,      //��

	SMOKE = 13,     //��
	STEAM = 14,     //����

	COUNT = 15      //��ʾö������
};

#endif
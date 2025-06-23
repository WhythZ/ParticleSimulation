#ifndef _PARTICLE_H_

#include <cstdint> //uint8_t

#include <SDL.h>

#include "../Infrastructure/Vector2f.h"

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

struct Particle
{
	bool updatedInThisFrame;                  //1�ֽڣ������Ƿ��ڵ�ǰ֡���¹�
	ParticleType type = ParticleType::EMPTY;  //1�ֽڣ���������ö��
	SDL_Color color;		                  //4�ֽڣ�������Ⱦ��ɫ��RGBA��
	float lifeTime;                           //4�ֽڣ������������ڣ���λs��
	Vector2f velocity;                        //8�ֽڣ������ٶ�����
};

#endif
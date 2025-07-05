#ifndef _PARTICLE_H_

#include <SDL.h>

#include "../Infrastructure/Vector2f.h"
#include "ParticleType.h"

struct Particle
{
	bool isUpdatedThisFrame = false;          //1�ֽڣ������Ƿ��ڱ�֡�����¹��������ظ�����ͬһ����
	ParticleType type = ParticleType::EMPTY;  //1�ֽڣ���������ö��

	Particle(ParticleType _type) : type(_type) {};
};

#endif
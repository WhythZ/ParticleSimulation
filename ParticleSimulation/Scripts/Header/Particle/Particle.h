#ifndef _PARTICLE_H_

#include <SDL.h>

#include "../Infrastructure/Vector2f.h"
#include "ParticleType.h"

struct Particle
{
	bool updatedInThisFrame;                  //1�ֽڣ������Ƿ��ڵ�ǰ֡���¹�
	ParticleType type = ParticleType::EMPTY;  //1�ֽڣ���������ö��
	SDL_Color color;		                  //4�ֽڣ�������Ⱦ��ɫ��RGBA��
	float lifeTime;                           //4�ֽڣ������������ڣ���λs��
	Vector2f velocity;                        //8�ֽڣ������ٶ�����
};

#endif
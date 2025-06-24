#ifndef _PARTICLE_MANAGER_H_

#include <unordered_map>
#include <random>
#include <functional>

#include <SDL.h>

#include "../Manager.hpp"
#include "../../Particle/Particle.h"

class ParticleManager :public Manager<ParticleManager>
{
	friend class Manager<ParticleManager>;

public:
	std::unordered_map<ParticleType, SDL_Color> particleColors;

private:
	SDL_Rect windowRect;                              //���ھ������򣨴�GameManager����ȡ��

	#pragma region DoubleBuffer
	Particle* frontBuffer = nullptr;                  //��ǰ֡����״̬��˫���弼����
	Particle* backBuffer = nullptr;                   //��һ֡����״̬��˫���弼����
	#pragma endregion

	#pragma region RandomEngine
	std::mt19937 rng;                                 //�����������
	std::uniform_int_distribution<int> dist{ 0, 1 };  //�����������ѡ��
	#pragma endregion

public:
	void OnUpdate(double);
	void OnRender(SDL_Renderer*);

	void AddParticle(int, int, ParticleType);
	void RemoveParticle(int, int);
	void ClearParticles();

private:
	ParticleManager();
	~ParticleManager();

	void SwapBuffers();                               //����˫����

	Particle GetParticle(int, int) const;
	bool IsValidPosition(int, int) const;             //���λ���Ƿ���Ч

	#pragma region UpdateSpecificParticleType
	void UpdateEmpty(int, int);

	void UpdateDirt(int, int);
	void UpdateStone(int, int);
	void UpdateWood(int, int);
	void UpdateIce(int, int);

	void UpdateSand(int, int);
	void UpdateSnow(int, int);
	void UpdateGunPowder(int, int);
	void UpdateSalt(int, int);

	void UpdateWater(int, int);
	void UpdateOil(int, int);
	void UpdateAcid(int, int);
	void UpdateLava(int, int);

	void UpdateFire(int, int);

	void UpdateSmoke(int, int);
	void UpdateSteam(int, int);
	#pragma endregion
};

#endif
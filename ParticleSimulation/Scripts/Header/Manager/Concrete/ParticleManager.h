#ifndef _PARTICLE_MANAGER_H_

#include <random>
#include <functional>
#include <vector>

#include <SDL.h>

#include "../Manager.hpp"
#include "../../Particle/Particle.h"

class ParticleManager :public Manager<ParticleManager>
{
	friend class Manager<ParticleManager>;

private:
	SDL_Rect windowRect;                              //���ھ������򣨴�GameManager����ȡ��

	#pragma region DoubleBuffer
	//�����Ķ�ά�������ܸ���������������ڴ������Ե͵���֡�ʵͣ�Ӧת��һά����
	//std::vector<std::vector<Particle>> frontBuffer;
	//std::vector<std::vector<Particle>> backBuffer;

	std::vector<Particle> frontBuffer;                //��ǰ֡����״̬��˫���弼����
	std::vector<Particle> backBuffer;                 //��һ֡����״̬��˫���弼����
	#pragma endregion

	#pragma region RandomEngine
	std::mt19937 rng;                                 //�����������
	std::uniform_int_distribution<int> dist{ 0, 1 };  //�����������ѡ��
	#pragma endregion

public:
	void OnUpdate(double);                            //˫���������Ļ����
	void OnRender(SDL_Renderer*);

	void SetParticleAt(int, int, ParticleType);
	void EmptizeParticleAt(int, int);

private:
	ParticleManager();
	~ParticleManager();

	void UpdateParticle(int, int);

	bool IsValidPosition(int, int) const;             //��������Ƿ��ڴ��ڷ�Χ��

	#pragma region UpdateSpecificParticleType
	//void UpdateEmpty(int, int);

	void UpdateDirt(int, int);
	void UpdateStone(int, int);
	void UpdateWood(int, int);
	void UpdateIce(int, int);

	void UpdateSand(int, int);
	void UpdateSnow(int, int);
	void UpdateGunPowder(int, int);

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
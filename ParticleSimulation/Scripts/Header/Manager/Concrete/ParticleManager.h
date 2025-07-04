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
	SDL_Rect windowRect;                              //窗口矩形区域（从GameManager处获取）

	#pragma region DoubleBuffer
	//这样的二维数组虽能更方便地索引，但内存连续性低导致帧率低，应转用一维数组
	//std::vector<std::vector<Particle>> frontBuffer;
	//std::vector<std::vector<Particle>> backBuffer;

	std::vector<Particle> frontBuffer;                //当前帧粒子状态（双缓冲技术）
	std::vector<Particle> backBuffer;                 //下一帧粒子状态（双缓冲技术）
	#pragma endregion

	#pragma region RandomEngine
	std::mt19937 rng;                                 //随机数生成器
	std::uniform_int_distribution<int> dist{ 0, 1 };  //用于随机方向选择
	#pragma endregion

public:
	void OnUpdate(double);                            //双缓冲更新屏幕画面
	void OnRender(SDL_Renderer*);

	void SetParticleAt(int, int, ParticleType);
	void EmptizeParticleAt(int, int);

private:
	ParticleManager();
	~ParticleManager();

	void UpdateParticle(int, int);

	bool IsValidPosition(int, int) const;             //检查坐标是否在窗口范围内

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
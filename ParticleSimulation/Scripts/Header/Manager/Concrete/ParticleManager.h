#ifndef _PARTICLE_MANAGER_H_

#include <random>
#include <functional>

#include <SDL.h>

#include "../Manager.hpp"
#include "../../Particle/Particle.h"

class ParticleManager :public Manager<ParticleManager>
{
	friend class Manager<ParticleManager>;

private:
	SDL_Rect windowRect;                              //窗口矩形区域（从GameManager处获取）

	#pragma region DoubleBuffer
	Particle* frontBuffer = nullptr;                  //当前帧粒子状态（双缓冲技术）
	Particle* backBuffer = nullptr;                   //下一帧粒子状态（双缓冲技术）
	#pragma endregion

	#pragma region RandomEngine
	std::mt19937 rng;                                 //随机数生成器
	std::uniform_int_distribution<int> dist{ 0, 1 };  //用于随机方向选择
	#pragma endregion

public:
	void OnUpdate(double);                            //双缓冲更新屏幕画面
	void OnRender(SDL_Renderer*);

	void AddParticle(int, int, ParticleType);
	void RemoveParticle(int, int);
	void ClearAllParticles();

private:
	ParticleManager();
	~ParticleManager();

	Particle GetParticle(int, int) const;             //获取坐标位置的粒子对象引用
	bool IsValidPosition(int, int) const;             //检查坐标是否在游戏窗口内部

	#pragma region UpdateSpecificParticleType
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
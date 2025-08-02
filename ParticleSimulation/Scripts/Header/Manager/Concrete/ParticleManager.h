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

	void BrushParticleAt(int, int, ParticleType);     //在前缓冲区绘制粒子类型
	void EmptizeParticleAt(int, int);

private:
	ParticleManager();
	~ParticleManager();

	inline void UpdateParticleAt(int, int);
	inline void WriteParticleAt(int, int, ParticleType);

	inline bool IsValidPosition(int, int) const;      //检查坐标是否在窗口范围内
	inline bool IsEmptyPType(int, int) const;         //检坐标上粒子是否是空粒子
	inline bool IsSolidPType(int, int) const;         //检坐标上粒子是否是固体粒子
	inline bool IsPowderPType(int, int) const;        //检坐标上粒子是否是粉末粒子
	inline bool IsLiquidPType(int, int) const;        //检坐标上粒子是否是液体粒子
	inline bool IsSpreadPType(int, int) const;        //检坐标上粒子是否是蔓延粒子
	inline bool IsGasPType(int, int) const;           //检坐标上粒子是否是气体粒子

	#pragma region UpdateSolid
	void UpdateDirt(int, int);
	void UpdateStone(int, int);
	void UpdateWood(int, int);
	void UpdateIce(int, int);
	#pragma endregion

	#pragma region UpdatePowder
	void UpdateSand(int, int);
	void UpdateSnow(int, int);
	void UpdateGunPowder(int, int);
	#pragma endregion

	#pragma region UpdateLiquid
	void UpdateWater(int, int);
	void UpdateOil(int, int);
	void UpdateAcid(int, int);
	void UpdateLava(int, int);
	#pragma endregion

	#pragma region UpdateSpread
	void UpdateFire(int, int);
	#pragma endregion

	#pragma region UpdateGas
	void UpdateSmoke(int, int);
	void UpdateSteam(int, int);
	#pragma endregion
};

#endif
#include "../../../Header/Manager/Concrete/ParticleManager.h"

void ParticleManager::OnUpdate(double _delta)
{
	//每个像素点代表一个粒子，遍历屏幕中的像素点更新每个粒子的状态
}

void ParticleManager::OnRender(SDL_Renderer* _renderer)
{
	//渲染每个像素点对应的粒子为一个特定颜色，并调整Gamma值模拟光影效果等
}

#pragma region UpdateSpecificParticleType
void ParticleManager::UpdateEmpty()
{
}

void ParticleManager::UpdateDirt()
{
}

void ParticleManager::UpdateStone()
{
}

void ParticleManager::UpdateWood()
{
}

void ParticleManager::UpdateIce()
{
}

void ParticleManager::UpdateSand()
{
}

void ParticleManager::UpdateSnow()
{
}

void ParticleManager::UpdateGunPowder()
{
}

void ParticleManager::UpdateSalt()
{
}

void ParticleManager::UpdateWater()
{
}

void ParticleManager::UpdateOil()
{
}

void ParticleManager::UpdateAcid()
{
}

void ParticleManager::UpdateLava()
{
}

void ParticleManager::UpdateFire()
{
}

void ParticleManager::UpdateSmoke()
{
}

void ParticleManager::UpdateSteam()
{
}
#pragma endregion
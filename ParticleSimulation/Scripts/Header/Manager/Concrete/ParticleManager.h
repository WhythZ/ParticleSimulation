#ifndef _PARTICLE_MANAGER_H_

#include <SDL.h>

#include "../Manager.hpp"
#include "../../Particle/Particle.h"

class ParticleManager :public Manager<ParticleManager>
{
	friend class Manager<ParticleManager>;

private:


public:
	void OnUpdate(double);
	void OnRender(SDL_Renderer*);

private:
	ParticleManager() = default;
	~ParticleManager() = default;

	#pragma region UpdateSpecificParticleType
	void UpdateEmpty();

	void UpdateDirt();
	void UpdateStone();
	void UpdateWood();
	void UpdateIce();

	void UpdateSand();
	void UpdateSnow();
	void UpdateGunPowder();
	void UpdateSalt();

	void UpdateWater();
	void UpdateOil();
	void UpdateAcid();
	void UpdateLava();

	void UpdateFire();

	void UpdateSmoke();
	void UpdateSteam();
	#pragma endregion
};

#endif
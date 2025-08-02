#ifndef _UIW_CLEAR_ALL_PARTICLES_BUTTON_H_
#define _UIW_CLEAR_ALL_PARTICLES_BUTTON_H_

#include "../UIWidget.h"

class UIW_ClearAllParticlesButton :public UIWidget
{
public:
	UIW_ClearAllParticlesButton() = default;
	~UIW_ClearAllParticlesButton() = default;

	void OnInput(const SDL_Event&) override;
	void OnUpdate(SDL_Renderer*) override;
	void OnRender(SDL_Renderer*) override;
};

#endif
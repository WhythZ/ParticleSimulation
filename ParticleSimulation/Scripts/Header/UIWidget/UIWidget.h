#ifndef _UI_WIDGET_H_
#define _UI_WIDGET_H_

#include <SDL.h>
#include <string>

class UIWidget
{
public:
	UIWidget();
	~UIWidget();

	virtual void OnInput(const SDL_Event&);
	virtual void OnUpdate(SDL_Renderer*);
	virtual void OnRender(SDL_Renderer*);
};

#endif
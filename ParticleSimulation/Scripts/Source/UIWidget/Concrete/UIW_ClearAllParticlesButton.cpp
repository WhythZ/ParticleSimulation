#include "../../../header/UIWidget/Concrete/UIW_ClearAllParticlesButton.h"

#include "../../../Header/Manager/Concrete/UIManager.h"

void UIW_ClearAllParticlesButton::OnInput(const SDL_Event& _event)
{
	UIWidget::OnInput(_event);

	//获取鼠标指针位置
	static const UIManager& _ui = UIManager::Instance();
	const SDL_Point& _cursorPosition = _ui.cursorPosition;

	//突然不想做了，放着吧先
}

void UIW_ClearAllParticlesButton::OnUpdate(SDL_Renderer* _renderer)
{
	UIWidget::OnUpdate(_renderer);
}

void UIW_ClearAllParticlesButton::OnRender(SDL_Renderer* _renderer)
{
	UIWidget::OnRender(_renderer);
}
#include "../Header/Manager/Concrete/GameManager.h"

//将此宏定义，否则main函数在预处理阶段会被define为SDL_main
#define SDL_MAIN_HANDLED

int main(int _argc, char** _argv)
{
	return GameManager::Instance().Run(_argc, _argv);
}
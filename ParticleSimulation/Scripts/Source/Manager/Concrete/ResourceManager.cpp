#include "../../../Header/Manager/Concrete/ResourceManager.h"

bool ResourceManager::LoadResource(SDL_Renderer* _renderer)
{
	//if (!LoadTextureRes(_renderer)) return false;
	//if (!LoadMusicRes()) return false;
	//if (!LoadSoundRes()) return false;
	if (!LoadFontRes()) return false;

	return true;
}

//const TexturePool& ResourceManager::GetTexturePool()
//{
//	return texturePool;
//}
//
//const MusicPool& ResourceManager::GetMusicPool()
//{
//	return musicPool;
//}
//
//const SoundPool& ResourceManager::GetSoundPool()
//{
//	return soundPool;
//}

const FontPool& ResourceManager::GetFontPool()
{
	return fontPool;
}

//bool ResourceManager::LoadTextureRes(SDL_Renderer* _renderer)
//{
//	//因为此处我们无需用到SDL_Surface*对象，所以可以直接使用IMG_LoadTexture()方法省略将两个步骤合一
//	//SDL_Surface* _imgSurface = IMG_Load("Assets/xx.jpg");                             //从外存加载到内存（内存结构体）
//	//SDL_Texture* _imgTexture = SDL_CreateTextureFromSurface(_renderer, _imgSurface);  //从内存加载到显存（GPU纹理数据）
//
//	//将图片资源加载存储在图像池（unordered_map类型的容器）
//	texturePool[TextureResID::Player_Dragon] = IMG_LoadTexture(_renderer, "Assets/Sprites/Player/PlayerDragon/Player_Dragon.png");
//
//	//检查unordered_map容器中所有键值对的值是否有效；其中auto是自动类型推导，成员second访问的是键值对的值
//	for (const auto& _pair : texturePool)
//		if (!_pair.second) return false;
//	//检查无误就返回加载成功
//	return true;
//}

//bool ResourceManager::LoadMusicRes()
//{
//	//从文件中加载音乐
//	musicPool[MusicResID::BGM_InLevel_0] = Mix_LoadMUS("Assets/Audios/Musics/BGM_InLevel_0.flac");
//
//	//检查unordered_map容器中所有键值对的值是否有效；其中auto是自动类型推导，成员second访问的是键值对的值
//	for (const auto& _pair : musicPool)
//		if (!_pair.second) return false;
//	//检查无误就返回加载成功
//	return true;
//}

//bool ResourceManager::LoadSoundRes()
//{
//	//从文件中加载音效
//	soundPool[SoundResID::Player_Dragon_Skill_Flash] = Mix_LoadWAV("Assets/Audios/Sounds/Player_Dragon_Skill_Flash.wav");
//
//	//检查unordered_map容器中所有键值对的值是否有效；其中auto是自动类型推导，成员second访问的是键值对的值
//	for (const auto& _pair : soundPool)
//		if (!_pair.second) return false;
//	//检查无误就返回加载成功
//	return true;
//}

bool ResourceManager::LoadFontRes()
{
	//从文件中加载字体
	fontPool[FontResID::FusionPixel_12px_EN] = TTF_OpenFont("Assets/Fonts/fusion-pixel-12px-proportional-latin.ttf", 24);
	fontPool[FontResID::FusionPixel_12px_CN] = TTF_OpenFont("Assets/Fonts/fusion-pixel-12px-proportional-zh_hans.ttf", 24);

	//检查unordered_map容器中所有键值对的值是否有效；其中auto是自动类型推导，成员second访问的是键值对的值
	for (const auto& _pair : fontPool)
		if (!_pair.second) return false;
	//检查无误就返回加载成功
	return true;
}
#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <unordered_map>

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "../Manager.hpp"

//enum class TextureResID {};
//enum class MusicResID {};
//enum class SoundResID {};

enum class FontResID
{
	FusionPixel_12px_EN,
	FusionPixel_12px_CN
};

//typedef std::unordered_map<TextureResID, SDL_Texture*> TexturePool;
//typedef std::unordered_map<MusicResID, Mix_Music*> MusicPool;
//typedef std::unordered_map<SoundResID, Mix_Chunk*> SoundPool;
typedef std::unordered_map<FontResID, TTF_Font*> FontPool;

//游戏资产管理器
class ResourceManager :public Manager<ResourceManager>
{
	friend class Manager<ResourceManager>;

private:
	//TexturePool texturePool;              //图像享元池
	//MusicPool musicPool;                  //音乐享元池
	//SoundPool soundPool;                  //音效享元池
	FontPool fontPool;                      //字体享元池

public:
	bool LoadResource(SDL_Renderer*);       //加载所有资源

	//const TexturePool& GetTexturePool();  //获取只读图像享元池
	//const MusicPool& GetMusicPool();      //获取只读音频享元池
	//const SoundPool& GetSoundPool();      //获取只读音效享元池
	const FontPool& GetFontPool();          //获取只读图像享元池

private:
	ResourceManager() = default;
	~ResourceManager() = default;

	//bool LoadTextureRes(SDL_Renderer*);   //从文件中加载图像资产
	//bool LoadMusicRes();                  //从文件中加载音乐资产
	//bool LoadSoundRes();                  //从文件中加载音效资产
	bool LoadFontRes();                     //从文件中加载字体资产
};

#endif

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

//��Ϸ�ʲ�������
class ResourceManager :public Manager<ResourceManager>
{
	friend class Manager<ResourceManager>;

private:
	//TexturePool texturePool;              //ͼ����Ԫ��
	//MusicPool musicPool;                  //������Ԫ��
	//SoundPool soundPool;                  //��Ч��Ԫ��
	FontPool fontPool;                      //������Ԫ��

public:
	bool LoadResource(SDL_Renderer*);       //����������Դ

	//const TexturePool& GetTexturePool();  //��ȡֻ��ͼ����Ԫ��
	//const MusicPool& GetMusicPool();      //��ȡֻ����Ƶ��Ԫ��
	//const SoundPool& GetSoundPool();      //��ȡֻ����Ч��Ԫ��
	const FontPool& GetFontPool();          //��ȡֻ��ͼ����Ԫ��

private:
	ResourceManager() = default;
	~ResourceManager() = default;

	//bool LoadTextureRes(SDL_Renderer*);   //���ļ��м���ͼ���ʲ�
	//bool LoadMusicRes();                  //���ļ��м��������ʲ�
	//bool LoadSoundRes();                  //���ļ��м�����Ч�ʲ�
	bool LoadFontRes();                     //���ļ��м��������ʲ�
};

#endif

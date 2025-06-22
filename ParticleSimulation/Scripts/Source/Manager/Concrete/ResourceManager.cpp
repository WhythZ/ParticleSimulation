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
//	//��Ϊ�˴����������õ�SDL_Surface*�������Կ���ֱ��ʹ��IMG_LoadTexture()����ʡ�Խ����������һ
//	//SDL_Surface* _imgSurface = IMG_Load("Assets/xx.jpg");                             //�������ص��ڴ棨�ڴ�ṹ�壩
//	//SDL_Texture* _imgTexture = SDL_CreateTextureFromSurface(_renderer, _imgSurface);  //���ڴ���ص��Դ棨GPU�������ݣ�
//
//	//��ͼƬ��Դ���ش洢��ͼ��أ�unordered_map���͵�������
//	texturePool[TextureResID::Player_Dragon] = IMG_LoadTexture(_renderer, "Assets/Sprites/Player/PlayerDragon/Player_Dragon.png");
//
//	//���unordered_map���������м�ֵ�Ե�ֵ�Ƿ���Ч������auto���Զ������Ƶ�����Աsecond���ʵ��Ǽ�ֵ�Ե�ֵ
//	for (const auto& _pair : texturePool)
//		if (!_pair.second) return false;
//	//�������ͷ��ؼ��سɹ�
//	return true;
//}

//bool ResourceManager::LoadMusicRes()
//{
//	//���ļ��м�������
//	musicPool[MusicResID::BGM_InLevel_0] = Mix_LoadMUS("Assets/Audios/Musics/BGM_InLevel_0.flac");
//
//	//���unordered_map���������м�ֵ�Ե�ֵ�Ƿ���Ч������auto���Զ������Ƶ�����Աsecond���ʵ��Ǽ�ֵ�Ե�ֵ
//	for (const auto& _pair : musicPool)
//		if (!_pair.second) return false;
//	//�������ͷ��ؼ��سɹ�
//	return true;
//}

//bool ResourceManager::LoadSoundRes()
//{
//	//���ļ��м�����Ч
//	soundPool[SoundResID::Player_Dragon_Skill_Flash] = Mix_LoadWAV("Assets/Audios/Sounds/Player_Dragon_Skill_Flash.wav");
//
//	//���unordered_map���������м�ֵ�Ե�ֵ�Ƿ���Ч������auto���Զ������Ƶ�����Աsecond���ʵ��Ǽ�ֵ�Ե�ֵ
//	for (const auto& _pair : soundPool)
//		if (!_pair.second) return false;
//	//�������ͷ��ؼ��سɹ�
//	return true;
//}

bool ResourceManager::LoadFontRes()
{
	//���ļ��м�������
	fontPool[FontResID::Ipix] = TTF_OpenFont("Assets/Fonts/Ipix.ttf", 25);

	//���unordered_map���������м�ֵ�Ե�ֵ�Ƿ���Ч������auto���Զ������Ƶ�����Աsecond���ʵ��Ǽ�ֵ�Ե�ֵ
	for (const auto& _pair : fontPool)
		if (!_pair.second) return false;
	//�������ͷ��ؼ��سɹ�
	return true;
}
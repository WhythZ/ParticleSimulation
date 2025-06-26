#include "../../../Header/Manager/Concrete/GameManager.h"

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "../../../Header/Manager/Concrete/ResourceManager.h"
#include "../../../Header/Manager/Concrete/ParticleManager.h"
#include "../../../Header/Manager/Concrete/UIManager.h"

const char* WINDOW_TITLE = "ParticleSimulation";  //���ڱ���
const int WINDOW_WIDTH = 1344;                    //���ڿ��
const int WINDOW_HEIGHT = 720;                    //���ڸ߶�
const int FPS = 120;                              //֡������

GameManager::GameManager()
{
	#pragma region SDL
	//��ʼ��SDL���������ϵͳ����ΪSDL_Init��������0��ʾ�ɹ������Դ˴���һ���������ȡ��
	InitAssert(!SDL_Init(SDL_INIT_EVERYTHING), u8"Failed To Init SDL");
	//��ʼ��SDL_ttf�⣻TTF_Init��������0��ʾ�ɹ�
	InitAssert(!TTF_Init(), u8"Failed To Init SDL_ttf");
	//��ʼ��SDL_image��ĸ�֧�ָ�ʽ��IMG_Init�������ط���ֵ��ʾ�ɹ�������ֱ�Ӵ��뼴��
	InitAssert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"Failed To Init SDL_image");
	//��ʼ��SDL_mixer���֧�ָ�ʽ��Mix_Init�������ط���ֵ��ʾ�ɹ�
	InitAssert(Mix_Init(MIX_INIT_MP3), u8"Failed To Init SDL_mixer");
	//�򿪻�������������Mix_OpenAudio(��Ƶ������, ������Ƶ��ʽ, ������, ��Ƶ���뻺������С)
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	#pragma endregion

	#pragma region Window&Renderer
	//����Ļ������ʾһ����������ض��ߴ��һ����ʽ�Ĵ���
	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	//��¼���ھ�������
	windowRect = { 0, 0, (int)WINDOW_WIDTH, (int)WINDOW_HEIGHT };
	//��ⴰ���Ƿ��ʼ���ɹ�
	InitAssert(window, u8"Failed To Create Window");

	//������Ⱦ��������window�ϣ���������λʹ����������Ⱦ����
	//SDL_RENDERER_ACCELERATED��Ӳ������
	//SDL_RENDERER_PRESENTVSYNC����ֱͬ������һ��Ϊ��������Ļ˺�ѣ������ڴ�����Ƶ֡������ʾ��ˢ���ʲ�ͬ��������ʾ����
	//SDL_RENDERER_TARGETTEXTURE������ȾĿ������Ϊ����������Ⱦ����ͼƬ���ٽ�ͼƬ��Ⱦ�����ڣ�������Ƭ��ͼ������
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	//�����Ⱦ���Ƿ��ʼ���ɹ�
	InitAssert(renderer, u8"Failed To Create Renderer");

	//ʹ���ڴ�SDL����ʱ�����������Ŀ�����ʾ��ѡ���б�����������л�ΪӢ�����뷨����Ϊ���������޷�����������
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
	#pragma endregion

	#pragma region LoadResource
	//������Դ
	InitAssert(ResourceManager::Instance().LoadResource(renderer), u8"Failed To Load Resources");
	#pragma endregion
}

GameManager::~GameManager()
{
	//ע������˳����������Ⱦ���봰��
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//����ͷſ�ĳ�ʼ�����ݣ���Ϊ���������������ڿ�����ڵ�
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

int GameManager::Run(int _argc, char** _argv)
{
	#pragma region LimitFPS
	//�˺�����ȡһ�������ܣ����Ƚϸߣ���ʱ�����������ص�ֵ����ʱ��������������Ϊ��ʱ������㣬ͨ����������Ƶ�ʲ�������
	Uint64 _lastCounter = SDL_GetPerformanceCounter();
	//Ƶ�ʼ�ÿһ��˼�ʱ���������ٴ�
	Uint64 _counterFreq = SDL_GetPerformanceFrequency();
	#pragma endregion

	//��Ϸ��ѭ��
	while (!isQuit)
	{
		#pragma region LimitFPS
		//��ȡ��ǰ�ļ�ʱ��������������������ѭ��ǰ�õ��ļ�ʱ����������
		Uint64 _currentCounter = SDL_GetPerformanceCounter();
		//�����ת��Ϊ˫���ȸ��㣬����Ƶ�ʵõ�ÿ��ѭ����ʱ��������λΪ�룩
		double _delta = (double)(_currentCounter - _lastCounter) / _counterFreq;
		//����ǰ�Ĵ�����Ϊ��㣬������һ��ѭ��
		_lastCounter = _currentCounter;
		//��̬��ʱ����֡�ʣ�����֡�ʳ������޶�ֵ����ô�ͽ������ʱ���ӳٵ���ֹ��ѭ��Ƶ�ʹ��죻����1000�ǽ���ת��Ϊ���룬��Ϊ�������λ̫������Ȳ���
		if (_delta * 1000 < 1000.0 / FPS)
			SDL_Delay((Uint32)(1000.0 / FPS - _delta * 1000));
		#pragma endregion

		//��ȡ�������¼��Ա�֤������������
		while (SDL_PollEvent(&event))
			OnInput();

		//���ݸ��¼��
		OnUpdate(_delta);

		#pragma region Render
		//ȷ����Ⱦ����ɫΪ���ڣ���͸����������RGB��ɫ��Alpha����¼ͼ���͸������Ϣ��256���Ҷȣ�
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		//ʹ���趨�Ĳ�͸����ɫ����������ڴﵽ������Ч��
		SDL_RenderClear(renderer);

		//�ھ���������׼���󣬽��о������Ⱦ��ͼ
		OnRender();
		//����Ⱦ�����ݸ��µ����ڻ�������
		SDL_RenderPresent(renderer);
		#pragma endregion
	}

	return 0;
}

void GameManager::InitAssert(bool _flag, const char* _errMsg)
{
	//�����ʼ���ɹ�����ô���·�����ֱ�ӷ���
	if (_flag) return;
	//�����ʼ��ʧ�ܣ���ô����SDL����һ��������Ϣ���ڣ��ú���(��Ϣ����, ���ڱ���, ��ϸ������Ϣ, ��Ϊ˭���Ӵ���)
	//���ĸ����������NULL����ô�����ڲ���Ϊ�Ӵ��ڣ������д��봰�ڣ���ô�����ڽ���Ϊ����Ĵ��ڵ��Ӵ��ڣ����Ӵ��ڲ��ص����������޷����û�����
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"Game Init Failed", _errMsg, window);
	//��-1������������
	exit(-1);
}

void GameManager::OnInput()
{
	//������ڵ��˳���ʱ������SDL_QUIT�¼�
	if (event.type == SDL_QUIT)
		isQuit = true;

	//����UI��������
	UIManager::Instance().OnInput(event);
}

void GameManager::OnUpdate(double _delta)
{
	//���¸�������
	ParticleManager::Instance().OnUpdate(_delta);
	//����UI����
	UIManager::Instance().OnUpdate(renderer);
}

void GameManager::OnRender()
{
	//��Ⱦ��������
	ParticleManager::Instance().OnRender(renderer);
	//��ȾUI����
	UIManager::Instance().OnRender(renderer);
}
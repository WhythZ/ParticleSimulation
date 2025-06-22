#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

//�ɼ̳е���Managerģ����ʵ��
template <typename M>
class Manager
{
public:
	static M& Instance();                          //��ȡ����ʵ������

protected:
	Manager() = default;
	~Manager() = default;
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
};

//ģ������ڱ�������ɣ��޷���������Դ�ļ��е�ʵ�֣���������ʵ�ֲ��ɲ��
template <typename M>
M& Manager<M>::Instance()
{
	//C++11�ľֲ���̬�������̰߳�ȫ��
	static M manager;
	return manager;
}

#endif

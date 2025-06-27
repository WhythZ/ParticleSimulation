#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

//可继承单例Manager模板类实现
template <typename M>
class Manager
{
public:
	//获取单例实例引用
	//此处懒汉实现保证了GameManager最先初始化，以确保其它依赖于GameManager的管理器在其后初始化
	static M& Instance();

protected:
	Manager() = default;
	~Manager() = default;
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
};

//模板编译在编译期完成，无法链接其它源文件中的实现，故声明与实现不可拆分
template <typename M>
M& Manager<M>::Instance()
{
	//C++11的局部静态变量是线程安全的
	static M manager;
	return manager;
}

#endif

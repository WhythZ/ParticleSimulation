#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

//可继承单例Manager模板类实现
template <typename M>
class Manager
{
public:
	static M& Instance();                          //获取单例实例引用

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

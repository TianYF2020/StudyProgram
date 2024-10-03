#include "ThreadClass.h"
#include "functional"
#include "memory"


typedef struct AdjustRGB_st
{
	int r, g, b;

	int& operator[](int index)
	{
		switch (index)
		{
		case 0:
			return this->r;
		case 1:
			return this->g;
		case 2:
			return this->b;
		default:
			throw std::out_of_range("out of index");
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const struct AdjustRGB_st& p) {
		os << "RGB(" << p.r << ", " << p.g << ", " << p.b << ")";
		return os;
	}
}AdjustRGB;

class CallState
{
public:
	CallState() { m_bindCallback = nullptr; m_State = 0; m_Value = 0; };
	~CallState() { m_bindCallback(m_State, m_Value); };
	void bindFuntion(std::function<int(int, float)>& cb) { m_bindCallback = cb; };
	int m_State;
	float m_Value;
	std::function<int(int, float)> m_bindCallback;
};



class C_Control
{
public:
	C_Control() {};
	~C_Control() {};

	int UpdataUIControl(int type, float value)
	{
		std::cout << "cb::C_Control:Class type = " << type << " out value = " << value << std::endl;
		return 0;
	}
};

//更新调用函数的更新
int UpdateUI(int type, float value)
{
	std::cout << "cb::function: type = " << type << " out value = " << value << std::endl;
	return 0;
}


//使用类进行更新 - 普通复制传值
void ThreadDealProces(AdjustRGB data, std::function<int(int, float)> cb)
{
	std::cout << "thread: " << data << std::endl;
	std::cout << "Tid = " << std::this_thread::get_id() << std::endl;
	//std::shared_ptr<CallState> state = make_shared<CallState>();
	std::unique_ptr<CallState> state = std::make_unique<CallState>();
	state->bindFuntion(cb);
	state->m_State = 1;
	state->m_Value = 2.2f;
	data.r = 128;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "End thread " << std::endl;
}

//使用类进行更新 引用传值
void ThreadDealProces_Quote(AdjustRGB &data,std::function<int(int,float)> &cb)
{
	std::cout << "thread: " << data << std::endl;
	std::cout << "Tid = " << std::this_thread::get_id() << std::endl;
	//std::shared_ptr<CallState> state = make_shared<CallState>();
	std::unique_ptr<CallState> state = std::make_unique<CallState>();
	state->bindFuntion(cb);
	state->m_State = 1;
	state->m_Value = 2.2f;
	data.r = 128;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "End thread " << std::endl;
}


// ******  1、 线程函数是普通函数
int TestThreadFunction()
{

	// 创建线程，把更新函数绑定进去，并传递数据
	AdjustRGB data;	// 传入的数据
	data = { 255,255,255 };
	std::thread adjust(ThreadDealProces, data, UpdateUI);
	adjust.join();
	std::cout << "Finish1: " << data << std::endl;
	std::cout << std::endl;

	// 创建线程把类中的更新函绑定进去，并传递数据
	C_Control ctrl;		// UI端来更细数据的
	data = { 0,0,0 };
	std::function<int(int,float)> cb = std::bind(&C_Control::UpdataUIControl, &ctrl, std::placeholders::_1, std::placeholders::_2);
	//ref() 指定是引用传值，对应要写上 &
	std::thread adjustClass(ThreadDealProces_Quote, std::ref(data), std::ref(cb));
	adjustClass.join();
	std::cout << "Finish2: " << data << std::endl;
	std::cout << std::endl;
	return 0;
}


// ****** 2、 线程函数是类中的函数
class MyClass {
public:
	// 类中的成员函数
	void MyFunction(int value) {
		std::cout << "Run funtion  value: " << value << std::endl;
	}
	void ThreadClassDeal(AdjustRGB data, std::function<int(int, float)> cb)
	{
		std::cout << "Class::thread: " << data << std::endl;
		std::cout << "Class::Tid = " << std::this_thread::get_id() << std::endl;
		std::unique_ptr<CallState> state = std::make_unique<CallState>();
		state->bindFuntion(cb);
		state->m_State = 1;
		state->m_Value = 2.2f;
		data.r = 128;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Class::End thread " << std::endl;
	}
};


int TestThreadClassFunction()
{
	C_Control ctrl;				// UI端来更细数据的
	AdjustRGB data = {0,0,0};	// 传入的数据
	MyClass obj;				// 创建类对象,里面有现成函数
	std::function<int(int, float)> cb = std::bind(&C_Control::UpdataUIControl, &ctrl, std::placeholders::_1, std::placeholders::_2);
	//ref() 指定是引用传值，对应要写上 &
	std::thread adjustClass(&MyClass::ThreadClassDeal, &obj, std::ref(data), std::ref(cb));
	// 创建线程并在线程中执行类的成员函数
	std::thread t(&MyClass::MyFunction, &obj, 42);  // 传递对象和参数
	adjustClass.join();
	t.join();  // 等待线程结束
	return 0;
}


void output(int i)
{
	std::cout << "tid=" << std::this_thread::get_id() << std::endl;
}

int TestBaseThread()
{
	for (uint8_t i = 0; i < 4; i++)
	{
		std::thread t(output, i);
		t.detach(); // 线程分离
	}
	getchar();
	return 0;
}




//线程同步的方式
//1,互斥锁 2.条件变量 3.信号量 4.原子操作

#include <mutex>

std::mutex mymutex;
int count = 0;

void increment_counter(int time)
{
	for(int i=0; i<time; i++)
	{
		mymutex.lock();
		count ++;
		std::cout << std::this_thread::get_id() << std::endl;
		mymutex.unlock();
	}
}

int TestMutex()
{
	std::thread t1(increment_counter,100);
	std::thread t2(increment_counter,100);
	t1.join();
	t2.join();
	return 0;
}
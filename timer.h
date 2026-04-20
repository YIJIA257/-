#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	//初始化计时器，使计时器可以重复使用
	void restart()
	{
		pass_time = 0;
		shotted = false;
	}

	//设置等待时间
	void set_wait_time(float val)
	{
		wait_time = val;
	}

	//设置计时器是否重复触发
	void set_one_shot(bool flag)
	{
		one_shot = flag;
	}

	//设置超时时的回调函数
	void set_on_timeout(std::function<void()> on_timeout)
	{
		this->on_timeout = on_timeout;
	}

	//设置停顿的开关
	void pause()
	{
		paused = true;
	}

	//取消暂停状态
	void resume()
	{
		paused = false;
	}

	//设置更新和渲染
	void on_update(float delta)
	{
		if (paused)
		{
			return;
		}

		pass_time += delta;
		if (pass_time >= wait_time)
		{
			bool can_shot = (!one_shot || (one_shot && !shotted));
			shotted = true;
			if (can_shot && on_timeout)
			{
				on_timeout();
			}
			pass_time -= wait_time;
		}
	}

private:

	//定义各数值，开关和回调函数
	float pass_time = 0;
	float wait_time = 0;
	bool paused = false;
	bool shotted = false;
	bool one_shot = false;
	std::function<void()> on_timeout;

};
#endif 
// !_TIMER_H_

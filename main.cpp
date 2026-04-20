#include "util.h"
#include "character_manager.h"
#include "resources_manager.h"
#include "collision_manager.h"
#include "bullet_time_manager.h"

#include <chrono>
#include <thread>
#include <graphics.h>

//将所有的头文件包含
static void draw_background()
{
	//先导入背景
	static IMAGE* img_background = ResourcesManager::instance()->find_image("background");
	static Rect rect_dst =
	{
		(getwidth() - img_background->getwidth()) / 2,
		//将照片裁剪后作为背景
		(getheight() - img_background->getheight()) / 2,
		img_background->getwidth(),
		img_background->getheight()
		//将高度和宽度确定
	};
	putimage_ex(img_background, &rect_dst);
	//将照片导入
}

static void draw_remain_hp()
{
	//获取当前的血量值
	static IMAGE* img_ui_heart = ResourcesManager::instance()->find_image("ui_heart");
	//并显示血量
	Rect rect_dst = { 0, 10, img_ui_heart->getwidth(), img_ui_heart->getheight() };
	for (int i = 0; i < CharacterManager::instance()->get_player()->get_hp(); i++)
	{
		rect_dst.x = 10 + i * 40;
		putimage_ex(img_ui_heart, &rect_dst);
		//获取并显示血量
	}
}

int main(int argc, char** argv)
{
    using namespace std::chrono;

	srand((unsigned int)time(NULL));

    HWND hwnd = initgraph(1280, 720/*, EW_SHOWCONSOLE*/);
    SetWindowText(hwnd, _T("Hollow Katana"));
    
	try
	{
		ResourcesManager::instance()->load();
		//尝试导入资源
	}
	catch (const LPCTSTR id)
	{
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("无法加载： % s"), id);
		//失败后的提示
		MessageBox(hwnd, err_msg, _T("资源加载失败"), MB_OK | MB_ICONERROR);
		//失败后的提示
		return -1;
	}

	play_audio(_T("bgm"), true);
	//将音频导入
    const nanoseconds frame_duration(1000000000 / 144);
    steady_clock::time_point last_tick = steady_clock::now();
	//时间点准备

	ExMessage msg;
	bool is_quit = false;
	//判断是否放弃
	BeginBatchDraw();

	while (!is_quit)
	{
		//开始游戏
		//并开始运行主程序
		while (peekmessage(&msg))
		{
			CharacterManager::instance()->on_input(msg);
		}

		steady_clock::time_point frame_start = steady_clock::now();
		duration<float> delta = duration<float>(frame_start - last_tick);

		//持续时间
		float scaled_delta = BulletTimeManager::instance()->on_update(delta.count());
		CharacterManager::instance()->on_update(scaled_delta);
		//角色的位置速度等实时更新和渲染
		CollisionManager::instance()->process_collide();
		//碰撞机等实时更新和渲染

		setbkcolor(RGB(0, 0, 0));
		cleardevice();
		//清空设置

		draw_background();
		//导入背景
		CharacterManager::instance()->on_render();
		//CollisionManager::instance()->on_debug_render();
		draw_remain_hp();
		FlushBatchDraw();

		last_tick = frame_start;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frame_start);

		if (sleep_duration > nanoseconds(0))
		{
			//沉睡时间设置
			std::this_thread::sleep_for(sleep_duration);
		}
	}

	EndBatchDraw();

    return 0;

}
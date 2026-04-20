#ifndef _UTIL_H_
#define _UTIL_H_

#include <graphics.h>

#pragma comment(lib, "WINMM.lib")
//链接了绘图函数需要的库文件
#pragma comment(lib, "MSIMG32.LIB")
//链接了音频播放需要的库文件

struct Rect
{
	int x, y;
	//记录矩形的位置
	int w, h;
	//记录矩形的宽高
};

//在一张图集上实现选择并展示一帧图画
inline void putimage_ex(IMAGE* img, const Rect* rect_dst, const Rect* rect_src = nullptr)
{
	static BLENDFUNCTION blend_func = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(GetImageHDC(GetWorkingImage()), rect_dst->x, rect_dst->y, rect_dst->w, rect_dst->h,
		GetImageHDC(img), rect_src ? rect_src->x : 0, rect_src ? rect_src->y : 0, rect_src ? rect_src->w : 
		img->getwidth(), rect_src ? rect_src->h : 
		img->getheight(), blend_func);
}

inline void load_audio(LPCTSTR path, LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("open %s alias %s"), path, id);
	//存储路径
	mciSendString(str_cmd, NULL, 0, NULL);
	//发送此MCI命令
}

inline void play_audio(LPCTSTR id, bool is_loop = false)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("play %s %s from 0"), id, is_loop ? _T("repeat") : _T(""));
	//存储路径与设置状态是否为循环播放
	mciSendString(str_cmd, NULL, 0, NULL);
	//发送此MCI命令
}

//只需要调整目标矩形就可以实现放大和缩放
inline void stop_audio(LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("stop %s"), id);
	mciSendString(str_cmd, NULL, 0, NULL);
	//发送此MCI命令
}

inline int range_random(int min_num, int max_num)
{
	return min_num + rand() % (max_num - min_num + 1);
}

#endif 
// !_UTIL_H_
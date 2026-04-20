#ifndef _ATLAS_H_
#define _ATLAS_H_

#include <vector>
#include <graphics.h>
//图集是资源层面的内容
//用来管理一套存在动画关系的图片素材
//方便对其进行统一的加载和存储

class Atlas
{
public:
	Atlas() = default;
	~Atlas() = default;

	//由于文件命名十分有规律
//在load文件内部使用格式化的字符串
//作为图片健在的路径
	void load(LPCTSTR path_template, int num)
	{
		img_list.clear();
		img_list.resize(num);

		TCHAR path_file[256];
		for (int i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path_template, i + 1);
			loadimage(&img_list[i], path_file);
		}
	}

	//对于像玩家动画这样一整个长条的素材图片
//将其进行拆分处理
	void clear()
	{
		img_list.clear();
	}
	//清除前一帧的动作

	int get_size() const
	{
		return (int)img_list.size();
	}
	//获取人物的图片大小

	IMAGE* get_image(int idx)
	{
		if (idx < 0 || idx >= img_list.size())
			return nullptr;

		return &img_list[idx];
	}
	//实现获取图片资源

	void add_image(const IMAGE& img)
	{
		img_list.push_back(img);
	}
	//实现增加图片资源

private:
	std::vector<IMAGE> img_list;
};

#endif // !_ATLAS_H_
//定义图集类实现对图片的管理
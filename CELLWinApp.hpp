#pragma once

#include <Windows.h>
#include <tchar.h>
#include <math.h>

#include <EGL/egl.h>
#include <gles2/gl2.h>

#include "freeImage/FreeImage.h"
#include "CELLFont.h"

#include "CELLMath.hpp"
#include "CELLShader.hpp"
#include "CELLFont.h"
#include "CELLRole.hpp"
#include "CELL3RDCamera.hpp"
#include "CELLMouseButton.hpp"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "mesh.h"
#include <iostream>
#include <sstream>
#include <fstream>
namespace   CELL
{
//文字的数量
#define LENGHT_TITLE	15
//纹理的数量
#define LENGHT_TEXTURE	4
//墙壁的数量
#define NUM_WALLS		12

#define NUM_GLOBAL_WIDTH	40
#define NUM_GLOBAL_HEIGHT	2000
	//const wchar_t content[] = L"如是我闻一时佛在毗耶离大林中重阁讲堂与大比丘众千二百五十人俱尔时世尊而与阿难于晨朝时着衣持钵入城乞食还归所止食竟洗漱收摄衣钵告阿难言汝可取我尼师坛来吾今当往遮波罗支提入定思惟作此言已即与阿难俱往彼处既至彼处阿难即便敷尼师坛于是世尊结跏";// 趺坐寂然思惟阿难尔时去佛不远亦于别处端坐入定世尊须臾从定而觉告阿难言此毗耶离优陀延支提瞿昙支提庵罗支提多子支提娑罗支提遮波罗支提此等支提甚可爱乐阿难四神足人尚能住寿满于一劫若减一劫如来今者有大神力岂当不能住寿一劫若减一劫尔时世尊既开如是可请之门";// 以语阿难阿难默然而不觉知世尊乃至殷勤三说阿难茫然犹不解悟不请如来住寿一劫若减一劫利益世间诸天人民所以者何";
	const wchar_t newcontent[LENGHT_TITLE][50]
		= {
			{L"真理惟一可靠的标准就是永远自相符合"},
			{L"时间是一切财富中最宝贵的财富"},
			{L"世界上一成不变的东西只有任何事物都是在不断变化的这条真理"},
			{L"相信谎言的人必将在真理之前毁灭"},
			{ L"爱情原如树叶一样在人忽视里绿了在忍耐里露出蓓蕾" },

			{ L"一件事实是一条没有性别的真理" },
			{ L"友谊是一棵可以庇荫的树" },
			{ L"真正的科学家应当是个幻想家谁不是幻想家谁就只能把自己称为实践家" },
			{ L"我读的书愈多就愈亲近世界愈明了生活的意义愈觉得生活的重要" },
			{ L"人生并不像火车要通过每个站似的经过每一个生活阶段人生总是直向前行走从不留下什么" },

			{ L"科学是到处为家的不过在任何不播种的地方是决不会得到丰收的" },
			{ L"没有人不爱惜他的生命但很少人珍视他的时间" },
			{ L"笨蛋自以为聪明聪明人才知道自己是笨蛋" },
			{ L"毫无经验的初恋是迷人的但经得起考验的爱情是无价的" },
			{ L"良好的健康状况和高度的身体训练是有效的脑力劳动的重要条件" }
	};

	class Rainbase
	{
	public :
		//std::string content;//记录文字内容
		unsigned count_rain;//记录有多少条要显示的
		unsigned global_width;
		unsigned global_height;
		struct Vertex
		{
			float x, y, z;
			float u, v;
			float r, g, b, a;
		};
		//将纹理中的汉字拆分成单独的个体
		struct list_font
		{
			wchar_t ch;
			unsigned index;//记录在当前纹理中的位置
			unsigned life_time;//记录经历过的时间
			unsigned count_time;//临时计数器1
			unsigned count_time2;
			unsigned char r;
			unsigned char g;
			unsigned char b;
		};
		//用于绘制纹理的结构体
		struct list_texture
		{
			unsigned textureId;//纹理ID
			unsigned speed;//纹理的速度
			unsigned index_text;//纹理的起始文字位置。
			std::vector<list_font> list;
			unsigned width;//矩形的宽
			unsigned height;//矩形的高			
		};
		//用于显示的矩形
		struct list_show
		{
			//Vertex position[4];//矩形的四个顶点的位置			
			list_texture index_textureid;//矩形的纹理索引
		};
		list_show show[LENGHT_TEXTURE];
		struct list_wall
		{
			Vertex position[4];//矩形的四个顶点的位置
			unsigned textureId;//纹理ID，这里只读取
		};
		std::vector<list_wall> mywall;

		Vertex _data_wall[NUM_WALLS][4]=
		{
			//1通道左侧
			{
				{ 0- NUM_GLOBAL_WIDTH * 3 / 2.0f,       NUM_GLOBAL_WIDTH  / 2.0f,				 	          0.0f,		0.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{ 0- NUM_GLOBAL_WIDTH * 3 / 2.0f,       NUM_GLOBAL_WIDTH  / 2.0f,		 -(float)NUM_GLOBAL_HEIGHT,		0.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{ 0- NUM_GLOBAL_WIDTH * 3 / 2.0f,       NUM_GLOBAL_WIDTH * 3 / 2.0f,						  0.0f,		1.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{ 0- NUM_GLOBAL_WIDTH * 3 / 2.0f,       NUM_GLOBAL_WIDTH * 3 / 2.0f,	 -(float)NUM_GLOBAL_HEIGHT,		1.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f }
			},
			{
				{ 0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,    0 - NUM_GLOBAL_WIDTH / 2.0f,		 			          0.0f,		0.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{ 0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,    0 - NUM_GLOBAL_WIDTH / 2.0f,		 -(float)NUM_GLOBAL_HEIGHT,		0.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{ 0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,        NUM_GLOBAL_WIDTH / 2.0f,							  0.0f,		1.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{ 0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,        NUM_GLOBAL_WIDTH / 2.0f,		 -(float)NUM_GLOBAL_HEIGHT,		1.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f }
			},
			{
				{ 0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,    0 - NUM_GLOBAL_WIDTH / 2.0f,							  0.0f,		0.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{ 0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,    0 - NUM_GLOBAL_WIDTH / 2.0f,	     -(float)NUM_GLOBAL_HEIGHT,		0.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{ 0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,    0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,					      0.0f,		1.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{ 0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,    0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,   -(float)NUM_GLOBAL_HEIGHT,		1.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f }
			},
			//1通道右侧
			{
				{  NUM_GLOBAL_WIDTH * 3 / 2.0f,       NUM_GLOBAL_WIDTH / 2.0f,				 	          0.0f,		0.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{  NUM_GLOBAL_WIDTH * 3 / 2.0f,       NUM_GLOBAL_WIDTH / 2.0f,		 -(float)NUM_GLOBAL_HEIGHT,		0.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{  NUM_GLOBAL_WIDTH * 3 / 2.0f,       NUM_GLOBAL_WIDTH * 3 / 2.0f,						  0.0f,		1.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{  NUM_GLOBAL_WIDTH * 3 / 2.0f,       NUM_GLOBAL_WIDTH * 3 / 2.0f,	 -(float)NUM_GLOBAL_HEIGHT,		1.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f }
			},
			{
				{  NUM_GLOBAL_WIDTH * 3 / 2.0f,    0 - NUM_GLOBAL_WIDTH / 2.0f,		 			          0.0f,		0.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{  NUM_GLOBAL_WIDTH * 3 / 2.0f,    0 - NUM_GLOBAL_WIDTH / 2.0f,		 -(float)NUM_GLOBAL_HEIGHT,		0.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{  NUM_GLOBAL_WIDTH * 3 / 2.0f,        NUM_GLOBAL_WIDTH / 2.0f,							  0.0f,		1.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{  NUM_GLOBAL_WIDTH * 3 / 2.0f,        NUM_GLOBAL_WIDTH / 2.0f,		 -(float)NUM_GLOBAL_HEIGHT,		1.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f }
			},
			{
				{  NUM_GLOBAL_WIDTH * 3 / 2.0f,    0 - NUM_GLOBAL_WIDTH / 2.0f,							  0.0f,		0.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{  NUM_GLOBAL_WIDTH * 3 / 2.0f,    0 - NUM_GLOBAL_WIDTH / 2.0f,	     -(float)NUM_GLOBAL_HEIGHT,		0.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{  NUM_GLOBAL_WIDTH * 3 / 2.0f,    0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,					      0.0f,		1.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{  NUM_GLOBAL_WIDTH * 3 / 2.0f,    0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,   -(float)NUM_GLOBAL_HEIGHT,		1.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f }
			},
			//1通道上侧
			{
				{ 0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,     NUM_GLOBAL_WIDTH * 3 / 2.0f,							  0.0f,		0.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{ 0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,     NUM_GLOBAL_WIDTH * 3 / 2.0f,	     -(float)NUM_GLOBAL_HEIGHT,		0.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{	  0 - NUM_GLOBAL_WIDTH / 2.0f,     NUM_GLOBAL_WIDTH * 3 / 2.0f,					          0.0f,		1.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{     0 - NUM_GLOBAL_WIDTH / 2.0f,     NUM_GLOBAL_WIDTH * 3 / 2.0f,      -(float)NUM_GLOBAL_HEIGHT,		1.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f }
			},
			{
				{	 0 - NUM_GLOBAL_WIDTH  / 2.0f,     NUM_GLOBAL_WIDTH * 3 / 2.0f,							  0.0f,		0.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{	 0 - NUM_GLOBAL_WIDTH  / 2.0f,     NUM_GLOBAL_WIDTH * 3 / 2.0f,	     -(float)NUM_GLOBAL_HEIGHT,		0.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{		 NUM_GLOBAL_WIDTH  / 2.0f,     NUM_GLOBAL_WIDTH * 3 / 2.0f,					          0.0f,		1.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{		 NUM_GLOBAL_WIDTH  / 2.0f,     NUM_GLOBAL_WIDTH * 3 / 2.0f,      -(float)NUM_GLOBAL_HEIGHT,		1.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f }
			},
			{
				{	     NUM_GLOBAL_WIDTH  / 2.0f,     NUM_GLOBAL_WIDTH * 3 / 2.0f,							  0.0f,		0.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{		 NUM_GLOBAL_WIDTH  / 2.0f,     NUM_GLOBAL_WIDTH * 3 / 2.0f,	     -(float)NUM_GLOBAL_HEIGHT,		0.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{	  NUM_GLOBAL_WIDTH * 3 / 2.0f,     NUM_GLOBAL_WIDTH * 3 / 2.0f,					          0.0f,		1.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{	  NUM_GLOBAL_WIDTH * 3 / 2.0f,     NUM_GLOBAL_WIDTH * 3 / 2.0f,      -(float)NUM_GLOBAL_HEIGHT,		1.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f }
			},
			//1通道下侧
			{
				{ 0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,     0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,							  0.0f,		0.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{ 0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,     0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,	     -(float)NUM_GLOBAL_HEIGHT,		0.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{	  0 - NUM_GLOBAL_WIDTH / 2.0f,     0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,					          0.0f,		1.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{	  0 - NUM_GLOBAL_WIDTH / 2.0f,     0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,      -(float)NUM_GLOBAL_HEIGHT,		1.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f }
			},
			{
				{	  0 - NUM_GLOBAL_WIDTH / 2.0f,     0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,							  0.0f,		0.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{	  0 - NUM_GLOBAL_WIDTH / 2.0f,     0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,	     -(float)NUM_GLOBAL_HEIGHT,		0.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{		  NUM_GLOBAL_WIDTH / 2.0f,     0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,					          0.0f,		1.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{		  NUM_GLOBAL_WIDTH / 2.0f,     0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,      -(float)NUM_GLOBAL_HEIGHT,		1.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f }
			},
			{
				{		  NUM_GLOBAL_WIDTH / 2.0f,     0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,							  0.0f,		0.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{		  NUM_GLOBAL_WIDTH / 2.0f,     0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,	     -(float)NUM_GLOBAL_HEIGHT,		0.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{	  NUM_GLOBAL_WIDTH * 3 / 2.0f,     0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,					          0.0f,		1.0f,0.0f,    1.0f, 1.0f, 1.0f,1.0f },
				{	  NUM_GLOBAL_WIDTH * 3 / 2.0f,     0 - NUM_GLOBAL_WIDTH * 3 / 2.0f,      -(float)NUM_GLOBAL_HEIGHT,		1.0f,1.0f,    1.0f, 1.0f, 1.0f,1.0f }
			}
		};
	public :
		Rainbase()
		{
			//*content = L"如是我闻一时佛在毗耶离大林中重阁讲堂与大比丘众千二百五十人俱尔时世尊而与阿难于晨朝时着衣持钵入城乞食还归所止食竟洗漱收摄衣钵告阿难言汝可取我尼师坛来吾今当往遮波罗支提入定思惟作此言已即与阿难俱往彼处既至彼处阿难即便敷尼师坛于是世尊结跏趺坐寂然思惟阿难尔时去佛不远亦于别处端坐入定世尊须臾从定而觉告阿难言此毗耶离优陀延支提瞿昙支提庵罗支提多子支提娑罗支提遮波罗支提此等支提甚可爱乐阿难四神足人尚能住寿满于一劫若减一劫如来今者有大神力岂当不能住寿一劫若减一劫尔时世尊既开如是可请之门以语阿难阿难默然而不觉知世尊乃至殷勤三说阿难茫然犹不解悟不请如来住寿一劫若减一劫利益世间诸天人民所以者何。其为魔王所迷惑故。尔时世尊。三说此语。犹见阿难心不开悟。即便默然。尔时魔王。来至佛所。而白佛言。世尊今者宜般涅槃。善逝今者宜般涅槃。所以者何。我于往昔在尼连禅河侧。劝请世尊入般涅槃。世尊尔时而见答言。我四部众。比丘比丘尼。优婆塞优婆夷。犹未具足。又未降伏诸余外道。所以未应入般涅槃。世尊今者四部之众。无不具足。又已降伏诸余外道。所为之事皆悉已毕。今者宜应入般涅槃。于时魔王如是三请。如来即便答言善哉。我于往昔。在尼连禅河侧。已自许汝。以四部众未具足故。所以至今。今已具足。却后三月当般涅槃。是时魔王。闻佛此语。欢喜踊跃。还归天宫。尔时世尊。即便舍寿。而以神力住命三月。是时大地十八相动。天鼓自鸣。以佛力故空中唱言。如来不久当般涅槃。诸天人众。忽闻此声。心大悲憹遍体血现。是时世尊。即于彼处。而说偈言。一切诸众生，皆随有生死。我今亦生死，而不随于有。一切造作行，我今欲弃舍。尔时世尊。说此偈已。默然而住。是时阿难。见大地动。心大惊怖。而自念言。今者何故忽有是相。如此之事非为小缘。我今当往咨问世尊。作此念已。即从座起。到于佛前。头面礼足白言。世尊我向于彼。别处思惟。忽见大地十八相动。又闻空中天鼓之声。心大怖惧。不知此相。是何因缘。佛言。阿难。大地震动。有八因缘。一者大地依于水住。又此大水依风轮住。又此风轮依虚空住。空中有时猛风大起。吹彼风轮。风轮既动。彼水亦动。彼水既动。大地乃动。二者比丘比丘尼优婆塞优婆夷。有修神通。始成就者。欲自试验。故大地动。三者菩萨在兜率天。将欲来下。降神母胎。故大地动。四者菩萨初生。从右胁出。故大地动。五者菩萨舍于王宫。出家学道。成一切种智。故大地动。六者如来成道。始为人天转妙法轮。故大地动。七者如来舍寿。以神通力住命而住。故大地动。八者如来般涅槃时。故大地动。阿难。当知地动因缘。有此八事。阿难。有八部众。一者刹利。二者婆罗门。三者长者居士。四者沙门。五者四天王。六者忉利天。七者魔王。八者梵王。此八部众。我观其根应得度者。随所现形。而为说法。彼亦不知是我所说。阿难。有八胜处。一者内有色想外观色少境界。二者内有色想外观色无量境界。三者内无色想外观色少境界。四者内无色想外观色无量境界。五者观一切色青。六者观一切色黄。七者观一切色赤。八者观一切色白。此是行者上胜之法。复次阿难。有八解脱。一者内有色想外观色。二者内无色想外观色不净思惟。三者净解脱。四者空处解脱。五者识处解脱。六者无所有处解脱。七者非想非非想处解脱。八者灭尽定解脱。此亦复是行者胜法。若能究竟此等法者。即于诸法。自在无碍。阿难。知不。我于往昔。初成道时。度优楼频螺迦叶。在尼连禅河侧。尔时魔王来至我所。而请我言。世尊。今者宜般涅槃。善逝。今者宜般涅槃。何以故。所应度者皆悉解脱。今者正是般涅槃时。如是三请。我即答言。今者未是般涅槃时。所以者何。我四部众未具足故。所应度者皆未究竟。诸外道众。又未降伏。如是三答。魔王闻已。心怀愁憹。即还天宫。向者又来。而请我言。世尊。今者宜般涅槃。善逝。今者宜般涅槃。所以者何。我于往昔。在尼连禅河侧。劝请世尊而般涅槃。世尊尔时即答我言。我四部众。比丘比丘尼。优婆塞优婆夷。犹未具足。又未降伏诸余外道。是以未应入般涅槃。世尊。今者四部之众。无不具足。又已降伏诸余外道。所为之事皆悉已毕。今者宜应入般涅槃。魔王乃至如是三请。我即答言。我于往昔。在尼连禅河侧。已自许汝。以四部众未具足故。所以至今。今已具足。却后三月。当般涅槃。魔王闻我作此语已。欢喜踊跃还归天宫。我既于此受魔请已。即便舍寿。住命三月。以是因缘。大地震动。尔时阿难闻佛此语。心大悲憹遍体血现。涕泣流泪。而白佛言。唯愿世尊。哀愍我等。住寿一劫。若减一劫。利益世间诸天人民。如是三请。尔时世尊。告阿难言。汝今非是请如来时。所以者何。我已许魔。却后三月。当般涅槃。汝今云何而请住耶。阿难。汝侍我来。颇曾闻我说二言不。阿难白佛。实不曾闻天人之师有二言也。我于往昔曾闻。世尊为四部众。而说法言。四神足人。则能住寿。满足一劫。若减一劫。况复如来。无量神力自在之王。今更不能住寿一劫。若减一劫。而便舍寿。住命三月。唯愿世尊。哀愍我等。住寿一劫。若减一劫。尔时世尊答阿难言。我今所以便舍寿者。正由汝故。所以者何。我前于此向汝说言。四神足人。尚能住寿。满足一劫。若减一劫。如来今者有大神力。岂当不能住寿一劫。若减一劫。乃至如是殷勤三说。开劝请门。而汝默然。曾不请我。住寿一劫。若减一劫。是故我今住命三月。汝今云何方请我住。尔时阿难闻佛此语。决定知佛入般涅槃不可劝请。心生苦痛。闷绝懊憹。泣涕流连。不能自胜。尔时世尊既见阿难生大苦憹。而以梵音安慰之言。阿难。汝今勿生忧悲。有为之法皆悉如是。一切合会无不别离。世尊即便而说偈言。";
			global_width = NUM_GLOBAL_WIDTH;
			global_height = NUM_GLOBAL_HEIGHT;
			for (int i = 0; i < LENGHT_TEXTURE; i++)
			{
				show[i].index_textureid.width = (int)global_width;
				show[i].index_textureid.height = (int)global_height;
				show[i].index_textureid.speed = (i%10)+2;
				show[i].index_textureid.index_text = i;
				show[i].index_textureid.textureId = 0;
				int tmpvalue = (int)(global_height / global_width);
				show[i].index_textureid.list.clear();

				//int aa = wcslen(newcontent[tmp.index_textureid.index_text]);
				
				for (int j = 0; j < tmpvalue; j++)
				{
					list_font font_tmp;
					font_tmp.index = j;
					font_tmp.life_time = 0;
					font_tmp.count_time = 0;
					font_tmp.count_time2 = 0;
					font_tmp.r = 255;
					font_tmp.g = 252;
					font_tmp.b = 255;					
					font_tmp.ch = newcontent[(show[i].index_textureid.index_text)% LENGHT_TITLE][font_tmp.index%wcslen(newcontent[(show[i].index_textureid.index_text) % LENGHT_TITLE])];
					show[i].index_textureid.list.push_back(font_tmp);
				}
			}

#pragma region 这里要生成地形图
			for(int i=0;i<NUM_WALLS;i++)
			{
				list_wall tmpwall;
				for (int j = 0; j < 4; j++)
				{
					tmpwall.position[j].x = _data_wall[i][j].x;
					tmpwall.position[j].y = _data_wall[i][j].y;
					tmpwall.position[j].z = _data_wall[i][j].z;
					tmpwall.position[j].u = _data_wall[i][j].u;
					tmpwall.position[j].v = _data_wall[i][j].v;
					tmpwall.position[j].r = _data_wall[i][j].r;
					tmpwall.position[j].g = _data_wall[i][j].g;
					tmpwall.position[j].b = _data_wall[i][j].b;
					tmpwall.position[j].a = _data_wall[i][j].a;
				}				
				mywall.push_back(tmpwall);
			}
			
#pragma endregion

		}
		~Rainbase()
		{
		
		}
	};


	class   CELLWinApp
	{
	public:
		struct LineVertex
		{
			float x, y;
			float r, g, b, a;
		};
		struct Vertex
		{
			float x, y, z;
			float u, v;
			float r, g, b, a;
		};
	public:
		//! 实例句柄
		HINSTANCE   _hInstance;
		//! 窗口句柄
		HWND        _hWnd;
		//! 窗口的高度
		int         _width;
		//! 窗口的宽度
		int         _height;
		/// for gles2.0
		EGLConfig   _config;
		EGLSurface  _surface;
		EGLContext  _context;
		EGLDisplay  _display;
		//! 增加shader
		PROGRAM_P2_AC4  _shader_font;
		unsigned        _textureId;
		CELLFont        _font;

		PROGRAM_P2_T2_C3    _shader_band;
		unsigned            _textureId_color;
		unsigned            _texDynamic;
		unsigned            _texGrass;
		unsigned            _vbo;
		unsigned            _indexbo;

		std::pair<unsigned, unsigned > _fBuf;

		unsigned			_width_texture;
		unsigned			_height_texture;

		Rainbase			_rain;
		CELL3RDCamera       _3rdcamera;
		Role                _role;
		bool                _rightButtonDown;
		float2              _mousePos;

		model				mymodel;
	public:
		CELLWinApp(HINSTANCE hInstance)
			:_hInstance(hInstance)
		{
			WNDCLASSEX  winClass;
			winClass.lpszClassName = _T("CELLWinApp");
			winClass.cbSize = sizeof(winClass);
			winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			winClass.lpfnWndProc = wndProc;
			winClass.hInstance = hInstance;
			winClass.hIcon = 0;
			winClass.hIconSm = 0;
			winClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
			winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
			winClass.lpszMenuName = NULL;
			winClass.cbClsExtra = 0;
			winClass.cbWndExtra = 0;
			RegisterClassEx(&winClass);
			_textureId_color = 0;
			_width_texture = _rain.global_width;
			_height_texture = _rain.global_height;


		}
		virtual ~CELLWinApp()
		{
			UnregisterClass(_T("CELLWinApp"), _hInstance);
		}
		/**
		*   初始化 OpenGLES2.0
		*/
		bool    initOpenGLES20()
		{
			const EGLint attribs[] =
			{
				EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
				EGL_BLUE_SIZE, 8,
				EGL_GREEN_SIZE, 8,
				EGL_RED_SIZE, 8,
				EGL_DEPTH_SIZE,24,
				EGL_NONE
			};
			EGLint 	format(0);
			EGLint	numConfigs(0);
			EGLint  major;
			EGLint  minor;

			//! 1
			_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

			//! 2init
			eglInitialize(_display, &major, &minor);

			//! 3
			eglChooseConfig(_display, attribs, &_config, 1, &numConfigs);

			eglGetConfigAttrib(_display, _config, EGL_NATIVE_VISUAL_ID, &format);
			//! 4 
			_surface = eglCreateWindowSurface(_display, _config, _hWnd, NULL);

			//! 5
			EGLint attr[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
			_context = eglCreateContext(_display, _config, 0, attr);
			//! 6
			if (eglMakeCurrent(_display, _surface, _surface, _context) == EGL_FALSE)
			{
				return false;
			}

			eglQuerySurface(_display, _surface, EGL_WIDTH, &_width);
			eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height);

			return  true;

		}
		/**
		*   销毁OpenGLES2.0
		*/
		void    destroyOpenGLES20()
		{
			if (_display != EGL_NO_DISPLAY)
			{
				eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
				if (_context != EGL_NO_CONTEXT)
				{
					eglDestroyContext(_display, _context);
				}
				if (_surface != EGL_NO_SURFACE)
				{
					eglDestroySurface(_display, _surface);
				}
				eglTerminate(_display);
			}
			_display = EGL_NO_DISPLAY;
			_context = EGL_NO_CONTEXT;
			_surface = EGL_NO_SURFACE;
		}


		virtual unsigned    createTexture(int width, int height)
		{
			unsigned    textureId;
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexImage2D(
				GL_TEXTURE_2D
				, 0
				, GL_RGB
				, width
				, height
				, 0
				, GL_RGB
				, GL_UNSIGNED_BYTE
				, 0);
			return  textureId;
		}
		virtual unsigned    buildMipMap(char* fileNames[], int size)
		{
			unsigned    textureId = 0;
			/**
			*   产生一个纹理Id,可以认为是纹理句柄，后面的操作将书用这个纹理id
			*/
			glGenTextures(1, &textureId);
			/**
			*   使用这个纹理id,或者叫绑定(关联)
			*/
			glBindTexture(GL_TEXTURE_2D, textureId);
			/**
			*   指定纹理的放大,缩小滤波，使用线性方式，即当图片放大的时候插值方式
			*/
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



			for (int i = 0; i < size; ++i)
			{
				//1 获取图片格式
				FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileNames[i], 0);

				//2 加载图片
				FIBITMAP    *dib = FreeImage_Load(fifmt, fileNames[i], 0);

				//3 转化为rgb 24色
				dib = FreeImage_ConvertTo24Bits(dib);



				//4 获取数据指针
				BYTE    *pixels = (BYTE*)FreeImage_GetBits(dib);

				int     width = FreeImage_GetWidth(dib);
				int     height = FreeImage_GetHeight(dib);

				for (int x = 0; x < width * height * 3; x += 3)
				{
					BYTE temp = pixels[x];
					pixels[x] = pixels[x + 2];
					pixels[x + 2] = temp;
				}


				/**
				*   将图片的rgb数据上传给opengl.
				*/
				glTexImage2D(
					GL_TEXTURE_2D,      //! 指定是二维图片
					i,              //! 指定为第一级别，纹理可以做mipmap,即lod,离近的就采用级别大的，远则使用较小的纹理
					GL_RGB,             //! 纹理的使用的存储格式
					width,              //! 宽度，老一点的显卡，不支持不规则的纹理，即宽度和高度不是2^n。
					height,             //! 宽度，老一点的显卡，不支持不规则的纹理，即宽度和高度不是2^n。
					0,                  //! 是否的边
					GL_RGB,             //! 数据的格式，bmp中，windows,操作系统中存储的数据是bgr格式
					GL_UNSIGNED_BYTE,   //! 数据是8bit数据
					pixels
				);

				FreeImage_Unload(dib);
			}

			return  textureId;
		}
		virtual unsigned    loadTexture(const char* fileName)
		{
			unsigned    textureId = 0;
			//1 获取图片格式
			FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileName, 0);

			//2 加载图片
			FIBITMAP    *dib = FreeImage_Load(fifmt, fileName, 0);

			//3 转化为rgb 24色
			dib = FreeImage_ConvertTo24Bits(dib);

			//4 获取数据指针
			BYTE    *pixels = (BYTE*)FreeImage_GetBits(dib);

			int     width = FreeImage_GetWidth(dib);
			int     height = FreeImage_GetHeight(dib);

			/**
			*   产生一个纹理Id,可以认为是纹理句柄，后面的操作将书用这个纹理id
			*/
			glGenTextures(1, &textureId);

			/**
			*   使用这个纹理id,或者叫绑定(关联)
			*/
			glBindTexture(GL_TEXTURE_2D, textureId);
			/**
			*   指定纹理的放大,缩小滤波，使用线性方式，即当图片放大的时候插值方式
			*/
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			/**
			*   将图片的rgb数据上传给opengl.
			*/
			glTexImage2D(
				GL_TEXTURE_2D,      //! 指定是二维图片
				0,                  //! 指定为第一级别，纹理可以做mipmap,即lod,离近的就采用级别大的，远则使用较小的纹理
				GL_RGB,             //! 纹理的使用的存储格式
				width,              //! 宽度，老一点的显卡，不支持不规则的纹理，即宽度和高度不是2^n。
				height,             //! 宽度，老一点的显卡，不支持不规则的纹理，即宽度和高度不是2^n。
				0,                  //! 是否的边
				GL_RGB,             //! 数据的格式，bmp中，windows,操作系统中存储的数据是bgr格式
				GL_UNSIGNED_BYTE,   //! 数据是8bit数据
				pixels
			);
			/**
			*   释放内存
			*/
			FreeImage_Unload(dib);

			return  textureId;
		}



	protected:
		static  LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{

			CELLWinApp*  pThis = (CELLWinApp*)GetWindowLong(hWnd, GWL_USERDATA);
			if (pThis)
			{
				return  pThis->onEvent(hWnd, msg, wParam, lParam);
			}
			if (WM_CREATE == msg)
			{
				CREATESTRUCT*   pCreate = (CREATESTRUCT*)lParam;
				SetWindowLong(hWnd, GWL_USERDATA, (DWORD_PTR)pCreate->lpCreateParams);
			}
			return  DefWindowProc(hWnd, msg, wParam, lParam);
		}
	public:
		/**
		*   事件函数
		*/
		/**
		*   鼠标移动
		*/
		virtual void    onMouseMove(int absx, int absy, int absz)
		{
			if (absz > 0)
			{
				_3rdcamera._radius = _3rdcamera._radius * 1.1f;
			}
			else if (absz < 0)
			{
				_3rdcamera._radius = _3rdcamera._radius * 0.9f;
			}
			else if (_rightButtonDown)
			{
				float2  curPos(absx, absy);
				float2  offset = curPos - _mousePos;
				_mousePos = curPos;
				_3rdcamera.rotateView(offset.x * 0.1f,offset.y * 0.1f);
				_3rdcamera.update();
			}
		}
		/**
		*   鼠标按下
		*/
		virtual void    onMousePress(int absx, int absy, CELL::MouseButton id)
		{

			if (id == CELL::MouseButton::Left)
			{
				//Ray     ray = _3rdcamera.createRayFromScreen(absx, absy);
				//float3  pos = ray.getOrigin();
				//float   tm = abs((pos.y) / ray.getDirection().y);
				//float3  target = ray.getPoint(tm);
				//_role.setTarget(float3(target.x, 0, target.z));
			}
			else if (id == CELL::MouseButton::Right)
			{
				_mousePos = float2(absx, absy);
				_rightButtonDown = true;
			}
		}

		/**
		*   鼠标释放
		*/
		virtual void    onMouseRelease(int /*absx*/, int /*absy*/, CELL::MouseButton id)
		{
			if (id == CELL::MouseButton::Right)
			{
				_rightButtonDown = false;
			}
		}


		virtual LRESULT onEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#endif

#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
#endif

#ifndef GET_WHEEL_DELTA_WPARAM
#define GET_WHEEL_DELTA_WPARAM(wParam)          (int)((short)HIWORD(wParam))
#endif
			switch (msg)
			{
			case WM_SIZE:
			{
				RECT    rt;
				GetClientRect(_hWnd, &rt);
				_width = rt.right - rt.left;
				_height = rt.bottom - rt.top;
				/*if (_frame)
				{
					_frame->onSize(_width, _height);
				}*/
			}
			break;
			case WM_LBUTTONDOWN:
			{
				onMousePress(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), CELL::MouseButton::Left);
			}
			break;
			case WM_LBUTTONUP:
			{				
				onMouseRelease(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), CELL::MouseButton::Left);
			}
			break;
			case WM_RBUTTONDOWN:
			{
				onMousePress(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), CELL::MouseButton::Right);
			}
			break;
			case WM_RBUTTONUP:
			{
				onMouseRelease(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), CELL::MouseButton::Right);
			}
			break;
			case WM_MOUSEMOVE:
			{
				onMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 0);
			}
			break;

			case WM_MOUSEWHEEL:
			{
				onMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), GET_WHEEL_DELTA_WPARAM(wParam));
			}
			break;
			case WM_CHAR:
			{
				//if (_frame)
				//{
				//	_frame->onChar(wParam);
				//}
			}
			break;
			case WM_KEYDOWN:
			{
				switch (wParam)
				{
					case VK_LEFT:
					{
						float3  _tmp = _role.getPosition();
						_tmp-= CELL::normalize(_3rdcamera._right) * float3(2, 0, 2);
						_role.setPosition(_tmp);
					}
					break;
					case VK_RIGHT:
					{
						float3  _tmp = _role.getPosition();
						_tmp += CELL::normalize(_3rdcamera._right) * float3(2, 0, 2);
						_role.setPosition(_tmp);
					}
					break;
					case  VK_UP:
					{
						float3  _tmp = _role.getPosition();
						_tmp += CELL::normalize(_3rdcamera._dir) * float3(2, 0, 2);
						_role.setPosition(_tmp);
					}
					break;
					case VK_DOWN:
					{
						float3  _tmp = _role.getPosition();
						_tmp -= CELL::normalize(_3rdcamera._dir) * float3(2, 0, 2);
						_role.setPosition(_tmp);
					}
					break;
				}
			}
			break;
			case WM_CLOSE:
			case WM_DESTROY:
			{
				::PostQuitMessage(0);
			}
			break;
			default:
				return DefWindowProc(_hWnd, msg, wParam, lParam);
			}
			return  S_OK;
		}

		virtual std::pair<unsigned, unsigned >  createFBO(int width,int height)
		{
			std::pair<unsigned ,unsigned >buf;
			glGenFramebuffers(1,&buf.first);
			glBindFramebuffer(GL_FRAMEBUFFER, buf.first);

			glGenRenderbuffers(1, &buf.second);
			glBindRenderbuffer(GL_RENDERBUFFER, buf.second);

			glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT16,width,height);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buf.second);
			glBindFramebuffer(GL_FRAMEBUFFER,0);
			return buf;
		}
		virtual void beginFBO(unsigned FBO, unsigned textureId)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
			//glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,);
		}
		virtual void endFBO()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		virtual void createraintexture()
		{				
			for (int i=0;i<LENGHT_TEXTURE;i++)
			{
				beginFBO(_fBuf.first,_rain.show[i].index_textureid.textureId);
				{
					glClearColor(0, 0, 0, 0);
					glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);//清空缓冲区
					CELL::matrix4   screenProj = CELL::ortho<float>(0, float(36), (float)(_rain.global_height), 0, -100.0f, 100);
					_font.beginText(screenProj);					
					std::vector < Rainbase::list_font>::iterator tex;					
					for (tex = _rain.show[i].index_textureid.list.begin(); tex != _rain.show[i].index_textureid.list.end(); tex++)
					{
						if ((*tex).count_time < 20)
						{
							(*tex).count_time += _rain.show[i].index_textureid.speed;
							break;
						}
						else
						{
							//if ((*tex).count_time2++ > 2)
							//{
								(*tex).count_time2 = 0;
								(*tex).life_time += _rain.show[i].index_textureid.speed;
								if ((*tex).r > _rain.show[i].index_textureid.speed) { (*tex).r -= _rain.show[i].index_textureid.speed; }
								else { (*tex).r = 0; }
								if ((*tex).b > _rain.show[i].index_textureid.speed) { (*tex).b -= _rain.show[i].index_textureid.speed; }
								else { (*tex).b = 0; }
								if ((*tex).g > _rain.show[i].index_textureid.speed) { (*tex).g -= _rain.show[i].index_textureid.speed/2; }
								else { (*tex).g = 0; }
								if ((*tex).life_time > 900)
								{
									(*tex).life_time = 0;
									if ((*tex).index == 0)
									{
										int tmp = (rand() % LENGHT_TITLE);
										//if (tmp % 2) { tmp--; }
										_rain.show[i].index_textureid.index_text = tmp;
									}
									(*tex).ch = newcontent[_rain.show[i].index_textureid.index_text][(*tex).index % wcslen(newcontent[_rain.show[i].index_textureid.index_text])];
									(*tex).count_time = 100;
									(*tex).b = (*tex).r = (*tex).g = 252;
								}
								
							//}
							_font.drawText(0, (*tex).index * _rain.show[i].index_textureid.width, 0, Rgba4Byte((*tex).r, (*tex).g, (*tex).b)
										, (const wchar_t*)(&(*tex).ch)
										, -1);
						}
					}					
					_font.endText();						
				}
				endFBO();
			}
		}

		struct Vertexbox
		{
			float x, y, z;
			float u, v;
		};

		Vertexbox  boxVertex[36] =
		{
			{ -1.0f,-1.0f, 1.0f,  0.0f,0.0f,},
			{ 1.0f,-1.0f, 1.0f,  1.0f,0.0f, },
			{ 1.0f, 1.0f, 1.0f,  1.0f,1.0f, },

			{ -1.0f,-1.0f, 1.0f,  0.0f,0.0f,},
			{ 1.0f, 1.0f, 1.0f,  1.0f,1.0f, },
			{ -1.0f, 1.0f, 1.0f,  0.0f,1.0f,},

			{ -1.0f,-1.0f,-1.0f,  1.0f,0.0f,},
			{ -1.0f, 1.0f,-1.0f,  1.0f,1.0f,},
			{ 1.0f, 1.0f,-1.0f,  0.0f,1.0f,} ,

			{ -1.0f,-1.0f,-1.0f,  1.0f,0.0f,},
			{ 1.0f, 1.0f,-1.0f,  0.0f,1.0f,} ,
			{ 1.0f,-1.0f,-1.0f,  0.0f,0.0f,} ,

			{ -1.0f, 1.0f,-1.0f,  0.0f,1.0f,},
			{ -1.0f, 1.0f, 1.0f,  0.0f,0.0f,},
			{ 1.0f, 1.0f, 1.0f,  1.0f,0.0f,} ,

			{ -1.0f, 1.0f,-1.0f,  0.0f,1.0f,},
			{ 1.0f, 1.0f, 1.0f,  1.0f,0.0f, },
			{ 1.0f, 1.0f,-1.0f,  1.0f,1.0f, },

			{ -1.0f,-1.0f,-1.0f,  1.0f,1.0f, },
			{ 1.0f,-1.0f,-1.0f,  0.0f,1.0f, },
			{ 1.0f,-1.0f, 1.0f,  0.0f,0.0f, },

			{ -1.0f,-1.0f,-1.0f,  1.0f,1.0f, },
			{ 1.0f,-1.0f, 1.0f,  0.0f,0.0f, },
			{ -1.0f,-1.0f, 1.0f,  1.0f,0.0f, },

			{ 1.0f,-1.0f,-1.0f,  1.0f,0.0f, },
			{ 1.0f, 1.0f,-1.0f,  1.0f,1.0f, },
			{ 1.0f, 1.0f, 1.0f,  0.0f,1.0f, },

			{ 1.0f,-1.0f,-1.0f,  1.0f,0.0f, },
			{ 1.0f, 1.0f, 1.0f,  0.0f,1.0f, },
			{ 1.0f,-1.0f, 1.0f,  0.0f,0.0f, },

			{ -1.0f,-1.0f,-1.0f,  0.0f,0.0f, },
			{ -1.0f,-1.0f, 1.0f,  1.0f,0.0f, },
			{ -1.0f, 1.0f, 1.0f,  1.0f,1.0f, },

			{ -1.0f,-1.0f,-1.0f,  0.0f,0.0f, },
			{ -1.0f, 1.0f, 1.0f,  1.0f,1.0f, },
			{ -1.0f, 1.0f,-1.0f,  0.0f,1.0f, }
		};

		virtual void    render()
		{	
			//生成相应的文字纹理
			createraintexture();

			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);//清空缓冲区

			RECT    rect;
			GetClientRect(_hWnd, &rect);
			_width = rect.right - rect.left;
			_height = rect.bottom - rect.top;

			glViewport(0, 0, _width, _width);//设置视角大小

			_3rdcamera.setViewSize(_width, _height);
			_role.render(1.0f / 60.0f);
			_3rdcamera.setTarget(_role._pos);
			_3rdcamera.update();

			CELL::matrix4   matModel;
			matModel.translate(_role._pos);
			CELL::matrix4   matView = _3rdcamera.getView();

			float   gSize = 100;
			float   gPos = -5;
			float   rept = 10;

			Vertex grounds[] =
			{
				{ -gSize, gPos,-gSize,	0.0f, 0.0f,	1.0f, 1.0f, 1.0f,1.0f },
				{  gSize, gPos,-gSize,	rept, 0.0f,	1.0f, 1.0f, 1.0f,1.0f },
				{  gSize, gPos, gSize,	rept, rept,	1.0f, 1.0f, 1.0f,1.0f },

				{ -gSize, gPos,-gSize,	0.0f, 0.0f,	1.0f, 1.0f, 1.0f,1.0f },
				{  gSize, gPos, gSize,	rept, rept,	1.0f, 1.0f, 1.0f,1.0f },
				{ -gSize, gPos, gSize,	0.0f, rept,	1.0f, 1.0f, 1.0f,1.0f },
			};
			glEnable(GL_DEPTH_TEST);

			_shader_band.begin();
			{
				CELL::matrix4   matWorld(1);//生成世界矩阵
				CELL::matrix4   matProj = CELL::perspective(45.0f, (GLfloat)_width / (GLfloat)_height, 0.1f, 3000.0f);//生成三维世界矩阵

				CELL::matrix4   MVP = matProj * matView * matWorld;

				//glBindTexture(GL_TEXTURE_2D, _texDynamic);
				std::vector<Rainbase::list_wall>::iterator it;
				for (it = _rain.mywall.begin(); it != _rain.mywall.end(); it++)
				{
					glBindTexture(GL_TEXTURE_2D, (*it).textureId);
					glVertexAttribPointer(_shader_band._positionAttr,	3, GL_FLOAT, false, sizeof(Vertex), &(*it).position[0].x);
					glVertexAttribPointer(_shader_band._uvAttr,			2, GL_FLOAT, false, sizeof(Vertex), &(*it).position[0].u);
					glVertexAttribPointer(_shader_band._colorAttr,		4, GL_FLOAT, false, sizeof(Vertex), &(*it).position[0].r);
					glUniformMatrix4fv(_shader_band._MVP, 1, false, MVP.data());
					glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof((*it).position) / sizeof((*it).position[0]));
				}

				std::vector<Mesh>::iterator iit;
				for (iit = mymodel.mymodel.begin(); iit != mymodel.mymodel.end(); iit++)
				{
					glBindTexture(GL_TEXTURE_2D, _textureId_color);
					glVertexAttribPointer(_shader_band._positionAttr, 3, GL_FLOAT, false, sizeof(assimp_Vertex), &(*iit).vertData[0].x);
					glVertexAttribPointer(_shader_band._uvAttr, 2, GL_FLOAT, false, sizeof(assimp_Vertex), &(*iit).vertData[0].u);
					glVertexAttribPointer(_shader_band._colorAttr, 4, GL_FLOAT, false, sizeof(assimp_Vertex), &(*iit).vertData[0].r);
					glUniformMatrix4fv(_shader_band._MVP, 1, false, MVP.data());
					glDrawElements(GL_TRIANGLES, (*iit).indices.size(), GL_UNSIGNED_INT,&(*iit).indices[0]);
				}
			}
			_shader_band.end();
		}


		bool processNode(const aiNode* node, const aiScene* sceneObjPtr)
		{

			for (size_t i = 0; i < node->mNumMeshes; ++i) // 先处理自身结点
			{
				// 注意node中的mesh是对sceneObject中mesh的索引
				aiMesh * meshPtr = sceneObjPtr->mMeshes[node->mMeshes[i]];
				if (meshPtr)
				{
					Mesh tmp_mesh;
					// 从Mesh得到顶点数据、法向量、纹理数据
					for (size_t i = 0; i < meshPtr->mNumVertices; ++i)
					{
						assimp_Vertex	tmp;
						if (meshPtr->HasPositions())
						{
							tmp.x = meshPtr->mVertices[i].x;
							tmp.y = meshPtr->mVertices[i].y;
							tmp.z = meshPtr->mVertices[i].z;
							tmp.r = 1; tmp.g = 1; tmp.b = 1; tmp.a = 1;
						}
						// 获取纹理数据 目前只处理0号纹理
						if (meshPtr->HasTextureCoords(0))
						{
							tmp.u = meshPtr->mTextureCoords[0][i].x;
							tmp.v = meshPtr->mTextureCoords[0][i].y;
						}
						else
						{
							
						}
						// 获取法向量数据
						if (meshPtr->HasNormals())
						{
							tmp.fx = meshPtr->mNormals[i].x;
							tmp.fy = meshPtr->mNormals[i].y;
							tmp.fz = meshPtr->mNormals[i].z;
						}
						tmp_mesh.vertData.push_back(tmp);
					}
					// 获取索引数据
					for (size_t i = 0; i < meshPtr->mNumFaces; ++i)
					{
						aiFace face = meshPtr->mFaces[i];
						if (face.mNumIndices != 3)
						{
							return false;
						}
						tmp_mesh.indices.push_back(face.mIndices[0]);
						tmp_mesh.indices.push_back(face.mIndices[1]);
						tmp_mesh.indices.push_back(face.mIndices[2]);
					}
					mymodel.mymodel.push_back(tmp_mesh);
				}
			}

			for (size_t i = 0; i < node->mNumChildren; ++i) // 再处理孩子结点
			{
				this->processNode(node->mChildren[i], sceneObjPtr);
			}
			return true;
		}
		/**
		*   主函数
		*/
		int     main(int width, int height)
		{
			_hWnd = CreateWindowEx(NULL,
				_T("CELLWinApp"),
				_T("智能洗肺机老化程序"),
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				width,
				height,
				NULL,
				NULL,
				_hInstance,
				this
			);

			if (_hWnd == 0)
			{
				return  -1;
			}
			UpdateWindow(_hWnd);

			ShowWindow(_hWnd, SW_SHOW);

			if (!initOpenGLES20())
			{
				return  false;
			}
			_shader_band.initialize();
			_font.buildSystemFont("data/font/STXINGKA.TTF", 40);
			//_font.buildSystemFont("data/font/simsun.ttc", 16);
			_textureId_color = loadTexture("data/image/2.jpg");
			_texDynamic = createTexture(_rain.global_width, _rain.global_height);
			
			_role.setPosition(float3(0, 0, 0));
			_role.setTarget(float3(0, 0, 0));
			_3rdcamera.setRadius(50);
			_3rdcamera.setEye(float3(0, 0, 50));
			_3rdcamera.setTarget(float3(0, 0, 0));
			_3rdcamera.calcDir();
			_3rdcamera.setUp(float3(0, 1, 0));

			for (int i=0;i<LENGHT_TEXTURE;i++)
			{
				_rain.show[i].index_textureid.textureId = createTexture(_rain.show[i].index_textureid.width, _rain.show[i].index_textureid.height);
			}
			int tmp_textureid = 0;
			std::vector<Rainbase::list_wall>::iterator iit;
			for (iit = _rain.mywall.begin(); iit != _rain.mywall.end(); iit++)
			{
				(*iit).textureId = _rain.show[(tmp_textureid++)%LENGHT_TEXTURE].index_textureid.textureId;
			}

			_fBuf = createFBO(_rain.global_width, _rain.global_height);
			
			Assimp::Importer importer;
			std::string filePath = "data/test/test.obj";
			const aiScene* sceneObjPtr = importer.ReadFile(filePath,aiProcess_Triangulate | aiProcess_FlipUVs);
			if (!sceneObjPtr
				|| sceneObjPtr->mFlags == AI_SCENE_FLAGS_INCOMPLETE
				|| !sceneObjPtr->mRootNode)
			{
				return false;
			}
			processNode(sceneObjPtr->mRootNode, sceneObjPtr);			
			

			std::ofstream outfile("E:\\out.txt",std::ofstream::app);
			
			for (int x = 0; x < mymodel.mymodel.size(); x++)
			{
				for (int y = 0; y < mymodel.mymodel[x].indices.size(); y++)
				{
					char temp[100];
					memset(temp, 0, 100);
					sprintf_s(temp, "x=[%d]\r\n\0", mymodel.mymodel[x].indices[y]);
					outfile << temp;
				}
			}
			

			outfile.close();



			MSG msg = { 0 };
			while (msg.message != WM_QUIT)
			{
				if (msg.message == WM_DESTROY ||
					msg.message == WM_CLOSE)
				{
					break;
				}
				/**
				*   有消息，处理消息，无消息，则进行渲染绘制
				*/
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					render();
					eglSwapBuffers(_display, _surface);
				}
			}
			/**
			*   销毁OpenGLES20
			*/
			destroyOpenGLES20();

			return  0;
		}
	};
}

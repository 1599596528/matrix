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
//���ֵ�����
#define LENGHT_TITLE	15
//���������
#define LENGHT_TEXTURE	4
//ǽ�ڵ�����
#define NUM_WALLS		12

#define NUM_GLOBAL_WIDTH	40
#define NUM_GLOBAL_HEIGHT	2000
	//const wchar_t content[] = L"��������һʱ������Ү��������ظ�����������ǧ������ʮ�˾��ʱ������밢���ڳ���ʱ���³ֲ������ʳ������ֹʳ��ϴ�������²��氢�������ȡ����ʦ̳��������ڲ���֧���붨˼Ω�������Ѽ��밢�Ѿ����˴������˴����Ѽ������ʦ̳�����������";// ������Ȼ˼Ω���Ѷ�ʱȥ��Զ���ڱ𴦶����붨���������Ӷ������氢���Դ���Ү��������֧�����֧������֧�����֧�����֧���ڲ���֧��˵�֧�����ɰ��ְ���������������ס������һ������һ�����������д������񵱲���ס��һ������һ�ٶ�ʱ����ȿ����ǿ���֮��";// ���ﰢ�Ѱ���ĬȻ������֪��������������˵����ãȻ�̲�����������ס��һ������һ�����������������������ߺ�";
	const wchar_t newcontent[LENGHT_TITLE][50]
		= {
			{L"����Ωһ�ɿ��ı�׼������Զ�������"},
			{L"ʱ����һ�вƸ������ĲƸ�"},
			{L"������һ�ɲ���Ķ���ֻ���κ����ﶼ���ڲ��ϱ仯����������"},
			{L"���Ż��Ե��˱ؽ�������֮ǰ����"},
			{ L"����ԭ����Ҷһ�����˺�����������������¶������" },

			{ L"һ����ʵ��һ��û���Ա������" },
			{ L"������һ�ÿ��Ա������" },
			{ L"�����Ŀ�ѧ��Ӧ���Ǹ������˭���ǻ����˭��ֻ�ܰ��Լ���Ϊʵ����" },
			{ L"�Ҷ�������������׽���������������������������������Ҫ" },
			{ L"�����������Ҫͨ��ÿ��վ�Ƶľ���ÿһ������׶���������ֱ��ǰ���ߴӲ�����ʲô" },

			{ L"��ѧ�ǵ���Ϊ�ҵĲ������κβ����ֵĵط��Ǿ�����õ����յ�" },
			{ L"û���˲���ϧ������������������������ʱ��" },
			{ L"��������Ϊ���������˲�֪���Լ��Ǳ���" },
			{ L"���޾���ĳ��������˵ĵ���������İ������޼۵�" },
			{ L"���õĽ���״���͸߶ȵ�����ѵ������Ч�������Ͷ�����Ҫ����" }
	};

	class Rainbase
	{
	public :
		//std::string content;//��¼��������
		unsigned count_rain;//��¼�ж�����Ҫ��ʾ��
		unsigned global_width;
		unsigned global_height;
		struct Vertex
		{
			float x, y, z;
			float u, v;
			float r, g, b, a;
		};
		//�������еĺ��ֲ�ֳɵ����ĸ���
		struct list_font
		{
			wchar_t ch;
			unsigned index;//��¼�ڵ�ǰ�����е�λ��
			unsigned life_time;//��¼��������ʱ��
			unsigned count_time;//��ʱ������1
			unsigned count_time2;
			unsigned char r;
			unsigned char g;
			unsigned char b;
		};
		//���ڻ�������Ľṹ��
		struct list_texture
		{
			unsigned textureId;//����ID
			unsigned speed;//������ٶ�
			unsigned index_text;//�������ʼ����λ�á�
			std::vector<list_font> list;
			unsigned width;//���εĿ�
			unsigned height;//���εĸ�			
		};
		//������ʾ�ľ���
		struct list_show
		{
			//Vertex position[4];//���ε��ĸ������λ��			
			list_texture index_textureid;//���ε���������
		};
		list_show show[LENGHT_TEXTURE];
		struct list_wall
		{
			Vertex position[4];//���ε��ĸ������λ��
			unsigned textureId;//����ID������ֻ��ȡ
		};
		std::vector<list_wall> mywall;

		Vertex _data_wall[NUM_WALLS][4]=
		{
			//1ͨ�����
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
			//1ͨ���Ҳ�
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
			//1ͨ���ϲ�
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
			//1ͨ���²�
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
			//*content = L"��������һʱ������Ү��������ظ�����������ǧ������ʮ�˾��ʱ������밢���ڳ���ʱ���³ֲ������ʳ������ֹʳ��ϴ�������²��氢�������ȡ����ʦ̳��������ڲ���֧���붨˼Ω�������Ѽ��밢�Ѿ����˴������˴����Ѽ������ʦ̳�����������������Ȼ˼Ω���Ѷ�ʱȥ��Զ���ڱ𴦶����붨���������Ӷ������氢���Դ���Ү��������֧�����֧������֧�����֧�����֧���ڲ���֧��˵�֧�����ɰ��ְ���������������ס������һ������һ�����������д������񵱲���ס��һ������һ�ٶ�ʱ����ȿ����ǿ���֮�����ﰢ�Ѱ���ĬȻ������֪��������������˵����ãȻ�̲�����������ס��һ������һ�����������������������ߺΡ���Ϊħ�����Ի�ʡ���ʱ������˵����̼������Ĳ����򡣼���ĬȻ����ʱħ�����������������׷��ԡ���������˰����������Ž����˰������������ߺΡ������������������ӲࡣȰ��������������������ʱ�������ԡ����Ĳ��ڡ���������ᡣ�����������ġ���δ���㡣��δ�����������������δӦ�����������������Ĳ�֮�ڡ��޲����㡣���ѽ��������������Ϊ֮�½�Ϥ�ѱϡ�������Ӧ�����������ʱħ���������롣��������������ա��������������������Ӳࡣ�������ꡣ���Ĳ���δ����ʡ��������񡣽��Ѿ��㡣ȴ�����µ�����������ʱħ�����ŷ�����ϲӻԾ�������칬����ʱ���𡣼������١���������ס�����¡���ʱ���ʮ���ද������������Է����ʿ��г��ԡ��������õ����������������ڡ����Ŵ������Ĵ󱯑�����Ѫ�֡���ʱ���𡣼��ڱ˴�����˵���ԡ�һ�����������������������ҽ������������������С�һ�������У��ҽ������ᡣ��ʱ����˵�����ѡ�ĬȻ��ס����ʱ���ѡ�����ض����Ĵ󾪲����������ԡ����ߺιʺ������ࡣ���֮�·�ΪСԵ���ҽ������������������ѡ��������𡣵��ڷ�ǰ��ͷ��������ԡ����������ڱˡ���˼Ω���������ʮ���ද�����ſ������֮�����Ĵ���塣��֪���ࡣ�Ǻ���Ե�����ԡ����ѡ�����𶯡��а���Ե��һ�ߴ������ˮס���ִ˴�ˮ������ס���ִ˷��������ס��������ʱ�ͷ���𡣴��˷��֡����ּȶ�����ˮ�ද����ˮ�ȶ�������˶������߱�������������������ġ�������ͨ��ʼ�ɾ��ߡ��������顣�ʴ�ض������������ڶ����졣�������¡�����ĸ̥���ʴ�ض���������������������в�����ʴ�ض�������������������������ѧ������һ�����ǡ��ʴ�ض������������ɵ���ʼΪ����ת��֡��ʴ�ض��������������١�����ͨ��ס����ס���ʴ�ض�����������������ʱ���ʴ�ض������ѡ���֪�ض���Ե���д˰��¡����ѡ��а˲��ڡ�һ��ɲ�������������š����߳��߾�ʿ������ɳ�š����������������������졣����ħ���������������˰˲��ڡ��ҹ����Ӧ�ö��ߡ��������Ρ���Ϊ˵�������಻֪������˵�����ѡ��а�ʤ����һ������ɫ�����ɫ�پ��硣��������ɫ�����ɫ�������硣��������ɫ�����ɫ�پ��硣��������ɫ�����ɫ�������硣���߹�һ��ɫ�ࡣ���߹�һ��ɫ�ơ����߹�һ��ɫ�ࡣ���߹�һ��ɫ�ס�����������ʤ֮�������ΰ��ѡ��а˽��ѡ�һ������ɫ�����ɫ����������ɫ�����ɫ����˼Ω�����߾����ѡ����߿մ����ѡ�����ʶ�����ѡ����������д����ѡ����߷���Ƿ��봦���ѡ������𾡶����ѡ����ิ������ʤ�������ܾ����˵ȷ��ߡ�������������ް������ѡ�֪�����������������ɵ�ʱ������¥Ƶ����Ҷ�����������Ӳࡣ��ʱħ�������������������ԡ����𡣽����˰����������š������˰����������Թʡ���Ӧ���߽�Ϥ���ѡ��������ǰ�����ʱ���������롣�Ҽ����ԡ�����δ�ǰ�����ʱ�������ߺΡ����Ĳ���δ����ʡ���Ӧ���߽�δ������������ڡ���δ��������������ħ�����ѡ��Ļ���������칬�������������������ԡ����𡣽����˰����������š������˰������������ߺΡ��������������������ӲࡣȰ��������������������ʱ�������ԡ����Ĳ��ڡ���������ᡣ�����������ġ���δ���㡣��δ�����������������δӦ������������𡣽����Ĳ�֮�ڡ��޲����㡣���ѽ��������������Ϊ֮�½�Ϥ�ѱϡ�������Ӧ���������ħ�������������롣�Ҽ����ԡ��������������������Ӳࡣ�������ꡣ���Ĳ���δ����ʡ��������񡣽��Ѿ��㡣ȴ�����¡�����������ħ�������������ѡ���ϲӻԾ�����칬���Ҽ��ڴ���ħ���ѡ��������١�ס�����¡�������Ե������𶯡���ʱ�����ŷ����Ĵ󱯑�����Ѫ�֡��������ᡣ���׷��ԡ�ΨԸ���𡣰���ҵȡ�ס��һ�١�����һ�١������������������������롣��ʱ���𡣸氢���ԡ�������������ʱ�������ߺΡ�������ħ��ȴ�����¡���������������ƺζ���סҮ�����ѡ�������������������˵���Բ������Ѱ׷�ʵ����������֮ʦ�ж���Ҳ�������������š�����Ϊ�Ĳ��ڡ���˵���ԡ��������ˡ�����ס�١�����һ�١�����һ�١�����������������������֮�����������ס��һ�١�����һ�١��������١�ס�����¡�ΨԸ���𡣰���ҵȡ�ס��һ�١�����һ�١���ʱ��������ԡ��ҽ����Ա������ߡ�������ʡ������ߺΡ���ǰ�ڴ�����˵�ԡ��������ˡ�����ס�١�����һ�١�����һ�١����������д��������񵱲���ס��һ�١�����һ�١���������������˵����Ȱ���š�����ĬȻ���������ҡ�ס��һ�١�����һ�١��ǹ��ҽ�ס�����¡�����ƺη�����ס����ʱ�����ŷ�������֪�������������Ȱ�롣������ʹ���ƾ��Ñ�������������������ʤ����ʱ����ȼ������������������������ο֮�ԡ����ѡ���������Ǳ�����Ϊ֮����Ϥ���ǡ�һ�кϻ��޲����롣���𼴱��˵���ԡ�";
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

#pragma region ����Ҫ���ɵ���ͼ
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
		//! ʵ�����
		HINSTANCE   _hInstance;
		//! ���ھ��
		HWND        _hWnd;
		//! ���ڵĸ߶�
		int         _width;
		//! ���ڵĿ��
		int         _height;
		/// for gles2.0
		EGLConfig   _config;
		EGLSurface  _surface;
		EGLContext  _context;
		EGLDisplay  _display;
		//! ����shader
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
		*   ��ʼ�� OpenGLES2.0
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
		*   ����OpenGLES2.0
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
			*   ����һ������Id,������Ϊ��������������Ĳ����������������id
			*/
			glGenTextures(1, &textureId);
			/**
			*   ʹ���������id,���߽а�(����)
			*/
			glBindTexture(GL_TEXTURE_2D, textureId);
			/**
			*   ָ������ķŴ�,��С�˲���ʹ�����Է�ʽ������ͼƬ�Ŵ��ʱ���ֵ��ʽ
			*/
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



			for (int i = 0; i < size; ++i)
			{
				//1 ��ȡͼƬ��ʽ
				FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileNames[i], 0);

				//2 ����ͼƬ
				FIBITMAP    *dib = FreeImage_Load(fifmt, fileNames[i], 0);

				//3 ת��Ϊrgb 24ɫ
				dib = FreeImage_ConvertTo24Bits(dib);



				//4 ��ȡ����ָ��
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
				*   ��ͼƬ��rgb�����ϴ���opengl.
				*/
				glTexImage2D(
					GL_TEXTURE_2D,      //! ָ���Ƕ�άͼƬ
					i,              //! ָ��Ϊ��һ�������������mipmap,��lod,����ľͲ��ü����ģ�Զ��ʹ�ý�С������
					GL_RGB,             //! �����ʹ�õĴ洢��ʽ
					width,              //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
					height,             //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
					0,                  //! �Ƿ�ı�
					GL_RGB,             //! ���ݵĸ�ʽ��bmp�У�windows,����ϵͳ�д洢��������bgr��ʽ
					GL_UNSIGNED_BYTE,   //! ������8bit����
					pixels
				);

				FreeImage_Unload(dib);
			}

			return  textureId;
		}
		virtual unsigned    loadTexture(const char* fileName)
		{
			unsigned    textureId = 0;
			//1 ��ȡͼƬ��ʽ
			FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileName, 0);

			//2 ����ͼƬ
			FIBITMAP    *dib = FreeImage_Load(fifmt, fileName, 0);

			//3 ת��Ϊrgb 24ɫ
			dib = FreeImage_ConvertTo24Bits(dib);

			//4 ��ȡ����ָ��
			BYTE    *pixels = (BYTE*)FreeImage_GetBits(dib);

			int     width = FreeImage_GetWidth(dib);
			int     height = FreeImage_GetHeight(dib);

			/**
			*   ����һ������Id,������Ϊ��������������Ĳ����������������id
			*/
			glGenTextures(1, &textureId);

			/**
			*   ʹ���������id,���߽а�(����)
			*/
			glBindTexture(GL_TEXTURE_2D, textureId);
			/**
			*   ָ������ķŴ�,��С�˲���ʹ�����Է�ʽ������ͼƬ�Ŵ��ʱ���ֵ��ʽ
			*/
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			/**
			*   ��ͼƬ��rgb�����ϴ���opengl.
			*/
			glTexImage2D(
				GL_TEXTURE_2D,      //! ָ���Ƕ�άͼƬ
				0,                  //! ָ��Ϊ��һ�������������mipmap,��lod,����ľͲ��ü����ģ�Զ��ʹ�ý�С������
				GL_RGB,             //! �����ʹ�õĴ洢��ʽ
				width,              //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
				height,             //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
				0,                  //! �Ƿ�ı�
				GL_RGB,             //! ���ݵĸ�ʽ��bmp�У�windows,����ϵͳ�д洢��������bgr��ʽ
				GL_UNSIGNED_BYTE,   //! ������8bit����
				pixels
			);
			/**
			*   �ͷ��ڴ�
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
		*   �¼�����
		*/
		/**
		*   ����ƶ�
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
		*   ��갴��
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
		*   ����ͷ�
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
					glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);//��ջ�����
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
			//������Ӧ����������
			createraintexture();

			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);//��ջ�����

			RECT    rect;
			GetClientRect(_hWnd, &rect);
			_width = rect.right - rect.left;
			_height = rect.bottom - rect.top;

			glViewport(0, 0, _width, _width);//�����ӽǴ�С

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
				CELL::matrix4   matWorld(1);//�����������
				CELL::matrix4   matProj = CELL::perspective(45.0f, (GLfloat)_width / (GLfloat)_height, 0.1f, 3000.0f);//������ά�������

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

			for (size_t i = 0; i < node->mNumMeshes; ++i) // �ȴ���������
			{
				// ע��node�е�mesh�Ƕ�sceneObject��mesh������
				aiMesh * meshPtr = sceneObjPtr->mMeshes[node->mMeshes[i]];
				if (meshPtr)
				{
					Mesh tmp_mesh;
					// ��Mesh�õ��������ݡ�����������������
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
						// ��ȡ�������� Ŀǰֻ����0������
						if (meshPtr->HasTextureCoords(0))
						{
							tmp.u = meshPtr->mTextureCoords[0][i].x;
							tmp.v = meshPtr->mTextureCoords[0][i].y;
						}
						else
						{
							
						}
						// ��ȡ����������
						if (meshPtr->HasNormals())
						{
							tmp.fx = meshPtr->mNormals[i].x;
							tmp.fy = meshPtr->mNormals[i].y;
							tmp.fz = meshPtr->mNormals[i].z;
						}
						tmp_mesh.vertData.push_back(tmp);
					}
					// ��ȡ��������
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

			for (size_t i = 0; i < node->mNumChildren; ++i) // �ٴ����ӽ��
			{
				this->processNode(node->mChildren[i], sceneObjPtr);
			}
			return true;
		}
		/**
		*   ������
		*/
		int     main(int width, int height)
		{
			_hWnd = CreateWindowEx(NULL,
				_T("CELLWinApp"),
				_T("����ϴ�λ��ϻ�����"),
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
				*   ����Ϣ��������Ϣ������Ϣ���������Ⱦ����
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
			*   ����OpenGLES20
			*/
			destroyOpenGLES20();

			return  0;
		}
	};
}

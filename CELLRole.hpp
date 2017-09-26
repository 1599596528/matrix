#pragma once
#include <math.h>
#include <EGL/egl.h>
#include <gles2/gl2.h>
#include "CELLMath.hpp"

namespace   CELL
{
	class   Role
	{
	public:
		float3  _pos;
		float3  _target;
		float   _speed;
	public:
		Role()
		{
			_speed = 5;
		}
		/**
		*   �����ƶ���Ŀ���
		*/
		float3 getTarget()
		{
			return _target;
		}
		void    setTarget(float3 target)
		{
			_target = target;
		}
		/**
		*   ����λ��
		*/
		float3 getPosition()
		{
			return _pos;
		}
		void    setPosition(float3 pos)
		{
			_pos = pos;
			//_pos.y = 1;
		}
		void moveCheck(const float elasped)
		{
			/**
			*   Ŀ��λ�ò��ǵ�ǰλ�á�
			*/
			if (_target == _pos)
			{
				return;
			}
			/**
			*   ��ȡ��ǰ���λ����Ŀ��λ�õ�ƫ����
			*/
			float3  offset = _target - _pos;
			/**
			*   ��ȡ���ƶ��ķ���
			*/
			float3  dir = normalize(offset);

			if (distance(_target, _pos) > 1)
			{
				float   speed = elasped * _speed;

				_pos += float3(dir.x * speed, 0, dir.z  * speed);
			}
			else
			{
				_target = _pos;
			}
		}
		/**
		*   ���ƽ�ɫ
		*/
		void    render(float fElapsed)
		{
			//moveCheck(fElapsed);
		}
	};
}
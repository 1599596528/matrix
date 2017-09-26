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
		*   设置移动的目标点
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
		*   更新位置
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
			*   目标位置不是当前位置。
			*/
			if (_target == _pos)
			{
				return;
			}
			/**
			*   获取当前玩家位置与目标位置的偏移量
			*/
			float3  offset = _target - _pos;
			/**
			*   获取到移动的方向
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
		*   绘制角色
		*/
		void    render(float fElapsed)
		{
			//moveCheck(fElapsed);
		}
	};
}
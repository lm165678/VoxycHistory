/*
Copyright (C) 2018 Dimitri Lozovoy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Camera.h"

void Camera::init(Object *mouseLook)
{
#ifndef USE_PLAYEROBJ
	this->player = player;
#endif
	this->mouseLook = mouseLook;

	ints["ignorecollisions"] = 1;
}

void Camera::tick()
{
	if (playerObj == nullptr)
		return;

#ifdef USE_PLAYEROBJ
	switch (cameraScheme)
	{
	case CAMERA_FPS:
		this->position = playerObj->position;
		this->yaw = playerObj->yaw + mouseLook->yaw;
		this->pitch = playerObj->pitch + mouseLook->pitch;
		this->roll = playerObj->roll + mouseLook->roll;
		break;
	case CAMERA_THIRDPERSON:
		
				if (g_common.touchCtrlRJDown)
		{
		    yaw += g_common.touchCtrlRJDistX / 20.0;

		    if (playerObj != nullptr)
			    playerObj->secondaryYaw = yaw;
		}

		
		this->position = playerObj->position;
		this->setDeltaXZ(-yaw, 30.0);
		move();		
		this->position.y += 5;
		

		break;
	case CAMERA_UFOSHOOTER_360:
		this->position = playerObj->position;

		this->setDeltaXZ(-playerObj->yaw - 180, -40.0);
		move();

		this->position.y += 8.0;

		this->yaw = playerObj->yaw;
		this->pitch = 0;
		this->roll = 0;
		break;
	case CAMERA_UFOSHOOTER_VR:
		this->position = playerObj->position;

		this->position.y += 0.5;

		this->yaw = playerObj->yaw;
		this->pitch = 0;
		this->roll = 0;
		break;
	default:
	    this->position = playerObj->position;
	    this->yaw = playerObj->yaw + mouseLook->yaw;
	    this->pitch = playerObj->pitch + mouseLook->pitch;
	    this->roll = playerObj->roll + mouseLook->roll;
        break;
	}
#else
	glm::vec4 camPos;

	switch (cameraScheme)
	{
	case CAMERA_FPS:
		this->position = player->position;
		this->yaw = player->yaw + mouseLook->yaw;
		this->pitch = player->pitch + mouseLook->pitch;
		this->roll = player->roll + mouseLook->roll;
		break;
	case CAMERA_UFOSHOOTER:
		camPos = vehicle->position;
		camPos.z += 40;
		camPos.y += 8;
		this->position = camPos;
		this->yaw = 0;
		this->pitch = 0;
		this->roll = 0;
		break;
	case CAMERA_UFOSHOOTER_360:
		this->position = vehicle->position;;

		this->setDeltaXZ(-vehicle->yaw - 180, -40.0);
		move();

		this->position.y += 8.0;

		this->yaw = vehicle->yaw;
		this->pitch = 0;
		this->roll = 0;
		break;
	case CAMERA_UFOSHOOTER_VR:
		this->position = vehicle->position;;

//		this->setDeltaXZ(-vehicle->yaw - 180, -40.0);
//		move();

		this->position.y += 0.5;
//		this->position.y -= 50.0;

		this->yaw = vehicle->yaw;
		this->pitch = 0;
		this->roll = 0;
		break;
	}
#endif
}

void Camera::setCameraScheme(CameraSchemes scheme)
{
	cameraScheme = scheme;
}

void Camera::setPlayerObj(Object *playerObj)
{
#ifdef USE_PLAYEROBJ
	this->playerObj = playerObj;
#endif
}

void Camera::mouse(float mouseX, float mouseY)
{
	switch (cameraScheme)
	{
	case CAMERA_THIRDPERSON:
		yaw += mouseX;

		if (playerObj != nullptr)
			playerObj->secondaryYaw = yaw;

		break;
	}
}

#pragma once
#include "Scene.h"

class MainScene_2
	:public Scene
{
public:
	MainScene_2();
	virtual ~MainScene_2();

public:
	virtual bool Initialize();
	virtual int Update(const float& TimeDelta);
	virtual void Release();

private:
	int m_SpawnPosInfo[6][7] =
	{ 719 - 80   /*Y*/, 298,  535,   685,  787,   -1,  -1, 
	  527 - 80   /*Y*/, 262,  514,   742,   -1,   -1,  -1,
	  333 - 80   /*Y*/, 598,  391,    -1,   -1,   -1,  -1,
	  274 - 80   /*Y*/, 1681, 1495, 1387, 1201,  946, 826,
	  527 - 80   /*Y*/, 1708, 1468, 1282, 1054,   -1,  -1,
	  784 - 80	 /*Y*/, 1699, 1543, 1279, 1138, 1009,  -1};
};


#pragma once
#include "Scene.h"

class MainScene_1
	:public Scene
{
public:
	MainScene_1();
	virtual ~MainScene_1();

public:
	virtual bool Initialize();
	virtual int Update(const float& TimeDelta);
	virtual void Release();

private:
	int m_SpawnPosInfo[5][11] = 
	{ 1237  /*Y*/, 104,  299,  431,  671,  848,  971,  1166, 1244, 1469, 1523,
	  993   /*Y*/, 1463, 1382, 1205, 1076, 962,  779,  596,  463,  -1,   -1,
	  746   /*Y*/, 538,  673,  751,  961,  1138, 1342, -1,   -1,   -1,   -1,
	  502   /*Y*/, 1318, 973,  784,  580,  -1,   -1,   -1,   -1,   -1,   -1,
	  254   /*Y*/, 995,  1195, 664,  -1,   -1,   -1,   -1,   -1,   -1,   -1, };
};


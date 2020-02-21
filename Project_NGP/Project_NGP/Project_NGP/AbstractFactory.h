#pragma once

// 추상 팩토리 패턴 : 객체 생성을 공통된 로직으로 하나의 템플릿으로 통일
class GameObject;

template <class SubClass>
class AbstractFactory
{
public:
	static GameObject* CreateObj()
	{
		GameObject* pObj = new SubClass;
		pObj->Initialize();

		return pObj;
	}

	static GameObject* CreateObj(int posX, int posY)
	{
		GameObject* pObj = new SubClass;
		pObj->Initialize();
		pObj->SetPosition(posX, posY);

		return pObj;
	}

	static GameObject* CreateObj(int posX, int posY, float angle)
	{
		GameObject* pObj = new SubClass;
		pObj->Initialize();
		pObj->SetPosition(posX, posY);
		pObj->SetAngle(angle);

		return pObj;
	}
};

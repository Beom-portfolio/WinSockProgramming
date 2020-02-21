#pragma once

// 그냥 기본으로 사용할 정보
typedef struct BaseInfo
{
	float X;
	float Y;

	void operator=(const BaseInfo& other)
	{
		this->X = other.X;
		this->Y = other.Y;
	}

	bool operator==(const BaseInfo& other)
	{
		if (this->X == other.X &&
			this->Y == other.Y )
			return true;
		else
			return false;
	}

	BaseInfo operator+(const BaseInfo& other)
	{
		return BaseInfo{ this->X + other.X, this->Y + other.Y };
	}

	void operator+=(const BaseInfo& other)
	{
		this->X += other.X; this->Y += other.Y;
	}

	BaseInfo operator-(const BaseInfo& other)
	{
		return BaseInfo{ this->X - other.X, this->Y - other.Y };
	}

	BaseInfo operator*(const float& other)
	{
		return BaseInfo{ this->X * other, this->Y * other };
	}

	BaseInfo operator/(const float &other)
	{
		return BaseInfo{ this->X / other, this->Y / other };
	}

}POSITION, RESOLUTION, OFFSET;

// 게임 오브젝트 정보
typedef struct GameObjectInfo
{
	int Pos_X;
	int Pos_Y;
	int Size_Width;
	int Size_Height;
}GAMEOBJINFO;

// 스프라이트 정보
typedef struct SpriteInfo
{
	// 스프라이트 이미지 이름
	const TCHAR* key;
	// 스프라이트 y축의 시작점
	int StateIndex;
	// 상태
	int CurState;
	int PreState;
	// 재생타입
	SPRITETYPE Type;
	// Max
	int   MaxFrame;
	// 스피드
	float Speed;
	// 현재 인덱스 위치
	float SpriteIndex;
}SPRITEINFO;

// GDI 이미지 정보 (GDI+는 해당하지 않음)
typedef struct GdiImageInfo
{
	HDC		hDC;
	HDC		hMemDC;

	HBITMAP Bitmap;
	HBITMAP OldBmp;
}GDIINFO;

// 픽셀 정보
typedef struct _tagPixel24
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}PIXEL24;

typedef struct _tagPixelColliderInfo
{
	vector<PIXEL24>		vecPixel;
	UINT				Width;
	UINT				Height;
	PIXEL24				CollPixel;
	POSITION			IntersectPos;
}PIXELCOLLIDERINFO;


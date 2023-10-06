#pragma once
#include"MapWall.h"
#include"IMapWall.h"

#include"MapWall.h"

class MapWallManager
{
public:
	MapWallManager();
	~MapWallManager();

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

	/// <summary>
	/// リストを消す
	/// </summary>
	void ListClear() { object_.clear();}
	
	/// <summary>
	/// 
	/// </summary>
	void SetObject(IMapWall* obj) { object_.push_back(obj); }
	
	/// <summary>
	/// 壁と当たったかのチェック
	/// </summary>
	void CheckMapWall();

private:

	void Riflection(IMapWall*mA);

	list<IMapWall*> object_{};

	unique_ptr<MapWall> mapWall_ = nullptr;
};


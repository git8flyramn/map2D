#pragma once
#include "Library/GameObject.h"
#include <vector>
#include "globals.h"
#include <map>
class MapChip :
    public GameObject
{
public:
    MapChip();
    ~MapChip();
    void Update()override;
    void Draw() override;
    int GetHandle(int index) { return bgHandle[index]; }
    bool IsHold(); //マップのチップを持っているか
    bool GetHoldImage();//持っているマップチップのハンドル
    int GetChipIndex(int handle);
private:
    std::vector<int> bgHandle;
    std::map<int, int> HandleToIndex;
    std::vector<Rect> bgRects_;
    bool isUpdate_;
    Point selected_; //選択したマップチップの座標
    int selectedIndex_;
    bool isHold_;
    bool isInMapChipArea_;
};


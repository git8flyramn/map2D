#pragma once
#include "Library/GameObject.h"
#include <vector>

struct Rect
{
    int x, y;
};
struct Point
{
    int x, y;
    int w, h;
};
class MapChip :
    public GameObject
{
    std::vector<int> BgHandle;
    std::vector<Rect> bgRects_;
    bool isUpdate_;
    Point selected_; //選択したマップチップの座標
    int selectedIndex_;
    bool isHold_;
public:
    MapChip();
    ~MapChip();
    void Update()override;
    void Draw() override;

};


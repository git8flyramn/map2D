#pragma once
#include "Library//GameObject.h"
#include <vector> //可変長配列
#include "MapChip.h"
#include "MapEdit.h"
class Stage :
    public GameObject
{   
    //int *BgHandle; //背景画像のハンドルの配列へのポインタ(配列自体)
    //std::vector<int> BgHandle_;
    MapChip* mapChip_;
    MapEdit* mapEdit_;
   /* bool isMouseDown_;
    bool isOldMouseDown_;
    bool isDragging_;*/

public:
    Stage();
    ~Stage();
    void Update()override;
    void Draw() override;
};

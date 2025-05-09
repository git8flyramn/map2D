#pragma once
#include "Library/GameObject.h"
#include <vector>
class MapChip :
    public GameObject
{
    std::vector<int> BgHandle;
public:
    MapChip();
    ~MapChip();
    void Update()override;
    void Draw() override;

};


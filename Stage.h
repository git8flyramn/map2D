#pragma once
#include "Library//GameObject.h"
#include <vector> //�ϒ��z��
#include "MapChip.h"
#include "MapEdit.h"
class Stage :
    public GameObject
{   
    //int *BgHandle; //�w�i�摜�̃n���h���̔z��ւ̃|�C���^(�z�񎩑�)
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

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
public:
    Stage();
    ~Stage();
    void Update()override;
    void Draw() override;
};

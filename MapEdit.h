#pragma once
#include "Library/GameObject.h"
#include <vector>
#include "globals.h"
#include "MapEditConfig.h"


namespace
{
    int UP_Scale_Resize = 0;
    int Down_Scale_Resize = 0;
    int Line_resize_left = 0;
    int Line_resize_right = 0;
   
}
class MapEdit :
    public GameObject
{
public:
    MapEdit();
    ~MapEdit();

    void SetMap(Point p, int value);
    int GetMap(Point p) const;
    void Update()override;
    void Draw() override;
    bool IsInMapEditArea() const { return isInMapEditArea_; }
    void SaveMapData();
    void LoadMapData();
private:
    MapEditConfig Ecfg_; //�}�b�v�`�b�v�̐ݒ�
    std::vector<int>myMap_;
    Rect mapEditRect_; //�}�b�v�̈�̋�`
    Rect drawAreaRect_;//�`��̈�̋�`
    bool isInMapEditArea_;
    bool Scaleresize_;

};


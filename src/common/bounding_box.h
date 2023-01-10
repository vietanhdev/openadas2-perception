#ifndef BOUNDING_BOX_
#define BOUNDING_BOX_

#include <cstdint>
#include <string>

class BoundingBox {
public:
    BoundingBox()
        :class_id(0), label(""), score(0), x(0), y(0), w(0), h(0)
    {}

    BoundingBox(int32_t _class_id, std::string _label, float _score, int32_t _x, int32_t _y, int32_t _w, int32_t _h)
        :class_id(_class_id), label(_label), score(_score), x(_x), y(_y), w(_w), h(_h)
    {}

    int32_t     class_id;
    std::string label;
    float       score;
    int32_t     x;
    int32_t     y;
    int32_t     w;
    int32_t     h;
};


namespace BoundingBoxUtils
{
    float CalculateIoU(const BoundingBox& obj0, const BoundingBox& obj1);
    void Nms(std::vector<BoundingBox>& bbox_list, std::vector<BoundingBox>& bbox_nms_list, float threshold_nms_iou, bool check_class_id = false);
    void FixInScreen(BoundingBox& bbox, int32_t width, int32_t height);
}


#endif

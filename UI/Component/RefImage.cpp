//
// Created by wuru8 on 2024/6/8.
//

#include "RefImage.hpp"
#include <allegro5/allegro.h>
#include <memory>

#include "Engine/IObject.hpp"
#include "Image.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"

namespace Engine {
    RefImage::RefImage(std::string img, float x, float y, float w, float h, float anchorX, float anchorY) :
            IObject(x, y, w, h, anchorX, anchorY) {
        if (Size.x == 0 && Size.y == 0) {
            bmp = Resources::GetInstance().GetBitmap(img);
            Size.x = GetBitmapWidth();
            Size.y = GetBitmapHeight();
        }
        else if (Size.x == 0) {
            bmp = Resources::GetInstance().GetBitmap(img);
            Size.x = GetBitmapWidth() * Size.y / GetBitmapHeight();
        }
        else if (Size.y == 0) {
            bmp = Resources::GetInstance().GetBitmap(img);
            Size.y = GetBitmapHeight() * Size.x / GetBitmapWidth();
        }
        else /* Size.x != 0 && Size.y != 0 */ {
            bmp = Resources::GetInstance().GetBitmap(img, Size.x, Size.y);
        }
    }
    void RefImage::Draw() const {
        al_draw_scaled_bitmap(bmp.get(), 0, 0, GetBitmapWidth(), GetBitmapHeight(),
                              Position.x - Anchor.x * GetBitmapWidth(), Position.y - Anchor.y * GetBitmapHeight(),
                              Size.x, Size.y, 0);
    }
    int RefImage::GetBitmapWidth() const {
        return al_get_bitmap_width(bmp.get());
    }
    int RefImage::GetBitmapHeight() const {
        return al_get_bitmap_height(bmp.get());
    }

    void RefImage::ChangeImageTo(std::string img, int x, int y) {
        Position.x = x;
        Position.y = y;
        if (Size.x == 0 && Size.y == 0) {
            bmp = Resources::GetInstance().GetBitmap(img);
            Size.x = GetBitmapWidth();
            Size.y = GetBitmapHeight();
        }
        else if (Size.x == 0) {
            bmp = Resources::GetInstance().GetBitmap(img);
            Size.x = GetBitmapWidth() * Size.y / GetBitmapHeight();
        }
        else if (Size.y == 0) {
            bmp = Resources::GetInstance().GetBitmap(img);
            Size.y = GetBitmapHeight() * Size.x / GetBitmapWidth();
        }
        else /* Size.x != 0 && Size.y != 0 */ {
            bmp = Resources::GetInstance().GetBitmap(img, Size.x, Size.y);
        }
    }
}




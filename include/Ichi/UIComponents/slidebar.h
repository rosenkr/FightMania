#ifndef SLIDEBAR_H
#define SLIDEBAR_H
#include "Ichi/UIComponents/uicomponent.h"
#include "Ichi/Graphics/sprite.h"
#include "Ichi/DataTypes/hitbox.h"
namespace ichi::uicomponents
{
    class SlideBar : public UIComponent
    {
    public:
        SlideBar(const datatypes::Hitbox &barHitbox, const graphics::Sprite &barSprite, int sliderWidth, int sliderHeight, const std::string &sliderPath, const std::string &fs, std::function<void(float)> ptr);
        void update();
        void draw() const;
        float getSliderValue() const;

        ~SlideBar()
        {
            delete sliderSprite;
            delete focusedSliderSprite;
            delete sliderHitbox;
            sliderHitbox = nullptr;
            sliderSprite = nullptr;
            focusedSliderSprite = nullptr;
        }

    private:
        void updateNormalizedSliderValue();
        graphics::Sprite barSprite;
        graphics::Sprite *sliderSprite;
        graphics::Sprite *focusedSliderSprite;
        datatypes::Hitbox *sliderHitbox;
        std::function<void(float)> valueSetter;
        float sliderValue;
        bool isDragging;
    };
}

#endif
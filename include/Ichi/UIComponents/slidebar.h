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
        SlideBar(const datatypes::Hitbox &barHitbox, const graphics::Sprite &barSprite, int sliderWidth, int sliderHeight, const std::string &sliderPath, const std::string &fs);
        void update();
        void draw() const;
        float getSliderValue() const;

        ~SlideBar()
        {
            delete sliderSprite;
            delete focusedSliderSprite;
            sliderSprite = nullptr;
            focusedSliderSprite = nullptr;
        }

    private:
        void updateNormalizedSliderValue();
        graphics::Sprite barSprite;
        graphics::Sprite *sliderSprite;
        graphics::Sprite *focusedSliderSprite;
        float sliderValue;
        bool isDragging;
    };
}

#endif
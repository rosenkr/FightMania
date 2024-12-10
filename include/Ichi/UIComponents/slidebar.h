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
        SlideBar(const datatypes::Hitbox &barHitbox, const graphics::Sprite &barSprite, const graphics::Sprite &sliderSpritePath, const graphics::Sprite &focusedSliderSpritePath);
        void update();
        void draw() const;
        float getSliderValue() const;

    private:
        void updateNormalizedSliderValue(int sliderX, int barX, int sliderWidth, int barWidth);
        graphics::Sprite barSprite;
        graphics::Sprite sliderSprite;
        graphics::Sprite focusedSliderSprite;
        float sliderValue;
        bool isDragging;
    };
}

#endif
#ifndef SLIDEBAR_H
#define SLIDEBAR_H

#include "Ichi/UIComponents/uicomponent.h"

#include "Ichi/Graphics/sprite.h"
#include "Ichi/DataTypes/hitbox.h"

#include <memory>

namespace ichi::uicomponents
{
    class SlideBar : public UIComponent
    {
    public:
        SlideBar(const datatypes::Hitbox &barHitbox, const graphics::Sprite &barSprite, int sliderWidth, int sliderHeight, const std::string &sliderPath, const std::string &fs, std::function<void(float)> ptr);
        void update();
        void draw() const;
        float getSliderValue() const;

        bool isAtBegining() { return sliderSprite.get()->getX() == hitbox.getX(); }
        bool isAtEnd() { return sliderSprite.get()->getX() == (hitbox.getX() + hitbox.getWidth() - sliderSprite->getWidth() / 2); }

    private:
        void updateNormalizedSliderValue();
        graphics::Sprite barSprite;
        std::unique_ptr<graphics::Sprite> sliderSprite;
        std::unique_ptr<graphics::Sprite> focusedSliderSprite;
        std::function<void(float)> valueSetter;
        float sliderValue;
        bool isDragging;

        const float CONTROLLER_SPEED = 1;
    };
}

#endif
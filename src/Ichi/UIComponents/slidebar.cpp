
#include "Ichi/UIComponents/slidebar.h"
#include "Ichi/UIComponents/uicomponent.h"
#include "Ichi/Graphics/sprite.h"
#include "Ichi/DataTypes/hitbox.h"
#include "Ichi/log.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/Core/engine.h"
#include "Ichi/Graphics/textureManager.h"
#include <algorithm>
using namespace ichi::datatypes;
namespace ichi::uicomponents
{

    SlideBar::SlideBar(const Hitbox &barHitbox, const graphics::Sprite &barSprite, int sliderWidth, int sliderHeight, const std::string &sliderPath, const std::string &focusedSliderPath)
        : UIComponent(barHitbox), barSprite(barSprite)
    {
        auto barCenter = Point(barSprite.getX() + barSprite.getWidth() / 2, barSprite.getY() + barSprite.getHeight() / 2);
        auto sliderCenter = Point(sliderWidth / 2, sliderHeight / 2);

        sliderHitbox = new Hitbox(barCenter - sliderCenter, sliderWidth, sliderHeight, false);
        sliderSprite = new graphics::Sprite(*sliderHitbox, graphics::Sprite::Layer::UICOMPONENT, sliderPath);
        focusedSliderSprite = new graphics::Sprite(*sliderHitbox, graphics::Sprite::Layer::UICOMPONENT, focusedSliderPath);
    }

    void SlideBar::update()
    {
        if (input::Mouse::DX() != 0 || input::Mouse::DY() != 0)
            focused = hitbox.pointIsInRect(Point(input::Mouse::getX(), input::Mouse::getY()));

        if (focused && input::Mouse::buttonIsDown(input::Mouse::MouseButton::LEFT))
            sliderSprite->setX(input::Mouse::getX() - sliderSprite->getWidth() / 2);

        updateNormalizedSliderValue();
    }

    void SlideBar::draw() const
    {
        barSprite.draw();

        if (focused)
            focusedSliderSprite->draw();
        else
            sliderSprite->draw();
    }

    float SlideBar::getSliderValue() const
    {
        return sliderValue;
    }

    // Update slider value 0-1
    void SlideBar::updateNormalizedSliderValue()
    {
        int pixels = (sliderSprite->getX() + sliderSprite->getWidth() / 2) - barSprite.getX(); // Distance between the middle of slider to bar X pos

        sliderValue = pixels / (float)barSprite.getWidth();

        sliderValue = std::clamp(sliderValue, 0.0f, 1.0f);
        sliderValue = std::round(sliderValue * 100.0f) / 100.0f; // two decimals

        ICHI_INFO("SliderValue: {}", sliderValue);
        this->sliderValue = sliderValue;
    }
}
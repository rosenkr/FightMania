
#include "Ichi/Graphics/textureManager.h"

#include "Ichi/UIComponents/uicomponent.h"
#include "Ichi/UIComponents/slidebar.h"

#include "Ichi/DataTypes/hitbox.h"

#include "Ichi/Graphics/sprite.h"

#include "Ichi/Input/controllerHandler.h"
#include "Ichi/Input/mouse.h"

#include "Ichi/Core/engine.h"

#include "Ichi/log.h"

#include <algorithm>

using namespace ichi::datatypes;

namespace ichi::uicomponents
{

    SlideBar::SlideBar(const Hitbox &barHitbox, const graphics::Sprite &barSprite, int sliderWidth, int sliderHeight, const std::string &sliderPath, const std::string &focusedSliderPath, std::function<void(float)> ptr)
        : UIComponent(barHitbox), barSprite(barSprite), valueSetter(ptr)
    {
        auto barCenter = Point(barSprite.getX() + barSprite.getWidth() / 2, barSprite.getY() + barSprite.getHeight() / 2);
        auto sliderCenter = Point(sliderWidth / 2, sliderHeight / 2);

        Hitbox sliderHitbox(barCenter - sliderCenter, sliderWidth, sliderHeight, false);
        sliderSprite = std::make_unique<graphics::Sprite>(sliderHitbox, graphics::Sprite::Layer::UICOMPONENT, sliderPath);
        focusedSliderSprite = std::make_unique<graphics::Sprite>(sliderHitbox, graphics::Sprite::Layer::UICOMPONENT, focusedSliderPath);
    }

    void SlideBar::update()
    {
        if (input::Mouse::DX() != 0 || input::Mouse::DY() != 0)
            focused = hitbox.pointIsInRect(Point(input::Mouse::getX(), input::Mouse::getY()));

        if (hitbox.pointIsInRect(Point(input::Mouse::getX(), input::Mouse::getY())) && input::Mouse::buttonIsDown(input::Mouse::MouseButton::LEFT))
        {
            sliderSprite->setX(input::Mouse::getX() - sliderSprite->getWidth() / 2);
            focusedSliderSprite->setX(sliderSprite->getX());
        }

        if (!focused || input::ControllerHandler::getTotalLeftStickX() == 0)
        {
            updateNormalizedSliderValue();
            return;
        }

        auto value = sliderSprite.get()->getX() + static_cast<int>(input::ControllerHandler::getTotalLeftStickX() * CONTROLLER_SPEED);
        sliderSprite->setX(std::clamp(value, hitbox.getX(), hitbox.getX() + hitbox.getWidth() - sliderSprite->getWidth() / 2));
        focusedSliderSprite->setX(sliderSprite->getX());

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

        this->sliderValue = sliderValue;
        valueSetter(sliderValue);
    }
}

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

    SlideBar::SlideBar(const Hitbox &barHitbox, const graphics::Sprite &barSprite, const graphics::Sprite &ss, const graphics::Sprite &fs)
        : UIComponent(barHitbox), barSprite(barSprite), sliderSprite(ss), focusedSliderSprite(fs) {}

    void SlideBar::update()
    {
        if (input::Mouse::DX() != 0 || input::Mouse::DY() != 0)
            focused = hitbox.pointIsInRect(Point(ichi::input::Mouse::getX(), ichi::input::Mouse::getY()));

        bool btnPressedOrDown = (ichi::input::Mouse::buttonIsPressed(ichi::input::Mouse::MouseButton::LEFT) ||
                                 ichi::input::Mouse::buttonIsDown(ichi::input::Mouse::MouseButton::LEFT));

        if (focused && btnPressedOrDown)
        {
            sliderSprite.setX(ichi::input::Mouse::getX() - sliderSprite.getWidth() / 2);
        }

        int sliderX = sliderSprite.getHitbox().getX();
        int barX = barSprite.getHitbox().getX();
        int sliderWidth = sliderSprite.getHitbox().getWidth();
        int barWidth = barSprite.getHitbox().getWidth();
        updateNormalizedSliderValue(sliderX, barX, sliderWidth, barWidth);
    }

    void SlideBar::draw() const
    {
        barSprite.draw();
        if (focused)
        {
            focusedSliderSprite.draw();
        }
        else
        {
            sliderSprite.draw();
        }
    }

    // Return slider value 0-1
    float SlideBar::getSliderValue() const
    {
        return sliderValue;
    }

    // Update slider value 0-1
    void SlideBar::updateNormalizedSliderValue(int sliderX, int barX, int sliderWidth, int barWidth)
    {
        int dx = sliderX - barX;

        float sliderValue = static_cast<float>(dx) / barWidth;
        sliderValue = std::clamp(sliderValue, 0.0f, 1.0f);
        sliderValue = std::round(sliderValue * 100.0f) / 100.0f;
        ICHI_INFO("SliderValue: {}", sliderValue);
        this->sliderValue = sliderValue;
    }
}

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
namespace ichi::uicomponents{
 
    SlideBar::SlideBar(const Hitbox& barHitbox, 
                   const graphics::Sprite& barSprite, 
                   std::string sliderSpritePath, 
                   std::string focusedSliderSpritePath)
    : UIComponent(barHitbox), 
      sliderHitbox(Hitbox(
                      Point(barHitbox.getX() + barHitbox.getWidth() / 2, barHitbox.getY() + (barHitbox.getHeight() - barHitbox.getHeight() * 2) / 2),
                      barHitbox.getHeight(), 
                      barHitbox.getHeight() * 2, 
                      false)),
      barSprite(barSprite),
      sliderSprite(sliderHitbox, graphics::Sprite::Layer::UICOMPONENT, sliderSpritePath),
      focusedSliderSprite(sliderHitbox, graphics::Sprite::Layer::UICOMPONENT, focusedSliderSpritePath) {}


    void SlideBar::update() {

        focused = hitbox.pointIsInRect(Point(ichi::input::Mouse::getX(), ichi::input::Mouse::getY()));
        bool btnPressedOrDown = (ichi::input::Mouse::buttonIsPressed(ichi::input::Mouse::MouseButton::LEFT) ||
            ichi::input::Mouse::buttonIsDown(ichi::input::Mouse::MouseButton::LEFT));

        if (focused && btnPressedOrDown) {
            sliderHitbox.setX(ichi::input::Mouse::getX());
        }

        int sliderX = sliderSprite.getHitbox().getX();
        int barX = barSprite.getHitbox().getX();
        int sliderWidth = sliderSprite.getHitbox().getWidth();
        int barWidth = barSprite.getHitbox().getWidth();
        updateNormalizedSliderValue(sliderX, barX, sliderWidth, barWidth);
    }

    void SlideBar::draw() const {
        barSprite.draw();
        if (focused) {
            focusedSliderSprite.draw();
        } else {
            sliderSprite.draw();
        }
    }

    // Return slider value 0-1
    float SlideBar::getSliderValue() const {
        return sliderValue;
    }

    // Update slider value 0-1
    void SlideBar::updateNormalizedSliderValue(int sliderX, int barX, int sliderWidth, int barWidth) { 
        int dx = sliderX - barX;

        float sliderValue = static_cast<float>(dx) / barWidth;
        sliderValue = std::clamp(sliderValue, 0.0f, 1.0f);
        sliderValue = std::round(sliderValue * 100.0f) / 100.0f;
        ICHI_INFO("SliderValue: {}", sliderValue);
        this->sliderValue = sliderValue;
    }
}
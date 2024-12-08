#include "Ichi/UIComponents/checkbox.h"
#include "Ichi/Core/engine.h"
#include "Ichi/log.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/Input/controllerHandler.h"

using namespace ichi::input;
namespace ichi::uicomponents
{
    Checkbox::Checkbox(const datatypes::Hitbox &hb, const graphics::Sprite &us, const graphics::Sprite &cs, bool checked) : UIComponent(hb), isChecked(checked), uncheckedSprite(us), checkedSprite(cs) {}

    // Toggles isChecked on mouse/keyboard input
    void Checkbox::update()
    {
        if (focused && (Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_RETURN) ||
                        Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_SPACE) ||
                        ControllerHandler::anyControllerIsPressing(ControllerHandler::ControllerButton::A)))
            isChecked = !isChecked;

        if (hitbox.pointIsInRect(datatypes::Point(Mouse::getX(), Mouse::getY())) && Mouse::buttonIsPressed(Mouse::MouseButton::LEFT))
            isChecked = !isChecked;
    }

    void Checkbox::draw() const
    {
        if (isChecked)
            checkedSprite.draw();
        else
            uncheckedSprite.draw();
    }
}

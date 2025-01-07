#include "Ichi/UIComponents/checkbox.h"
#include "Ichi/Core/engine.h"
#include "Ichi/log.h"
#include "Ichi/Input/keyboard.h"
#include "Ichi/Input/mouse.h"
#include "Ichi/Input/controllerHandler.h"

using namespace ichi::input;
namespace ichi::uicomponents
{
    Checkbox::Checkbox(const datatypes::Hitbox &hb, const graphics::Sprite &fus, const graphics::Sprite &fcs, const graphics::Sprite &us, const graphics::Sprite &cs, bool checked)
        : UIComponent(hb), checked(checked), focusedUncheckedSprite(fus), focusedCheckedSprite(fcs), uncheckedSprite(us), checkedSprite(cs) {}

    // Toggles checked on mouse/keyboard input
    void Checkbox::update()
    {
        if (Mouse::DX() != 0 || Mouse::DY() != 0)
            setFocus(hitbox.pointIsInRect(datatypes::Point(Mouse::getX(), Mouse::getY())));

        if (focused && (Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_RETURN) || Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_SPACE) ||
                        ControllerHandler::anyControllerIsPressing(ControllerHandler::ControllerButton::A)))
            checked = !checked;

        if (hitbox.pointIsInRect(datatypes::Point(Mouse::getX(), Mouse::getY())) && Mouse::buttonIsPressed(Mouse::MouseButton::LEFT))
            checked = !checked;
    }

    void Checkbox::draw() const
    {
        if (!focused)
        {
            if (checked)
                checkedSprite.draw();
            else
                uncheckedSprite.draw();
            return;
        }
        if (checked)
            focusedCheckedSprite.draw();
        else
            focusedUncheckedSprite.draw();
    }
}

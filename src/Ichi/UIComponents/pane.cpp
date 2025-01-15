#include "Ichi/UIComponents/pane.h"

#include "Ichi/UIComponents/label.h"
#include "Ichi/UIComponents/textbox.h"
#include "Ichi/UIComponents/slidebar.h"

#include "Ichi/Input/controllerHandler.h"
#include "Ichi/Input/keyboard.h"

using namespace ichi::input;

namespace ichi::uicomponents
{

    void Pane::update()
    {
        lastFocused = focused;

        bool everyComponentIsUnFocused = true;

        for (auto c : uiComponents)
        {
            c.second.get()->update();
            if (c.second.get()->isFocused())
            {
                everyComponentIsUnFocused = false;
                if (c.second.get()->getHitbox().getPos() != focused)
                {
                    focused = c.first;
                    break;
                }
            }
        }

        bool down = ControllerHandler::anyControllerIsPressing(ControllerHandler::ControllerButton::DPAD_Down) || Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_DOWN) || ControllerHandler::getTotalLeftStickY() > 0;
        bool up = ControllerHandler::anyControllerIsPressing(ControllerHandler::ControllerButton::DPAD_Up) || Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_UP) || ControllerHandler::getTotalLeftStickY() < 0;
        bool left = ControllerHandler::anyControllerIsPressing(ControllerHandler::ControllerButton::DPAD_Left) || Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_LEFT) || ControllerHandler::getTotalLeftStickX() < 0;
        bool right = ControllerHandler::anyControllerIsPressing(ControllerHandler::ControllerButton::DPAD_Right) || Keyboard::keyIsPressed(Keyboard::Key::ICHIKEY_RIGHT) || ControllerHandler::getTotalLeftStickX() > 0;

        if ((down && up) || (left && right))
            return;

        if (everyComponentIsUnFocused && !(down || up || left || right)) //
        {
            focused = {-1, -1};
            return;
        }

        datatypes::Point p;

        if (down)
        {
            p = findClosestPoint(0, -1);
            if (p != datatypes::Point{-1, -1})
                focused = p;
        }

        if (up)
        {
            p = findClosestPoint(0, 1);
            if (p != datatypes::Point{-1, -1})
                focused = p;
        }

        if (left)
        {
            p = findClosestPoint(-1, 0);
            if (p != datatypes::Point{-1, -1})
            {
                auto it = uiComponents.find(focused);
                if (it != uiComponents.end())
                {
                    if (auto ptr = dynamic_cast<uicomponents::Textbox *>(it->second.get()))
                        if (left && ptr->canMoveCursorLeft())
                            return;

                    if (auto ptr = dynamic_cast<uicomponents::SlideBar *>(it->second.get()))
                        if (left && !ptr->isAtBegining())
                            return;
                }
                focused = p;
            }
        }

        if (right)
        {
            p = findClosestPoint(1, 0);
            if (p != datatypes::Point{-1, -1})
            {
                auto it = uiComponents.find(focused);
                if (it != uiComponents.end())
                {
                    if (auto ptr = dynamic_cast<uicomponents::Textbox *>(it->second.get()))
                        if (right && ptr->canMoveCursorRight())
                            return;

                    if (auto ptr = dynamic_cast<uicomponents::SlideBar *>(it->second.get()))
                        if (right && !ptr->isAtEnd())
                            return;
                }
                focused = p;
            }
        }

        if (lastFocused != focused && uiComponents.find(lastFocused) != uiComponents.end())
            uiComponents[lastFocused].get()->setFocus(false);

        if (uiComponents.find(focused) != uiComponents.end())
            uiComponents[focused].get()->setFocus(true);
    }

    datatypes::Point Pane::findClosestPoint(int deltaX, int deltaY)
    {
        datatypes::Point closestPoint{-1, -1};

        for (auto &c : uiComponents)
        {
            if (dynamic_cast<uicomponents::Label *>(c.second.get()))
                continue;

            bool isValidDirection = (deltaY == 0 || (deltaY < 0 && focused.Y < c.first.Y) || (deltaY > 0 && focused.Y > c.first.Y)) &&
                                    (deltaX == 0 || (deltaX < 0 && focused.X > c.first.X) || (deltaX > 0 && focused.X < c.first.X));

            if (!isValidDirection)
                continue;

            if (closestPoint == datatypes::Point{-1, -1} || c.first.distanceTo(focused) < closestPoint.distanceTo(focused))
                closestPoint = c.first;
        }

        return closestPoint;
    }

    void Pane::draw() const
    {
        for (auto c : uiComponents)
            c.second.get()->draw();
    }

} // namespace ichi::uicomponents

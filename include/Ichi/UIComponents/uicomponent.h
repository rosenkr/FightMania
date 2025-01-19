#ifndef UICOMPONENT_H
#define UICOMPONENT_H
#include "Ichi/Core/component.h"
namespace ichi::uicomponents
{
    class UIComponent : public core::Component
    {
    public:
        void setFocus(bool val) { focused = val; }
        bool isFocused() const { return focused; }

        virtual void update() = 0;
        virtual void draw() const = 0;
        virtual void handleinput() {};

        virtual ~UIComponent() = default;

    protected:
        UIComponent(datatypes::Hitbox hb) : Component(hb) {}
        bool focused = false;
    };
}
#endif
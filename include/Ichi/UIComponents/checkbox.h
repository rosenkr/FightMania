#ifndef CHECKBOX_H
#define CHECKBOX_H
#include "Ichi/UIComponents/uicomponent.h"
#include "Ichi/Graphics/sprite.h"
#include "Ichi/DataTypes/hitbox.h"
namespace ichi::uicomponents
{
    class Checkbox : public UIComponent
    {
    public:
        Checkbox(const datatypes::Hitbox &hb, const graphics::Sprite &fus, const graphics::Sprite &fcs, const graphics::Sprite &us, const graphics::Sprite &cs, bool checked = false);
        void update();
        void draw() const;

    private:
        bool isChecked;
        graphics::Sprite focusedUncheckedSprite;
        graphics::Sprite focusedCheckedSprite;
        graphics::Sprite uncheckedSprite;
        graphics::Sprite checkedSprite;
    };
}

#endif
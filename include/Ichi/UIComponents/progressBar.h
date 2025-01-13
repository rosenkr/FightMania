#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include "Ichi/UIComponents/uicomponent.h"
#include "Ichi/Graphics/sprite.h"

namespace ichi::uicomponents
{

    class ProgressBar : public UIComponent
    {
    public:
        ProgressBar(datatypes::Hitbox, graphics::Sprite, std::string, bool);

        void update() {}
        void draw() const;
        void setProcentageFilled(float);

        ~ProgressBar()
        {
            SDL_DestroyTexture(color);
            color = nullptr;
        };

    private:
        graphics::Sprite bar;
        SDL_Texture *color;
        float procentageFilled = 1; // 0-1 is the range
        bool isMirrored = false;
    };

} // namespace ichi::uicomponents

#endif
#ifndef LABEL_H
#define LABEL_H

#include "Ichi/UIComponents/uicomponent.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <string>

namespace ichi::uicomponents
{
    class Label : public UIComponent
    {
    public:
        Label(datatypes::Hitbox h, const std::string &s, TTF_Font *f, SDL_Color c);
        ~Label()
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }

        void update() {}
        void draw() const;

    private:
        SDL_Texture *texture;
    };

} // namespace ichi::uicomponents

#endif
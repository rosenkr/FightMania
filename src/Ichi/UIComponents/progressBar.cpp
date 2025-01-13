#include "Ichi/UIComponents/progressBar.h"
#include "Ichi/Core/engine.h"
#include "SDL2/SDL_image.h"

#include <algorithm>

namespace ichi::uicomponents
{

    ProgressBar::ProgressBar(datatypes::Hitbox hb, graphics::Sprite s, std::string path, bool mirror = false) : UIComponent(hb), bar(s), isMirrored(mirror)
    {
        SDL_Surface *surf = IMG_Load(path.c_str());

        if (surf == nullptr)
            return;

        SDL_Texture *texture = SDL_CreateTextureFromSurface(core::Engine::getInstance()->getRenderer(), surf);

        SDL_FreeSurface(surf);

        if (texture == nullptr)
            return;

        color = texture;
    }

    void ProgressBar::draw() const
    {
        auto hb = datatypes::Hitbox(datatypes::Point(hitbox.getX(), hitbox.getY()), hitbox.getWidth() * procentageFilled, hitbox.getHeight(), false);
        if (isMirrored)
            hb.setX(hitbox.getX() + (hitbox.getWidth() - hb.getWidth()));
        SDL_RenderCopy(core::Engine::getInstance()->getRenderer(), color, NULL, hb.getSDLRect());

        bar.draw();
    }

    void ProgressBar::setProcentageFilled(float f)
    {
        procentageFilled = std::clamp(f, 0.f, 1.f);
    }

} // namespace ichi::uicomponents

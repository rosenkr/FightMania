#ifndef SPRITE_H
#define SPRITE_H
namespace ichi::graphics
{
    class Sprite
    {
    public:
        // Define operator< for Sprite comparison, usage in textureManager std::map
        bool operator<(const Sprite &other) const
        {
            return id < other.id;
        }

    private:
        int id; // Temporary
    };
}
#endif
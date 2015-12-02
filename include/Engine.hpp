#ifndef ENGINE_HPP
#define ENGINE_HPP


class Engine
{
    public:
        Engine();
        virtual ~Engine();
        bool collisionAABB(AABB box1, AABB box2);
    protected:
    private:
};

#endif // ENGINE_HPP

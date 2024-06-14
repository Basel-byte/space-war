#ifndef VISUALEFFECT_H
#define VISUALEFFECT_H

class VisualEffect {
public:
    virtual void updateFireballs() = 0;
    virtual void renderFireballs() = 0;
    virtual bool isAlive() = 0;

    virtual ~VisualEffect() = default;
};

#endif //VISUALEFFECT_H
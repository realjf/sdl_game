#ifndef _LAYER_H_
#define _LAYER_H_

#include <vector>

class Layer;
class Level;

class Layer {
public:
    virtual void render() = 0;
    virtual void update(Level *pLevel) = 0;

    virtual ~Layer() {}
};

#endif /* _LAYER_H_ */

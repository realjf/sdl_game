#ifndef _LAYER_H_
#define _LAYER_H_

#include <vector>

class Layer {
public:
    virtual void render() = 0;
    virtual void update() = 0;

protected:
    virtual ~Layer() {}
};

#endif /* _LAYER_H_ */

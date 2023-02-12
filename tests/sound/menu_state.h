#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

class MenuState : public GameState {
public:
    virtual ~MenuState() {}

protected:
    typedef void (*Callback)();
    virtual void setCallbacks(const std::vector<Callback> &callbacks) = 0;

    std::vector<Callback> m_callbacks;
};

#endif /* _MENU_STATE_H_ */

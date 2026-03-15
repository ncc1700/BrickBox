//
// Created by maks on 10.03.2026.
//

#ifndef BRICKBOX_ABSTRACTRENDERLOOP_H
#define BRICKBOX_ABSTRACTRENDERLOOP_H

class Window;

class AbstractRenderer {
public:
    explicit AbstractRenderer(Window &window);
    virtual ~AbstractRenderer() = default;
    virtual void loop() = 0;
protected:
    Window& parent;
};

#endif //BRICKBOX_ABSTRACTRENDERLOOP_H
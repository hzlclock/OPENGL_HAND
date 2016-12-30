#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include "gl_viewer.h"
#include "timer.h"

class line_segment {
public:
    line_segment(int x0, int y0, int x1, int y1)
            : x0(x0), y0(y0), x1(x1), y1(y1) {}

    int x0, y0, x1, y1;


};

class application : public gl_viewer {
public:
    application();

    ~application();

    void init_event();

    void draw_event();

    void mouse_click_event(int button, int button_state, int x, int y);

    void mouse_move_event(int x, int y);

    void keyboard_event(unsigned char key, int x, int y);

private:
    bool solid;
    timer t;
    const float size[8] = {2, 2.5, 3, 3, 5, 5, 4, 3};
    const float rad[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    const float speed[8] = {1, 0.9, 0.7, 0.6, 0.4, 0.3, 0.2, 0.1};
    const float startDeg[8] = {15, 842, 564, 18, 589, 66, 107, 25};
    const unsigned int color[9] = {
            0xD2D2D2, 0xF9C368, 0x0071E7, 0xF69600, 0xE4B9A3, 0xE4CBA3, 0x0CFFE2, 0x0199E1, 0xFFE3B0
    };

    inline void begin_RotateAroundTheSun(float, float, int);

    inline void end_RotateAroundTheSun();

    inline float getRed(unsigned int color) { return float(color >> 16) / 256; }

    inline float getBlue(unsigned int color) { return float(color % 256) / 256; }

    inline float getGreen(unsigned int color) { return float((color >> 8) % 256) / 256; }
};

#endif

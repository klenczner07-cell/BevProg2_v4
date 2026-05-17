#include "application.hpp"
#include "widgets.hpp"
#include "graphics.hpp"

using namespace genv;

Application::Application(int ablakSzel, int ablakMag) {
    gout.open(ablakSzel, ablakMag);
}

Application::~Application() {
    for (Widget* w : widgets)
        delete w;
}

void Application::register_widget(Widget* w) {
    widgets.push_back(w);
}

void Application::event_loop() {
    event esem;
    int fokusz = -1;

    for (Widget* w : widgets)
        w->draw();
    gout << refresh;

    while (gin >> esem && esem.keycode != key_escape) {
        if (esem.type == ev_mouse && esem.button == btn_left) {
            for (size_t i = 0; i < widgets.size(); i++) {
                if (widgets[i]->is_selected(esem.pos_x, esem.pos_y)) {
                    fokusz = i;
                }
            }
        }

        if (fokusz != -1)
            widgets[fokusz]->handle(esem);

        for (Widget* w : widgets)
            w->draw();
        gout << refresh;
    }
}

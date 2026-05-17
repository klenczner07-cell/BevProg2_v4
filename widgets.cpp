#include "widgets.hpp"
#include "application.hpp"

Widget::Widget(Application* szulo, int x, int y, int sx, int sy) :
    _x(x), _y(y), _size_x(sx), _size_y(sy), _parent(szulo)
{
    if (_parent)
        _parent->register_widget(this);
}

Widget::~Widget() {}

bool Widget::is_selected(int egx, int egy) {
    return egx > _x && egx < _x + _size_x && egy > _y && egy < _y + _size_y;
}

#include "cell.h"

Cell::Cell()
{
    color = WHITE;
    number = NOT_INITIALIZE;
    illumination = false;
    dual_illumination = false;
    lantern = false;
    cross = false;
}

void Cell::set_color(bool _color)
{
    color = _color;
}

bool Cell::is_white()
{
    return color == WHITE? true : false;
}

bool Cell::is_black()
{
    return color == BLACK? true : false;
}

void Cell::set_number(int _number)
{
    number = _number;
}

int Cell::get_number()
{
    return number;
}

void Cell::set_lantern()
{
    lantern = true;
    set_illumination();
}

void Cell::delete_lantern()
{
    lantern = false;
    delete_illumination();
}

bool Cell::is_lantern()
{
    return lantern;
}


void Cell::set_illumination()
{
    if (illumination)
        dual_illumination = true;
    else
        illumination = true;
}

void Cell::delete_illumination()
{
    if (dual_illumination)
        dual_illumination = false;
    else
        illumination = false;
}

bool Cell::is_illumination()
{
    return illumination;
}


void Cell::set_cross()
{
    cross = true;
}

void Cell::delete_cross()
{
    cross = false;
}

bool Cell::is_cross()
{
    return cross;
}
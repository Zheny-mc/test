/*
#include "solution.h"

void Solution::install_obvious_lanterns_around_black_cells()
{
    List<Coor_cell> places = find_seats_around_black_cell();

    while (!places.empty())
    {
        for (int i = 0; i < places.size(); i++)
            install_lantern(places[i].y, places[i].x);
        cout << to_show() << endl;

        places = find_seats_around_black_cell();
    }

    //cout << to_show() << endl;
}

void Solution::install_empty_cells()
{
    List<Coor_cell> places = find_not_illuminate_seat();

    while (!places.empty())
    {
        install_lantern(places[0].y, places[0].x);
            
        cout << to_show() << endl;

        places = find_not_illuminate_seat();
    }
}
*/
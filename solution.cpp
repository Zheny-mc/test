#include "solution.h"

void Solution::setup_lunterns(Field field)
{
    if (field.is_full_lunterns())
    {
        save_map(field.get_map());
        cout << to_show() << endl;
        return;
    }
    
    vector<Coor_cell> places = field.find_places_for_lunterns();
    
    for (int i = 0; i < places.size(); i++)
    {
        if (field.is_can_install_luntern(places[i]))
        {
            field.install_lantern(places[i].y, places[i].x);
            setup_lunterns(field);
            field.remove_lantern(places[i].y, places[i].x);
        }
    }
}

void Solution::backlight_cells(Field field)
{

}

void Solution::find_decision()
{
    Field field;

    field.install_places_for_cross();
    field.install_places_for_simple_luntern();
    save_map(field.get_map());
    cout << to_show() << endl;

    setup_lunterns(field);
    field.save_map(get_map());
    //backlight_cells(field);
    
    cout << to_show() << endl;
}


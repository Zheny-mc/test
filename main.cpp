#include "field.h"

int main()
{
    Field field;

    cout << field.to_show() << '\n';
    field.install_places_for_cross();
    cout << field.to_show() << '\n';

    field.install_places_for_simple_luntern();
    cout << field.to_show() << '\n';  

    return 0;
}
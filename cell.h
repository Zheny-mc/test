#include <iostream>
#define BLACK false
#define WHITE true
#define NOT_INITIALIZE -1

class Cell
{
public:
    Cell();

    void set_color(bool _color);
    bool is_white();
    bool is_black();

    void set_number(int _number);
    int  get_number();

    void set_lantern();
    void delete_lantern();
    bool is_lantern();

    void set_illumination();
    void delete_illumination();
    bool is_illumination();

    void set_cross();
    void delete_cross();
    bool is_cross();
    
private:
    bool color;
    int  number;
    bool lantern;
    bool illumination;
    bool dual_illumination;
    bool cross;
};
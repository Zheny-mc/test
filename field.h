#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "colormod.h"
#include "cell.h"

using std::vector;
using std::string;
using std::ifstream;
using std::cout;
using std::endl;

#define MAP "map.txt"
#define CHAR_WHITE '*'
#define PLACES_FOR_CROSS 0

int to_int(char chr);

class Coor_cell
{
public:
    int y;
    int x;
    int number;

    Coor_cell(int _y=0, int _x=0, int _number=0) : 
              y(_y), x(_x), number(_number) {}

};

class Field
{
public:
    Field();
    ~Field() {}

    //***********************************************
    vector<Coor_cell> find_places_for_cross();
    void install_places_for_cross();

    //************************************************
    vector<Coor_cell> find_black_cells_whis_simple_luntern();
    vector<Coor_cell> find_places_for_simple_luntern();
    void install_places_for_simple_luntern();

    void mark_illumination_area(int _y, int _x);
    void install_lantern(int y, int x);

    void unmark_illumination_area(int _y, int _x);
    void remove_lantern(int y, int x);
    //***********************************************
    bool is_game_over();

    string to_show();
    //************************************************************

private:
    bool is_check_board(int y, int x);

private:
    int SIZE;
    vector<vector<Cell>> map;

public:
    vector<Coor_cell> coor_black_cell;

};



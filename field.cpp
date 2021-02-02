#include "field.h"

int to_int(char chr) { return int(chr) - 48; }

vector<vector<Cell>> Field::get_map() const { return map; }

Field::Field()
{
    ifstream file(MAP);

    file >> SIZE;
    map = vector(SIZE, vector<Cell>(SIZE));

    char cur_value;

    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            file >> cur_value;

            if (cur_value != CHAR_WHITE)
            {
                map[y][x].set_color(BLACK);
                map[y][x].set_number( to_int(cur_value) );

                coor_black_cell.push_back(Coor_cell(y, x, to_int(cur_value)));
            }
        }
    }

    file.close();
}

void Field::save_map(const vector<vector<Cell>>& obj)
{ 
    map = obj; 
}

string Field::to_show()
{
    Color::Modifier fg_white(Color::FG_WHITE);
    Color::Modifier fg_yellow(Color::FG_YELLOW);
    Color::Modifier fg_def(Color::FG_DEFAULT);

    Color::Modifier bg_white(Color::BG_WHITE);
    Color::Modifier bg_black(Color::BG_BLACK);
    Color::Modifier bg_blue(Color::BG_BLUE);
    Color::Modifier bg_def(Color::BG_DEFAULT);

    std::stringstream ss;

    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            if (map[y][x].is_black())
                ss << bg_black << fg_white << map[y][x].get_number() << fg_def << bg_def;
            if (map[y][x].is_white())
            {
                if (!map[y][x].is_illumination())
                {
                    if (map[y][x].is_cross())
                        ss << bg_white << 'x' << bg_def;
                    else
                        ss << bg_white << ' ' << bg_def;
                }
                else if (map[y][x].is_illumination() && !map[y][x].is_lantern())
                {
                    if (map[y][x].is_cross())
                        ss << bg_blue << 'x' << bg_def;
                    else
                        ss << bg_blue << ' ' << bg_def;
                }
                else if (map[y][x].is_illumination() && map[y][x].is_lantern())
                    ss << bg_blue << fg_yellow << '*' << fg_def << bg_def;
            }

        }
        ss << '\n';
    }

    ss << bg_def;

    return ss.str();
}

bool Field::is_check_board(int y, int x)
{
    return (y < 0 || y >= SIZE || x < 0 || x >= SIZE) ? false : true;
}

//---------------------------------------------------------------
vector<Coor_cell> Field::find_places_for_cross()
{
    vector<Coor_cell> seats;
    int y, x;
    int _y, _x;

    for (int i = 0; i < coor_black_cell.size(); i++)
    {
        if (coor_black_cell[i].number == PLACES_FOR_CROSS)
        {
            _y = coor_black_cell[i].y;
            _x = coor_black_cell[i].x;

            //вверх
            y = _y - 1;
            if (is_check_board(y, _x) && map[y][_x].is_white())
                seats.push_back(Coor_cell(y, _x));
            
            //вниз
            y = _y + 1;
            if (is_check_board(y, _x) && map[y][_x].is_white())
                seats.push_back(Coor_cell(y, _x));
            
            //влево
            x = _x - 1;
            if (is_check_board(_y, x) && map[_y][x].is_white())
                seats.push_back(Coor_cell(_y, x));
            
            //вправо
            x = _x + 1;
            if (is_check_board(_y, x) && map[_y][x].is_white())
                seats.push_back(Coor_cell(_y, x));    
        }
    }

    return seats;
}


void Field::install_places_for_cross()
{
    vector<Coor_cell> places = find_places_for_cross();
    
    int y, x;
    for (int i = 0; i < places.size(); i++)
    {
        y = places[i].y;
        x = places[i].x;
        map[y][x].set_cross();
    }
}
//---------------------------------------------------------------------
void Field::mark_illumination_area(int _y, int _x)
{
    //вверх
    for (int y = _y - 1; y >= 0; y--)
        if (map[y][_x].is_white())
            map[y][_x].set_illumination();
        else
            break;

    //вниз
    for (int y = _y + 1; y < SIZE; y++)
        if (map[y][_x].is_white())
            map[y][_x].set_illumination();
        else
            break;

    //влево
    for (int x = _x - 1; x >= 0; x--)
        if (map[_y][x].is_white())
            map[_y][x].set_illumination();
        else
            break;


    //вправо
    for (int x = _x + 1; x < SIZE; x++)
        if (map[_y][x].is_white())
            map[_y][x].set_illumination();
        else
            break;
}

void Field::install_lantern(int y, int x)
{
    map[y][x].set_lantern();
    mark_illumination_area(y, x);
}

void Field::unmark_illumination_area(int _y, int _x)
{
    //вверх
    for (int y = _y - 1; y >= 0; y--)
        if (map[y][_x].is_white())
            map[y][_x].delete_illumination();
        else
            break;
    //вниз
    for (int y = _y + 1; y < SIZE; y++)
        if (map[y][_x].is_white())
            map[y][_x].delete_illumination();
        else
            break;

    //влево
    for (int x = _x - 1; x >= 0; x--)
        if (map[_y][x].is_white())
            map[_y][x].delete_illumination();
        else
            break;

    //вправо
    for (int x = _x + 1; x < SIZE; x++)
        if (map[_y][x].is_white())
            map[_y][x].delete_illumination();
        else
            break;
}

void Field::remove_lantern(int y, int x)
{
    map[y][x].delete_lantern();
    unmark_illumination_area(y, x);
}
//-------------------------------------------------
int Field::number_lunterns_black_cell(Coor_cell& cell) 
{
    int num_lampern = 0;
    int y, x;
    int _y, _x;

    if ((cell.number != PLACES_FOR_CROSS) && 
        (cell.number != BLACK_CELL_NOT_LIMIT_LUNTERNS))
    {          
        _y = cell.y;
        _x = cell.x;

        //вверх
        y = _y - 1;
        if (is_check_board(y, _x) && map[y][_x].is_lantern())
            num_lampern++;

        //вниз
        y = _y + 1;
        if (is_check_board(y, _x) && map[y][_x].is_lantern())
            num_lampern++;

        //влево
        x = _x - 1;
        if (is_check_board(_y, x) && map[_y][x].is_lantern())
            num_lampern++;

        //вправо
        x = _x + 1;
        if (is_check_board(_y, x) && map[_y][x].is_lantern())
            num_lampern++;
    }

    return num_lampern;
}

int Field::number_places_for_lunterns_black_cell(Coor_cell& cell)
{
    int num_places_for_lunterns = 0;
    int y, x;
    int _y, _x;

    if ((cell.number != PLACES_FOR_CROSS) && 
        (cell.number != BLACK_CELL_NOT_LIMIT_LUNTERNS))
    {
        _y = cell.y;
        _x = cell.x;

        //вверх
        y = _y - 1;
        if (is_check_board(y, _x) && map[y][_x].is_white() && 
            !(map[y][_x].is_cross() || map[y][_x].is_lantern() || map[y][_x].is_illumination()) )
            num_places_for_lunterns++;

        //вниз
        y = _y + 1;
        if (is_check_board(y, _x) && map[y][_x].is_white() && 
            !(map[y][_x].is_cross() || map[y][_x].is_lantern() || map[y][_x].is_illumination()) )
            num_places_for_lunterns++;

        //влево
        x = _x - 1;
        if (is_check_board(_y, x) && map[_y][x].is_white() && 
            !(map[_y][x].is_cross() || map[_y][x].is_lantern() || map[_y][x].is_illumination()) )
            num_places_for_lunterns++;

        //вправо
        x = _x + 1;
        if (is_check_board(_y, x) && map[_y][x].is_white() &&
            !(map[_y][x].is_cross() || map[_y][x].is_lantern() || map[_y][x].is_illumination()) )
            num_places_for_lunterns++;
    }

    return num_places_for_lunterns;
}

//----------------------------------
bool Field::is_simple_luntern(Coor_cell& cell) 
{
    int num_luntern = number_lunterns_black_cell(cell);
    int num_places_for_luntern = number_places_for_lunterns_black_cell(cell);
    return (cell.number - num_luntern) == num_places_for_luntern;
}

vector<Coor_cell> Field::find_places_for_simple_luntern()
{
    vector<Coor_cell> seats;
    int y, x;
    int _y, _x;

    for (int i = 0; i < coor_black_cell.size(); i++)
    {
        if ( (coor_black_cell[i].number != PLACES_FOR_CROSS &&
             coor_black_cell[i].number != BLACK_CELL_NOT_LIMIT_LUNTERNS) && 
             is_simple_luntern(coor_black_cell[i]) )
        {
            _y = coor_black_cell[i].y;
            _x = coor_black_cell[i].x;

            //вверх
            y = _y - 1;
            if (is_check_board(y, _x) && map[y][_x].is_white() &&
                !(map[y][_x].is_cross() || map[y][_x].is_lantern() || map[y][_x].is_illumination()) )
                seats.push_back(Coor_cell(y, _x));

            //вниз
            y = _y + 1;
            if (is_check_board(y, _x) && map[y][_x].is_white() &&
                !(map[y][_x].is_cross() || map[y][_x].is_lantern() || map[y][_x].is_illumination()) )
                seats.push_back(Coor_cell(y, _x));

            //влево
            x = _x - 1;
            if (is_check_board(_y, x) && map[_y][x].is_white() &&
                !(map[_y][x].is_cross() || map[_y][x].is_lantern() || map[_y][x].is_illumination()) )
                seats.push_back(Coor_cell(_y, x));

            //вправо
            x = _x + 1;
            if (is_check_board(_y, x) && map[_y][x].is_white() &&
                !(map[_y][x].is_cross() || map[_y][x].is_lantern() || map[_y][x].is_illumination()))
                seats.push_back(Coor_cell(_y, x));
        }
    }

    return seats;
}

void Field::install_places_for_simple_luntern() 
{
    vector<Coor_cell> places = find_places_for_simple_luntern();

    while (!places.empty())
    {
        for (int i = 0; i < places.size(); i++)
            install_lantern(places[i].y, places[i].x);
        
        places = find_places_for_simple_luntern();
    }
}

bool Field::is_full_black_cell(Coor_cell& cell)
{
    return number_lunterns_black_cell(cell) == map[cell.y][cell.x].get_number();
}

bool Field::is_have_around_white_cell_full_black_cell(int _y, int _x) 
//Является ли клетка является окружнием полной черной клеки
{
    if (map[_y][_x].is_white() && !map[_y][_x].is_lantern() && 
        !map[_y][_x].is_cross() && !map[_y][_x].is_illumination())
    {
        int y, x;
        Coor_cell cell;
        //вверх
        y = _y - 1;
        if (is_check_board(y, _x) && map[y][_x].is_black())
        {
            cell = Coor_cell(y, _x, map[y][_x].get_number());
            if (is_full_black_cell(cell))
                return true;
        }
        //вниз
        y = _y + 1;
        if (is_check_board(y, _x) && map[y][_x].is_black())
        {
            cell = Coor_cell(y, _x, map[y][_x].get_number());
            if (is_full_black_cell(cell))
                return true;
        }
        //влево
        x = _x - 1;
        if (is_check_board(_y, x) && map[_y][x].is_black())
        {
            cell = Coor_cell(_y, x, map[_y][x].get_number());
            if (is_full_black_cell(cell))
                return true;
        }
        //вправо
        x = _x + 1;
        if (is_check_board(_y, x) && map[_y][x].is_black())
        {
            cell = Coor_cell(_y, x, map[_y][x].get_number());
            if (is_full_black_cell(cell))
                return true;
        }
    }
    
    return false;
}

bool Field::is_not_full_black_cell(Coor_cell& cell) 
{
    return number_lunterns_black_cell(cell) != cell.number;
}

bool Field::is_white_cell_without_possibility_light()
{
    bool result;
    for (int _y = 0; _y < map.size(); _y++) 
    {
        for (int _x = 0; _x < map.size(); _x++)
        {
            result = true;

            if ( (map[_y][_x].is_cross() && 
                 !map[_y][_x].is_illumination()) ||
                  is_have_around_white_cell_full_black_cell(_y, _x))
            {
                //вверх
                for (int y = _y - 1; y >= 0 && !map[y][_x].is_black(); y--)
                    if (!(map[y][_x].is_cross() || map[y][_x].is_illumination()))
                    {
                        result = false;
                        break;
                    }
                        

                //вниз
                for (int y = _y + 1; y < map.size() && !map[y][_x].is_black(); y++)
                    if (!(map[y][_x].is_cross() || map[y][_x].is_illumination()))
                    {
                        result = false;
                        break;
                    }

                //влево
                for (int x = _x - 1; x >= 0 && !map[_y][x].is_black(); x--)
                    if (!(map[_y][x].is_cross() || map[_y][x].is_illumination()))
                    {
                        result = false;
                        break;
                    }

                //вправо
                for (int x = _x + 1; x < map.size() && !map[_y][x].is_black(); x++)
                    if (!(map[_y][x].is_cross() || map[_y][x].is_illumination()))
                    {
                        result = false;
                        break;
                    }

                if (result)
                    return true;
            }
            
        }
    }

    return false;
}

bool Field::is_can_install_luntern(Coor_cell& cell)
{
    int y = cell.y;
    int x = cell.x;
    bool is_res = true;

    if (map[y][x].is_illumination() )
        is_res = false;

    if (is_have_around_white_cell_full_black_cell(y, x))
        is_res = false;

    install_lantern(y, x);
    if (is_white_cell_without_possibility_light())
        is_res = false;
    remove_lantern(y, x);

    return is_res;
}

vector<Coor_cell> Field::find_places_for_lunterns()
{
    vector<Coor_cell> seats;
    int y, x;
    int _y, _x;

    for (int i = 0; i < coor_black_cell.size(); i++)
    {
        if ((coor_black_cell[i].number != PLACES_FOR_CROSS &&
            coor_black_cell[i].number != BLACK_CELL_NOT_LIMIT_LUNTERNS) && 
            is_not_full_black_cell(coor_black_cell[i]))
        {
            _y = coor_black_cell[i].y;
            _x = coor_black_cell[i].x;

            //вверх
            y = _y - 1;
            if (is_check_board(y, _x) && map[y][_x].is_white() &&
                !(map[y][_x].is_cross() || map[y][_x].is_lantern() || map[y][_x].is_illumination()))
                seats.push_back(Coor_cell(y, _x));

            //вниз
            y = _y + 1;
            if (is_check_board(y, _x) && map[y][_x].is_white() &&
                !(map[y][_x].is_cross() || map[y][_x].is_lantern() || map[y][_x].is_illumination()))
                seats.push_back(Coor_cell(y, _x));

            //влево
            x = _x - 1;
            if (is_check_board(_y, x) && map[_y][x].is_white() &&
                !(map[_y][x].is_cross() || map[_y][x].is_lantern() || map[_y][x].is_illumination()))
                seats.push_back(Coor_cell(_y, x));

            //вправо
            x = _x + 1;
            if (is_check_board(_y, x) && map[_y][x].is_white() &&
                !(map[_y][x].is_cross() || map[_y][x].is_lantern() || map[_y][x].is_illumination()))
                seats.push_back(Coor_cell(_y, x));
        }
    }

    return seats;
}
//------------------------------------------------------------------------------

vector<Coor_cell> Field::find_not_backlight_cell()
{
    vector<Coor_cell> seats;

    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map.size(); x++)
        {
            if (map[y][x].is_white() &&
                !map[y][x].is_cross() &&
                !map[y][x].is_illumination() )
                seats.push_back(Coor_cell(y, x));
        }
    }

    return seats;
}

//------------------------------------------------------------------------------

bool Field::is_full_lunterns()
{
    for (int i = 0; i < coor_black_cell.size(); i++)
    {
        if (coor_black_cell[i].number != PLACES_FOR_CROSS &&
            coor_black_cell[i].number != BLACK_CELL_NOT_LIMIT_LUNTERNS)
        {
            if (coor_black_cell[i].number != number_lunterns_black_cell(coor_black_cell[i]))
                return false;
        }
    }

    return true;
}
bool Field::is_game_over()
{
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map.size(); x++)
        {
            if (map[y][x].is_white() &&
                !map[y][x].is_illumination())
                return false;
        }
    }

    return true;
}
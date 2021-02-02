#include "field.h"

class Solution : public Field
{
public:
    void backlight_cells(Field field);
    void setup_lunterns(Field field);

    void find_decision();
};

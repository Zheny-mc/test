#include <ostream>
namespace Color {
    enum Code {
        FG_WHITE    = 37,
        FG_YELLOW   = 33,//фонарь
        FG_DEFAULT  = 39,

        BG_BLACK    = 40,
        BG_BLUE     = 44,
        BG_WHITE    = 100, 
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

#include "Graphics.h"

const std::vector<std::string> Graphics::QUEEN_ANT = {
        "       +       ",
        "      oOo      ",
      R"(      """      )",
      R"(     \(")/     )",
        "     -( )-     ",
      R"(     /(_)\     )",
};

const std::vector<std::string> Graphics::BEE_HIVE = {
        "     .-=-.     ",
        "    (`=-=`)    ",
        "   (`=-=-=`)   ",
        "   (`=-(@)`)   ",
        "   (`=-=-=`)   ",
        "    '-=-=-'    " };

const std::vector<std::string> Graphics::BEE = {
        "        __     ",
      R"(       / \\    )",
      R"(    \\ \_//    )",
        "    (')(||)-   ",
        "        '''    ",
        "      x%-2d      "
};

const std::vector<std::string> Graphics::ANT = {
        "               ",
        "               ",
      R"(     \(")/     )",
        "     -( )-     ",
      R"(     /(_)\     )",
        "      x%1d      "
};

const std::vector<std::string> Graphics::ANT_AND_BEE = {
        "           __  ",
      R"(      	   / \\ )",
      R"(\(")/  \\ \_// )",
      R"(-( )-  (')(||)-)",
      R"(/(_)\      ''' )",
        " x%1d        x%-2d "
};

const std::vector<std::string>Graphics::BLANK = {
        "               ",
        "               ",
        "               ",
        "               ",
        "               ",
        "               "
};



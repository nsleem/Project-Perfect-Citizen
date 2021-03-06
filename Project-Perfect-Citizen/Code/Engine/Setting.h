#pragma once

#include <SFML/System/Vector2.hpp>
#include <map>

namespace ppc {


class Setting {
public:

  /////////////////////////////////////////////////////////////////////
  // Data
  /////////////////////////////////////////////////////////////////////

    sf::Vector2u resolution = {0, 0};
    bool fullscreen = false;
    //Volume Vars


  /////////////////////////////////////////////////////////////////////
  // Operators
  /////////////////////////////////////////////////////////////////////

    friend std::istream& operator>>(std::istream&, Setting&);

    friend std::ostream& operator<<(std::ostream&, const Setting&);


private:

  /////////////////////////////////////////////////////////////////////
  // Private vars
  /////////////////////////////////////////////////////////////////////

    enum IniTags {
        ResolutionX = 0,
        ResolutionY,
        Fullscreen,
        TagCount
    };

    static std::map<std::string, IniTags> iniGroupMap;

};


};

/**
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                     Version 2, December 2004
 *
 *  Copyright (C) 2017 Fabian Thuering
 *
 *  Everyone is permitted to copy and distribute verbatim or modified
 *  copies of this license document, and changing it is allowed as long
 *  as the name is changed.
 *
 *             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *   0. You just DO WHAT THE FUCK YOU WANT TO.
 *
 **/

#include "Configuration.hpp"
#include <iostream>

int main() {
  dycore::configuration config;
  config.print();

  // Get / set
  std::cout << config.get_dt() << std::endl;
  config.set_dt(4.0);

  // Get / set by string
  config.set("dt", 3.0);
  std::cout << config.get<dycore::Real>("dt") << std::endl;
}

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <exception>
#include <iostream>

#include "utils/utils.hpp"
#include "conf/conf.h"
#include "context/Context.hpp"

void init(Context &context);
void eventLoop(Context &context);


#endif

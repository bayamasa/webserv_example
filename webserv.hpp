#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <exception>
#include <iostream>

#include "utils/utils.hpp"
#include "conf/conf.h"
#include "context/Context.hpp"
#include "socket/Socket.hpp"
#include "server/server.h"

void init(Context &context);
void eventLoop(Context &context);


#endif

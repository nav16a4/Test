#ifndef PRECOMPILED_H
#define PRECOMPILED_H

#pragma comment(lib,"ws2_32.lib")

#include <iostream>
#include <chrono>
#include <sstream>
#include <functional>
#include <thread>
#include <vector>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Singleton.h"
#include "Util.h"


#define IP "127.0.0.1"
#define PORT 44000

#endif // !PRECOMPILED_H

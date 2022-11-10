#pragma once

#include <cstdio>
#include <iostream>
#include <Windows.h>

extern int generate(struct struct_config config);

extern struct struct_config {
	char mod_folder[512];
	char server_ip[20];
	int port;
};


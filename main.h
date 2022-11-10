#pragma once

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>

extern int generate(struct struct_config config);

extern struct struct_config {
	char mod_folder[512];
	char server_ip[20];
	int port;
};

extern struct file_linknode{
	char mod_name[128]
	char path[512];
	char local_md5[36];
	char sample_md5[36];
	file_linknode* next;
};

#pragma once

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>

using namespace std;

extern int generate(struct struct_config config);
extern int simple_check(struct_config config);
extern int check(struct_config config);

extern struct struct_config {
	char mod_folder[512];
	char server_ip[20];
	int port;
};

extern struct mod_linknode {
	char mod_name[512];
	bool flag = false;
	mod_linknode* next;

	mod_linknode(string modname) {
		strcpy_s(this->mod_name, modname.c_str());
		this->next = NULL;
	}

	mod_linknode() {
		this->next = NULL;
	}
};

extern struct file_linknode {
	char mod_name[128];
	char path[512];
	char local_md5[36];
	char sample_md5[36];
	file_linknode* next;

	file_linknode(string path, string local_md5, string sample_md5) {
		strcpy_s(this->mod_name, path.substr(path.find('\\'), path.find('\\')).c_str());
		strcpy_s(this->path, path.c_str());
		strcpy_s(this->local_md5, local_md5.c_str());
		strcpy_s(this->sample_md5, sample_md5.c_str());
		this->next = NULL;
	}

	file_linknode(string modname){
		strcpy_s(this->mod_name, modname.c_str());
		this->next = NULL;
	}
};

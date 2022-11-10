//check.cpp
//检查文件md5值是否匹配

#include "./main.h"
#include "./generater.h"

ifstream ifs_md5


int checkOnce(string mod_folder, string path, string sample_md5){
	int flag = 0;
	string local_md5;
	fullpath = mod_folder + path;
	local_md5 = fileMD5(fullpath);
	if(local_md5 == sample_md5){
		flag = 1;
	}
	else{
		flag = 0;
		tail.next = new file_linknode(path.substr(0, path.find('\\')), path, local_md5, sample_md5, NULL);
		tail = tail.next;
	}
	cout << path << endl;
	return flag;
}

int check(struct_config config){
	ifstream ifs;
	file_linknode tail;
	string path;
	string sample_md5, local_md5;

	ifs.open("./md5.txt");
	while(ifs.getline(path, 512)){
		ifs.getline(sample_md5, 36);
		if(checkOnce(config.mod_folder, path, sample_md5))
			printf("[not pass]");
		else
			printf("[pass]");
		cout << path << endl;
	}
	ifs.close();
	
	return 0;
}


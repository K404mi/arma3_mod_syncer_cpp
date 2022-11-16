//check.cpp
//检查文件md5值是否匹配

#include "./main.h"
#include "./generater.h"

using namespace std;

extern struct stat stat_buffer;

ifstream ifs_md5;
ofstream ofs_dump;
file_linknode* tail;
mod_linknode* head_sample;


int dumplist(file_linknode* cursor) {
	ofs_dump.open("./dump.txt");
	do{
		ofs_dump << "MOD: " << cursor->mod_name << '\n' << "路径: " << cursor->path << '\n' << "本地md5: " << cursor->local_md5 << '\n' << "样本md5: " << cursor->sample_md5 << '\n' << endl;
		cursor = cursor->next;
	}while(cursor!=NULL);
	ofs_dump.close();
	return 0;
}

int checkOnce(string mod_folder, string path, string sample_md5){
	int flag = 0;
	string local_md5;
	string fullpath = mod_folder + path;
	if (stat(fullpath.c_str(), &stat_buffer) != 0)
		return 0;
	local_md5 = fileMD5(fullpath);
	if(local_md5 == sample_md5){
		flag = 1;
	}
	else{
		flag = 0;
		tail->next = new file_linknode(path, local_md5, sample_md5);
		tail = tail->next;
	}
	return flag;
}

int pos(string T, string P, int n){
	int count = 0;
	unsigned begined = 0;
	while((begined=T.find(P,begined))!=string::npos){
		count++;
		begined += P.length();
		if(n==count)
			return begined-1;
	}
}

int walkthroughOnce(string dirPath) {
    WIN32_FIND_DATAA fileInfo;
    string workDir = dirPath;
    dirPath += "*";
    HANDLE hFile = FindFirstFileA(dirPath.c_str(), &fileInfo);
	HANDLE last_pos = hFile;
    if (hFile == INVALID_HANDLE_VALUE) 
        return -1;
    do{
        if (!(strcmp(fileInfo.cFileName, ".") && strcmp(fileInfo.cFileName, "..")))
            continue;
        //如果是文件夹则改变工作目录继续遍历
        if (fileInfo.dwFileAttributes != 16 && fileInfo.dwFileAttributes != 1040) {
            cout << "正在生成：" << workDir + fileInfo.cFileName << endl;
            ofs_md5 << workDir.substr(mod_path_len) + fileInfo.cFileName << endl;
            string mytmp = workDir + fileInfo.cFileName;
            ofs_md5 << fileMD5(mytmp) << endl;
        }
    } while (FindNextFileA(hFile, &fileInfo));
    return 0;
}


int simple_check(struct_config config){
	ifstream ifs;
	WIN32_FIND_DATAA fileInfo;
	mod_linknode* tail_sample = head_sample;
	mod_linknode* head_local = new mod_linknode();
	mod_linknode* tail_local = head_local;
	string modname, dirPath = config.mod_folder;
	if(dirPath.back() != '\\')
		dirPath += '\\';
    string workDir = dirPath;
    dirPath += "*";
    HANDLE hFile = FindFirstFileA(dirPath.c_str(), &fileInfo);
	if (hFile == INVALID_HANDLE_VALUE) 
        return -1;

	//将样本mod列表与本地mod列表导入内存
	ifs.open("./md5.txt");
	while(ifs.getline(modname, 512)){
		modname = modname.substr(modname.find('\\'),modname.find('\\'));
		if(tail_sample->mod_name != modname){
			tail_sample->next = new mod_linknode(modname);
			tail_sample = tail_sample->next;
		}
		ifs.getline(modname, 512);
	}
	ifs.close();
	do{
        if (!(strcmp(fileInfo.cFileName, ".") && strcmp(fileInfo.cFileName, "..")))
            continue;
		if (!strcmp(fileInfo.cFileName, "!DO_NOT_CHANGE_FILES_IN_THESE_FOLDERS"))
            continue;
        if (fileInfo.dwFileAttributes == 16 || fileInfo.dwFileAttributes == 1040) {
			tail_local->next = new mod_linknode(fileInfo.cFileName);
			tail_local = tail_local->next;
        }
    } while (FindNextFileA(hFile, &fileInfo));
	tail_sample = head_sample;
	tail_local = head_local;

	//比对
	while(tail_sample = tail_sample->next){
		while (tail_local = tail_local->next){
			if(tail_local->flag == true)
				continue;
			if(tail_sample->mod_name != tail_local->mod_name)
				continue;
			tail_sample->flag = true;
			tail_local->flag == true
			break;
		}
		tail_local = head_local;
	}
	tail_sample = head_sample;

	//输出结果
	cout<< "\n缺失的mod:"<< endl;
	while(tail_sample = tail_sample->next)
		if(tail_sample->flag == false)
			cout<< tail_sample->mod_name << endl;
	cout<< "\n多余的mod:"<< endl;
	while(tail_local = tail_local->next)
		if(tail_local->flag == false)
			cout<< tail_local->mod_name << endl;

	return 0;
}

int check(struct_config config){
	ifstream ifs;
	file_linknode* head = tail;
	int count_pass = 0, count_error = 0;
	char choice = 'n';
	char mod_name_buffer[128];
	char path[512];
	char sample_md5[36];
	char local_md5[36];

	ifs.open("./md5.txt");
	while(ifs.getline(path, 512)){
		ifs.getline(sample_md5, 36);
		if (checkOnce(config.mod_folder, path, sample_md5)) {
			printf("\033[32m[pass]\033[0m");
			count_pass++;
		}
		else {
			printf("\033[31m[error]\033[0m");
			count_error++;
		}
		cout << path << endl;
	}
	ifs.close();

	cout << "匹配结果: " << count_pass << "个符合, " << count_error << "个不符" << endl;
	if (count_error) {
		file_linknode* cursor = head->next;
		cout << "损坏模组列表: " << endl;
		do {
			if (strcmp(mod_name_buffer, cursor->mod_name)) {
				strcpy_s(mod_name_buffer, cursor->mod_name);
				cout << mod_name_buffer << endl;
			}
		} while (cursor->next == NULL);

		cout << "\n是否导出损坏文件列表? (y/others)" << endl;
		scanf_s("%c", &choice, 1);
		if (choice == 'y') {
			dumplist(head->next);
		}
	}
	return 0;
}


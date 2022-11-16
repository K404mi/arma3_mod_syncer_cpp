//main.cpp
//负责主进程处理，包括初始化和配置写入读取等


#include <string>
#include "./main.h"

using namespace std;

struct struct_config config;
struct stat stat_buffer;

int init();
int config_helper(struct_config* ptr_config);



int main() {
	if (init()) {
		printf("初始化失败");
		getchar();
		return -1;
	}
	int func = 1;

	//system("cls");
	printf("\n\n1、生成样本文件(测试中)\n2、本地检查MOD列表(测试中)\n3、本地检查MOD完整性(测试中)\n4、联网检查MOD列表(待开发)\n5、联网检查MOD完整性(待开发)\n\n");
	printf("请选择功能（输入数字）：");
	scanf_s("%d", &func);

	switch (func){
	case 1:
		generate(config);
	case 3:
		check(config);
	default:
		break;
	}

	system("pause");
	return 0;
}


int init() {
	char choice[32] = "y";
	if (stat("./config.txt", &stat_buffer) == 0) {
		//存在config文件则直接使用
		ifstream ifs;
		ifs.open("./config.txt");
		ifs.getline(config.mod_folder, 512);
		ifs.getline(config.server_ip, 20);
		ifs >> config.port;
		ifs.close();
		printf("检测到现有配置文件:\n");
		printf("mod文件夹路径:%s\n", config.mod_folder);
		printf("服务器ip:%s\n", config.server_ip);
		printf("端口:%d\n", config.port);
		printf("是否直接使用？(y/others)");
		scanf_s("%s", &choice, 32);
		if (!strcmp(choice,"y"))
			return 0;
		else
			remove("./config.txt");
	}

	//不存在配置文件或不选择载入则进行创建
	printf("正在创建新的配置文件...\n");
	printf("请输入mod文件夹路径:");
	cin.getline(config.mod_folder, 512);
	printf("请输入服务器ip(待开发): ");
	strcpy_s(config.server_ip, "127.0.0.1");
	//scanf_s("%s", config.server_ip, 20);
	printf("请输入端口(待开发): ");
	config.port = 9877;
	//scanf_s("%d", &config.port);
	config_helper(&config);
	printf("\n\n配置生成完毕，为当前目录下的config.txt文件\n");
	
	return 0;
}

//将缓存中配置写入文件
int config_helper(struct_config* ptr_config) {
	ofstream ofs_config;
	ofs_config.open("./config.txt");
	ofs_config << config.mod_folder << '\n' << config.server_ip << '\n' << config.port << endl;
	ofs_config.close();
	return 0;
}






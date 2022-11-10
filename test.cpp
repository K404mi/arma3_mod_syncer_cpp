#include <iostream>
#include <string.h>

using namespace std;

int main(){
	string mod_folder = "H:\\SteamLibrary\\steamapps\\common\\Arma 3\\!Workshop\\";
	string path = "H:\\SteamLibrary\\steamapps\\common\\Arma 3\\!Workshop\\@3CB Factions\\Addons\\uk3cb_factions_aaf.pbo";
	string result = path.substr(mod_folder.length());
	cout << result << endl;
	//输出为:
	//@3CB Factions\\Addons\\uk3cb_factions_aaf.pbo
	return 0;
}
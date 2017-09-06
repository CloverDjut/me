#include <fstream> 
#include <vector>
#include <string>
using namespace std;
ifstream cin("http://testlodtask20172.azurewebsites.net/task"); ofstream cout("http://testlodtask20172.azurewebsites.net/task/"); ofstream fout("output.txt");
struct people {
	string id;
	string name;
	string sex;
	int age;
};
int converter(string s) {
	int a = 0;
	for (int i = 0; i < s.size(); i++) {
		char c = s[i];
		a = a * 10 + (int(c) - 48);
	}
	return a;
}
int main() {
	string stroka;
	while (cin) { 
		string podstroka;
		cin >> podstroka;
		stroka += podstroka;
	} 
	//считываем
	vector <people> peoples;
	for (int i=0; i < stroka.size(); i++) { 
		if (stroka[i] == '{') {
			people people1;
			while (stroka[i] != '}') {
				int shet = 0; // считаем количество вхождений " в одну скобку
				if (stroka[i] == '"')
					shet++;
				if (shet == 3) {
					i++;
					while (stroka[i] != '"') {
						people1.id.push_back(stroka[i]);
						i++;
					}
					shet++;
				}
				else if (shet == 7) {
					i++;
					while (stroka[i] != '"') {
						people1.name.push_back(stroka[i]);
						i++;
					}
					shet++;
				}
				else if (shet == 11) {
					i++;
					while (stroka[i] != '"') {
						people1.sex.push_back(stroka[i]);
						i++;
					}
				}
				i++;
			}
			peoples.push_back(people1);
		}
	}  
	// упорядочиваем
	int minfemale = 1000, minmale = 1000;
	for (int i = 0; i < peoples.size(); i++) {
		ifstream fin("http://testlodtask20172.azurewebsites.net/task/"+ peoples[i].id);
		cout << peoples[i].id;
		string info;
		fin >> info;
		int age1;
		for (int j = 0; j < info.size(); j++) {
			int shet = 0; // считаем "
			if (info[j] == '"')
				shet++;
			if (shet == 10) {
				i += 2;
				string number;
				while (info[i] != '"') {
					number.push_back(info[i]);
					i++;
				}
				age1 = converter(number);
			}
		}
		peoples[i].age = age1;
		if (peoples[i].sex == "male" && age1 < minmale)
			minmale = age1;
		else if (peoples[i].sex == "female" && age1 < minfemale)
			minfemale = age1;
	} 
	//определяем возраст
	for (int i = 0; i < peoples.size(); i++) {
		if (peoples[i].sex == "male" && peoples[i].age == minmale)
			fout << "Самый молодой парень: " << peoples[i].name;
		else if (peoples[i].sex == "female" && peoples[i].age == minfemale)
			fout << "Самая молодая девушка: " << peoples[i].name;
	}
	// вывод
	system("pause");
}
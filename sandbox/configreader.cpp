#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[]){
    vector<string> v;                  
    string str, s;                      

	(void)argc;
    ifstream ifs(argv[1]);   
	if (ifs.fail())
	{
		exit(1);
	}
    while (getline(ifs, s)){
        v.push_back(s);
    }

    for (const string& s : v){
        cout << s << endl;
		string test;
		stringstream ss(s);
		getline(ss, test, ' ');
		cout << test << endl;
    }
}

// #include <iostream>
// #include <sstream>
// #include <vector>
// using namespace std;

// int main(void){
//     vector<string> v;                  // 分割した文字列を格納するvector
//     string str, s;                      
//     str = "A B C D E";                  // 分割対象の文字列str
//     stringstream ss(str);              // 入出力可能なsstreamに変換
//     while ( getline(ss, s, ' ') ){     // スペース（' '）で区切って，格納
//         v.push_back(s);
//     }
//     for (const string& s : v){         // vの中身を出力
//         cout << s << endl;
//     }
// }



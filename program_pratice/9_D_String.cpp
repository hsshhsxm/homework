#include <iostream>
#include <string>
#include <vector>
using namespace std;

//#define DEBUG

void mySplit(const string & s, vector<string> & result, const char* seperator = " "){
    if(result.size())
        result.clear();
    if(s == "")
        return;
    string strs = s + seperator;
    size_t pos = strs.find(seperator);
    while(pos != strs.npos){
        string tmp = strs.substr(0,pos);
        result.push_back(tmp);
        strs = strs.substr(pos + 1, strs.size());
        pos = strs.find(seperator);
    }
}

bool isDigit(const string & str){
    return str.find_first_not_of("0123456789") == string::npos;
}

int main(){
    int num;
    cin >> num;
    string * pstr = new string[num];
    for(int i = 0; i < num; ++i)
        cin >> *(pstr + i);
    string str_tmp;
    getline(cin, str_tmp);
    while(true){
        string str;
        getline(cin, str);
        if(str == "over")
            break;
        if(str == "printall"){
            for(int j = 0; j < num; ++j)
                cout << *(pstr + j) << endl;
            continue;
            #ifdef DEBUG
                cout << "printall "<< endl; 
            #endif
        }
        vector<string>  result;
        mySplit(str, result);
        int i = result.size() - 1;
        while(result.size() > 1){
            #ifdef DEBUG
                cout << "result[i] = " << result[i] << endl;
            #endif
            if(result[i] == "copy" || result[i] == "add" || result[i] == "find" || result[i] == "rfind" 
            || result[i] == "insert" || result[i] == "reset" || result[i] == "print"){
                if(result[i] == "copy"){
                    string tmp = (pstr + stoi(result[i+1]) - 1)->substr(stoi(result[i+2]), stoi(result[i+3]));
                    result.erase(result.begin() + i + 1, result.begin() + i + 4);
                    result[i] = tmp;
                    #ifdef DEBUG
                        cout << "copy " << tmp << " to result[i]" << endl; 
                        cout << "current result = ";
                        for(int k = 0; k < result.size(); ++k)
                            cout << result[k] << " ";
                        cout << endl;
                    #endif
                }
                if(result[i] == "add"){
                    if(isDigit(result[i+1]) && isDigit(result[i+2])){
                        int s1 = stoi(result[i+1]);
                        int s2 = stoi(result[i+2]);
                        //**S1 S2可能大于99999**
                        if(s1 <= 99999 && s2 <= 99999 && s1>= 0 && s2 >= 0)
                            result[i] = to_string(s1 + s2);
                        else 
                            result[i] = result[i+1] + result[i+2];
                    } else{
                        result[i] = result[i+1] + result[i+2];
                    }
                    #ifdef DEBUG
                        cout << "add " << result[i+1] << " and " << result[i+2] << ", result[i] = " << result[i] << endl; 
                    #endif
                    result.erase(result.begin() + i + 1, result.begin() + i + 3);
                    #ifdef DEBUG
                        cout << "current result = ";
                        for(int k = 0; k < result.size(); ++k)
                            cout << result[k] << " ";
                        cout << endl;
                    #endif
                }
                if(result[i] == "find"){
                    string s = result[i+1];
                    int n = stoi(result[i+2]);
                    int No = (pstr + n - 1)->find(s);
                    if(No != string::npos)
                        result[i] = to_string(No);
                    else 
                        result[i] = to_string(s.size());
                    #ifdef DEBUG
                        cout << "find " << s << " in " << *(pstr + n - 1) << ", result = " << result[i] << endl; 
                    #endif
                    result.erase(result.begin() + i + 1, result.begin() + i + 3);
                    #ifdef DEBUG
                        cout << "current result = ";
                        for(int k = 0; k < result.size(); ++k)
                            cout << result[k] << " ";
                        cout << endl;
                    #endif
                }
                if(result[i] == "rfind"){
                    string s = result[i+1];
                    int n = stoi(result[i+2]);
                    int No = (pstr + n - 1)->rfind(s);
                    if(No != string::npos)
                        result[i] = to_string(No);
                    else 
                        result[i] = to_string(s.size());
                    #ifdef DEBUG
                        cout << "rfind " << s << " in " << *(pstr + n - 1) << ", result = " << result[i] << endl; 
                    #endif
                    result.erase(result.begin() + i + 1, result.begin() + i + 3);
                    #ifdef DEBUG
                        cout << "current result = ";
                        for(int k = 0; k < result.size(); ++k)
                            cout << result[k] << " ";
                        cout << endl;
                    #endif
                }
                if(result[i] == "insert"){
                    string s = result[i+1];
                    int n = stoi(result[i+2]);
                    int x = stoi(result[i+3]);
                    #ifdef DEBUG
                        cout << "insert " << s << " in pos " << x << " in " << *(pstr + n - 1) << endl; 
                    #endif
                    (pstr + n - 1)->insert(x, s);
                    result.erase(result.begin() + i + 1, result.begin() + i + 4);
                    #ifdef DEBUG
                        cout << "current result = ";
                        for(int k = 0; k < result.size(); ++k)
                            cout << result[k] << " ";
                        cout << endl;
                    #endif
                }
                if(result[i] == "reset"){
                    string s = result[i+1];
                    int n = stoi(result[i+2]);
                    #ifdef DEBUG
                        cout << "reset " << *(pstr + n - 1) << " to " << s << endl; 
                    #endif
                    (pstr + n - 1)->clear();
                    *(pstr + n - 1) = s;
                    result.erase(result.begin() + i + 1, result.begin() + i + 3);
                    #ifdef DEBUG
                        cout << "current result = ";
                        for(int k = 0; k < result.size(); ++k)
                            cout << result[k] << " ";
                        cout << endl;
                    #endif
                }
                if(result[i] == "print"){
                    int n = stoi(result[i+1]);
                    cout << *(pstr + n - 1) << endl;
                    result.erase(result.begin() + i, result.begin() + i + 2);
                    #ifdef DEBUG
                        cout << "print "<< endl; 
                        cout << "current result = ";
                        for(int k = 0; k < result.size(); ++k)
                            cout << result[k] << " ";
                        cout << endl;
                    #endif
                }
                if(result[i] == "over"){
                    break;
                }
                i = result.size() - 1;
                #ifdef DEBUG
                    cout << "reset i=" << i << endl;
                #endif
            }
            else{
                --i;
                #ifdef DEBUG
                    cout << "i--" << endl;
                #endif
            }
        }
    }
    return 0;
}
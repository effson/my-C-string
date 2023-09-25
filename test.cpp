#define _CRT_SECURE_NO_WARNINGS
#include"String.h"
int main() {
    mstr::string s("hello world");
    s.insert(6,"fuck");
    mstr::string s1 = s;
    cout << s1 <<s<< endl;
    s1.insert(10, "sddfsdgsdgs");
    mstr::string s2;
    s1.append("sdf");
    cout << s1 << endl;
    cin >> s2;
    cout << s2;
    return 0;
}

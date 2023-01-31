#ifndef SEG_H
#define SEG_H
#include <queue>
#include <string>
#include <array>
#include <set>
using namespace std;
#define LEN 640
#define INF 0X7FFFFFFF
class Seg
{
public:
    // 载入dict.txt到set类型的dict变量
    bool loadDict(const string &location);
    string cut(string &s);

private:
    set<string> dict;
};

#endif

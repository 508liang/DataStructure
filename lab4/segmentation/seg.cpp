#include "seg.h"
#include <fstream>
#include <codecvt>
#include <locale>

// 载入dict.txt到set类型的dict变量
bool Seg::loadDict(const string &location)
{
    ifstream fin(location); // 通过ifstream流读取文件
    if (!fin.is_open())
    {
        return false;
    }

    string line;       // 将文件逐行读取到字符串line中，截取第一部分
    while (!fin.eof()) // 读取到文件末尾的EOF前一直执行while循环
    {
        getline(fin, line);
        int end = line.find_first_of(' '); // end对应第一列后的空格的索引下标,也即单词字符串的长度
        if (end != -1)                     // find_first_of()函数返回值不为-1，即找到了所给' '字符
        {
            dict.insert(line.substr(0, end)); // 将该词语子串插入到类内的private变量dict中
        }
    }
    return true;
}

// 使用dijkstra算法获得最短路径
string Seg::cut(string &s)
{
    int startPos = 0;
    int fullLen = s.size();
    vector<string> path; // 使用vector记录最终所求的最短路径，方便进行插入、倒置等操作
    int count = 0;       // 用来记录上一句插词结束后path中的词数，作为下一句向path中插词的位置标记

    while (startPos < fullLen)
    {
        // 判断中文字符方式：基于中文字符由3字节构成，转化为unsigned int必然大于0x7f
        while (!((unsigned int)s[startPos] > 0x7f)) // 找到首中文字符的位置作为sentence的起始
        {
            startPos++;
            continue;
        }
        if(startPos>=fullLen) break;
        int endPos = startPos;
        do
        {
            endPos += 3;                                                 // 注意到一个中文字符在utf-8中占3个字节，故以3为步长
        } while (endPos < fullLen and ((unsigned int)s[endPos] > 0x7f)); // 找到连续中文字符末位置作为sentence的末尾的下一位
        string sentence = s.substr(startPos, endPos - startPos);

        int num = sentence.length() / 3; // 恰好为当前sentence包含的词数
        array<int, LEN> g;
        g.fill(-1);
        array<array<int, LEN>, LEN> graph;
        graph.fill(g); // 定义2dim array graph,索引到的数值记录sentence各位置之间的可达性。每个位置均初始化为-1，表示不可达

        for (int i = 0; i < num; i++)
        {
            graph[i][i + 1] = 2; // 每个字符和下一个字符显然可连通，距离为2，即闭区间跨越2个词可达到
        }

        for (int i = 0; i <= num - 2; i++)
        {
            for (int j = 2; j <= num - i and j <= 12; j++) // dict最长词长度为12字符，作为查找上限
            {
                string checkStr = sentence.substr(i * 3, j * 3);
                if (dict.count(checkStr))
                {
                    graph[i][i + j] = 1; // 更新gragh，表示i节点和i+j节点可处于同一个词内，距离为1
                }
            }
        }
        // 下述部分执行dijkstra算法过程，对当前的sentence进行切词
        // 初始化
        array<int, LEN> d; // 记录dijkstra算法执行到当前时刻，各节点到初始节点的距离
        d.fill(INF);
        d[0] = 0;
        array<int, LEN> preNum; // 记录各节点当前所得的最小路径的前驱节点序号
        preNum.fill(-1);
        array<int, LEN> used; // 记录是否已作为最短路径节点使用过
        used.fill(0);
        for (int i = 1; i <= num; i++) // 初始化与初始节点直接相连的各节点
        {
            if (graph[0][i] > 0)
            {
                d[i] = graph[0][i];
                preNum[i] = 0;
            }
        }
        // dijkstra算法主体
        for (int i = 1; i <= num; i++) // 遍历寻找到未被使用过的节点中距初始节点的最短距离，该节点序号记为k
        {
            int min = INF;
            int k = 0;
            if (!used[i] and d[i] < min)
            {
                min = d[i];
                k = i;
            }
            used[k] = 1; // k节点被使用，更新used

            for (int j = 1; j <= num; j++)
            {
                if (graph[k][j] > 0 and graph[k][j] + min < d[j]) // 借助k节点可以构造出到节点j到初始节点的更短距离，更新d和preNum
                {
                    d[j] = graph[k][j] + d[k];
                    preNum[j] = k;
                }
            }
        }

        while (num != 0) // 从当前centence最后字符处往前不断找前驱节点，过程中把词edges构建为路径vector path
        {
            string word = sentence.substr(preNum[num] * 3, (num - preNum[num]) * 3); // 截取以当前位置为末节点的词edge
            wstring_convert<codecvt_utf8<wchar_t>> cov;                              // 欲借助c++的iswpunct()和iswspace()来判断是否为中文标点，需先将string转化为wchar_t
            wchar_t ch = cov.from_bytes(word)[0];
            if (!iswpunct(ch) && !iswspace(ch)) // 判断为无（非）中文标点的word，插入path中固定位置count处，自然地实现了逆序插入
            {
                path.insert(path.begin() + count, word);
            }
            num = preNum[num];
        }
        count = path.size(); // 完成当前centence的分词后，更新位置标记count
        startPos = endPos;   // 更新startPos，向后推进
    }
    string output;
    for (int i = 0; i < count; i++) // 返回path中各词用"/"连接后的字符串
    {
        output.append(path[i] + "/");
    }
    return output;
}

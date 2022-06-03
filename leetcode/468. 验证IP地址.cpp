#include <string>
#include <vector>
using namespace std;

/*
 * 不得不说这个题还挺有意思的。我忽略的点主要有：
 * 1. 结尾的 . 或者 :。需要将最终空的 substr 也保存到 components 中，
 *    以判断 components 的元素个数。
 * 2. IPv4 数字太长，导致 stoi 报错。针对 IPv4 也需要增加字符串长度
 *    判断逻辑。
 * 3. 判断前导 0 逻辑不严密。用了转换成 int 后的 number != 0 来判断，
 *    如果是多个 0 则会判断出错，例如 192.168.00.1
 */

class Solution {
public:
    string validIPAddress(string queryIP) {
       if(isIPv4(queryIP)) return "IPv4";
       if(isIPv6(queryIP)) return "IPv6";
       return "Neither";
    }

    bool isIPv4(const string& queryIP){
        vector<string> components;
        split(components, queryIP, '.');
        if(components.size() != 4) return false;

        for(auto component : components){
            if(!isIPv4Component(component))
                return false;
        }
        return true;
    }

    bool isIPv4Component(const string& str){
        int m = str.length();
        if(m < 1 || m > 3) return false;
        for(auto ch : str){
            if(!isdigit(ch)) return false;
        }
        int num = stoi(str);
        if(num < 0 || num > 255) return false;
        if(str[0] == '0' && m > 1) return false;
        return true;
    }

    bool isIPv6(const string& queryIP){
        vector<string> components;
        split(components, queryIP, ':');
        if(components.size() != 8) return false;

        for(auto component : components){
            if(!isIPv6Component(component)) return false;
        }
        return true;
    }

    bool isIPv6Component(const string& str){
        int m = str.length();
        if(m < 1 || m > 4) return false;
        for(auto ch : str){
            if(!isdigit(ch) &&
               !('a' <= ch && ch <= 'f') &&
               !('A' <= ch && ch <= 'F'))
                return false;
        }
        return true;
    }

    void split(vector<string>& res, const string& str, char delimiter){
        int start = 0, end;

        while(true){
            end = str.find(delimiter, start);
            if(end == str.npos) break;
            res.push_back(str.substr(start, end - start));
            start = end + 1;
        }

        res.push_back(str.substr(start));
    }
};

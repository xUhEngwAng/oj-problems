class Solution {
public:
    string replaceSpace(string s) {
        string ret;
        int start = 0, end;

        while((end = s.find(" ", start)) != string::npos){
            ret += s.substr(start, end-start) + "%20";
            start = end + 1;
        }

        ret += s.substr(start);
        return ret;
    }
};

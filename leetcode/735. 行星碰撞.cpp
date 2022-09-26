class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> ret, st;
        int pos = -1, n = asteroids.size(), curr, prev;

        while(++pos != n){
            curr = asteroids[pos], prev = 0;
            if(0 < curr) st.push_back(curr);
            else{
                while(!st.empty()){
                    prev = st.back();
                    st.pop_back();

                    if(curr + prev < 0) continue;
                    if(0 < curr + prev) st.push_back(prev);
                    break;
                }
                if(curr + prev < 0) ret.push_back(curr);
            }
        }

        for(auto e : st)
            ret.push_back(e);

        return ret;
    }
};

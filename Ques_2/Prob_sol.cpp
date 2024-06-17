#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 1e5+5, P = 37, MOD = 1e9+7;

ll p_pwr[N], prefix_hash[N];

class Solution {
    unordered_map<int, multiset<int>> hash_per_len;
public:
    long long totalPairs(vector<string>& phrases) {        
        p_pwr[0] = 1;
        for (int j=1; j<N; j++) 
            p_pwr[j] = (p_pwr[j-1]*P) % MOD;
        
        ll ans = 0;
        for (int i = 0; i < phrases.size(); i ++) {
            const string& s = phrases[i];
            const int n = s.length();

            prefix_hash[0] = 0;
            for (int j = 1; j <= n; j ++)
                prefix_hash[j] = (prefix_hash[j-1] + p_pwr[j]*(s[j-1]-'a'+1)) % MOD;
            
            for (int l = 1; l <= n; l ++) {
                ll fwd = prefix_hash[l];
                ll bck = (prefix_hash[n] - prefix_hash[n-l] + MOD) % MOD;  
                ll adjusted_fwd = ((l != n)? fwd*p_pwr[n-l] : fwd) % MOD;
                if (adjusted_fwd == bck) 
                    ans += hash_per_len[l].count(fwd);
            }
            hash_per_len[n].insert(prefix_hash[n]);
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<string> phrases = {"x","xyx","xyxyx","xx"};
    cout << sol.totalPairs(phrases) << endl;
    return 0;
}
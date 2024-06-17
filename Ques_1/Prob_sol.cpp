#include<bits/stdc++.h>
using namespace std;

const int P = 31;
const int M1 = 1e9+9;
const int M2 = 1e9+7;

#define ll long long

class Solution {
    int n;
    map<pair<int, int>, int> hash_to_ind;
    void HashAndInsert(const vector<string>& words) {
        for (int cur_ind = 0; cur_ind < n; cur_ind ++) {
            const string& s = words[cur_ind];
            ll hash1 = 0, hash2 = 0;
            ll pwr_p1 = 1, pwr_p2 = 1;
            
            for (int j = s.length()-1; j >= 0; j --) {
                pwr_p1 = (pwr_p1 * P) % M1;
                hash1 = (hash1 + (pwr_p1*s[j]) % M1) % M1;
                
                pwr_p2 = (pwr_p2 * P) % M2;
                hash2 = (hash2 + (pwr_p2*s[j]) % M2) % M2;

                auto it = hash_to_ind.find({hash1, hash2});
                
                if (it == hash_to_ind.end()) 
                    hash_to_ind[{hash1, hash2}] = cur_ind;
                else {
                    int prv_ind = it->second;
                    if (words[prv_ind].length() > words[cur_ind].length())
                        it->second = cur_ind;
                }                
            }
        }
    }
    
public:
    vector<int> matchingPostfix(vector<string>& dictionary, vector<string>& queryString) {
        n = dictionary.size();
        HashAndInsert (dictionary);
        
        int smallest_ind = 0;
        for (int i = 0; i < dictionary.size(); i ++) 
            if (dictionary[smallest_ind].length() > dictionary[i].length())
                smallest_ind = i;
        
        vector<int> ans;
        for (auto s: queryString) {
            ll hash1 = 0;
            ll hash2 = 0;
            ll pwr_p1 = 1;
            ll pwr_p2 = 1;
            
            ans.push_back(smallest_ind);
            
            for (int j = s.length()-1; j >= 0; j --) {
                pwr_p1 = (pwr_p1 * P) % M1;
                hash1 = (hash1 + (pwr_p1*s[j]) % M1) % M1;
                
                pwr_p2 = (pwr_p2 * P) % M2;
                hash2 = (hash2 + (pwr_p2*s[j]) % M2) % M2;
                
                if (auto it = hash_to_ind.find({hash1, hash2}); it != hash_to_ind.end())
                    ans.back() = it->second;
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<string> dictionary = {"ab", "bc", "cd", "de", "ef", "fg", "gh", "hi", "ij", "jk"};
    vector<string> queryString = {"ab", "bc", "cd", "de", "ef", "fg", "gh", "hi", "ij", "jk"};
    vector<int> ans = sol.matchingPostfix(dictionary, queryString);
    for (int i: ans) cout << i << " ";
    return 0;
}
#include <iostream>

#include <algorithm>

#include "f.h"

using namespace std;

vector<_table> JoinBased::gen_table_ins(const vector<string> &C1, const vector<SpaceInstance> &E){
    vector<_table> T1;
    for(auto it = C1.begin(); it < C1.end(); it++){
        string flag = *it;
        vector<int> temp;
        for(auto it_E = E.begin(); it_E < E.end(); it_E++){
            if(flag == (*it_E).FeatureType){
                temp.push_back((*it_E).InstanceID);
            }
        }
        T1.push_back(make_pair(vector<string>{flag}, temp));
    }
    return T1;
}

vector<string> merge_v(vector<string> &a, vector<string> &b){
    set<string> temp;
    temp.insert(a.begin(), a.end());
    temp.insert(b.begin(), b.end());
    return vector<string>{temp.begin(), temp.end()};
}

vector<vector<string> > JoinBased::gen_candidate_colocation(const vector<vector<string> > &Pk, int k){
    vector<vector<string> > Ck_add_1;
    for(auto it = Pk.begin(); it < Pk.end(); it++){
        vector<string> temp = *it;
        for(auto it_r = (it+1); it_r < Pk.end(); it_r++){
            vector<string> t = *it_r;
            vector<string> merged = merge_v(temp, t);
            if(merged.size() == k+1){
                Ck_add_1.push_back(merged);
            }
        }
    }
    return Ck_add_1;
}

void JoinBased::process(){
    int k = 1;
    vector<string> C1 = ET;
    vector<string> P1 = ET;
    vector<vector<string> > Pk = revert(P1);
    vector<_table> T1 = gen_table_ins(C1, E);
    cout << "process succeed" << endl;
    while(!Pk.empty()){
        
    }
}




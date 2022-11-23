#include <iostream>
#include <math.h>
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

//产生候选co-location， 需要补充减枝操作, 可以像书上一的写法
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

bool JoinBased::isNiber(const Position &a, const Position &b){
    double distance = sqrt((pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
    if(distance < R){
        return true;
    }
    return false;
}

//产生候选co-location的表实例
vector<_table> JoinBased::gen_table_ins(double min_prev, const vector<vector<string> > &Ck_add_1, vector<_table> &Tk, double R){

}
vector<vector<string> > revert(const vector<string> &P1){
    vector<vector<string> > Pk;
    for(auto it = P1.begin(); it < P1.end(); it++){
        vector<string> t{*it};
        Pk.push_back(t);
    }
    return Pk;
}

void JoinBased::process(){
    int k = 1;
    vector<string> C1 = ET;
    vector<string> P1 = ET;
    vector<vector<string> > Pk = revert(P1);
    vector<_table> T1 = gen_table_ins(C1, E);
    vector<_table> Tk = T1;
    cout << "process succeed" << endl;
    while(!Pk.empty()){
        vector<vector<string> > Ck_add_1 = gen_candidate_colocation(Pk, 1);
        vector<_table> Tk_add_1 = gen_table_ins(min_prev, Ck_add_1, Tk, R);
    }
}




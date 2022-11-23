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
            bool flag = true;
            for(int i = 0; i < (k-1); i++){
                if(temp[i] != (*it_r)[i]){
                    flag = false;
                    break;//匹配失败则不再进行匹配
                }
            }
            if(flag == true){
                temp.push_back((*it_r)[k-1]);
                Ck_add_1.push_back(temp);
                temp = *it;
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

bool is_same_table_pre_k(_table &a, _table &b, int k){
    if(k == 0)
        return true;//前0个一定相等
    vector<string> a_str{a.first.begin(), a.first.end()};
    vector<string> b_str{b.first.begin(), b.first.end()};
    vector<int> a_int{a.second.begin(), a.second.end()};
    vector<int> b_int{b.second.begin(), b.second.end()};
    for(int i = 0; i < k; i++){
        if(a_str[i] != b_str[i] || a_int[i] != b_int[i])
            return false;
    }
    return true;
}

Position find_item_pos(const _table &t, int k, const vector<SpaceInstance> &E){
    vector<string> v_str = t.first;
    vector<int> v_int = t.second;
    for(auto it = E.begin(); it < E.end(); it++){
        if(v_str[k] == (*it).FeatureType && v_int[k] == (*it).InstanceID){
            return (*it).Location;
        }
    }
}

//产生候选co-location的表实例
vector<_table> JoinBased::gen_table_ins(double min_prev, const vector<vector<string> > &Ck_add_1, vector<_table> &Tk, double R){
    vector<_table> Tc;
    int k = (*(Tk.begin())).first.size();
    for(auto it = Tk.begin(); it < Tk.end(); it++){
        _table temp = (*it);
        
        for(auto it_r = (it+1); it_r < Tk.end(); it++){
            _table t = (*it_r);
            if(is_same_table_pre_k(temp, t, k-1)){//如果前k-1个相同才进行连接
                if(isNiber(find_item_pos(temp, k, E), find_item_pos(t, k, E))){//需要找到表实例第i项对应的空间实例集的位置
                    vector<string> t_str{temp.first.begin(), temp.first.end()};
                    vector<int> t_int{temp.second.begin(), temp.second.end()};
                    t_str.push_back(t.first[k-1]);
                    t_int.push_back(t.second[k-1]);
                    Tc.push_back(make_pair(t_str, t_int));
                }
            }
        }
    }
    return Tc;
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




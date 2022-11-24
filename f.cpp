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

Position JoinBased::getPosition(string type, int id){
    for(auto it = E.begin(); it < E.end(); it++){
        if((*it).FeatureType == type && (*it).InstanceID == id){
            return (*it).Location;
        }
    }
}

//把这个函数改造成连接函数
bool JoinBased::is_same_pre_k(const _pro_table &a, const _pro_table &b, int k){
    if(k == 0){
        return true;
    }
    //如果前k-1项的string不相等，那么就说明不用继续比较了
    for(int i = 0; i < k; i++){
        if(a.first[i] != b.first[i]){
            return false;
        }
    }
    //接着比较前k个数是不是相等，如果不相等也不用比较了
    vector<set<int> > _save;
    for(auto it = a.second.begin(); it < a.second.end(); it++){
        set<int> merge_int{(*it).begin(), ((*it).begin()+k)};
        for(auto it_r = b.second.begin(); it_r < b.second.end(); it_r++){
            merge_int.insert((*it_r).begin(), (*it_r).begin()+k);
            if(merge_int.size() == k){
                //说明前k个相等，其实这时候就可以连接了
                // _save.push_back(merge_int);
                
                if(isNiber(getPosition((a.first)[k], (*it)[k]), getPosition((b.first)[k], (*it_r)[k]))){

                }
                
            }
        }
    }

}

//产生候选co-location的表实例, 产生表实例 _table设计的有问题
vector<_pro_table> JoinBased::gen_table_ins(double min_prev, const vector<vector<string> > &Ck_add_1, vector<_pro_table> &Tk, double R){
    vector<_pro_table> Tc;
    int k = (*(Tk.begin())).first.size();
    for(auto it = Tk.begin(); it < Tk.end(); it++){
        _pro_table temp = (*it);
        for(auto it_r = (it+1); it_r < Tk.end(); it_r++){
            _pro_table t = (*it_r);
            if(is_same_pre_k(temp, t, k-1)){//如果前k个相等，则尝试连接，连接的内容为第k个元素
                // join()
                
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

vector<_pro_table> table_2_pro_table(const vector<_table> &T1){
    vector<_pro_table> Tk;
    for(auto it = T1.begin(); it < T1.end(); it++){
        vector<string> v_string = (*it).first;
        vector<vector<int> > v_v_int;
        for(auto it_int = (*it).second.begin(); it_int < (*it).second.end(); it_int++){
            v_v_int.push_back(vector<int>{*it_int});
        }
        Tk.push_back(make_pair(v_string, v_v_int));
    }
    return Tk;
}


void JoinBased::process(){
    int k = 1;
    vector<string> C1 = ET;
    vector<string> P1 = ET;
    vector<vector<string> > Pk = revert(P1);
    vector<_table> T1 = gen_table_ins(C1, E);
    vector<_pro_table> Tk = table_2_pro_table(T1);
    // vector<_table> Tk = T1;
    cout << "process succeed" << endl;
    while(!Pk.empty()){
        vector<vector<string> > Ck_add_1 = gen_candidate_colocation(Pk, k);
        vector<_pro_table> Tk_add_1 = gen_table_ins(min_prev, Ck_add_1, Tk, R);
    }
}




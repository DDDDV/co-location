#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;

//保存位置信息
struct Position{
    double x;
    double y;
    Position(double x, double y) : x(x), y(y) {};
};
//保存空间实例
struct SpaceInstance{
    int InstanceID;//{1,2,}
    Position Location;//{x, y}
    string FeatureType;//{A}
    SpaceInstance(int id, Position p, string FeatureType) : 
        InstanceID(id), Location(p), FeatureType(FeatureType) {};
};

class JoinBased{
private:
    vector<SpaceInstance> E;
    vector<string> ET;
    double min_prev;
    double min_conf;
    double R;//距离R
    map<string, int> count_et;//保存空间特征出现次数

public:
    JoinBased(const vector<SpaceInstance> &E, const vector<string> &ET, double min_prev, double min_conf, double R) : 
        E(E), ET(ET), min_prev(min_prev), min_conf(min_conf), R(R) {};
    void getCountET();//计算每个元素出现的次数，用于求参考率
    bool isNiber(Position a, Position b);//计算两个点的距离，如果满足R返回true，否则返回false;
    vector<pair<set<string>, set<int> > > gen_table_ins(const vector<string> &C1, const vector<SpaceInstance> &E);
    void process();
};

void JoinBased::getCountET(){
    for(auto it_et = ET.begin(); it_et < ET.end(); it_et++){
        // count_et.insert(pair<string, int>(*it_et, 0));
        for(auto it_e = E.begin(); it_e < E.end(); it_e++){
            if((*it_et) == (*it_e).FeatureType){
                pair<map<string, int>::iterator, bool> p = count_et.insert(make_pair((*it_et), 1));
                if(p.second == false){
                    p.first->second += 1;
                }
            }
        }
    }
};

bool JoinBased::isNiber(Position a, Position b){
    double distance = sqrt((pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
    if(distance < R){
        return true;
    }
    return false;
};

//存放1阶co-lcoation和表实例
vector<pair<set<string>, set<int> > > JoinBased::gen_table_ins(const vector<string> &C1, const vector<SpaceInstance> &E){
    vector<pair<set<string>, set<int> > > T1;
    for(auto it = C1.begin(); it < C1.end(); it++){
        set<string> co_location;
        set<int> id;
        for(auto it_ins = E.begin(); it_ins < E.end(); it_ins++){
            if((*it_ins).FeatureType == (*it)){
                co_location.insert(*it);
                id.insert((*it_ins).InstanceID); 
            }
        }
        T1.push_back(make_pair(co_location, id));
    }
    return T1;
};

vector<set<string> > C1_2_P1(vector<string> C1){//如果返回引用，不行，因为ret的作用域离开该函数会被销毁，导致访问到非法地址
    vector<set<string> > ret;
    for(auto it = C1.begin(); it < C1.end(); it++){
        set<string> s;
        s.insert(*it);
        ret.push_back(s);
    }
    return ret;
}

// int is_same(set<string> l, set<string> r){
//     for(auto it = l.begin(); it != l.end(); it++){
//         r.erase(*it);
//     }
//     return r.size();
// }   

vector<set<string> > gen_candidate_col(vector<set<string> > &Pk, int k){
    vector<set<string> > ck_add_1;
    for(auto it = Pk.begin(); it < Pk.end(); it++){
        set<string> temp_l = *it;
        for(auto it_r = ++(it); it_r < Pk.end(); it_r++){
            for(auto it_str = (*it_r).begin(); it_str != (*it_r).end(); it_str++){
                temp_l.insert(*it_str);
                if(temp_l.size() == k+1){
                    ck_add_1.push_back(temp_l);
                    temp_l = *it;
                    continue;
                }
            }
        }
    }
}

void JoinBased::process(){
    int k = 1;
    vector<string> C1 = ET;
    vector<set<string> > P1 = C1_2_P1(ET);//里面用set包装
    vector<set<string> > Pk = P1;
    vector<pair<set<string>, set<int> > > T1 = gen_table_ins(ET, E);
    while(Pk.size() != 0){
        vector<set<string> > Ck_add_1 = gen_candidate_col(Pk, k);
    }


}

int main(){
    vector<SpaceInstance> E{
        SpaceInstance(1, Position(24,14), "A"),
        SpaceInstance(2, Position(64,44), "A"),
        SpaceInstance(3, Position(46,24), "A"),
        SpaceInstance(4, Position(63,7), "A"),
        SpaceInstance(1, Position(13,3), "B"),
        SpaceInstance(2, Position(19,45), "B"),
        SpaceInstance(3, Position(47.5,10.5), "B"),
        SpaceInstance(4, Position(62,52), "B"),
        SpaceInstance(5, Position(13,50), "B"),
        SpaceInstance(1, Position(39,11), "C"),
        SpaceInstance(2, Position(52,50), "C"),
        SpaceInstance(3, Position(40,36), "C"),
        SpaceInstance(1, Position(40,20), "D"),
        SpaceInstance(2, Position(6,10), "D")
    };
    vector<string> ET{"A", "B", "C", "D"};//这里设置为vector<set<string> > 更好一些
    JoinBased j(E, ET, 0.3, 0.3, 12);
    j.getCountET();
    j.gen_table_ins(ET, E);
    j.process();
}
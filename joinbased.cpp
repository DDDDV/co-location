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
    // int k;//co-location的阶
    // vector<SpaceInstance> Ck;//k阶候选co-location集
    // map<set<int>, set<int> > Tk;//Ck中co-location的表实例集
    // vector<vector<string> > Pk;//k阶频繁co-location集

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

vector<set<string> > & C1_2_P1(vector<string> C1){
    vector<set<string> > ret;
    for(auto it = C1.begin(); it < C1.end(); it++){
        set<string> s;
        s.insert(*it);
        ret.push_back(s);
    }
    return ret;
}

void JoinBased::process(){
    vector<set<string> > P1 = C1_2_P1(ET);
    
    int k = 2;


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
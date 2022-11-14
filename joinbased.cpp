#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
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
    SpaceInstance(int id, Position p, string FeatureType) : InstanceID(id), Location(p), FeatureType(FeatureType) {};
};

class JoinBased{
private:
    vector<SpaceInstance> E;
    vector<string> ET;
    double min_prev;
    double min_conf;
    double R;
    int k;//co-location的阶
    vector<SpaceInstance> Ck;
    map<string, int> count_et;


public:
    JoinBased(const vector<SpaceInstance> E, vector<string> ET, double min_prev, double min_conf, double R) : 
        E(E), ET(ET), min_prev(min_prev), min_conf(min_conf), R(R) {};
    void getCountET();
    bool isNiber(Position a, Position b);//计算两个点的距离，如果满足R返回true，否则返回false;

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
}

bool JoinBased::isNiber(Position a, Position b){
    double distance = sqrt((pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
    if(distance < R){
        return true;
    }
    return false;
}

int main(){
    vector<SpaceInstance> E{
        SpaceInstance(1, Position(24,14), "A"),
        SpaceInstance(2, Position(64,44), "A"),
        SpaceInstance(3, Position(46,24), "A"),
        SpaceInstance(4, Position(63,7), "A")
    };
    vector<string> ET{"A"};
    // JoinBased j(E, ET, 0.3, 0.3);
}
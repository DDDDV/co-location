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
public:
    JoinBased(const vector<SpaceInstance> &E, const vector<string> &ET, double min_prev, double min_conf, double R) : 
        E(E), ET(ET), min_prev(min_prev), min_conf(min_conf), R(R) {};
    bool isNiber(Position a, Position b);//计算两个点的距离，如果满足R返回true，否则返回false;
    //根据E生成二阶候选表实例，返回一个存储了二阶表实例的结构
    vector<pair<vector<string>, vector<int> > > getTable2(const vector<SpaceInstance> &E);
    

};

bool JoinBased::isNiber(Position a, Position b){
    double distance = sqrt((pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
    if(distance < R){
        return true;
    }
    return false;
};

bool cmp(pair<vector<string>, vector<int> > a, pair<vector<string>, vector<int> > b){
    return a.first < b.first;
}
//这样的数据组织形式不方便计算参与度，需要再整理一下
vector<pair<vector<string>, vector<int> > > JoinBased::getTable2(const vector<SpaceInstance> &E){
    vector<pair<vector<string>, vector<int> > > T2;
    for(auto it = E.begin(); it < E.end(); it++){
        for(auto it_r = (it+1); it_r < E.end(); it_r++){
            if((*it).FeatureType != (*it_r).FeatureType && isNiber((*it).Location, (*it_r).Location)){//不相等
                vector<string> temp_str{(*it).FeatureType, (*it_r).FeatureType};
                vector<int> temp_int{(*it).InstanceID, (*it_r).InstanceID};
                T2.push_back(make_pair(temp_str,temp_int));
            }
        }
    }
    sort(T2.begin(), T2.end(), cmp);
    return T2;
}

//整理数据，结果格式为{{A,B} : {{1,2,3,4},{1,4,3,#3}}}
void reorganization(const vector<pair<vector<string>, vector<int> > > &T){
    //T已经被排序
    map<vector<string>, vector<set<int> > > reorgan_ret;
    for(auto it = T.begin(); it < T.end(); it++){
        
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
}
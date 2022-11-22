#ifndef _F_H_
#define _F_H_

#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

#define _table pair<vector<string>, vector<int> >

struct Position{
    double x;
    double y;
    Position(double x, double y) : x(x), y(y) {};
};

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
    //产生表实例集T1,格式应该是什么样的呢{ {A}:{1,2,3,4}, {B}:{}}
    vector<_table> gen_table_ins( const vector<string> &C1, const vector<SpaceInstance> &E);//C1==ET
    vector<vector<string>, vector<int> > gen_table_ins(double min_prev, const vector<vector<string> > &Ck_add_1, double R);
    vector<vector<string> > gen_candidate_colocation(const vector<vector<string> > &Pk, int k);
    void process();
};

#endif
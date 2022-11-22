#include <iostream>
#include "f.h"
using namespace std;

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
    vector<string> ET{"A", "B", "C", "D"};
    JoinBased j(E, ET, 0.3, .03, 16);
    j.process();
}
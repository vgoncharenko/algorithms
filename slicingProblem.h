//
// Created by Vitaliy on 8/9/20.
//

#ifndef TREE_SLICINGPROBLEM_H
#define TREE_SLICINGPROBLEM_H


class fileBase {
public:
    int x = 20;
    int b = 20;
};

class fileDerived : public fileBase {
public:
    int x = 10;
    int f = 10;
};

class slicingProblem {
public:
    void slicingProblemTest1();
};

#endif //TREE_SLICINGPROBLEM_H

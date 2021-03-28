//
// Created by Vitaliy on 1/24/21.
//

/** Recursion to iterative refactoring problem https://pic.plover.com/knuth-GOTO.pdf (p.281) */
struct NodeGoTo {
    NodeGoTo *l;
    NodeGoTo *r;
    int v;
};

void printNode(NodeGoTo *t) {
    std::cout << t->v;
}

void knuthRecursive(NodeGoTo *t) {
    if (t == nullptr) return;

    knuthRecursive(t->l);
    printNode(t);
    knuthRecursive(t->r);
}

void knuthIterative(NodeGoTo *t) {
    std::stack<NodeGoTo*> s;

    L1:
        while (t != nullptr) {
            s.push(t);
            t = t->l;
            goto L1;

            L2:
                t = s.top(); s.pop();
                printNode(t);
                t = t->r;
        }
        if (!s.empty()) goto L2;
}

void myIterative(NodeGoTo *t) {
    std::stack<NodeGoTo*> s;

    while (t != nullptr) {
        if (t->l != nullptr) {
            if (t->r != nullptr) s.push(t->r);
            s.push(t);
            t = t->l;
        } else {
            printNode(t);
            if (t->r != nullptr) t = t->r;
            else {t = s.top(); s.pop();}
        }
    }
}



/**
 * N + 1/2 problem: https://pic.plover.com/knuth-GOTO.pdf (p. 278)
 *
 * Description of the problem:
 * A:
 *    S;
 *    if B => go to Z;
 *    T;
 *    go to A;
 * Z:
 *
 * My possible solution:
 * do {
 *    S;
 *    if (B) break;
 *    T;
 * } while (true);
 * Z;
 *
*/
//for (i to 5)
//    for (x to 10)
//        for (a to 5)
//            if (imdone) { a = 5+1; x=10+1; i=5+1; }
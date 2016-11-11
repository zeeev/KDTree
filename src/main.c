#include <stdio.h>
#include "twoDtree.hpp"

int main()
{

    tree * myTree = initTree(9,2);

    void * dummy;

    loadDatum(myTree, dummy, 150, 175);
    loadDatum(myTree, dummy, 62, 65);
    loadDatum(myTree, dummy, 20, 50);
    loadDatum(myTree, dummy, 5,  6);
    loadDatum(myTree, dummy, 52,  63);
    loadDatum(myTree, dummy, 51,  52);
    loadDatum(myTree, dummy, 75,  76);
    loadDatum(myTree, dummy, 100, 120);
    loadDatum(myTree, dummy, 125, 130);

    buildTree(myTree);

    return 0;
}

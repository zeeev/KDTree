#include <stdio.h>
#include "twoDtree.hpp"

int main()
{

    tree * myTree = initTree(4,2);

    void * dummy;

    loadDatum(myTree, dummy, 10, 20);
    loadDatum(myTree, dummy, 30, 40);
    loadDatum(myTree, dummy, 50, 60);
    loadDatum(myTree, dummy, 60, 70);

    buildTree(myTree);

  printTree(myTree->root, 2);

    int v[2]  = {50, 50};
    int dim = 0;

    node * lt;

  /*  if(lessThan(myTree->root, dim, v, 2, &lt) == 0){
      printf("FATAL: no node less than ends\n");
      return 1;
    }
*/

    //printNode(myTree->root, 2);
    //printNode(lt, 2);

    return 0;
}

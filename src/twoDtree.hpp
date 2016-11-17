//
//  twoDtree.hpp
//  2dt
//
//  Created by Zev Kronenberg on 24/10/2016.
//
//
#ifndef twoDtree_hpp
#define twoDtree_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

typedef struct node node;
typedef struct tree tree;

struct node{
  int  * ends   ;
  node * parent ;
  node * left   ;
  node * right  ;
  void * load   ;
};

struct tree{
  int index;
  int n;
  int nDim;
  int dataAdded;
  int treeBuilt;
  node * nodes;
  node * root;
};

int printNode(node * n, int nDim){

  if(n == 0){
    return 0;
  }

  int i = 0;
  printf("Node %i :\n", n);
  for(; i < nDim; i++){
    printf(" dim: %i end: %i\n", i, n->ends[i]);
  }
  printf( " Node left child: %i\n", n->left);
  printf( " Node right child: %i\n", n->right);
  printf( " parent node: %i\n", n->parent);

  return 1;
}

tree * initTree(int n, int dim)
{
  tree * t = (tree*)malloc(sizeof(tree));

  t->nodes = (node*)malloc(sizeof(node)*n);

  memset(t->nodes, 0, sizeof(node)*n);

  t->n         = n;
  t->nDim      = dim;
  t->index     = 0;
  t->treeBuilt = 0;

  return t;
}

int loadDatum(tree * t,
          void * load,
          ...)
{

    if(t->treeBuilt == 1){
      printf("Warning: cannot add data once tree built, nothing added\n");
      return 1;
    }
    va_list args;
    va_start(args, load);
    if(t->index == t->n){
      printf("Warning: more datum than tree size, nothing added\n");
      return 1;
    }

    t->dataAdded = 1;

    node * n = (node*)malloc(sizeof(node));
    n->ends = (int *)malloc(sizeof(int)* t->nDim);

    int i = 0;
    for(;i < t->nDim; i++){
      n->ends[i] = va_arg(args, long int);
    }
    va_end(args);

    n->left   = 0;
    n->right  = 0;
    n->parent = 0;

    t->nodes[t->index] = *n;
    t->index += 1;

    return 0;
  }

void swap(node * nodes, int i, int j)
{
    node tmp ;
    memcpy(&tmp, &nodes[j], sizeof(node));
    memcpy(&nodes[j], &nodes[i], sizeof(node));
    memcpy(&nodes[i], &tmp, sizeof(node));
}

node * partition(node * nodes,
    int low,
    int high,
    int dim)
{
  printf("part ... l: %i h: %i\n", low, high);

  if(low == high)
    nodes[low];
  if(low > high)
    return 0;

  int kth = ((high - low) / 2) + low;


  node * pivotNode = &nodes[kth];
  int left  = low;
  int right = high;

  while(left < right){
    while(nodes[left].ends[dim] < pivotNode->ends[dim])
      left++;
    while(nodes[right].ends[dim] > pivotNode->ends[dim])
      right--;

    swap(nodes, left, right);
  }
    if(&nodes[kth] == pivotNode)
      return pivotNode;
    if(nodes[kth].ends[dim] > pivotNode->ends[dim])
      return partition(nodes, low, nodes[kth].ends[dim], dim);

    return partition(nodes, nodes[kth].ends[dim], high, dim);
}

int recursiveAdd(tree * t,
    int low,
    int high,
    int dim,
    node * parent)
{
    if( low > high)
      return 0;

      int kth = ((high - low) / 2) + low ;

      node * mid = partition(t->nodes, low, high, dim);

      dim += 1;

      if(dim == t->nDim){
        dim = 0;
      }
      if(parent == 0){
        t->root = mid;
      }

      if(mid == parent)
        return 0;

      mid->left  = partition(t->nodes, low, kth-1, dim);
      mid->right = partition(t->nodes, kth+1, high, dim);

      mid->parent = parent;

//  printf("add ... l: %i h: %i k: %i\n", low, high, kth);

      assert(mid != parent);
      assert(mid != mid->left);
      assert(mid != mid->right);

  //    printNode(mid, 2);
  //    printNode(mid->left, 2);
  //    printNode(mid->right,2);

      recursiveAdd(t, low,   kth-1, dim, mid->left);
      recursiveAdd(t, kth+1,  high, dim, mid->right);

      return 0;
}

int buildTree(tree * t)
{

  /*
    we start by passing the:
      1. Tree containing node array
      2. Lower index of node array
      3. The upper index of node array
      4. The root node * which get's set if it == 0.
   */

  int dim   = 0;

  recursiveAdd(t, 0, t->n -1, dim, 0);

  printf("Tree built\n");

  return 1;

}

int lessThan(node * current,
  int dim,
  int * ends,
  int nDim,
  node ** lastNode)
{
  if(current == 0){
    return 0;
  }
  dim += 1;
  if(dim == nDim){
    dim = 1;
  }

  int lessThanBoth = 1;
  int i = 0;
  for(; i < nDim; i++){
    if(current->ends[i] > ends[i]){
      lessThanBoth = 0;
      break;
    }
  }
  if(lessThanBoth){
    *lastNode = current;
    return 1;
  }
  if(ends[dim-1] < current->ends[dim-1]){
    return lessThan(current->left, dim, ends, nDim, lastNode);
  }
  else{
    return lessThan(current->right, dim, ends, nDim, lastNode);
  }
}

int printTree(node * n, int nDim){
  if(n == 0){
      return 0;
  }
  printNode(n, nDim);
  printTree(n->right, 2);
  printTree(n->left,  2);

  return 0;
}

#endif /* twoDtree_hpp */

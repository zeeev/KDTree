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

    n->left  = 0;
    n->right = 0;

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

  int kth = ((high - low) / 2) + low;

  /* prevents a bad child node from being added */

  /*if(low == high)
    return 0;
    */

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

int addNodes(tree * t,
    int low,
    int high,
    int dim,
    node * parent)
{
    if( low >= high)
      return 0;

      int kth = ((high - low) / 2) + low;

      node * mid = partition(t->nodes, low, high, dim);

      dim += 1;

      if(dim == t->nDim){
        dim = 0;
      }

      if(parent == 0){
        t->root = mid;
      }

      mid->parent = parent;

printf("l: %i h: %i d: %i k: %i p: %i \n", low, high, dim, kth, parent);

      mid->left  = partition(t->nodes, low, kth-1, dim);
      mid->right = partition(t->nodes, kth+1, high, dim);

      addNodes(t, low,   kth-1, dim, mid->left  );
      addNodes(t, kth+1, high,  dim, mid->right );

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

  recursiveAdd(t, 0, t->n - 1, dim, 0);

  printf("Tree built\n");

  return 1;

}

#endif /* twoDtree_hpp */

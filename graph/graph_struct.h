#ifndef GRAPH_GRAPH_STRUCT_H
#define GRAPH_GRAPH_STRUCT_H

#define MAVVEX 100    //最大顶点数

/*
 * 图的邻接矩阵存储方式，结构由顶点数量、边数量、顶点集合和边集合组成。
 * 其中顶点集合一维数组，根据顶点的数量动态分配数组大小。
 * 边集合是二维数组，根据顶点的数量来动态分配数组大小，对于无向图来说，该邻接矩阵是对称矩阵。
 * 邻接矩阵比较适用于稠密图
 * 对于一个邻接矩阵M，如果M(i,j)=1，则说明顶点i和顶点j之间存在一条边，
 * 对于无向图来说，M (j ,i) = M (i, j)，所以其邻接矩阵是一个对称矩阵；
 * 对于有向图来说，则未必是一个对称矩阵。邻接矩阵的对角线元素都为0。
 * 当边上有权值的时候，称之为网图，则邻接矩阵中的元素不再仅是0和1了，邻接矩阵M中的元素定义为：
 *         {w_ij or 1, (i,j) belongs to E or <i,j> belongs E
 * M(i,j) ={0, i= j
 *         {0 or INFINITY
*/
typedef char vertexType;
typedef int edgeType;

typedef struct GraphMatrix {

    int vertexNumber;            // 顶点数量
    int edgeNumber;              // 边的数量
    vertexType vertex[MAVVEX];            // 顶点集合，一维数组
    edgeType arc[MAVVEX][MAVVEX];       // 边集合，  二维数组

} GraphMatrix;


void GraphMatrix_create(GraphMatrix *g);

void DfsTraverse(GraphMatrix *g);

void DfsSearch(GraphMatrix *g, vertexType gStart, vertexType gEnd);

void DfsTraverseSearch(GraphMatrix *g, vertexType v1, vertexType v2);

#endif //GRAPH_GRAPH_STRUCT_H

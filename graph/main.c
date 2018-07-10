/*
 *图的应用
 * -采用邻接矩阵存储图，可支持无向图，有向图
 * -采用DFS方式遍历图的顶点
 * -采用类似DFS的方式查询任意两个顶点间是否存在路径
 * -debug结果个图的描述可参考下面链接里的文件，给出了两个图的结构：
 * https://coding.net/u/rillhu/p/dmx512/attachment/3976567
 */


#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "graph_struct.h"

#define  MATRIX_GEN 1//如果需要生成新的矩阵，使能此定义，否则，屏蔽

#ifdef MATRIX_GEN
//#define  GEN_UNDIGRAPH 1  //如果是无向图，则使能此定义,否则，屏蔽
//#define USE_OTHER_NUMBER_FOR_VERTEX 1//如果顶点值使用非0~N编号，使能此定义，否则，屏蔽
#else
int vertexN = 14;
int edgeN = 18;
int maze[MAVVEX][MAVVEX] =  //he liu， 有向图
        {
                {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,},
                {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,},
                {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,},
                {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,},
                {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        };
#endif

int main() {

    GraphMatrix *gm;
    gm = (GraphMatrix *) malloc(sizeof(GraphMatrix));

#ifdef MATRIX_GEN
    GraphMatrix_create(gm);
#else

    gm->vertexNumber = vertexN;
    gm->edgeNumber = edgeN;
    memcpy((char *) gm->arc, (char *) maze, sizeof(maze));

    for (int i = 0; i < gm->vertexNumber; ++i) {
        gm->vertex[i] = i;
    }
#endif

    DfsTraverse(gm);
    //DfsTraverseSearch(gm, 0, 2);
    //DfsTraverseSearch(gm, 0, 3);



    /*------for He Liu------*/

    for (int i = 0; i < 5; ++i) {
//        for (int j = 0; j < 2 ; ++j) {
//
//        }
        DfsTraverseSearch(gm, i, 12);
        DfsTraverseSearch(gm, i, 13);
    }


    return 0;
}
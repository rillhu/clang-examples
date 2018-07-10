#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include"graph_struct.h"

/*GraphMatrix_create*/
void GraphMatrix_create(GraphMatrix *g) {

    printf("请分别输入图的顶点数量和边的数量，用空格隔开,vertexNumber edgeNumber:\n");
    scanf("%d %d", &g->vertexNumber, &g->edgeNumber);  //将顶点数量和边的数量存储在结构体g中相应的变量
    getchar(); //It is used to get the enter after scanf.

    //输入图的顶点
#ifdef USE_OTHER_NUMBER_FOR_VERTEX //如果顶点值使用非0~N编号，使能此定义
    printf("输入图的顶点字符,用空格隔开：\n");
    char v[MAVVEX];
    memset(v, '\0', sizeof(v));
    fgets(v, MAVVEX, stdin);

    //转换字符串为vertex值，并存入顶点数组
    char *temp = strtok(v, " ");
    for (int i = 0; i < g->vertexNumber && temp != NULL; ++i) {
        g->vertex[i] = (vertexType) atoi(temp);
        temp = strtok(NULL, " ");
    }
#else
    for (int i = 0; i < g->vertexNumber; ++i) {
        g->vertex[i] = (vertexType)i;
    }
#endif

    printf("The map vetexes are :\n");
    for (int i = 0; i < g->vertexNumber; ++i) {
        printf("%d ", (int) g->vertex[i]);
    }
    printf("\n");

    //初始化邻接矩阵的所有元素
    for (int i = 0; i < g->vertexNumber; i++) {
        for (int j = 0; j < g->vertexNumber; j++)
            g->arc[i][j] = 0;
    }

    //输入图的信息
    for (int k = 0; k < g->edgeNumber; k++) {

        int i, j;
        printf("请输入边(vi,vj)的下标, i和j，用空格隔开:");
        scanf("%d %d", &i, &j);
        g->arc[i][j] = 1;    //（i，j）和(j，i)指的是一条边， 如果带权值，修改1为权值
#ifdef GEN_UNDIGRAPH  // 如果是无向图，则对称赋值
        g->arc[j][i] = 1;
#endif
    }

    //输出图的信息
    printf("Your graph matrix is :\n{\n");
    for (int i = 0; i < g->vertexNumber; i++) {
        printf("{");
        for (int j = 0; j < g->vertexNumber; j++) {
            printf("%4d,", g->arc[i][j]);
        }
        printf("},\n");
    }
    printf("};\n");
}

/*DFS*/
bool visited[MAVVEX];

void Dfs(GraphMatrix *g, int v) {
    visited[v] = true;    //标识顶点下标v被访问过了。
    printf("%4d", g->vertex[v]);//打印节点信息, DFS类似于树的先序遍历，根->左->右
    for (int j = 0; j < g->vertexNumber; j++) {
        if (!visited[j] && g->arc[v][j] == 1) {
            Dfs(g, j);
        }
    }
//    printf("%4d", g->vertex[v]);//打印节点信息,不能在此处打印遍历信息，挪至函数开始
}

/*DFS Traverse*/
void DfsTraverse(GraphMatrix *g) {
    printf("深度遍历图：\n");
    //初始化各全局变量，避免先前赋值干扰
    int i;
    for (i = 0; i < g->vertexNumber; i++) {
        visited[i] = false;
    }

    for (i = 0; i < g->vertexNumber; i++) {
        if (!visited[i]) {
            Dfs(g, i);
            printf("*");
        }
    }
    printf("\n");
}


/**DfsSearch*/
bool existed;

void DfsSearch(GraphMatrix *g, vertexType gStart, vertexType gEnd) {

    int start = (int) gStart;
    int end = (int) gEnd;

    visited[start] = true;    //标识顶点下标start被访
    //找到end顶点和start顶点相同，找到路径，设置找到标识，退出递归。
    if (g->vertex[start] == g->vertex[end]) {
        //printf("yes\n");
        existed = true;
        return;
    }

    //未找到两个顶点之间的路径，继续以下一个顶点开始递归调用，找不到则退出递归。
    for (int i = 0; i < g->vertexNumber; ++i) {
        int next = g->arc[start][i];
        if (next == 0) continue;    //if there is no path between the adjacent vertexes, continue

        if (!visited[i]) {
            DfsSearch(g, g->vertex[i], g->vertex[end]); //recursive with next vertex as input
        }
    }
}

/**DfsTraverseSearch*/
void DfsTraverseSearch(GraphMatrix *g, vertexType v1, vertexType v2) {
    printf("使用深度遍历的方法查找顶点间是否存在路径：%2d -> %2d  ", (int) v1, (int) v2);

    //初始化各全局变量，避免先前赋值干扰
    int i;
    for (i = 0; i < g->vertexNumber; i++) {
        visited[i] = false;
    }
    existed = false;

    if((int)v1 > g->vertexNumber-1||(int)v2>g->vertexNumber-1){
        printf("Graph does not have the vertex!\n");
        return;
    }

    DfsSearch(g, v1, v2);
    if (existed) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}





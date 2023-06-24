#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INF 1e9

FILE* fin;
FILE* fout;

typedef struct Node 
{
	int vertex;
	int dist;	//distance
	int prev;
}Node;

typedef struct Graph 
{
	int size;
	int** vertices;  // 엣지의 weight, 없다면 0, 2차원 배열
	Node* nodes;
}Graph;

typedef struct Heap 
{
	int Capacity;
	int Size;
	Node* Element;
}Heap;

Graph* createGraph(int size);
void deleteGraph(Graph* g);
void dijkstra(Graph* g);
int* shortestPath(Graph* g, int dest);
Heap* createMinHeap(int heapSize);
void deleteMinHeap(Heap* minHeap);
void insertToMinHeap(Heap* minHeap, int vertex, int distance);
Node deleteMin(Heap* minHeap);

void swap(Node* node1, Node* node2)
{
	Node temp = *node1;
	*node1 = *node2;
	*node2 = temp;
}

void main(int argc, char* argv[]) 
{
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	Graph* g;
	int size;
	fscanf(fin, "%d\n", &size);
	g = createGraph(size + 1);

	char tmp = 0;
	while (tmp != '\n' && tmp != EOF)
	{
		int node1, node2, weight;
		fscanf(fin, "%d-%d-%d", &node1, &node2, &weight);
		g->vertices[node1][node2] = weight;
		tmp = fgetc(fin);
	}

	dijkstra(g);

	int j;
	for (int i = 2; i <= g->size; i++) 
	{
		int* path = shortestPath(g, i);
		if (path == NULL) 
		{
			fprintf(fout, "can not reach to node %d\n", i);
			continue;
		}
		for (j = g->size - 1; j > 0; j--) 
		{
			if (path[j] == 0) 
				continue;
			fprintf(fout, "%d->", path[j]);
		}
		fprintf(fout, "%d (cost : %d)\n", i, g->nodes[i].dist);
		free(path);
	}
	deleteGraph(g);
}
/*
Allocate Graph Matrix

Initial distance: INF except 1st node (source)
Initial prev: -1
*/
Graph* createGraph(int size) 
{
	Graph* new_G = (Graph*)malloc(sizeof(Graph));
	new_G->size = size-1;
	new_G->vertices = (int**)malloc(sizeof(int*) * size);
	for (int i = 0; i < size; i++)
	{
		new_G->vertices[i] = (int*)malloc(sizeof(int) * size);
		for (int t = 0; t < size; t++)
			new_G->vertices[i][t] = INF;
	}
	new_G->nodes = (Node*)malloc(sizeof(Node)*size);

	return new_G;
}

// deallocate graph
void deleteGraph(Graph* g) 
{
	free(g->nodes);
	for (int i = 0; i < g->size; i++)
		free(g->vertices[i]);
	free(g);
}
/*
Allocate min heap
*/
Heap* createMinHeap(int heapSize) 
{
	Heap* new_h = (Heap*)malloc(sizeof(Heap));
	new_h->Size = 0;
	new_h->Capacity = heapSize*heapSize;
	new_h->Element = (Node*)malloc(sizeof(Node)*heapSize*heapSize);
	return new_h;
}
/*
Deallocate min heap
*/
void deleteMinHeap(Heap* minHeap) 
{
	free(minHeap->Element);
	free(minHeap);
}

/*
Dijkstra Algorithm
*/
// minheap을 사용한 O(nlogn) 방식의 알고리즘
void dijkstra(Graph* g)
{
	int vert_size = g->size + 1;

	int* visited = (int*)malloc(sizeof(int) * (vert_size));
	Heap* minheap = createMinHeap(g->size);
	for (int i = 1; i <= g->size; i++)
	{
		g->nodes[i].vertex = i;
		g->nodes[i].dist = INF;
		g->nodes[i].prev = 0;
		visited[i] = -1;
	}
	visited[0] = 0;
	
	g->nodes[1].dist = 0; 
	visited[1] = 1;
	insertToMinHeap(minheap, g->nodes[1].vertex, g->nodes[1].dist);

	while (minheap->Size != 0)
	{
		Node tmp = deleteMin(minheap);
		
		if (tmp.dist > g->nodes[tmp.vertex].dist)
			continue;

		int min_dist = tmp.vertex;
		visited[min_dist] = 1;
		// 최단거리 업데이트
		int base_dist = g->nodes[min_dist].dist;
		for (int i = 1; i < vert_size; i++)
		{
			if (g->vertices[min_dist][i] != INF && visited[i] == -1)
			{
				if (base_dist + g->vertices[min_dist][i] < g->nodes[i].dist)
				{
					g->nodes[i].dist = base_dist + g->vertices[min_dist][i];
					g->nodes[i].prev = min_dist;
					insertToMinHeap(minheap, i,  g->nodes[i].dist);
				}
			}
		}
	}

	deleteMinHeap(minheap);
}

// minheap을 사용하지 않은 O(N^2) 방식의 알고리즘
void dijkstra2(Graph* g) 
{
	int vert_size = g->size+1;

	int* visited = (int*)malloc(sizeof(int)*(vert_size));
	//Heap* minheap = createMinHeap(g->size);

	for (int i = 1; i <= g->size; i++)
	{
		g->nodes[i].vertex = i;
		g->nodes[i].dist = INF;
		g->nodes[i].prev = 0;
		visited[i] = -1;
	}

	visited[1] = 1;
	for (int i = 2; i < vert_size; i++)
	{
		if (g->vertices[1][i] < g->nodes[i].dist)
		{
			g->nodes[i].dist = g->vertices[1][i];
			g->nodes[i].prev = 1;
		}
	}

	int visit_cnt = 2;
	while (visit_cnt < g->size)
	{
		// 방문하지 않은 v중에 가장 dist이 작은 v 찾기
		int min_dist = 1;
		for (int i = 2; i < vert_size; i++)
		{
			if (visited[i] == -1) // 방문 안한 노드 중에
			{
				if (g->nodes[i].dist < g->nodes[min_dist].dist) // dist가 가장 작은놈 찾기
				{
					min_dist = i;
				}
			}
		}
		visited[min_dist] = 1;
		// 최단거리 업데이트
		int base_dist = g->nodes[min_dist].dist;
		for (int i = 1; i < vert_size; i++)
		{
			if (g->vertices[min_dist][i] != INF && visited[i] == -1)
			{
				if (base_dist + g->vertices[min_dist][i] < g->nodes[i].dist)
				{
					g->nodes[i].dist = base_dist + g->vertices[min_dist][i];
					g->nodes[i].prev = min_dist;
				}
			}
		}

		visit_cnt++;
	}
	
	/*
	for (int i = 1; i < vert_size; i++)
	{
		printf("%d %d %d\n", g->nodes[i].vertex, g->nodes[i].dist, g->nodes[i].prev);
	}*/
}

/*
Return shortest path from source(1) to dest(i)
Return type is array and the size is the number of node.
You should save the path reversely.
For example, If shortest path is 1->2->3
and the number of node(g->size) is 5,
you must return [3, 2, 1 , 0, 0]
If there is no path, return NULL
*/
int* shortestPath(Graph* g, int dest) 
{
	if (g->nodes[dest].dist == INF)
		return NULL;

	int* path = (int*)malloc(sizeof(int)* (g->size+1));  // 경로를 저장할 배열 동적 할당
	for (int i = 0; i <= g->size; i++)
	{
		path[i] = 0;
	}

	int tmp = dest; int idx = 0;

	while (tmp != 1)
	{
		path[idx] = tmp; idx++;
		tmp = g->nodes[tmp].prev;
	}
	path[idx + 1] = tmp;

	return path;
}
/*
Insert Node with vertex and distance into minHeap
*/
void insertToMinHeap(Heap* minHeap, int vertex, int distance) 
{
	// 힙이 가득 차 있는지 확인
	if (minHeap->Size == minHeap->Capacity)
	{
		printf("Heap is full. Cannot insert more elements.\n");
		return;
	}

	// 새로운 노드 생성, prev는 사용 안해도 될것 같다.
	Node newNode;
	newNode.vertex = vertex;
	newNode.dist = distance;

	// 새로운 노드를 힙의 맨 끝에 추가
	int i = minHeap->Size;
	minHeap->Size++;
	minHeap->Element[i] = newNode;

	// 새로운 노드를 올바른 위치로 이동시키기 위해 힙을 재구성
	while (i != 0 && minHeap->Element[(i - 1) / 2].dist > minHeap->Element[i].dist)
	{
		swap(&minHeap->Element[i], &minHeap->Element[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}
/*
pop the Node with minimum distance from minHeap
return:
	Node with minimum distance
*/

void heapify(Heap* minHeap, int index) 
{
	int smallest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < minHeap->Size && minHeap->Element[left].dist < minHeap->Element[smallest].dist)
		smallest = left;

	if (right < minHeap->Size && minHeap->Element[right].dist < minHeap->Element[smallest].dist)
		smallest = right;

	if (smallest != index) {
		swap(&minHeap->Element[index], &minHeap->Element[smallest]);
		heapify(minHeap, smallest);
	}
}

Node deleteMin(Heap* minHeap) 
{
	if (minHeap->Size == 0) 
	{
		Node empty;
		empty.vertex = -1;
		empty.prev = -1;
		empty.dist = 0;
		return empty;
	}

	Node minNode = minHeap->Element[0];

	// 루트 노드를 마지막 노드로 대체합니다.
	minHeap->Element[0] = minHeap->Element[minHeap->Size - 1];
	minHeap->Size--;

	heapify(minHeap, 0);  // 최소힙 유지

	return minNode;
}


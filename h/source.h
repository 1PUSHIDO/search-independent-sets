#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <time.h>

struct setNI {
	int* set;
	struct setNI* next;
};

struct graph {
	int* matrix, size;
	struct graph* next;
	struct setNI* set;
};

int* CreateGraph(int vertexes) {
	int* Mtrx = (int*)malloc(sizeof(int) * vertexes * vertexes);
	if (!Mtrx) return 0;
	for (int i = 0; i != vertexes; i++) {
		*(Mtrx + i * vertexes + i) = 0;
		for (int j = 0; j < i; j++) {
			*(Mtrx + i * vertexes + j) = rand() % 2;
			*(Mtrx + j * vertexes + i) = *(Mtrx + i * vertexes + j);
		}
	}
	return Mtrx;
}

void ShowGraph(struct graph* graph) {
	if (!graph) return;
	for (int i = 0; i != graph->size; i++) {
		printf(" | |  ");
		for (int j = 0; j != graph->size; j++) {
			printf("%i ", *(graph->matrix + i * graph->size + j));
		}
		printf("|%i\n", i + 1);
	}
}

void ClearLine(struct setNI* list, int vertexes, int count) {
    if (!list) return;
    int cur = count;
    if (list->next)
        ClearLine(list->next, vertexes, cur + 1);
    if (list->next)
        free(list->set);
    if (cur)
        free(list);
}

void DeleteGraph(struct graph** startGraph, struct graph* currentGraph) {
	if (!startGraph || !currentGraph) return;
	struct graph* temp = *startGraph;
	if (*startGraph == currentGraph) {
		if ((*startGraph)->next)
			*startGraph = (*startGraph)->next;
		else
			*startGraph = NULL;
		free((currentGraph)->matrix);
        if ((currentGraph)->set) {
            for (int i = currentGraph->size - 1; i != 0; i--) {
                ClearLine(currentGraph->set + i, currentGraph->size, 0);
            };
        }
		free(currentGraph);
        
		return;
	}
	while (temp->next != currentGraph) {
		temp = temp->next;
	}
	if (!(currentGraph)->next)
		temp->next = NULL;
	else {
		temp->next = (currentGraph)->next;
	}
	free((currentGraph)->matrix);
    if ((currentGraph)->set) {
        for (int i = currentGraph->size - 1; i != 0; i--) {
            ClearLine(currentGraph->set + i, currentGraph->size, 0);
        };
    }
	free(currentGraph);
    
	return;
}

void DeleteGraphs(struct graph* ma, struct graph* current) {
    if (!current)
        return;
    if (current->next)
        DeleteGraphs(ma, current->next);
    DeleteGraph(&ma, current);
}

void FindSet(int* matrix, int* set, int size, int shift, int* queueCurrent, struct setNI* nodeCurrent, int* setsNum) {
    int* queue = (int*)malloc(sizeof(int) * size), * line = (int*)malloc(sizeof(int) * size);
    struct setNI* node = nodeCurrent;
    if (!queueCurrent) {
        for (int i = 0; i < size; i++) {
            queue[i] = 0;
        }
    }
    else {
        for (int i = 0; i < size; i++) {
            queue[i] = queueCurrent[i];
        }
    }

    int currentShift = shift + 1, cond = 0;
    for (int i = shift; i < (!shift ? 1 : size) && set[i] != 0; i++) {
        if (shift >= size) break;
        for (int j = 0; j < size; j++) {
            line[j] = 0;
        }
        queue[shift] = set[i];
        for (int j = 0; queue[j] != 0 && j < size; j++) {
            for (int k = 0; k < size; k++) {
                line[k] = line[k] || matrix[(queue[j] - 1) * size + k];
            }
        }
        for (int j = 0; queue[j] != 0 && j < size; j++) {
            if (line[queue[j] - 1] || queue[j] <= queue[j - 1]) {
                cond = 1;
                break;
            }
        }
        if (cond) {
            cond = 0;
            continue;
        }
        if (shift >= 0) {
            node->set = (int*)malloc(sizeof(int) * size);
            for (int j = 0; j < size; j++) {
                node->set[j] = 0;
            }
            for (int j = 0; queue[j] != 0 && j < size; j++) {
                node->set[j] = queue[j];
            }
            node->next = (struct setNI*)malloc(sizeof(struct setNI));
            node->next->next = NULL;
            (*setsNum)++;
            FindSet(matrix, set, size, currentShift, queue, node->next, setsNum);
        }
        else
            FindSet(matrix, set, size, currentShift, queue, node, setsNum);
        while (node->next) {
            node = node->next;
        }
    }
    free(queue);
    free(line);
}

void FindNotSmej(int* matrix, int size, int vertex, struct setNI* nodeCurrent, int* setsNum) {
    int temp = -1, * line = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        line[i] = matrix[vertex * size + i];
    }
    int* nSmejSet = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        nSmejSet[i] = 0;
    }
    for (int i = vertex; i < size; i++) {
        if (!matrix[vertex * size + i])
            nSmejSet[++temp] = i + 1;
    }
    FindSet(matrix, nSmejSet, size, 0, NULL, nodeCurrent, setsNum);
    free(line);
    free(nSmejSet);
};

void ShowList(struct setNI* node, int size) {   
    if (!node || !node->set) return;
    struct setNI* nodeCurrent = node;
    printf(" | |  ");
    do {
        printf("{");
        for (int i = 0; nodeCurrent->set[i] != 0 && i < size; i++) {
            printf("%d%c", nodeCurrent->set[i], (i == size - 1 || !nodeCurrent->set[i + 1]) ? 0 : ' ');
            }
        printf("} ");
        nodeCurrent = nodeCurrent->next;
    } while (nodeCurrent->next);
    printf("\n");
    return;
}

void ShowListAdv(struct setNI* node, int size, FILE* file) {
    if (!node || !node->set) return;
    struct setNI* nodeCurrent = node;
    do {
        fprintf(file, "{");
        for (int i = 0; nodeCurrent->set[i] != 0 && i < size; i++) {
            fprintf(file, "%d%c", nodeCurrent->set[i], (i == size - 1 || !nodeCurrent->set[i + 1]) ? 0 : ' ');
        }
        fprintf(file, "} ");
        nodeCurrent = nodeCurrent->next;
    } while (nodeCurrent->next);
    fprintf(file, "\n");
    return;
}
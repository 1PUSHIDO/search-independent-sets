#include "source.h"
void Intro() {
	setlocale(LC_ALL, "RU");
	char menu[] =
		"  ______________________________________________________________________________\n"
		" /  _________________________________________________________________///////////\n"
		" | |\n"
		" | |  \tКурсовая работа\n"
		" | |  по курсу \033[30;47m\"Логика и основы алгоритмизации в инженерных задачах\"\033[0m\n"
		" | |  на тему \033[30;47m\"Реализация алгоритма поиска независимых множеств вершин графа\"\033[0m\n"
		" | |  Выполнил:\n"
		" | |  \tстудент группы \033[30;47m22ВВП2\033[0m\n"
		" | |  \t\t\033[30;47mКуракин Н.Н.\033[0m\n"
		" | |  Нажмите любую клавишу для продолжения...\n"
		" | \\____________________________________________________________________________\n"
		" \\__ISoGNS___________________________________________________________///////////";
	printf(menu);
	_getch();
}

int MainMenu(int graphNum, int setsNum, int graphSetsNum, int marker) {
	int markerPosition = marker;
	char menu[] =
		"  ______________________________________________________________________________\n"
		" /  Меню_____________________________________________________________///////////\n"
		" | |\n"
		" | |\tГраф [Всего %d]\n"
		" | |  [%c] Генерация\n"
		" | |  [%c] Просмотр\n"
		" | |  [%c] Сохранение/загрузка\n"
		" | |\n"
		" | |\tНезависимые множества вершин [Всего найдено %d для %d графов]\n"
		" | |  [%c] Поиск\n"
		" | |  [%c] Просмотр\n"
		" | |  [%c] Сохранение\n"
		" | |\n"
		" | |\tПрограмма\n"
		" | |  [%c] Настройки(Изменить название файла для быстрого сохранения/загрузки)\n"
		" | |  [%c] Выход\n"
		" | \\____________________________________________________________________________\n"
		" \\__ISoGNS___________________________________________________________///////////";
	printf(menu, graphNum, markerPosition == 0 ? '#' : ' ', markerPosition == 1 ? '#' : ' ', markerPosition == 2 ? '#' : ' ', setsNum, graphSetsNum, markerPosition == 3 ? '#' : ' ', markerPosition == 4 ? '#' : ' ', markerPosition == 5 ? '#' : ' ', markerPosition == 6 ? '#' : ' ', markerPosition == 7 ? '#' : ' ');
	for (;;) {
		if (_kbhit()) {
			int pressedButton = _getch();
			if (pressedButton != 13 && pressedButton != 72 && pressedButton != 80)
				continue;
			system("cls");
			switch (pressedButton) {
			case 13:
				return markerPosition;
				break;
			case 72:
				markerPosition = markerPosition == 0 ? 7 : markerPosition - 1;
				break;
			case 80:
				markerPosition = markerPosition == 7 ? 0 : markerPosition + 1;
				break;
			}
			printf(menu, graphNum, markerPosition == 0 ? '#' : ' ', markerPosition == 1 ? '#' : ' ', markerPosition == 2 ? '#' : ' ', setsNum, graphSetsNum, markerPosition == 3 ? '#' : ' ', markerPosition == 4 ? '#' : ' ', markerPosition == 5 ? '#' : ' ', markerPosition == 6 ? '#' : ' ', markerPosition == 7 ? '#' : ' ');
		}
		Sleep(100);
	}
}

struct graph* OptionGenerateMatrix(struct graph* graph, int* graphNum, int* setsNum, int* graphSetsNum, struct graph* (*ReturnFunction)(struct graph*, int*, int*, int*)) {
	system("cls");
	int size = 0, * matrix = NULL, cond1 = 0, cond2 = 0, temp = 0;
	struct graph* cGraph = graph;
	char menu1[] =
		"  ______________________________________________________________________________\n"
		" /  Введите_порядок_генерируемого_графа(кол-во_вершин)_______________///////////\n"
		" | |\n"
		" | |  Граф порядком ",
		 menu2[] =
	    " | |\n"
		" | |  %s\n"
		" | \\____________________________________________________________________________\n"
		" \\__ISoGNS___________________________________________________________///////////";
	do { fseek(stdin, 0, SEEK_END); system("cls"); printf(menu1); } while (!scanf("%d", &size));
	if (size > 50) {
		printf(" | |  Генерировать граф с порядком больше 50 не рекомендуется: возможен риск\n | |  переполнения памяти при поиске независимых множеств вершин.\n | |  Вы хотите продолжить? Y/N\n");
		do {
			fseek(stdin, 0, SEEK_END);
			temp = _getch();
		} while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' && temp != 141 && temp != 173 && temp != 146 && temp != 226);
		if (temp == 'N' || temp == 'n' || temp == 146 || temp == 226)
			return graph;
	};
	matrix = size > 0 ? CreateGraph(size) : matrix;
	printf(menu2, (matrix && size > 0) ? "Граф создан успешно.\n | |  Хотите перейти к просмотру графов? Y/N" : "Ошибка создания графа(невозможно выделить память для графа).\n | |  Нажмите любую клавишу для продолжения...");
	if (!matrix || !size) {
		(void)_getch();
		return graph;
	}
	*setsNum = 0;
	*graphSetsNum = 0;
	if (!graph || !*graphNum) {
		graph = (struct graph*)malloc(sizeof(struct graph));
		cGraph = graph;
		cond1 = 1;
	}
	else {
		while (cGraph->next) {
			cGraph = cGraph->next;
		};
		cGraph->next = (struct graph*)malloc(sizeof(struct graph));
		cGraph = cGraph->next;
	}
	cGraph->matrix = matrix;
	cGraph->size = size;
	cGraph->next = NULL;
	cGraph->set = NULL;
	(*graphNum)++;
	if (!cond1) {
		do {
			fseek(stdin, 0, SEEK_END);
			temp = _getch();
		} while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' && temp != 141 && temp != 173 && temp != 146 && temp != 226);
		return (temp == 'Y' || temp == 'y' || temp == 141 || temp == 173) ? ReturnFunction(graph, graphNum, setsNum, graphSetsNum) : graph;
	}
	else {
		do {
			fseek(stdin, 0, SEEK_END);
			temp = _getch();
		} while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' && temp != 141 && temp != 173 && temp != 146 && temp != 226);
		return (temp == 'Y' || temp == 'y' || temp == 141 || temp == 173) ? ReturnFunction(cGraph, graphNum, setsNum, graphSetsNum) : cGraph;
	}
}

struct graph* OptionShowGraph(struct graph* graph, int* graphNum, int* setsNum, int* graphSetsNum) {
	system("cls");
	char menu1[] =
		"  ______________________________________________________________________________\n"
		" /  Просмотр_графов__________________________________________________///////////\n"
		" | |\n"
		" | |  Нет инициализированных графов для просмотра. Хотите создать граф? Y/N\n"
		" | \\____________________________________________________________________________\n"
		" \\__ISoGNS___________________________________________________________///////////";
	if (!graph || !*graphNum) {
		int temp = 0;
		printf(menu1);
		do { fseek(stdin, 0, SEEK_END);  
		temp = _getch(); } 
		while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' && temp != 141 && temp != 173 && temp != 146 && temp != 226);
		return (temp == 'Y' || temp == 'y' || temp == 141 || temp == 173) ? OptionGenerateMatrix(graph, graphNum, setsNum, graphSetsNum, OptionShowGraph) : graph;
	}
	int count = 0;
	char menu2[] =
		"  ______________________________________________________________________________\n"
		" /  Просмотр_графов__________________________________________________///////////\n"
		" | |\n"
		" | |  Граф %d\n",
		 menu3[] =
		" | \\____________________________________________________________________________\n"
		" \\__ISoGNS_/[-]Пред. [R]Удалить [Q] Меню [+]След.\\___________________///////////";
	printf(menu2, count + 1);
	ShowGraph(graph);
	printf(menu3);
	while (1) {
		struct graph* graphCurrent = graph;
		switch (_getch()) {
			case '+':
			case '=':
				count = count == (* graphNum - 1) ? 0 : count + 1;
				for (int i = 0; i < count; i++) {
					graphCurrent = graphCurrent->next;
				}
				system("cls");
				printf(menu2, count + 1);
				ShowGraph(graphCurrent);
				printf(menu3);
				break;
			case '-':
			case '_':
				count = !count ? (* graphNum - 1) : count - 1;
				for (int i = 0; i < count; i++) {
					graphCurrent = graphCurrent->next;
				}
				system("cls");
				printf(menu2, count + 1);
				ShowGraph(graphCurrent);
				printf(menu3);
				break;
			case 'R':
			case 'r':
			case 138:
			case 170:
				for (int i = 0; i < count; i++) {
					graphCurrent = graphCurrent->next;
				}
				DeleteGraph(&graph, graphCurrent);
				(*graphNum)--;
				*setsNum = 0;
				*graphSetsNum = 0;
				if (!graph)
					return OptionShowGraph(graph, graphNum, setsNum, graphSetsNum);
				count = count ? count - 1 : count;
				graphCurrent = graph;
				for (int i = 0; i < count; i++) {
					graphCurrent = graphCurrent->next;
				}
				system("cls");
				printf(menu2, count + 1);
				ShowGraph(graphCurrent);
				printf(menu3);
				break;
			case 'Q':
			case 'q':
			case 137:
			case 169:
				return graph;
				break;
		}
	}
	return graph;
}

struct graph* OptionFindSet(struct graph* graph, int* graphNum, int* setsNum, int* graphSetsNum, struct graph* (*ReturnFunction)(struct graph*, int*, int*, int*)) {
	system("cls");
	char menu1[] =
		"  ______________________________________________________________________________\n"
		" /  Поиск_независимых_множеств_вершин________________________________///////////\n"
		" | |\n"
		" | |  Нет инициализированных графов для поиска множеств. Хотите создать граф? Y/N\n"
		" | \\____________________________________________________________________________\n"
		" \\__ISoGNS___________________________________________________________///////////";
	if (!graph || !*graphNum) {
		int temp = 0;
		printf(menu1);
		do {
			fseek(stdin, 0, SEEK_END);
			temp = _getch();
		} while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' && temp != 141 && temp != 173 && temp != 146 && temp != 226);
		return (temp == 'Y' || temp == 'y' || temp == 141 || temp == 173) ? OptionGenerateMatrix(graph, graphNum, setsNum, graphSetsNum, OptionShowGraph) : graph;
	}
	char menu2[] = 
		"  ______________________________________________________________________________\n"
		" /  Поиск_независимых_множеств_вершин________________________________///////////\n"
		" | |\n"
		" | |  Поиск завершен успешно. Статистика:\n"
		" | |\n",
		 menu3[] =
		" | |  Граф %d, кол-во независимых множеств = %d\n",
		 menu4[] = 
		" | |\n"
		" | |  Хотите перейти к просмотру множеств? Y / N\n"
		" | \\____________________________________________________________________________\n"
		" \\__ISoGNS___________________________________________________________///////////";
	struct graph* currentGraph = graph;
	*setsNum = 0;
	printf(menu2);
	int temp = 0, count = 0;
	do {
		temp = *setsNum;
		if (currentGraph->set) 
			for (int i = currentGraph->size - 1; i != 0; i--) {
				ClearLine(currentGraph->set + i, currentGraph->size, 0);
			};
		currentGraph->set = (struct setNI*)malloc(sizeof(struct setNI) * currentGraph->size);
		for (int i = 0; i < currentGraph->size; i++) {
			(currentGraph->set[i]).next = NULL;
			(currentGraph->set[i]).set = NULL;
			FindNotSmej(currentGraph->matrix, currentGraph->size, i, currentGraph->set + i, setsNum);
		}
		currentGraph = currentGraph->next;
		printf(menu3, ++count, *setsNum - temp);
	} while (currentGraph);
	printf(menu4);
	*graphSetsNum = *graphNum;
	do {
		fseek(stdin, 0, SEEK_END);
		temp = _getch();
	} while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' && temp != 141 && temp != 173 && temp != 146 && temp != 226);
	return (temp == 'Y' || temp == 'y' || temp == 141 || temp == 173) ? ReturnFunction(graph, graphNum, setsNum, graphSetsNum) : graph;
}

struct graph* OptionShowSet(struct graph* graph, int* graphNum, int* setsNum, int* graphSetsNum) {
	system("cls");
	char menu1[] =
		"  ______________________________________________________________________________\n"
		" /  Просмотр_независимых_множеств_вершин_____________________________///////////\n"
		" | |\n"
		" | |  Нет инициализированных графов для поиска множеств. Хотите создать граф? Y/N\n"
		" | \\____________________________________________________________________________\n"
		" \\__ISoGNS___________________________________________________________///////////";
	char menu2[] =
		"  ______________________________________________________________________________\n"
		" /  Просмотр_независимых_множеств_вершин_____________________________///////////\n"
		" | |\n"
		" | |  Нет множеств, которые можно просмотреть. Хотите произвести поиск множеств? Y/N\n"
		" | \\____________________________________________________________________________\n"
		" \\__ISoGNS___________________________________________________________///////////";
	if (!graph && !*graphNum) {
		int temp = 0;
		printf(menu1);
		do {
			fseek(stdin, 0, SEEK_END); temp = _getch();} while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' && temp != 141 && temp != 173 && temp != 146 && temp != 226);
		return (temp == 'Y' || temp == 'y' || temp == 141 || temp == 173) ? OptionGenerateMatrix(graph, graphNum, setsNum, graphSetsNum, OptionShowGraph) : graph;
}
	if (!*setsNum || !*graphSetsNum) {
		int temp = 0;
		printf(menu2);
		do {
			fseek(stdin, 0, SEEK_END); temp = _getch();} while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' && temp != 141 && temp != 173 && temp != 146 && temp != 226);
		return (temp == 'Y' || temp == 'y' || temp == 141 || temp == 173) ? OptionFindSet(graph, graphNum, setsNum, graphSetsNum, OptionShowSet) : graph;
	}
	int count = 0;
	char menu3[] =
		"  ______________________________________________________________________________\n"
		" /  Просмотр_независимых_множеств_вершин_____________________________///////////\n"
		" | |\n"
		" | |  Граф %d\n",
		menu4[] =
		" | \\____________________________________________________________________________\n"
		" \\__ISoGNS_/[-]Пред. [Q] Меню [+]След.\\______________________________///////////";
	printf(menu3, count + 1);
	for (int i = 0; i < graph->size; i++) {
		ShowList(graph->set + i, graph->size);
	}
	printf(menu4);
	while (1) {
		struct graph* graphCurrent = graph;
		switch (_getch()) {
		case '+':
		case '=':
			count = count == (*graphNum - 1) ? 0 : count + 1;
			for (int i = 0; i < count; i++) {
				graphCurrent = graphCurrent->next;
			}
			system("cls");
			printf(menu3, count + 1);
			for (int i = 0; i < graphCurrent->size; i++) {
				ShowList(graphCurrent->set + i, graphCurrent->size);
			}
			printf(menu4);
			break;
		case '-':
		case '_':
			count = !count ? (*graphNum - 1) : count - 1;
			for (int i = 0; i < count; i++) {
				graphCurrent = graphCurrent->next;
			}
			system("cls");
			printf(menu3, count + 1);
			for (int i = 0; i < graphCurrent->size; i++) {
				ShowList(graphCurrent->set + i, graphCurrent->size);
			}
			printf(menu4);
			break;
		case 'Q':
		case 'q':
		case 137:
		case 169:
			return graph;
			break;
		}
	}
	return graph;
}

void OptionGetFileName(char* fileNameHolder, int type) {
	system("cls");
	char menu1[] =
		"  ______________________________________________________________________________\n"
		" /  Сохранение%s_____________________________________///////////\n"
		" | |\n"
		" | |  Введите название файла(без формата): ";
	do { fseek(stdin, 0, SEEK_END); system("cls"); printf(menu1, !type ? "/загрузка_графов__" : "_множеств_________"); } while (!scanf("%s", fileNameHolder));
}

struct graph* OptionSaveGraph(struct graph* graph, int* graphNum, int* setsNum, int* graphSetsNum, char* file) {
	//system("cls");
	
	char menu1[] =
		"  ______________________________________________________________________________\n"
		" /  Сохранение/загрузка_графов_______________________________________///////////\n"
		" | |\n",
		menu2[] = 
		" | |  %s\n"
		" | \\____________________________________________________________________________\n"
		" \\__ISoGNS___________________________________________________________///////////";
	if (!graph || !*graphNum) {
		int temp = 0;
		printf(menu1);
		printf(menu2, "Нет инициализированных графов для сохранения. Хотите создать граф? Y/N");
		do {
			fseek(stdin, 0, SEEK_END);
			temp = _getch();
		} while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' && temp != 141 && temp != 173 && temp != 146 && temp != 226);
		return (temp == 'Y' || temp == 'y' || temp == 141 || temp == 173) ? OptionGenerateMatrix(graph, graphNum, setsNum, graphSetsNum, OptionShowGraph) : graph;
	}
	if (!file[0])
		OptionGetFileName(file, 0);
	char fileName[256] = "";
	strcpy(fileName, file);
	strcpy(strchr(fileName, '\0'), ".gr");

	FILE* dbFile = fopen(fileName, "w");
	if (!dbFile) {
		printf(menu1);
		printf(menu2, "Ошибка, не удалось создать/открыть файл для сохранения.\n | |  Нажмите любую клавишу для продолжения...");
		(void)_getch();
		return graph;
	}

	struct graph* graphCurrent = graph;
	char graphInfo[] = "##########\n#%d########\n##########\n";
	do {
		fprintf(dbFile, graphInfo, graphCurrent->size);
		for (int i = 0; i < graphCurrent->size; i++) {
			for (int j = 0; j < graphCurrent->size; j++) {
				fprintf(dbFile, "%d, ", graphCurrent->matrix[i * graphCurrent->size + j]);
			}
			fprintf(dbFile, "\n");
		}
		graphCurrent = graphCurrent->next;
	} while (graphCurrent);
	fclose(dbFile);

	system("cls");
	printf(menu1);
	printf(menu2, "Успешно сохранено. Хотите открыть файл? Y/N");;
	int temp = 0;
	do {
		fseek(stdin, 0, SEEK_END);
		temp = _getch();
	} while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' && temp != 141 && temp != 173 && temp != 146 && temp != 226);
	if (temp == 'Y' || temp == 'y' || temp == 141 || temp == 173) {
		char temp[264] = "notepad ";
		strcpy(strchr(temp, '\0'), fileName);
		system(temp);
	}
	return graph;
}

struct graph* OptionSaveSets(struct graph* graph, int* graphNum, int* setsNum, int* graphSetsNum) {
	//system("cls");
	char filename[256] = { 0 };
	char menu1[] =
		"  ______________________________________________________________________________\n"
		" /  Сохранение_множеств______________________________________________///////////\n"
		" | |\n",
		menu2[] =
		" | |  %s\n"
		" | \\____________________________________________________________________________\n"
		" \\__ISoGNS___________________________________________________________///////////";
	printf(menu1);
	if (!graph || !*graphNum) {
		int temp = 0;
		printf(menu2, "Нет инициализированных графов для сохранения. Хотите создать граф? Y/N");
		do {
			fseek(stdin, 0, SEEK_END);
			temp = _getch();
		} while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' && temp != 141 && temp != 173 && temp != 146 && temp != 226);
		return (temp == 'Y' || temp == 'y' || temp == 141 || temp == 173) ? OptionGenerateMatrix(graph, graphNum, setsNum, graphSetsNum, OptionShowGraph) : graph;
	}
	if (!*setsNum || !*graphSetsNum) {
		int temp = 0;
		printf(menu2, "Нет множеств, которые можно сохранить. Хотите произвести поиск множеств? Y/N");
		do {
			fseek(stdin, 0, SEEK_END); temp = _getch();
		} while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' && temp != 141 && temp != 173 && temp != 146 && temp != 226);
		return (temp == 'Y' || temp == 'y' || temp == 141 || temp == 173) ? OptionFindSet(graph, graphNum, setsNum, graphSetsNum, OptionShowSet) : graph;
	}
	char fileName[256] = "";
	OptionGetFileName(fileName, 1);
	strcpy(strchr(fileName, '\0'), ".st");

	FILE* dbFile = fopen(fileName, "w");
	if (!dbFile) {
		printf(menu2, "Ошибка, не удалось создать/открыть файл для сохранения.\n | |  Нажмите любую клавишу для продолжения...");
		(void)_getch();
		return graph;
	}
	int count = 1;
	struct graph* graphCurrent = graph;
	char graphInfo[] = "##########\n#%d########\n##########\n";
	do {
		fprintf(dbFile, graphInfo, count++);
		for (int i = 0; i < graphCurrent->size; i++) {
			ShowListAdv(graphCurrent->set + i, graphCurrent->size, dbFile);
		}
		graphCurrent = graphCurrent->next;
	} while (graphCurrent);
	fclose(dbFile);

	system("cls");
	printf(menu1);
	printf(menu2, "Успешно сохранено. Хотите открыть файл? Y/N");
	int temp = 0;
	do {
		fseek(stdin, 0, SEEK_END);
		temp = _getch();
	} while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' && temp != 141 && temp != 173 && temp != 146 && temp != 226);
	if (temp == 'Y' || temp == 'y' || temp == 141 || temp == 173) {
		char temp[264] = "notepad ";
		strcpy(strchr(temp, '\0'), fileName);
		system(temp);
	}
	return graph;
}

struct graph* OptionLoadGraph(struct graph* graph, int* graphNum, int* setsNum, int* graphSetsNum, char* file) {
	system("cls");

	char menu1[] =
		"  ______________________________________________________________________________\n"
		" /  Сохранение/загрузка_графов_______________________________________///////////\n"
		" | |\n",
		menu2[] =
		" | |  %s\n"
		" | \\____________________________________________________________________________\n"
		" \\__ISoGNS___________________________________________________________///////////";
	printf(menu1);
	if (graph || *graphNum) {
		int temp = 0;
		printf(menu2, "В программе найдены инициализированные графы. Хотите продолжить? Y/N");
		do {
			fseek(stdin, 0, SEEK_END);
			temp = _getch();
		} while (temp != 'Y' && temp != 'y' && temp != 'N' && temp != 'n' && temp != 141 && temp != 173 && temp != 146 && temp != 226);
		if (temp == 'N' || temp == 'n' || temp == 146 || temp == 226) return graph;
	}
	
	if (!file[0])
		OptionGetFileName(file, 0);
	char fileName[256] = "";
	strcpy(fileName, file);
	strcpy(strchr(fileName, '\0'), ".gr");

	FILE* dbFile = fopen(fileName, "r+");
	if (!dbFile) {
		system("cls");
		printf(menu1);
		printf(menu2, "Ошибка, не удалось открыть файл для загрузки.\n | |  Нажмите любую клавишу для продолжения...");
		(void)_getch();
		return graph;
	}

	struct graph* cGraph = NULL, * temp = NULL;
	int tempCount = 0, tempSize = 0;
	while (1) {
		if (fscanf(dbFile, "##########\n#%d########\n##########\n", &tempSize) != 1) {
			fclose(dbFile);
			if (!tempCount || !cGraph) {
				system("cls");
				printf(menu1);
				printf(menu2, "Ошибка, некорректный файл. Нажмите любую клавишу для продолжения...");
			}
			else {
				system("cls");
				printf(menu1);
				printf(menu2, "Графы были загружены успешно. Нажмите любую клавишу для продолжения...");
				if (graph) {
					DeleteGraphs(graph, graph);
					graph->matrix = NULL;
					graph->next = NULL;
					graph->set = NULL;
					graph->size = 0;
				}
				*graphNum = tempCount;
				*setsNum = 0;
				*graphSetsNum = 0;
			}
			(void)_getch();
			return !cGraph ? graph : cGraph;
		}
		if (!cGraph) {
			cGraph = (struct graph*)malloc(sizeof(struct graph));
			temp = cGraph;
		}
		else {
			temp->next = (struct graph*)malloc(sizeof(struct graph));
			temp = temp->next;
		}
		tempCount++;
		temp->size = tempSize;
		temp->matrix = (int*)malloc(sizeof(int) * tempSize * tempSize);
		for (int i = 0; i < tempSize * tempSize; i++) {
			temp->matrix[i] = 0;
		}
		temp->set = NULL;
		temp->next = NULL;
		for (int i = 0; i < tempSize; i++) {
			for (int j = 0; j < tempSize; j++) {
				fscanf(dbFile, "%d, ", (temp->matrix + i * tempSize + j));
			}
			fscanf(dbFile, "\n");
		}
	}
	
}

struct graph* OptionManageGraph(struct graph* graph, int* graphNum, int* setsNum, int* graphSetsNum, char* defaultName) {
	system("cls");
	int markerPosition = 0;
	char menu1[] =
		"  ______________________________________________________________________________\n"
		" /  Сохранение/загрузка_графов_______________________________________///////////\n"
		" | |\n"
		" | |\tСохранение графов в файл\n"
		" | |  [%c] Быстрое сохранение [%s.gr]\n"
		" | |  [%c] Сохранение\n"
		" | |\n"
		" | |\tЗагрузка графов из файла\n"
		" | |  [%c] Быстрая загрузка [%s.gr]\n"
		" | |  [%c] Загрузка\n"
		" | |\n"
		" | |  [%c] Меню\n"
		" | \\____________________________________________________________________________\n"
		" \\__ISoGNS___________________________________________________________///////////",
		 filename[256] = { 0 };
	printf(menu1, markerPosition == 0 ? '#' : ' ', defaultName, markerPosition == 1 ? '#' : ' ', markerPosition == 2 ? '#' : ' ', defaultName, markerPosition == 3 ? '#' : ' ', markerPosition == 4 ? '#' : ' ');
	for (;;) {
		if (_kbhit()) {
			int pressedButton = _getch();
			if (pressedButton != 13 && pressedButton != 72 && pressedButton != 80)
				continue;
			system("cls");
			switch (pressedButton) {
			case 13:
				switch (markerPosition) {
				case 0:
					return OptionSaveGraph(graph, graphNum, setsNum, graphSetsNum, defaultName);
				case 1:
					return OptionSaveGraph(graph, graphNum, setsNum, graphSetsNum, filename);
				case 2:
					return OptionLoadGraph(graph, graphNum, setsNum, graphSetsNum, defaultName);
				case 3:
					return OptionLoadGraph(graph, graphNum, setsNum, graphSetsNum, filename);
				case 4:
					return graph;
				}
				break;
			case 72:
				markerPosition = markerPosition == 0 ? 4 : markerPosition - 1;
				break;
			case 80:
				markerPosition = markerPosition == 4 ? 0 : markerPosition + 1;
				break;
			}
			printf(menu1, markerPosition == 0 ? '#' : ' ', defaultName, markerPosition == 1 ? '#' : ' ', markerPosition == 2 ? '#' : ' ', defaultName, markerPosition == 3 ? '#' : ' ', markerPosition == 4 ? '#' : ' ');
			}
		Sleep(100);
	}
}
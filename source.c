//Поиск независимых множеств вершин графа
//independent sets of graph nodes search
#include "h\menu.h"

int main() {
	srand(time(NULL));
	Intro();
	system("cls");
	struct graph* matrixs = NULL;
	int graphNum = 0, setsNum = 0, graphSetsNum = 0, marker = 0;
	char defaultName[256] = "default";
	while (1) {
		marker = MainMenu(graphNum, setsNum, graphSetsNum, marker);
		switch (marker) {
		case 0:
			matrixs = OptionGenerateMatrix(matrixs, &graphNum, &setsNum, &graphSetsNum, OptionShowGraph);//генерация
			break;
		case 1:
			matrixs = OptionShowGraph(matrixs, &graphNum, &setsNum, &graphSetsNum);//Просмотр
			break;
		case 2:
			matrixs = OptionManageGraph(matrixs, &graphNum, &setsNum, &graphSetsNum, defaultName);//Сохранение/загрузка1
			break;
		case 3:
			matrixs = OptionFindSet(matrixs, &graphNum, &setsNum, &graphSetsNum, OptionShowSet);//Поиск
			break;
		case 4:
			matrixs = OptionShowSet(matrixs, &graphNum, &setsNum, &graphSetsNum);//Просмотр
			break;
		case 5:
			matrixs = OptionSaveSets(matrixs, &graphNum, &setsNum, &graphSetsNum);//Сохранение2
			break;
		case 6:
			OptionGetFileName(defaultName, 0);
			break;
		case 7:
			system("cls");
			exit(0);
			break;
		}
		system("cls");
	}
}
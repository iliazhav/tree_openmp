#include "Task.h"

const double eps = 1e-8;
int n = 2e6;                
int m = 1000;

int main()
{
	omp_set_num_threads(4);

	tree* tr = new tree;
	double* mas;    
	double time;
	std::string points("p1.txt");
	std::string tree("f1.txt");
	std::string flag("f");
	
	//createtxt(5e6, 1000, tree, points);

	// Инициализация
	tree_init(tr, time, flag, tree);        
	std::cout << "Tree from a file is created in " << time << " sec.";
	points_init(mas, flag, points);    

	// Проверка
	printR(tr);  // Правая ветвь
	printL(tr);  // Левая ветвь
	
	// Поиск
	std::cout << "\nSum = " << find(tr, mas, time);
	std::cout << "\nTime = " << time << " sec.\n";

	delete[] mas;
	free_tree(tr);
}

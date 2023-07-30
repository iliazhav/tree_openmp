#pragma once
#include "Task.h"


void points_init(double*& mas, std::string flag, std::string filename)
{
	if (flag == "r")
	{
		mas = new double[m];
		for (int i = 0; i < m; i++)
		{
			mas[i] = i * eps * rand;
		}
	}
	if (flag == "f")
	{
		std::ifstream file{ filename };
		if (!file.is_open()) std::cout << "Go back";

		file >> m;
		mas = new double[m];
		for (int i = 0; i < m; i++)
		{
			file >> mas[i];
		}
	}
}

void tree_init(tree* tr, double& time, std::string flag, std::string filename)
{
	body* mas(nullptr);

	if (flag == "r")
	{
		mas = new body[n];
		for (int i = 1; i < n; i++)
		{
			mas[i].x = rand;
			mas[i].m = rand;
		}
	}
	if (flag == "f")
	{
		std::ifstream file{ filename };
		if (!file.is_open()) std::cout << "Go back";

		file >> n;
		mas = new body[n];

		file >> tr->pnt.x;
		file >> tr->pnt.m;
		tr->left = tr->right = nullptr;

		for (int i = 1; i < n; i++)
		{
			file >> mas[i].x;
			file >> mas[i].m;
		}
	}                          

	time = -omp_get_wtime();
#pragma omp parallel for schedule(dynamic)
	for (int i = 1; i < n; i++)
	{
		double x = mas[i].x;
		double m = mas[i].m;

		tree* ptr = tr;
		while (ptr)
		{
			if (x < ptr->pnt.x)
				if (ptr->left) {
					ptr = ptr->left;
				}
				else
				{
#pragma omp critical
					{
						if (!(ptr->left)) {
							tree* tmp = new tree;
							ptr->left = tmp;
							tmp->pnt.x = x;
							tmp->pnt.m = m;
							ptr = tmp->left = tmp->right = nullptr;
						}
					}
				}
			else
				if (ptr->right) {
					ptr = ptr->right;
				}
				else
				{
#pragma omp critical
					{
						if (!(ptr->right)) {
							tree* tmp = new tree;
							ptr->right = tmp;
							tmp->pnt.x = x;
							tmp->pnt.m = m;
							ptr = tmp->left = tmp->right = nullptr;
						}
					}
				}
		}
		delete ptr;
	}
	time += omp_get_wtime();
	delete[] mas;
}

void free_tree(tree* tr)
{
	if (tr == nullptr)
	{
		return;
	}

	free(tr->left);
	free(tr->right);

	delete tr;
}

void createtxt(int n, int m, std::string treename, std::string pntsname)
{
	std::ofstream tree(treename);
	std::ofstream pnts(pntsname);

	tree << n << std::endl;
	for (int i = 0; i < n; i++)
	{
		tree << rand << " " << rand << std::endl;
	}
	pnts << m << std::endl;
	for (int i = 0; i < m; i++)
	{
		pnts << rand << std::endl;
	}

	pnts.close();
	tree.close();
}
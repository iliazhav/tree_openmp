#pragma once
#include "Task.h"


void printR(tree* tr)
{
	tree* ptr = tr;
	std::cout << "\n\nRight branch:\n";
	while (ptr)
	{
		std::cout << ptr->pnt.x << "\n";
		ptr = ptr->right;
	}
}

void printL(tree* tr)
{
	tree* ptr = tr;
	std::cout << "\nLeft branch:\n";
	while (ptr)
	{
		std::cout << ptr->pnt.x << "\n";
		ptr = ptr->left;
	}
}

double find(tree* tr, double* mas, double& time)
{
	double sum = 0;
	tree* ptr;

	time = -omp_get_wtime();
#pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < m; i++)
	{
		ptr = tr;
		double x = mas[i];
		while (ptr)
		{
			if (fabs(ptr->pnt.x - x) <= eps)
			{
				double temp = 0;
				alternative(ptr, x, temp);
				sum += temp;
				ptr = nullptr;
			}
			else if (x < ptr->pnt.x)
			{
				ptr = ptr->left;
			}
			else if (x > ptr->pnt.x)
			{
				ptr = ptr->right;
			}
		}
	}
	time += omp_get_wtime();
	return sum;
}

void alternative(tree* tr, double num, double& sum)
{
	if (fabs(tr->pnt.x - num) <= eps)
	{
		sum += tr->pnt.m;
		if (tr->left)
		{
			tr = tr->left;
			alternative(tr, num, sum);
		}
		if (tr->right)
		{
			tr = tr->right;
			alternative(tr, num, sum);
		}
		return;
	}
	return;
}
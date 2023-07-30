#pragma once
#include <iostream>
#include <omp.h>
#include <fstream>
#include <cmath>

#define rand rand() / 10.0

extern const double eps;
extern int n;
extern int m;

struct body
{
	double x = 0;
	double m = 0;
};
struct tree
{
	tree* left = nullptr;
	tree* right = nullptr;
	body pnt;
};

double find(tree* tr, double* mas, double& time);
void alternative(tree* tr, double num, double& sum);

void points_init(double*& mas, std::string flag, std::string filename);
void tree_init(tree* tr, double& time, std::string flag, std::string filename);

void printR(tree* tr);
void printL(tree* tr);

void free_tree(tree* tr);
void createtxt(int n, int m, std::string treename, std::string pntsname);
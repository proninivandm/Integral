#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define _USE_MATH_DEFINES
#define eps2 0.0001
#define eps 0.01
#define k 5
#include <math.h>
void chtenie(char *str, char *s, char *otr);
double integral1(double func(double), double x1, double x2);
double integral2(double func(double), double x1, double x2);
double f(double x);
double help_func(double x);
double os_tka(double(*Func)(double));
int znak1, znak2, trigonflag, en;
char arg[5][128];
double a, b, x_err;

int main()
{
	double integ1 = 0;
	double integ2 = 0;
	double x = 0;
	char s[128], st[128], otr[128];
	const char filenamein[] = "Text.bin";
	FILE *in;
	fopen_s(&in, filenamein, "r");
	if (!in)
	{
		perror("OPENING ERROR");
		return 0;
	}
	fread(s, sizeof(char), 128, in);
	fclose(in);
	printf("%.35s\n", s);
	printf("\nn=");
	scanf_s("%d", &en);
	chtenie(st, s, otr);

	if ((znak1 == 3)&&((strcmp(arg[3], "x"))||(strcmp(arg[3], "-x"))))
	{
		x_err = os_tka(help_func);
		integ1 = integral1(&f, a, x_err - eps2) + integral1(&f, x_err + eps2, b);
		integ2 = integral2(&f, a, x_err - eps2) + integral2(&f, x_err + eps2, b);
	}
	else
	{
		integ1 = integral1(&f, a, b);
		integ2 = integral2(&f, a, b);
	}

	printf("\nZnachenie integrala metodom trapezii =%f\n", integ1);
	printf("\nZnachenie integrala metodom pryamougolnikov =%f\n", integ2);
	_gettch();
	return 0;
}
void chtenie(char *str, char *s, char *otr)
{
	strncpy_s(str, 128, s, strcspn(s, "[") - 1);
	int i = 0;
	char razd[] = " ^+-*/=()";
	char *next = NULL;
	switch ((int)strchr(str, ')')[2])
	{
	case'+':
		znak1 = 0;
		break;
	case'-':
		znak1 = 1;
		break;
	case'*':
		znak1 = 2;
		break;
	case'/':
		znak1 = 3;
		break;
	}
	switch ((int)strrchr(str, ')')[2])
	{
	case'+':
		znak2 = 0;
		break;
	case'-':
		znak2 = 1;
		break;
	case'*':
		znak2 = 2;
		break;
	case'/':
		znak2 = 3;
		break;
	}
	strtok_s(str, razd, &next);
	str = strtok_s(NULL, razd, &next);
	while (str != NULL)
	{
		strcpy_s(arg[i], 5, str);
		str = strtok_s(NULL, razd, &next);
		i = i + 1;
	}
	if (strcmp(arg[2], "cosec") == 0)
		trigonflag = 0;
	else
		if (strcmp(arg[2], "sec") == 0)
			trigonflag = 1;
		else
			if (strcmp(arg[2], "ctg") == 0)
				trigonflag = 2;
			else
				if (strcmp(arg[2], "tg") == 0)
					trigonflag = 3;
				else
					if (strcmp(arg[2], "cos") == 0)
						trigonflag = 4;
					else
						if (strcmp(arg[2], "sin") == 0)
							trigonflag = 5;
	strcpy_s(otr, 128, strchr(s, '['));
	printf("otrezok:  %.10s\n", otr);
	char razd1[] = " ;[]";
	char *next1 = NULL;
	otr = strtok_s(otr, razd1, &next1);
	a = atof(otr);
	otr = strtok_s(NULL, razd1, &next1);
	b = atof(otr);
}
double integral1(double func(double), double x1, double x2)
{
	int n = en;
	double del = (x2 - x1) / n;
	double S1 = 0, S = 0;
	for (int i = 0; i < n; i++)
	{
		S = S + del*(func(x1 + del*i) + func(x1 + del*(i + 1))) / 2;
	}
	n *= k;
	del /= k;
	for (int i = 0; i < n; i++)
	{
		S1 = S1 + del*(func(x1 + del*i) + func(x1 + del*(i + 1))) / 2;
	}
	while (fabs(S1 - S)>eps)
	{
		S = S1;
		S1 = 0;
		n *= k;
		del /= k;
		for (int i = 0; i < n; i++)
		{
			S1 = S1 + del*(func(x1 + del*i) + func(x1 + del*(i + 1))) / 2;
		}
	}
	return S1;
}
double f(double x)
{
	double buf = 0;
	double itog = 0;

		if ((int)arg[0][0] == (int)'-')
			if ((int)arg[0][1] == (int)'e')
				itog = -M_E;
			else
				if ((int)arg[0][1] == (int)'x')
					itog = -x;
				else
					itog = atof(arg[0]);
		else
			if ((int)arg[0][0] == (int)'e')
				itog = M_E;
			else
				if ((int)arg[0][0] == (int)'x')
					itog = x;
				else
					itog = atof(arg[0]);

		if ((int)arg[1][0] == (int)'-')
			if ((int)arg[1][1] == (int)'e')
				itog = pow(itog, -M_E);
			else
				if ((int)arg[1][1] == (int)'x')
					itog = pow(itog, -x);
				else
					itog = pow(itog, atof(arg[1]));
		else
			if ((int)arg[1][0] == (int)'e')
				itog = pow(itog, M_E);
			else
				if ((int)arg[1][0] == (int)'x')
					itog = pow(itog, x);
				else
					itog = pow(itog, atof(arg[1]));

		if ((int)arg[3][0] == (int)'-')
			if ((int)arg[3][1] == (int)'e')
				buf = -M_E;
			else
				if ((int)arg[3][1] == (int)'x')
					buf = -x;
				else
					buf = atof(arg[3]);
		else
			if ((int)arg[3][0] == (int)'e')
				buf = M_E;
			else
				if ((int)arg[3][0] == (int)'x')
					buf = x;
				else
					buf = atof(arg[3]);
		switch (trigonflag)
		{
		case 0:
			buf = 1 / sin(buf);
			break;
		case 1:
			buf = 1 / cos(buf);
			break;
		case 2:
			buf = 1 / tan(buf);
			break;
		case 3:
			buf = tan(buf);
			break;
		case 4:
			buf = cos(buf);
			break;
		case 5:
			buf = sin(buf);
			break;
		}
		switch (znak1)
		{
		case 0:
			itog = itog + buf;
			break;
		case 1:
			itog = itog - buf;
			break;
		case 2:
			itog = itog * buf;
			break;
		case 3:
			itog = itog / buf;
			break;
		}

		switch (znak2)
		{
		case 0:
			itog = itog + atof(arg[4]);
			break;
		case 1:
			itog = itog - atof(arg[4]);
			break;
		case 2:
			itog = itog * atof(arg[4]);
			break;
		case 3:
			itog = itog / atof(arg[4]);
			break;
		}
		
	return itog;
}
double os_tka(double(*Func)(double))
{
	double x = a;
	while (fabs(Func(x)) > eps2)
	{
		x = (a + b) / 2;
		if (Func(a)*Func(x) < 0)
			b = x;
		else
			a = x;
	}
	return x;
}
double help_func(double x)
{
	switch (trigonflag)
	{
	case 0:
		return 1 / sin(x);
		break;
	case 1:
		return 1 / cos(x);
		break;
	case 2:
		return 1 / tan(x);
		break;
	case 3:
		return tan(x);
		break;
	case 4:
		return cos(x);
		break;
	case 5:
		return sin(x);
		break;
	}
	return 0;
}

double integral2(double func(double), double x1, double x2)
{
	int n = en;
	double del = (x2 - x1) / n;
	double S1 = 0, S = 0;
	for (int i = 0; i < n-1; i++)
	{
		S = S + del*func(x1 + del*(i+0.5));
	}
	n *= k;
	del /= k;
	for (int i = 0; i < n-1; i++)
	{
		S1 = S1 + del*func(x1 + del*(i+0.5));
	}
	while (fabs(S1 - S)>eps)
	{
		S = S1;
		S1 = 0;
		n *= k;
		del /= k;
		for (int i = 0; i < n-1; i++)
		{
			S1 = S1 + del*func(x1 + del*(i + 0.5));
		}
	}
	return S1;
}
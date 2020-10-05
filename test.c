///* friends.c -- использование указателя на структуру */
//#include <stdio.h>
//#define LEN 20
//
//struct names {
//	char first[LEN];
//	char last[LEN];
//};
//
//struct guy {
//	struct names handle;
//	char favfood[LEN];
//	char job [LEN];
//	float income;
//};
//
//
//int main(void)
//{
//	struct guy fellow[2] = {
//		{{ "Billy", "Bone" },
//		"fyed omars",
//		"personal trainer",
//		68122.00
//		},
//	
//		{{"Jim", "Hoakins" },
//		"fish frikase",
//		"tabloid editor",
//		232400.00
//		}
//	};
//
//struct guy *him; /* указатель на структуру */
//
//	printf("aдpec #1: %p #2: %p \n ", &fellow[0], &fellow[1]);
//	him = &fellow[0]; /* сообщает указателю, на что указывать */
//	printf("указатель #1: %p #2: %p \n ", him, him + 1);
//	printf("him->income равно $%.2f: (*him).income равно $%.2f\n",
//		him->income, (*him).income);
//	him++; /* указатель на следующую структуру */
//	printf("him->favfood равно %s: him->handle.last равно %s\n",
//	him->favfood, him->handle.last);
//	return (0);
//}
//
//

///* fundsl.c -- передача членов структуры в качестве аргументов */
//#include <stdio.h>
//#define FUNDLEN 50
//
//struct funds {
//	char bank[FUNDLEN];
//	double bankfund;
//	char save[FUNDLEN];
//	double savefund;
//};
//
//double sum_old(double, double) ;
//double sum(const struct funds *money);
//
//int main(void)
//{
//	struct funds stan = {
//	"Garlic-Melon Bank",
//	4032.27,
//	"Lucky's Savings and Loan",
//	8543.94
//	};
//
//	//printf("Общая сумма на счетах у Стэна составляет $ %.2f.\n", sum(stan.bankfund, stan.savefund));
//	
//	printf("Общая сумма на счетах у Стэна составляет $ %.2f.\n", sum(&stan));
//return (0);
//}
///* суммирование двух чисел типа double */
//double sum_old(double x, double y)
//{
//	return (x + y);
//}
//
//double sum(const struct funds *money)
//{
//	return(money->bankfund + money->savefund);
//}

/* namesl.c -- использует указатели на структуры */
#include <stdio.h>
#include <string.h>
#define NLEN 30

struct namect {
	char fname[NLEN];
	char lname[NLEN];
	int letters;
};

void getinfo(struct namect *);
void makeinfo(struct namect *);
void showinfo(const struct namect *);
char *s_gets(char * st, int n);

int main(void)
{
	struct namect person;
	getinfo(&person);
	makeinfo(&person);
	showinfo(&person);
	return 0;
}

void getinfo (struct namect *pst)
{
	printf("Введите свое имя.\n");
	s_gets(pst->fname, NLEN);
	printf("Введите свою фамилию.\n") ;
	s_gets(pst->lname, NLEN);
}

void makeinfo (struct namect *pst)
{
	pst->letters = strlen(pst->fname) + strlen(pst->lname);
}

void showinfo (const struct namect * pst)
{
	printf("%s %s, ваше имя и фамилия содержат %d букв.\n", pst->fname, pst->lname, pst->letters) ;
}

char * s_gets(char * st, int n)
{
	char *ret_val;
	char *find;

	ret_val = fgets(st, n, stdin) ;
	if (ret_val)
	{
		find = strchr(st, '\n'); // поиск новой строки
		if (find) // если адрес не равен NULL,
			*find = '\0'; // поместить туда нулевой символ
		else
			while (getchar () != '\n')
				continue; // отбросить остаток строки
	}
	return ret_val;
}

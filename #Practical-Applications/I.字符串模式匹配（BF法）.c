#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 16

typedef struct {
	char text[MAXLEN + 1];
	int length;
}string;

string* initstr();
void match_bf_ptr_lsp(string* s, char* p);
void match_bf_arr_lsp(string* s, char* p);
void match_bf_all(string* s, char* p);
void destroystr(string* s);

int main(int argc, const char* argv[])
{
	string* s = initstr();
	char t[] = "abababababababa";
	s->length = strlen(t);
	strcpy_s(s->text, MAXLEN, t);
	printf("%s\n", s->text);
	char p[] = "aba";
	//match_bf_ptr_lsp(s, p);
	match_bf_arr_lsp(s, p);
	match_bf_all(s, p);
	destroystr(s);
}

string* initstr()
{
	string* ret = (string*)malloc(sizeof(string));
	if (!ret) exit(EXIT_FAILURE);
	ret->length = 0;
	return ret;
}

void match_bf_ptr_lsp(string* s, char* p)
{
	char* i = p;
	char* j = s->text;
	int k = 0;
	while (1)
	{
		if (*i == '\0')
		{
			printf("The position of the pattern string is %d.\n", k + 1);
			break;
		}
		if (*j == '\0')
		{
			printf("Text not found.\n");
			break;
		}
		if (*i == *j)
		{
			i++;
			j++;
		}
		else
		{
			k++;
			i = p;
			j = &(s->text[k]);
		}
	}
}

void match_bf_arr_lsp(string* s, char* p)
{
	int i = 0;
	int j = 0;
	while (1)
	{
		if (p[i] == '\0')
		{
			printf("The position of the pattern string is %d.\n", (int)(j + 1 - strlen(p)));
			break;
		}
		if (s->text[j] == '\0')
		{
			printf("Text not found.\n");
			break;
		}
		if (p[i] == s->text[j])
		{
			i++;
			j++;
		}
		else
		{
			i = 0;
			j = j - i + 1;
		}
	}
}

void match_bf_all(string* s, char* p)
{
	int i = 0;
	int j = 0;
	for (int start = 0; start <= s->length - strlen(p); start++)
	{
		while (1)
		{
			if (p[i] == '\0')
			{
				printf("The pattern string has been found at %d.\n", (int)(j + 1 - strlen(p)));
				i = 0;
				j = start + 1;
				break;
			}
			if (s->text[j] == p[i])
			{
				i++;
				j++;
			}
			else
			{
				i = 0;
				j = start + 1;
				break;
			}
		}
		
	}
}

void destroystr(string* s)
{
	free(s);
}
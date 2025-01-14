#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

void printCharCodes();
char* escape(char*, char*);
void reverse(char*); //recursive
int htoi(char []);
char* itob(int, char*, int);

void test(int n)
{
    if (n < 0) {
        putchar('-');
        n = -n;
    }

    if (n / 10) {
        test(n / 10);
    }
    putchar(n % 10 + '0');
}

int main(int argc, char *argv[])
{
    printCharCodes();
    //reverse("string");
    
	return 0; 
}

void reverse(char* s)
{
    char* t = s;
    char c = *t;
    t++;

    if (c != '\0') {
        reverse(s);
    }
    putchar(c);
}

char* itob(int n, char* s, int b) 
{
	int nums[n];

	int div = n;
	int len = 0;
	for (int i=0; div>0; i++) {
		nums[i] = div % b;
		div=floor((float)div/b);
		len = i;
	}

	for (int i=0; i<=len; i++) {
		if (nums[len-i] < 10) {
			s[i] = nums[len-i] + '0';
		} else {
			s[i] = nums[len-i] + 'A' - 10;	
		}
	}

	s[len+1] = '\0';

	return s;	
}

int htoi(char original[]) 
{
	char s[strlen(original)];
	for (int i=0; i<strlen(original); ++i) {
		s[i] = original[i];
	}

	if (s[0] == '0') {
		int len = strlen(s);
		for (int i=2; i<len; ++i) {
			s[i-2] = s[i];
		}
		s[len-2] = '\0';
	}

	int output = 0;
	int o = 0;

	for (int i=strlen(s)-1; i>=0; --i) {
		if (isdigit(s[i])) {
			output += (s[i] - '0') * pow(16,o);
		} else if (s[i] >= 'A' && s[i] <= 'F') {
			output += (s[i] - 'A' + 10) * pow(16,o);
		}
		++o;
		s[i] = '\0';
	}

	return output;
}

// convert '\n' and '\t' to characters that can be seen
char* escape(char* s, char* t) 
{
    int offset = 0;
    
    for (int i=0; i<strlen(s); ++i) {
        t[i + offset] = s[i];
        switch (s[i]) {
            case '\n':
                t[i + offset] = '\\';
                t[i + offset + 1] = 'n';
                offset++;
                break;
            case '\t':
                t[i + offset] = '\\';
                t[i + offset + 1] = 't';
                offset++;
                break;
        }
    }
    
    return t;
}

void printCharCodes() 
{
	for (int i=0; i<=127; ++i) {
		printf("%c : %d\t",i,i);
	}
}



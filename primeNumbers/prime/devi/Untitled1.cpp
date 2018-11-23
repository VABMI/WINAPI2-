
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[80];
  char s[80];
  int i;
  for(i=0;i<10;i++)
  	strcpy (str,sprintf(s, "%s%f", " ", i));

  puts (str);
  return 0;
}

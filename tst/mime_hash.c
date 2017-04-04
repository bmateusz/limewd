
// gcc mime_hash.c && ./a.out

#include "../src/mime.h"
#include "../src/mime.c"

int hash(const char *str, int i, int j, int k, int n)
{
  int len = strlen(str);
  if (len == 0)
  {
    return 0;
  }
  else
  {
    // return (((str[0] + str[1] + str[2]) % n * i) + ((str[0] + str[2]) % n * j) + (str[0]) * k + len) % n;
    return ((str[0] & i) + (str[1] & j) + len) % n;
  }
}

int main()
{
  for (int i = 0; i < n_mime_str * 2; i += 2)
  {
    printf("\"%s\": \"%s\"\n", mime_str[i], mime_str[i + 1]);
  }

  int n = n_mime_str;
  char ht[n];
  char verbose = 0;
  int iterations = 512;
  int maxs = 0;
  
  for (int i = 0; i < iterations; ++i)
  {
    for (int j = 0; j < iterations; ++j)
    {
      char found = 1;
      memset(ht, 0, n);
      if (verbose) printf(" --- %d --- %d --- \n", i, j);
      for (int s = 0; s < n; ++s)
      {
        int h = hash(mime_str[s * 2], i, j, 0, n);
        if (ht[h])
        {
          found = 0;
          if (verbose) printf("collision at %d '%s'\n", h, mime_str[s * 2]);
          break; // collision, skip
        }
        else
        {
          ht[h] = s + 1; // because of 0
          if (maxs < s)
          {
            maxs = s;
          }
          if (verbose) printf("hash '%s' to %d\n", mime_str[s * 2], h);
        }
      }

      if (found)
      {
        printf("\n// Hash(x) = (x[0] & %d + x[1] & %d + len) mod %d\n", i, j, n);
        printf("static const char *mime_str[] =\n"
               "{\n");
        for (int s = 0; s < n; ++s)
        {
          printf("  \"%s\", \"%s\",\n", mime_str[(ht[s] - 1) * 2], mime_str[(ht[s] - 1) * 2 + 1]);
        }
        printf("};\n"
               "\n"
               "static const int n_mime_str = %d;\n\n", n);
        printf("static int hash_mime(const char *str)\n"
               "{\n"
               "  int len = strlen(str);\n"
               "  if (len) return ((str[0] & %d) + (str[1] & %d) + len) %% %d;\n"
               "  else return 0;\n"
               "}\n"
               "", i, j, n);
        exit(0);
      }
    }

    if (i % 64 == 0) printf("progress: %f (max: %d)\n", (float)i / (float)iterations * 100.0f, maxs);
  }

  return 0;
}

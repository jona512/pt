#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_len(char* input) {
  const char* current = input;
  for (;; ++current) {
    if (*current == '\0') {
      return current - input;
    }
  }
}

struct token {
  char* string;
  int length;
};

struct token_list_wrap {
  struct token* token_ptr;
  int length;
};

// return 1 if input char is space  or nulterminator
// || input == '\n' // newline is needed
int is_whitespace(char input) {
  if (input == ' ' || input == '\0') {
    return 1;
  } else {
    return 0;
  }
}

// char otherchars[1] = {'_'};
// //, 'ä', 'Ä', 'ö', 'Ö', 'ü', 'Ü', 'ß'}; // probably should not be used

// int isotherchar(char input) {
//   for (int i = 0; i < 1; i++) {
//     if (input == otherchars[i]) {
//       return 1;
//     }
//   }
//   return 0;
// }

// tokenizer (lexer?)
struct token_list_wrap* scan(char* input) {
  int length = get_len(input) + 1;
  int token_counter = -1;
  struct token* token_list = malloc(sizeof(struct token) * length);

  int cur_len = 0;
  char* cur_beg = input;

  for (int i = 0; i < length; i++) {
    cur_len++;

    if (!(isalpha(input[i]) || isdigit(input[i]) || input[i] == '_')) {
      // register token
      token_counter++;
      token_list[token_counter].string = cur_beg;
      token_list[token_counter].length = cur_len - 1;

      cur_len = 0;

      // register token i
      token_counter++;
      token_list[token_counter].string = input + i;
      token_list[token_counter].length = 1;

      cur_beg = input + i + 1;
    }
  }

  // remove whitespaces
  int tcr = 0;
  for (int i = 0; i < token_counter; i++) {
    if (token_list[i].length < 1) {
      continue;
    } else if (is_whitespace(token_list[i].string[0])) {
      continue;
    } else {
      token_list[tcr].string = token_list[i].string;
      token_list[tcr].length = token_list[i].length;
      tcr++;
    }
  }

  token_list = realloc(token_list, sizeof(struct token) * tcr);
  struct token_list_wrap* ret = malloc(sizeof(struct token_list_wrap));
  ret->token_ptr = token_list;
  ret->length = tcr;

  return ret;
}

char* types[2] = {"int", "float"};

int is_type(char* val) {
  for (int i = 0; i < 2; i++) {
    if (val == types[i]) {
      return 1;
    }
  }
  // return 0;
}

// TODO
void parsing_begin(struct token* tokens, int lenght) {
  // for (int i = 0; i < lenght; i++) {
  if (is_type(tokens->string)) {
    // call function for var or func
    printf("lol\n");
  }
  // }
}

// #define LR 100000 // loops
// found 35mio tokens in 1.9sec out of 5mio lines of c code (LR 25000)

int main() {
  FILE* infile;
  char* buffer;
  long numbytes;
  infile = fopen("pt1.saf", "r");
  fseek(infile, 0L, SEEK_END);
  numbytes = ftell(infile);
  fseek(infile, 0L, SEEK_SET);
  buffer = (char*)calloc(numbytes, sizeof(char));
  fread(buffer, sizeof(char), numbytes, infile);
  fclose(infile);

  struct token_list_wrap* res;
  // for (int i = 0; i < LR; i++) {
  res = scan(buffer);
  // }

  printf("total: %i tokens\n", res->length);
  // char* print_str = malloc(sizeof(char) * 50);
  // for (int i = 0; i < res->length; i++) {
  //   strncpy(print_str, (res->token_ptr + i)->string, (res->token_ptr + i)->length);
  //   print_str[(res->token_ptr + i)->length] = '\0';
  //   // printf("len: %i\n", (res->token_ptr + i)->length);
  //   printf("|%s|\n", print_str);
  // }
  // // printf("\n");

  parsing_begin(res->token_ptr, res->length);

  return 0;
}

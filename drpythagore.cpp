#include <iostream>
#include <readline/history.h>
#include <readline/readline.h>
#include "lexer.h"
#include "pool.h"

using namespace std;

/* The string containing the entered line */
static char *line_read = nullptr;

char *rl_gets()
{
    if (line_read) {
        free(line_read);
        line_read = NULL;
    }

    /* Get a line from the user */
    line_read = readline(">> ");

    /* If the line has any text in it, save it on the history */
    if (line_read && *line_read)
        add_history(line_read);

    return line_read;
}

int main()
{
    DPPlane plan;
    DPLexer lexer(&plan);

    do {
        char *ret = rl_gets();
        if (ret == NULL || strcmp(ret, "quit") == 0)
            break;
        if (*ret) {
            lexer.parse(ret);
            cout << "\t" << lexer.getResult() << endl;
        }
    }
    while (true);

    cout << endl;
    return 0;
}

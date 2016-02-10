#include <iostream>
#include "mathtree.h"
#include "asciitree.h"
#include "scanner.h"
using namespace std;

extern int yyparse();

// this is a global variable used by the parser
Tree* mathtree;

int main()
{
    // this is the user-input loop; there is no need to change it
    while(true)
    {
        cout << endl << "Enter expression: ";

        // this function gets the input and does the parsing
        yypush_buffer_state(yy_create_buffer( yyin, YY_BUF_SIZE ));
        yyparse();
        yypop_buffer_state();

        // the yyparse() function sets the global variable mathtree
        // to a new tree; if that tree is NULL (no tree), just quit
        if(mathtree != NULL)
        {
            cout << "Original tree:" << endl;
            // print the tree
            print_ascii_tree(mathtree);
            struct Tree *simplified = mathtree->simplify();
            cout << "Simplified tree:" << endl;
            print_ascii_tree(simplified);
            cout << "Printed in order:" << endl;
            simplified->print_inorder();
            cout << endl << endl << endl;
            struct Tree *derived = mathtree->derive();
            cout << "Derivative tree:" << endl;
            print_ascii_tree(derived);
            cout << "Printed in order:" << endl << endl;
            derived->print_inorder();
            cout << endl << endl;
            struct Tree *dsimplified = derived->simplify();
            cout << "Simplified derivative tree:" << endl;
            print_ascii_tree(dsimplified);
            cout << "Printed in order:" << endl << endl;
            dsimplified->print_inorder();
            cout << endl;

            delete_tree(simplified);
            delete_tree(derived);
            delete_tree(dsimplified);
            delete_tree(mathtree);

            // reset the tree back to NULL before looping
            mathtree = NULL;
        }
        break;
    }

    yylex_destroy();

    return 0;
}

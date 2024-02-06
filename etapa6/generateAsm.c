#include "generateAsm.h"

void generateAsm(tac_node* first) {
    tac_node* tac = first;

    FILE *fout;
    fout = fopen("out.s", "w");

    // init
    fprintf(fout,
            "\n## FIXED INIT\n"
            ".print_int:\n"
            "\t.asciz \"%%d\\n\" \n"
            ".print_str:\n"
            "\t.asciz \"%%s\\n\" \n"
    );

    //hash table

    //each tac
    while(tac) {
        switch(tac->type) {
            case TAC_BEGIN_FUNCTION:
                fprintf(fout, 
                        "## TAC_BEGINFUN\n"
                        "\t.globl	%s\n"
                        "%s:\n"
                        "\tpushq	%%rbp\n"
                        "\tmovq	%%rsp, %%rbp\n",
                        tac->res->value?tac->res->value:"",
                        tac->res->value?tac->res->value:""
                );
                break;
            case TAC_END_FUNCTION:
                fprintf(fout,
                        "## TAC_ENDFUN\n"
                        "\tpopq	%%rbp\n"
                        "\tretq\n"
                );
                break;
        }
        tac = tac->next;
    }

    fclose(fout);


}
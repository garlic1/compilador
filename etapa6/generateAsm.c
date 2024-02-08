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
                        "\n## TAC_ENDFUN\n"
                        "\tpopq	%%rbp\n"
                        "\tretq\n"
                );
                break;
            case TAC_SUM:
                fprintf(fout,
                            "\n## TAC_ADD\n"
                            "\tmovl _%s(%%rip), %%eax\n"
                            "\tmovl _%s(%%rip), %%edx\n"
                            "\taddl %%eax, %%edx\n"
                            "\tmovl %%edx, _%s(%%rip)\n", 
                            tac->op1->value, 
                            tac->op2->value, 
                            tac->res->value
                );
                break;

            case TAC_SUB:
                fprintf(fout,
                            "\n## TAC_SUB\n"
                            "\tmovl _%s(%%rip), %%eax\n"
                            "\tmovl _%s(%%rip), %%edx\n"
                            "\tsubl %%eax, %%edx\n"
                            "\tmovl %%edx, _%s(%%rip)\n", 
                            tac->op1->value, 
                            tac->op2->value, 
                            tac->res->value
                );
                break;

            case TAC_MUL:
                fprintf(fout,
                            "\n## TAC_MUL\n"
                            "\tmovl _%s(%%rip), %%eax\n"
                            "\tmovl _%s(%%rip), %%edx\n"
                            "\timull %%eax, %%edx\n"
                            "\tmovl %%edx, _%s(%%rip)\n", 
                            tac->op1->value, 
                            tac->op2->value, 
                            tac->res->value
                );
                break;

            case TAC_DIV:
                fprintf(fout,
                            "\n## TAC_DIV\n"
                            "\tmovl _%s(%%rip), %%eax\n"
                            "\tmovl _%s(%%rip), %%ecx\n"
                            "\tcltd\n"
                            "\tidivl %%ecx\n"
                            "\tmovl %%eax, _%s(%%rip)\n",
                            tac->op1->value, 
                            tac->op2->value, 
                            tac->res->value
                );
                break;
            
            case TAC_ATTR:
                fprintf(fout,
                            "\n## TAC_ATTR\n"
                            "\tmovl _%s(%%rip), %%eax\n"
                            "\tmovl %%eax, _%s(%%rip)\n", 
                            tac->op1->value, 
                            tac->res->value
                );
                break;
            
            case TAC_PRINT_VALUE:
                fprintf(fout,
                            "\n## TAC_PRINT\n"
                            "\tmovl	_%s(%%rip), %%esi\n"
                            "\tleaq	.print_int(%%rip), %%rdi\n"
                            "\tmovl	$0, %%eax\n"
                            "\tcall	printf@PLT\n",
                            tac->res?tac->res->value:""
                );
                break;
            case TAC_INPUT:
                fprintf(fout, 
                            "\n## TAC_INPUT\n"
                            "\tleaq	.print_int(%%rip), %%rdi\n"
                            "\tleaq	_%s(%%rip), %%rsi\n"
                            "\tmovb	$0, %%al\n"
                            "\tcallq	__isoc99_scanf@PLT\n",
                            tac->res?tac->res->value:""
                );
                break;
            // case TAC_LT:
            //     fprintf(stderr, "TAC_LT");
            //     break;

            // case TAC_GT:
            //     fprintf(stderr, "TAC_GT");
            //     break;

            // case TAC_LE:
            //     fprintf(stderr, "TAC_LE");
            //     break;

            // case TAC_GE:
            //     fprintf(stderr, "TAC_GE");
            //     break;

            // case TAC_EQ:
            //     fprintf(stderr, "TAC_EQ");
            //     break;

            // case TAC_DIF:
            //     fprintf(stderr, "TAC_DIF");
            //     break;

            // case TAC_AND:
            //     fprintf(stderr, "TAC_AND");
            //     break;

            // case TAC_OR:
            //     fprintf(stderr, "TAC_OR");
            //     break;

            // case TAC_NOT:
            //     fprintf(stderr, "TAC_NOT");
            //     break;
        }
        tac = tac->next;
    }

    fclose(fout);


}
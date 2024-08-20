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
    printAsm(fout);
    //each tac
    while(tac) {
        switch(tac->type) {
            case TAC_BEGINFUN:
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
            case TAC_ENDFUN:
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
            
            case TAC_VARIABLE_ATTRIBUTION:
                fprintf(fout,
                            "\n## TAC_ATTR\n"
                            "\tmovl _%s(%%rip), %%eax\n"
                            "\tmovl %%eax, _%s(%%rip)\n", 
                            tac->op1->value, 
                            tac->res->value
                );
                break;
            
            case TAC_PRINT_EXPRESSION:
                fprintf(fout,
                            "\n## TAC_PRINT\n"
                            "\tmovl	_%s(%%rip), %%esi\n"
                            "\tleaq	.print_int(%%rip), %%rdi\n"
                            "\tmovb	$0, %%al\n"
                            "\tcallq	printf@PLT\n",
                            tac->res?tac->res->value:""
                );
                break;
            case TAC_READ:
                fprintf(fout, 
                            "\n## TAC_INPUT\n"
                            "\tleaq	.print_int(%%rip), %%rdi\n"
                            "\tleaq	_%s(%%rip), %%rsi\n"
                            "\tmovb	$0, %%al\n"
                            "\tcallq	__isoc99_scanf@PLT\n",
                            tac->res?tac->res->value:""
                );
                break;

            case TAC_LT:
                break;

            case TAC_GT:
                break;

            case TAC_LE:
                break;

            case TAC_GE:
                break;

            case TAC_EQ:
                break;

            case TAC_DIF:
                break;

            case TAC_AND:
                break;

            case TAC_OR:
                break;

            case TAC_NOT:
                break;

            case TAC_IF:
                break;
            case TAC_IF_ELSE:
                break;
            case TAC_WHILE:
                break;
            
            case TAC_PRINT_STRING:
                break;

            case TAC_RETURN:
                break;
        }
        tac = tac->next;
    }

    fclose(fout);


}
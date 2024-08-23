#include "generateAsm.h"

void dataSection(FILE *fout, AST* node){
    if(!node) return;
	if(node->type == AST_VARIABLE_DECLARATION) {   
    	fprintf(fout,"_%s:\t .long	%s\n",
                     node->symbol->value,  
                     node->children[1]->symbol->value
                    );
	}
    for(int i = 0; i < MAX_CHILDREN; i++){
		dataSection(fout, node->children[i]);
	}
}

void generateAsm(tac_node* first, AST* ast) {
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
                            "\n## TAC_SUM\n"
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
                            "\tsubl %%edx, %%eax \n"
                            "\tmovl %%eax, _%s(%%rip)\n", 
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
                            "\n## TAC_VARIABLE_ATTRIBUTION\n"
                            "\tmovl _%s(%%rip), %%eax\n"
                            "\tmovl %%eax, _%s(%%rip)\n", 
                            tac->op1->value, 
                            tac->res->value
                );
                break;
            
            case TAC_PRINT_EXPRESSION:
                fprintf(fout,
                            "\n## TAC_PRINT_EXPRESSION\n"
                            "\tmovl	_%s(%%rip), %%esi\n"
                            "\tleaq	.print_int(%%rip), %%rdi\n"
                            "\tmovb	$0, %%al\n"
                            "\tcallq	printf@PLT\n",
                            tac->res?tac->res->value:""
                );
                break;
                	
            case TAC_PRINT_STRING:                
                fprintf(fout,
                            "\n## TAC_PRINT_STRING\n"
                            "\tleaq	%s(%%rip), %%rdi\n"
                            "\tmovb	$0, %%al\n"
                            "\tcallq	printf@PLT\n",
                            tac->res?tac->res->value:""
                );
                break;
                
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
            

            case TAC_RETURN:
                break;
        }
        tac = tac->next;
    }

    //hash table
    printAsm(fout);
    dataSection(fout, ast);

    fclose(fout);
}
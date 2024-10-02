#include "ast.h"

extern FILE *out;

AST* ast_create(int type, hash_node* symbol, AST* child_0, AST* child_1, AST* child_2, AST* child_3) {
    AST* node = (AST*) calloc(1, sizeof(AST));
    node->type = type;
    node->symbol = symbol;
    node->children[0] = child_0;
    node->children[1] = child_1;
    node->children[2] = child_2;
    node->children[3] = child_3;
    return node;
}

void ast_print(AST* node, int level) {
    if (node == 0) {
        return;
    }

    for (int i = 0; i < level; i++) {
        fprintf(stderr, "\t");
    }
    fprintf(stderr, "ast(");
    switch (node -> type) {
        case AST_GLOBAL_DECLARATION_LIST:
            fprintf(stderr, "AST_GLOBAL_DECLARATION_LIST");
            break;
        case AST_GLOBAL_DECLARATION:
            fprintf(stderr, "AST_GLOBAL_DECLARATION");
            break;
        case AST_VARIABLE_DECLARATION:
            fprintf(stderr, "AST_VARIABLE_DECLARATION");
            break;
        case AST_FUNCTION_DECLARATION:
            fprintf(stderr, "AST_FUNCTION_DECLARATION");
            break;
        case AST_ARRAY_DECLARATION:
            fprintf(stderr, "AST_ARRAY_DECLARATION");
            break;
        case AST_FUNCTION_PARAMETERS:
            fprintf(stderr, "AST_FUNCTION_PARAMETERS");
            break;
        case AST_ARRAY_INITIAL_VALUES:
            fprintf(stderr, "AST_ARRAY_INITIAL_VALUES");
            break;
        case AST_COMMAND:
            fprintf(stderr, "AST_COMMAND");
            break;
        case AST_FLOW_CONTROL:
            fprintf(stderr, "AST_FLOW_CONTROL");
            break;
        case AST_EXPRESSION:
            fprintf(stderr, "AST_EXPRESSION");
            break;
        case AST_BLOCK:
            fprintf(stderr, "AST_BLOCK");
            break;
        case AST_PRINT_EXPRESSION:
            fprintf(stderr, "AST_PRINT_EXPRESSION");
            break;
        case AST_PRINT_TYPE_STRING:
            fprintf(stderr, "AST_PRINT_TYPE_STRING");
            break;
        case AST_PRINT_STRING:
            fprintf(stderr, "AST_PRINT_STRING");
            break;
        case AST_READ:
            fprintf(stderr, "AST_READ");
            break;
        case AST_RETURN:
            fprintf(stderr, "AST_RETURN");
            break;
        case AST_VARIABLE_ATTRIBUTION:
            fprintf(stderr, "AST_VARIABLE_ATTRIBUTION");
            break;
        case AST_ARRAY_ATTRIBUTION:
            fprintf(stderr, "AST_ARRAY_ATTRIBUTION");
            break;
        case AST_COMMANDS_LIST:
            fprintf(stderr, "AST_COMMANDS_LIST");
            break;
        case AST_ARGUMENTS_LIST:
            fprintf(stderr, "AST_ARGUMENTS_LIST");
            break;
        case AST_TYPE:
            fprintf(stderr, "AST_TYPE");
            break;
        case AST_LITERAL:
            fprintf(stderr, "AST_LITERAL");
            break;
        case AST_SUM:
            fprintf(stderr, "AST_SUM");
            break;
        case AST_SUB:
            fprintf(stderr, "AST_SUB");
            break;
        case AST_MUL:
            fprintf(stderr, "AST_MUL");
            break;
        case AST_DIV:
            fprintf(stderr, "AST_DIV");
            break;
        case AST_LT:
            fprintf(stderr, "AST_LT");
            break;
        case AST_GT:
            fprintf(stderr, "AST_GT");
            break;
        case AST_LE:
            fprintf(stderr, "AST_LE");
            break;
        case AST_GE:
            fprintf(stderr, "AST_GE");
            break;
        case AST_EQ:
            fprintf(stderr, "AST_EQ");
            break;
        case AST_DIF:
            fprintf(stderr, "AST_DIF");
            break;
        case AST_AND:
            fprintf(stderr, "AST_AND");
            break;
        case AST_OR:
            fprintf(stderr, "AST_OR");
            break;
        case AST_NOT:
            fprintf(stderr, "AST_NOT");
            break;
        case AST_FUNCTION_CALL:
            fprintf(stderr, "AST_FUNCTION_CALL");
            break;
        case AST_INT:
            fprintf(stderr, "AST_INT");
            break;
        case AST_BOOL:
            fprintf(stderr, "AST_BOOL");
            break;
        case AST_CHAR:
            fprintf(stderr, "AST_CHAR");
            break;
        case AST_FLOAT:
            fprintf(stderr, "AST_FLOAT");
            break;
        case AST_IF:
            fprintf(stderr, "AST_IF");
            break;
        case AST_IF_ELSE:
            fprintf(stderr, "AST_IF_ELSE");
            break;
        case AST_WHILE:
            fprintf(stderr, "AST_WHILE");
            break;
        case AST_SYMBOL:
            fprintf(stderr, "AST_SYMBOL");
            break;
        case AST_ARRAY_ACCESS:
            fprintf(stderr, "AST_ARRAY_ACCESS");
            break;
        default:
            fprintf(stderr, "AST_UNKNOWN");
            break;
    }

    if (node->symbol!=0)
        fprintf(stderr, ", %s", node->symbol->value);
    else 
        fprintf(stderr, ", 0");
    
    fprintf(stderr, ")\n");
    

    for(int i=0; i<MAX_CHILDREN; i++)
        ast_print(node->children[i], level + 1);
}

void ast_decomp (AST *node) {
    if (node == 0) {
        return;
    }

    switch (node -> type) {
        case AST_GLOBAL_DECLARATION_LIST:
           ast_decomp(node->children[0]);
            if (node -> children[1]) {
                ast_decomp(node->children[1]);
            }
            break;
        case AST_VARIABLE_DECLARATION:
            ast_decomp(node->children[0]);
            fprintf(out, "%s: ", node -> symbol -> value);
            ast_decomp(node->children[1]);
            fprintf(out, ";\n");
            break;
        case AST_FUNCTION_DECLARATION:
            ast_decomp(node->children[0]);
            fprintf(out, "%s(", node -> symbol -> value);
            if (node -> children[1]) {
                ast_decomp(node->children[1]);
            }
            fprintf(out, ") ");
            ast_decomp(node->children[2]);
            break;
        case AST_FUNCTION_PARAMETERS: 
            if (node -> children[0]) {
                ast_decomp(node->children[0]);
            }
            fprintf(out, "%s", node -> symbol -> value);
            if (node -> children[1]) {
                fprintf(out, ", ");
                ast_decomp(node->children[1]);
            }
            break;
        case AST_ARRAY_DECLARATION:
            ast_decomp(node->children[0]);
            fprintf(out, "%s[", node -> symbol -> value);
            ast_decomp(node->children[1]);
            fprintf(out, "]");
            if (node -> children[2]) {
                fprintf(out, ": ");
                ast_decomp(node->children[2]);
            }
            fprintf(out, ";\n");
            break;
        case AST_ARRAY_INITIAL_VALUES:
            ast_decomp(node->children[0]);
            if (node -> children[1]) {
                fprintf(out, " ");
                ast_decomp(node->children[1]);
            }
            break;
        case AST_BLOCK:
            fprintf(out, "{\n");
            ast_decomp(node->children[0]);
            fprintf(out,"}\n");
            break;
        case AST_PRINT_EXPRESSION:
            fprintf(out, "print ");
            ast_decomp(node->children[0]);
            ast_decomp(node->children[1]);
            fprintf(out, ";\n");
            break;
        case AST_PRINT_TYPE_STRING:
            fprintf(out, "print ");
            ast_decomp(node->children[0]);
            ast_decomp(node->children[1]);
            fprintf(out, ";\n");
            break;
        case AST_PRINT_STRING:
            fprintf(out, "print ");
            ast_decomp(node->children[0]);
            fprintf(out, ";\n");
            break;
        case AST_READ:
            fprintf(out, "read ");
            ast_decomp(node->children[0]);
            fprintf(out, "%s", node -> symbol -> value);
            fprintf(out, ";\n");
            break;
        case AST_RETURN:
            fprintf(out, "return ");
            ast_decomp(node->children[0]);
            fprintf(out, ";\n");
            break;
        case AST_VARIABLE_ATTRIBUTION:
            fprintf(out, "%s = ", node -> symbol -> value);
            ast_decomp(node->children[0]);
            fprintf(out, ";\n");
            break;
        case AST_ARRAY_ATTRIBUTION:
            fprintf(out, "%s[", node -> symbol -> value);
            ast_decomp(node->children[0]);
            fprintf(out, "] = ");
            ast_decomp(node->children[1]);
            fprintf(out, ";\n");
            break;
        case AST_COMMANDS_LIST:
            if (node -> children[0]) {
                ast_decomp(node->children[0]);
                ast_decomp(node->children[1]);
            }
            break;
        case AST_SUM:            
            ast_decomp(node->children[0]);
			fprintf(out, "+");
			ast_decomp(node->children[1]);
            break;
        case AST_SUB:
            ast_decomp(node->children[0]);
			fprintf(out, "-");
			ast_decomp(node->children[1]);
            break;
        case AST_MUL:
            ast_decomp(node->children[0]);
			fprintf(out, "*");
			ast_decomp(node->children[1]);
            break;
        case AST_DIV:
            ast_decomp(node->children[0]);
			fprintf(out, "/");
			ast_decomp(node->children[1]);
            break;
        case AST_LT:
            ast_decomp(node->children[0]);
			fprintf(out, "<");
			ast_decomp(node->children[1]);
            break;
        case AST_GT:
            ast_decomp(node->children[0]);
			fprintf(out, ">");
			ast_decomp(node->children[1]);
            break;
        case AST_LE:
            ast_decomp(node->children[0]);
			fprintf(out, "<=");
			ast_decomp(node->children[1]);
            break;
        case AST_GE:
            ast_decomp(node->children[0]);
			fprintf(out, ">=");
			ast_decomp(node->children[1]);
            break;
        case AST_EQ:
            ast_decomp(node->children[0]);
			fprintf(out, "+");
			ast_decomp(node->children[1]);
            break;
        case AST_DIF:
            ast_decomp(node->children[0]);
			fprintf(out, "!=");
			ast_decomp(node->children[1]);
            break;
        case AST_AND:
            ast_decomp(node->children[0]);
			fprintf(out, "&");
			ast_decomp(node->children[1]);
            break;
        case AST_OR:
            ast_decomp(node->children[0]);
			fprintf(out, "|");
			ast_decomp(node->children[1]);
            break;
        case AST_NOT:
			fprintf(out, "~");
            ast_decomp(node->children[0]);
            break;
        case AST_FUNCTION_CALL:
            fprintf(out, "%s(", node -> symbol -> value);
            ast_decomp(node->children[0]);
			fprintf(out, ")");
            break;
        case AST_ARGUMENTS_LIST:
            if (node -> children[0]) {
                ast_decomp(node->children[0]);
            }
            if (node -> children[1]) {
                fprintf(out, ", ");
                ast_decomp(node->children[1]);
            }
            break;
        case AST_INT:
            fprintf(out, "int ");
            break;
        case AST_BOOL:
            fprintf(out, "bool ");
            break;
        case AST_CHAR:
            fprintf(out, "char ");
            break;
        case AST_FLOAT:
            fprintf(out, "float ");
            break;
        case AST_SYMBOL:
			fprintf(out,"%s",node -> symbol -> value);
			break;
        case AST_ARRAY_ACCESS:
            fprintf(out, "%s[", node -> symbol -> value);
            ast_decomp(node->children[0]);
            fprintf(out, "]");
            break;
        case AST_IF:
            fprintf(out, "if(");
            ast_decomp(node->children[0]);
            fprintf(out, ")");
            ast_decomp(node->children[1]);
            fprintf(out, ";\n");
            break;
        case AST_IF_ELSE:
            fprintf(out, "if(");
            ast_decomp(node->children[0]);
            fprintf(out, ")");
            ast_decomp(node->children[1]);
            fprintf(out, " else ");
            ast_decomp(node->children[2]);
            break;
        case AST_WHILE:
            fprintf(out, "while(");
            ast_decomp(node->children[0]);
            fprintf(out, ")");
            ast_decomp(node->children[1]);
            break;
        default:
            fprintf(stderr, "AST_UNKNOWN");
            break;
    }
    return;
}
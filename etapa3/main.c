extern FILE *yyin;

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: ./etapa2 test.txt\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        printf("Error while opening file\n");
        exit(2);
    }
    
    initMe();
    yyparse();
    print_table();

    exit(0);
}
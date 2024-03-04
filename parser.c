#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node *NODE;
typedef struct head_node *HEAD_NODE;
#define GRAMMAR_RULES 52

typedef enum
{
    program = 0,
    mainFunction = 1,
    otherFunctions = 2,
    function = 3,
    input_par = 4,
    output_par = 5,
    parameter_list = 6,
    dataType = 7,
    primitiveDatatype = 8,
    constructedDatatype = 9,
    remaining_list = 10,
    stmts = 11,
    typeDefinitions = 12,
    actualOrRedefined = 13,
    typeDefinition = 14,
    fieldDefinitions = 15,
    fieldDefinition = 16,
    moreFields = 17,
    declarations = 18,
    declaration = 19,
    global_or_not = 20,
    otherStmts = 21,
    stmt = 22,
    assignmentStmt = 23,
    singleOrRecId = 24,
    option_single_constructed = 25,
    oneExpansion = 26,
    moreExpansions = 27,
    funCallStmt = 28,
    outputParameters = 29,
    inputParameters = 30,
    iterativeStmt = 31,
    conditionalStmt = 32,
    elsePart = 33,
    ioStmt = 34,
    arithmeticExpression = 35,
    expPrime = 36,
    term = 37,
    termPrime = 38,
    factor = 39,
    highPrecedenceOperators = 40,
    lowPrecedenceOperators = 41,
    booleanExpression = 42,
    var = 43,
    logicalOp = 44,
    relationalOp = 45,
    returnStmt = 46,
    optionalReturn = 47,
    idList = 48,
    more_ids = 49,
    definetypestmt = 50,
    A = 51,
    TK_ASSIGNOP = 52,
    TK_COMMENT = 53,
    TK_FIELDID = 54,
    TK_ID = 55,
    TK_NUM = 56,
    TK_RNUM = 57,
    TK_FUNID = 58,
    TK_RUID = 59,
    TK_WITH = 60,
    TK_PARAMETERS = 61,
    TK_END = 62,
    TK_WHILE = 63,
    TK_UNION = 64,
    TK_ENDUNION = 65,
    TK_DEFINETYPE = 66,
    TK_AS = 67,
    TK_TYPE = 68,
    TK_MAIN = 69,
    TK_GLOBAL = 70,
    TK_PARAMETER = 71,
    TK_LIST = 72,
    TK_SQL = 73,
    TK_SQR = 74,
    TK_INPUT = 75,
    TK_OUTPUT = 76,
    TK_INT = 77,
    TK_REAL = 78,
    TK_COMMA = 79,
    TK_SEM = 80,
    TK_COLON = 81,
    TK_DOT = 82,
    TK_ENDWHILE = 83,
    TK_OP = 84,
    TK_CL = 85,
    TK_IF = 86,
    TK_THEN = 87,
    TK_ENDIF = 88,
    TK_READ = 89,
    TK_WRITE = 90,
    TK_RETURN = 91,
    TK_PLUS = 92,
    TK_MINUS = 93,
    TK_MUL = 94,
    TK_DIV = 95,
    TK_CALL = 96,
    TK_RECORD = 97,
    TK_ENDRECORD = 98,
    TK_ELSE = 99,
    TK_AND = 100,
    TK_OR = 101,
    TK_NOT = 102,
    TK_LT = 103,
    TK_LE = 104,
    TK_EQ = 105,
    TK_GT = 106,
    TK_GE = 107,
    TK_NE = 108,
    StackSymbol = 109
} TokenType;

TokenType getTokenTypeFromString(char *string)
{
    if (strcmp(string, "program") == 0)
        return program;
    else if (strcmp(string, "mainFunction") == 0)
        return mainFunction;
    else if (strcmp(string, "otherFunctions") == 0)
        return otherFunctions;
    else if (strcmp(string, "function") == 0)
        return function;
    else if (strcmp(string, "input_par") == 0)
        return input_par;
    else if (strcmp(string, "output_par") == 0)
        return output_par;
    else if (strcmp(string, "parameter_list") == 0)
        return parameter_list;
    else if (strcmp(string, "dataType") == 0)
        return dataType;
    else if (strcmp(string, "primitiveDatatype") == 0)
        return primitiveDatatype;
    else if (strcmp(string, "constructedDatatype") == 0)
        return constructedDatatype;
    else if (strcmp(string, "remaining_list") == 0)
        return remaining_list;
    else if (strcmp(string, "stmts") == 0)
        return stmts;
    else if (strcmp(string, "typeDefinitions") == 0)
        return typeDefinitions;
    else if (strcmp(string, "actualOrRedefined") == 0)
        return actualOrRedefined;
    else if (strcmp(string, "typeDefinition") == 0)
        return typeDefinition;
    else if (strcmp(string, "fieldDefinitions") == 0)
        return fieldDefinitions;
    else if (strcmp(string, "fieldDefinition") == 0)
        return fieldDefinition;
    else if (strcmp(string, "moreFields") == 0)
        return moreFields;
    else if (strcmp(string, "declarations") == 0)
        return declarations;
    else if (strcmp(string, "declaration") == 0)
        return declaration;
    else if (strcmp(string, "global_or_not") == 0)
        return global_or_not;
    else if (strcmp(string, "otherStmts") == 0)
        return otherStmts;
    else if (strcmp(string, "stmt") == 0)
        return stmt;
    else if (strcmp(string, "oneExpansion") == 0)
        return oneExpansion;
    else if (strcmp(string, "moreExpansions") == 0)
        return moreExpansions;
    else if (strcmp(string, "assignmentStmt") == 0)
        return assignmentStmt;
    else if (strcmp(string, "singleOrRecId") == 0)
        return singleOrRecId;
    else if (strcmp(string, "option_single_constructed") == 0)
        return option_single_constructed;
    else if (strcmp(string, "funCallStmt") == 0)
        return funCallStmt;
    else if (strcmp(string, "outputParameters") == 0)
        return outputParameters;
    else if (strcmp(string, "inputParameters") == 0)
        return inputParameters;
    else if (strcmp(string, "iterativeStmt") == 0)
        return iterativeStmt;
    else if (strcmp(string, "conditionalStmt") == 0)
        return conditionalStmt;
    else if (strcmp(string, "elsePart") == 0)
        return elsePart;
    else if (strcmp(string, "ioStmt") == 0)
        return ioStmt;
    else if (strcmp(string, "arithmeticExpression") == 0)
        return arithmeticExpression;
    else if (strcmp(string, "expPrime") == 0)
        return expPrime;
    else if (strcmp(string, "term") == 0)
        return term;
    else if (strcmp(string, "termPrime") == 0)
        return termPrime;
    else if (strcmp(string, "factor") == 0)
        return factor;
    else if (strcmp(string, "highPrecedenceOperators") == 0)
        return highPrecedenceOperators;
    else if (strcmp(string, "lowPrecedenceOperators") == 0)
        return lowPrecedenceOperators;
    else if (strcmp(string, "booleanExpression") == 0)
        return booleanExpression;
    else if (strcmp(string, "var") == 0)
        return var;
    else if (strcmp(string, "logicalOp") == 0)
        return logicalOp;
    else if (strcmp(string, "relationalOp") == 0)
        return relationalOp;
    else if (strcmp(string, "returnStmt") == 0)
        return returnStmt;
    else if (strcmp(string, "optionalReturn") == 0)
        return optionalReturn;
    else if (strcmp(string, "idList") == 0)
        return idList;
    else if (strcmp(string, "more_ids") == 0)
        return more_ids;
    else if (strcmp(string, "definetypestmt") == 0)
        return definetypestmt;
    else if (strcmp(string, "A") == 0)
        return A;
    else if (strcmp(string, "TK_ASSIGNOP") == 0)
        return TK_ASSIGNOP;
    else if (strcmp(string, "TK_COMMENT") == 0)
        return TK_COMMENT;
    else if (strcmp(string, "TK_FIELDID") == 0)
        return TK_FIELDID;
    else if (strcmp(string, "TK_ID") == 0)
        return TK_ID;
    else if (strcmp(string, "TK_NUM") == 0)
        return TK_NUM;
    else if (strcmp(string, "TK_RNUM") == 0)
        return TK_RNUM;
    else if (strcmp(string, "TK_FUNID") == 0)
        return TK_FUNID;
    else if (strcmp(string, "TK_RUID") == 0)
        return TK_RUID;
    else if (strcmp(string, "TK_WITH") == 0)
        return TK_WITH;
    else if (strcmp(string, "TK_PARAMETERS") == 0)
        return TK_PARAMETERS;
    else if (strcmp(string, "TK_END") == 0)
        return TK_END;
    else if (strcmp(string, "TK_WHILE") == 0)
        return TK_WHILE;
    else if (strcmp(string, "TK_UNION") == 0)
        return TK_UNION;
    else if (strcmp(string, "TK_ENDUNION") == 0)
        return TK_ENDUNION;
    else if (strcmp(string, "TK_DEFINETYPE") == 0)
        return TK_DEFINETYPE;
    else if (strcmp(string, "TK_AS") == 0)
        return TK_AS;
    else if (strcmp(string, "TK_TYPE") == 0)
        return TK_TYPE;
    else if (strcmp(string, "TK_MAIN") == 0)
        return TK_MAIN;
    else if (strcmp(string, "TK_GLOBAL") == 0)
        return TK_GLOBAL;
    else if (strcmp(string, "TK_PARAMETER") == 0)
        return TK_PARAMETER;
    else if (strcmp(string, "TK_LIST") == 0)
        return TK_LIST;
    else if (strcmp(string, "TK_SQL") == 0)
        return TK_SQL;
    else if (strcmp(string, "TK_SQR") == 0)
        return TK_SQR;
    else if (strcmp(string, "TK_INPUT") == 0)
        return TK_INPUT;
    else if (strcmp(string, "TK_OUTPUT") == 0)
        return TK_OUTPUT;
    else if (strcmp(string, "TK_INT") == 0)
        return TK_INT;
    else if (strcmp(string, "TK_REAL") == 0)
        return TK_REAL;
    else if (strcmp(string, "TK_COMMA") == 0)
        return TK_COMMA;
    else if (strcmp(string, "TK_SEM") == 0)
        return TK_SEM;
    else if (strcmp(string, "TK_COLON") == 0)
        return TK_COLON;
    else if (strcmp(string, "TK_DOT") == 0)
        return TK_DOT;
    else if (strcmp(string, "TK_ENDWHILE") == 0)
        return TK_ENDWHILE;
    else if (strcmp(string, "TK_OP") == 0)
        return TK_OP;
    else if (strcmp(string, "TK_CL") == 0)
        return TK_CL;
    else if (strcmp(string, "TK_IF") == 0)
        return TK_IF;
    else if (strcmp(string, "TK_THEN") == 0)
        return TK_THEN;
    else if (strcmp(string, "TK_ENDIF") == 0)
        return TK_ENDIF;
    else if (strcmp(string, "TK_READ") == 0)
        return TK_READ;
    else if (strcmp(string, "TK_WRITE") == 0)
        return TK_WRITE;
    else if (strcmp(string, "TK_RETURN") == 0)
        return TK_RETURN;
    else if (strcmp(string, "TK_PLUS") == 0)
        return TK_PLUS;
    else if (strcmp(string, "TK_MINUS") == 0)
        return TK_MINUS;
    else if (strcmp(string, "TK_MUL") == 0)
        return TK_MUL;
    else if (strcmp(string, "TK_DIV") == 0)
        return TK_DIV;
    else if (strcmp(string, "TK_CALL") == 0)
        return TK_CALL;
    else if (strcmp(string, "TK_RECORD") == 0)
        return TK_RECORD;
    else if (strcmp(string, "TK_ENDRECORD") == 0)
        return TK_ENDRECORD;
    else if (strcmp(string, "TK_ELSE") == 0)
        return TK_ELSE;
    else if (strcmp(string, "TK_AND") == 0)
        return TK_AND;
    else if (strcmp(string, "TK_OR") == 0)
        return TK_OR;
    else if (strcmp(string, "TK_NOT") == 0)
        return TK_NOT;
    else if (strcmp(string, "TK_LT") == 0)
        return TK_LT;
    else if (strcmp(string, "TK_LE") == 0)
        return TK_LE;
    else if (strcmp(string, "TK_EQ") == 0)
        return TK_EQ;
    else if (strcmp(string, "TK_GT") == 0)
        return TK_GT;
    else if (strcmp(string, "TK_GE") == 0)
        return TK_GE;
    else if (strcmp(string, "TK_NE") == 0)
        return TK_NE;
    else if(strcmp(string, "Dollar Symbol") == 0)
        return StackSymbol;
    else
        return -1;
}

const char *getStringFromToken(TokenType token)
{
    switch (token)
    {
    case program:
        return "program";
    case mainFunction:
        return "mainFunction";
    case otherFunctions:
        return "otherFunctions";
    case function:
        return "function";
    case input_par:
        return "input_par";
    case output_par:
        return "output_par";
    case parameter_list:
        return "parameter_list";
    case dataType:
        return "dataType";
    case primitiveDatatype:
        return "primitiveDatatype";
    case constructedDatatype:
        return "constructedDatatype";
    case remaining_list:
        return "remaining_list";
    case stmts:
        return "stmts";
    case typeDefinitions:
        return "typeDefinitions";
    case actualOrRedefined:
        return "actualOrRedefined";
    case typeDefinition:
        return "typeDefinition";
    case fieldDefinitions:
        return "fieldDefinitions";
    case fieldDefinition:
        return "fieldDefinition";
    case moreFields:
        return "moreFields";
    case oneExpansion:
        return "oneExpansion";
    case moreExpansions:
        return "moreExpansions";
    case declarations:
        return "declarations";
    case declaration:
        return "declaration";
    case global_or_not:
        return "global_or_not";
    case otherStmts:
        return "otherStmts";
    case stmt:
        return "stmt";
    case assignmentStmt:
        return "assignmentStmt";
    case singleOrRecId:
        return "singleOrRecId";
    case option_single_constructed:
        return "option_single_constructed";
    case funCallStmt:
        return "funCallStmt";
    case outputParameters:
        return "outputParameters";
    case inputParameters:
        return "inputParameters";
    case iterativeStmt:
        return "iterativeStmt";
    case conditionalStmt:
        return "conditionalStmt";
    case elsePart:
        return "elsePart";
    case ioStmt:
        return "ioStmt";
    case arithmeticExpression:
        return "arithmeticExpression";
    case expPrime:
        return "expPrime";
    case term:
        return "term";
    case termPrime:
        return "termPrime";
    case factor:
        return "factor";
    case highPrecedenceOperators:
        return "highPrecedenceOperators";
    case lowPrecedenceOperators:
        return "lowPrecedenceOperators";
    case booleanExpression:
        return "booleanExpression";
    case var:
        return "var";
    case logicalOp:
        return "logicalOp";
    case relationalOp:
        return "relationalOp";
    case returnStmt:
        return "returnStmt";
    case optionalReturn:
        return "optionalReturn";
    case idList:
        return "idList";
    case more_ids:
        return "more_ids";
    case definetypestmt:
        return "definetypestmt";
    case A:
        return "A";
    case TK_ASSIGNOP:
        return "TK_ASSIGNOP";
    case TK_COMMENT:
        return "TK_COMMENT";
    case TK_FIELDID:
        return "TK_FIELDID";
    case TK_ID:
        return "TK_ID";
    case TK_NUM:
        return "TK_NUM";
    case TK_RNUM:
        return "TK_RNUM";
    case TK_FUNID:
        return "TK_FUNID";
    case TK_RUID:
        return "TK_RUID";
    case TK_WITH:
        return "TK_WITH";
    case TK_PARAMETERS:
        return "TK_PARAMETERS";
    case TK_END:
        return "TK_END";
    case TK_WHILE:
        return "TK_WHILE";
    case TK_UNION:
        return "TK_UNION";
    case TK_ENDUNION:
        return "TK_ENDUNION";
    case TK_DEFINETYPE:
        return "TK_DEFINETYPE";
    case TK_AS:
        return "TK_AS";
    case TK_TYPE:
        return "TK_TYPE";
    case TK_MAIN:
        return "TK_MAIN";
    case TK_GLOBAL:
        return "TK_GLOBAL";
    case TK_PARAMETER:
        return "TK_PARAMETER";
    case TK_LIST:
        return "TK_LIST";
    case TK_SQL:
        return "TK_SQL";
    case TK_SQR:
        return "TK_SQR";
    case TK_INPUT:
        return "TK_INPUT";
    case TK_OUTPUT:
        return "TK_OUTPUT";
    case TK_INT:
        return "TK_INT";
    case TK_REAL:
        return "TK_REAL";
    case TK_COMMA:
        return "TK_COMMA";
    case TK_SEM:
        return "TK_SEM";
    case TK_COLON:
        return "TK_COLON";
    case TK_DOT:
        return "TK_DOT";
    case TK_ENDWHILE:
        return "TK_ENDWHILE";
    case TK_OP:
        return "TK_OP";
    case TK_CL:
        return "TK_CL";
    case TK_IF:
        return "TK_IF";
    case TK_THEN:
        return "TK_THEN";
    case TK_ENDIF:
        return "TK_ENDIF";
    case TK_READ:
        return "TK_READ";
    case TK_WRITE:
        return "TK_WRITE";
    case TK_RETURN:
        return "TK_RETURN";
    case TK_PLUS:
        return "TK_PLUS";
    case TK_MINUS:
        return "TK_MINUS";
    case TK_MUL:
        return "TK_MUL";
    case TK_DIV:
        return "TK_DIV";
    case TK_CALL:
        return "TK_CALL";
    case TK_RECORD:
        return "TK_RECORD";
    case TK_ENDRECORD:
        return "TK_ENDRECORD";
    case TK_ELSE:
        return "TK_ELSE";
    case TK_AND:
        return "TK_AND";
    case TK_OR:
        return "TK_OR";
    case TK_NOT:
        return "TK_NOT";
    case TK_LT:
        return "TK_LT";
    case TK_LE:
        return "TK_LE";
    case TK_EQ:
        return "TK_EQ";
    case TK_GT:
        return "TK_GT";
    case TK_GE:
        return "TK_GE";
    case TK_NE:
        return "TK_NE";
    case StackSymbol:
        return "$";
    default:
        return "Unrecognized Token";
    }
}
struct head_node
{
    TokenType token;
    NODE *next;
    int count;
    bool epsilon_trans;
};
struct node
{
    TokenType token;
    NODE next;
    bool isT;
};

HEAD_NODE grammar[GRAMMAR_RULES];
int grammar_filler = 0;
void GrammarReader(FILE *fp)
{
    for (int i = 0; i < GRAMMAR_RULES; i++)
    {
        HEAD_NODE nt = (HEAD_NODE)malloc(sizeof(struct head_node));
        nt->epsilon_trans = false;
        grammar[grammar_filler++] = nt;
        char temp[200];
        char tempo[100];
        fscanf(fp, "<%[^>]> = %[^\n]\n", tempo, temp);
        nt->token = getTokenTypeFromString(tempo);
        int j = 0;
        int cnt = 1;
        int sz = 1;
        while (temp[j] != '\0')
        {
            if (temp[j] == '|')
                cnt++;
            j++;
            sz = j;
        }
        nt->next = (NODE *)malloc(cnt * (sizeof(NODE)));
        NODE *curr_nt_arr = nt->next;
        int curr_cnt = 0;
        NODE curr = NULL;
        for (j = 0; j < sz; j++)
        {
            char *value;
            if (temp[j] == '<')
            {
                int k = ++j;
                while (temp[j] != '>')
                {
                    j++;
                }
                if (curr == NULL)
                {
                    *(curr_nt_arr + curr_cnt) = (NODE)malloc(sizeof(struct node));
                    curr = *(curr_nt_arr + curr_cnt);
                }
                else
                {
                    curr->next = (NODE)malloc(sizeof(struct node));
                    curr = curr->next;
                }
                value = (char *)malloc(sizeof(char) * (j - k));
                strncpy(value, temp + k, j - k);
                curr->token = getTokenTypeFromString(value);
                free(value);
                curr->isT = false;
                continue;
            }
            if ((temp[j] >= 'A') && (temp[j] <= 'Z'))
            {
                int k = j++;
                while (((temp[j] >= 'A') && (temp[j] <= 'Z')) || (temp[j] == '_'))
                {
                    j++;
                }
                if (curr == NULL)
                {
                    *(curr_nt_arr + curr_cnt) = (NODE)malloc(sizeof(struct node));
                    curr = *(curr_nt_arr + curr_cnt);
                }
                else
                {
                    curr->next = (NODE)malloc(sizeof(struct node));
                    curr = curr->next;
                }
                value = (char *)malloc(sizeof(char) * (j - k));
                strncpy(value, temp + k, j - k);
                curr->token = getTokenTypeFromString(value);
                free(value);
                j--;
                curr->isT = true;
                continue;
            }
            if (temp[j] == '?')
            {
                nt->epsilon_trans = true;
                continue;
            }
            if (temp[j] == '|')
            {
                curr_cnt++;
                curr = NULL;
            }
        }
        nt->count = cnt;
        if (nt->epsilon_trans == true)
            nt->count--;
    }
}

bool checkTerminal(TokenType token)
{
    if (token > (GRAMMAR_RULES - 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}
struct FirstTableEntry
{
    TokenType type;
    TokenType *FirstSet;
    bool isComputed;
    int size_firstset;
};

typedef struct FirstTableEntry *FirstEntry;
FirstEntry *FirstTable;

void ComputeFirst(HEAD_NODE head_entry)
{
    if (FirstTable[head_entry->token]->isComputed == true)
        return;
    for (int i = 0; i < head_entry->count; i++)
    {
        if (checkTerminal(head_entry->next[i]->token) == true)
        {
            // printf("%s\n",getStringFromToken(head_entry->next[i]->token));
            // printf("The size currently before reallocing is : %d\n", (FirstTable[head_entry->token]->size_firstset));
            FirstTable[head_entry->token]->FirstSet = realloc(FirstTable[head_entry->token]->FirstSet, (FirstTable[head_entry->token]->size_firstset + 1) * sizeof(TokenType));
            (FirstTable[head_entry->token]->size_firstset)++;
            FirstTable[head_entry->token]->FirstSet[FirstTable[head_entry->token]->size_firstset - 1] = head_entry->next[i]->token;
            // printf("First Set Token : %s size %d\n", getStringFromToken(FirstTable[head_entry->token]->FirstSet[(sizeof(FirstTable[head_entry->token]->FirstSet) / sizeof(TokenType)) - 1]),(sizeof(FirstTable[head_entry->token]->FirstSet) / sizeof(TokenType)));
            for (int j = 0; j < FirstTable[head_entry->token]->size_firstset; j++)
            {
                // printf("%s has %d elements in it's first set\n", getStringFromToken(FirstTable[head_entry->token]->type), FirstTable[head_entry->token]->size_firstset);
                // printf("Terminal found which is %s\n", getStringFromToken(FirstTable[head_entry->token]->FirstSet[j]));
            }
            continue;
        }
        else
        {
            if (FirstTable[head_entry->next[i]->token]->isComputed == false)
                ComputeFirst(grammar[head_entry->next[i]->token]);
            int x = FirstTable[head_entry->token]->size_firstset;
            // printf("The size currently before reallocing is (for non terminal): %d\n", (FirstTable[head_entry->token]->size_firstset));
            FirstTable[head_entry->token]->FirstSet = realloc(FirstTable[head_entry->token]->FirstSet, FirstTable[head_entry->token]->size_firstset + FirstTable[head_entry->next[i]->token]->size_firstset);
            FirstTable[head_entry->token]->size_firstset = FirstTable[head_entry->token]->size_firstset + FirstTable[head_entry->next[i]->token]->size_firstset;
            for (int j = x; j < FirstTable[head_entry->token]->size_firstset; j++)
            {
                FirstTable[head_entry->token]->FirstSet[j] = FirstTable[head_entry->next[i]->token]->FirstSet[j - x];
            }
        }
        if (grammar[head_entry->next[i]->token]->epsilon_trans == true)
        {
            NODE temp = head_entry->next[i]->next;
            while ((!checkTerminal(temp->token)) && (grammar[temp->token]->epsilon_trans == true))
            {
                if ((FirstTable[temp->token]->isComputed) == false)
                {
                    ComputeFirst(grammar[temp->token]);
                }
                int x = FirstTable[head_entry->token]->size_firstset;
                // printf("The size currently before reallocing is (For Epsilon): %d\n", (FirstTable[head_entry->token]->size_firstset + FirstTable[temp->token]->size_firstset));
                FirstTable[head_entry->token]->FirstSet = realloc(FirstTable[head_entry->token]->FirstSet, ((FirstTable[head_entry->token]->size_firstset) + (FirstTable[temp->token]->size_firstset)) * sizeof(TokenType));
                FirstTable[head_entry->token]->size_firstset = FirstTable[head_entry->token]->size_firstset + FirstTable[temp->token]->size_firstset;
                for (int i = x; i < FirstTable[head_entry->token]->size_firstset; i++)
                {
                    FirstTable[head_entry->token]->FirstSet[i] = FirstTable[temp->token]->FirstSet[i - x];
                }
                temp = temp->next;
            }
        }
    }
    FirstTable[head_entry->token]->isComputed = true;
}

FirstEntry *ComputeFirstTable(HEAD_NODE *grammar)
{
    FirstTable = (FirstEntry *)malloc(GRAMMAR_RULES * (sizeof(FirstEntry)));
    for (int i = 0; i < GRAMMAR_RULES; i++)
    {
        FirstTable[i] = (FirstEntry)malloc(sizeof(struct FirstTableEntry));
        FirstTable[i]->type = grammar[i]->token;
        FirstTable[i]->isComputed = false;
        FirstTable[i]->FirstSet = NULL;
        FirstTable[i]->size_firstset = 0;
    }

    for (int i = 0; i < GRAMMAR_RULES; i++)
    {
        ComputeFirst(grammar[i]);
    }
    return FirstTable;
}

struct FollowTableEntry
{
    TokenType type;
    TokenType *FollowSet;
    bool isComputed;
    int size_followset;
};
typedef struct FollowTableEntry *FollowEntry;
FollowEntry *FollowTable;
struct FollowElements
{
    TokenType type;
    TokenType *FollowElements;
    TokenType *FirstElements;
    TokenType *Terminals;
    int count_First;
    int count_Follow;
    int count_Terminals;
};

struct FollowElements *FE_Table[GRAMMAR_RULES];
void Traverse_DT()
{
    for (int i = 0; i < GRAMMAR_RULES; i++)
    {
        FE_Table[i] = (struct FollowElements *)malloc(sizeof(struct FollowElements));
        FE_Table[i]->count_First = 0;
        FE_Table[i]->count_Follow = 0;
        FE_Table[i]->count_Terminals = 0;
        FE_Table[i]->type = grammar[i]->token;
        FE_Table[i]->FollowElements = NULL;
        FE_Table[i]->FirstElements = NULL;
        FE_Table[i]->Terminals = NULL;
    }
    for (int i = 0; i < GRAMMAR_RULES; i++)
    {
        for (int j = 0; j < grammar[i]->count; j++)
        {
            NODE temp = grammar[i]->next[j];
            while (temp->next != NULL)
            {
                if (!temp->isT)
                {
                    if (temp->next->isT)
                    {
                        // printf("%s\n",getStringFromToken(temp->token));
                        FE_Table[temp->token]->count_Terminals++;
                        FE_Table[temp->token]->Terminals = realloc(FE_Table[temp->token]->Terminals, (FE_Table[temp->token]->count_Terminals) * sizeof(TokenType));
                        FE_Table[temp->token]->Terminals[FE_Table[temp->token]->count_Terminals - 1] = temp->next->token;
                    }
                    if ((temp->next->isT != true))
                    {
                        FE_Table[temp->token]->count_First++;
                        FE_Table[temp->token]->FirstElements = realloc(FE_Table[temp->token]->FirstElements, (FE_Table[temp->token]->count_First) * sizeof(TokenType));
                        FE_Table[temp->token]->FirstElements[FE_Table[temp->token]->count_First - 1] = temp->next->token;
                        if (grammar[temp->next->token]->epsilon_trans == true)
                        {
                            FE_Table[temp->token]->count_Follow++;
                            FE_Table[temp->token]->FollowElements = realloc(FE_Table[temp->token]->FollowElements, (FE_Table[temp->token]->count_Follow) * sizeof(TokenType));
                            FE_Table[temp->token]->FollowElements[FE_Table[temp->token]->count_Follow - 1] = temp->next->token;
                        }
                    }
                }
                temp = temp->next;
            }
            if ((temp->isT != true))
            {
                FE_Table[temp->token]->count_Follow++;
                FE_Table[temp->token]->FollowElements = realloc(FE_Table[temp->token]->FollowElements, (FE_Table[temp->token]->count_Follow) * sizeof(TokenType));
                FE_Table[temp->token]->FollowElements[FE_Table[temp->token]->count_Follow - 1] = grammar[i]->token;
            }
        }
    }
}

bool doesContain(TokenType A, TokenType B)
{
    for (int i = 0; i < FE_Table[B]->count_Follow; i++)
    {
        if (FE_Table[B]->FollowElements[i] == A)
            return true;
    }
    return false;
}

TokenType *removeDuplicates(TokenType *arr, int *size)
{
    if (*size == 0)
    {
        TokenType *result = (TokenType *)malloc(sizeof(TokenType));
        *result = StackSymbol;
        return result;
    }
    int newSize = 1;
    TokenType *result = (TokenType *)malloc(sizeof(TokenType) * newSize);
    *result = *arr;
    for (int i = 1; i < *size; i++)
    {
        TokenType current = arr[i];
        int isDuplicate = 0;
        for (int j = 0; j < newSize; j++)
        {
            if (result[j] == current)
            {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate)
        {
            newSize++;
            result = realloc(result, sizeof(TokenType) * newSize);
            *(result+newSize - 1) = current;
        }
    }
    *size = newSize;
    free(arr);
    return result;
}

void ComputeFollow(HEAD_NODE head_entry)
{
    if (FollowTable[head_entry->token]->isComputed == true)
    {
        return;
    }
    FollowTable[head_entry->token]->FollowSet = realloc(FollowTable[head_entry->token]->FollowSet, (FE_Table[head_entry->token]->count_Terminals) * sizeof(TokenType));
    for (int i = 0; i < FE_Table[head_entry->token]->count_Terminals; i++)
    {
        FollowTable[head_entry->token]->FollowSet[i] = FE_Table[head_entry->token]->Terminals[i];
    }
    FollowTable[head_entry->token]->size_followset = FE_Table[head_entry->token]->count_Terminals;

    for (int i = 0; i < FE_Table[head_entry->token]->count_First; i++)
    {
        FollowTable[head_entry->token]->FollowSet = realloc(FollowTable[head_entry->token]->FollowSet, (FollowTable[head_entry->token]->size_followset + FirstTable[FE_Table[head_entry->token]->FirstElements[i]]->size_firstset) * sizeof(TokenType));
        for (int j = FollowTable[head_entry->token]->size_followset; j < (FollowTable[head_entry->token]->size_followset + FirstTable[FE_Table[head_entry->token]->FirstElements[i]]->size_firstset); j++)
        {
            FollowTable[head_entry->token]->FollowSet[j] = FirstTable[FE_Table[head_entry->token]->FirstElements[i]]->FirstSet[j - FollowTable[head_entry->token]->size_followset];
        }
        FollowTable[head_entry->token]->size_followset += FirstTable[FE_Table[head_entry->token]->FirstElements[i]]->size_firstset;
    }
    for (int i = 0; i < FE_Table[head_entry->token]->count_Follow; i++)
    {
        if (FollowTable[FE_Table[head_entry->token]->FollowElements[i]]->type == head_entry->token)
            continue;

        if (FollowTable[FE_Table[head_entry->token]->FollowElements[i]]->isComputed == false)
        {
            if (doesContain(head_entry->token, FE_Table[head_entry->token]->FollowElements[i]))
            {
                continue;
            }

            ComputeFollow(grammar[FE_Table[head_entry->token]->FollowElements[i]]);
        }
        // printf("%d\n",FollowTable[head_entry->token]->size_followset + FollowTable[FE_Table[head_entry->token]->FollowElements[i]]->size_followset);
        FollowTable[head_entry->token]->FollowSet = realloc(FollowTable[head_entry->token]->FollowSet, (FollowTable[head_entry->token]->size_followset + FollowTable[FE_Table[head_entry->token]->FollowElements[i]]->size_followset) * sizeof(TokenType));

        for (int j = FollowTable[head_entry->token]->size_followset; j < (FollowTable[head_entry->token]->size_followset + FollowTable[FE_Table[head_entry->token]->FollowElements[i]]->size_followset); j++)
        {
            FollowTable[head_entry->token]->FollowSet[j] = FollowTable[FE_Table[head_entry->token]->FollowElements[i]]->FollowSet[j - FollowTable[head_entry->token]->size_followset];
        }
        FollowTable[head_entry->token]->size_followset += FollowTable[FE_Table[head_entry->token]->FollowElements[i]]->size_followset;
    }

    FollowTable[head_entry->token]->FollowSet = removeDuplicates(FollowTable[head_entry->token]->FollowSet, &FollowTable[head_entry->token]->size_followset);
    FollowTable[head_entry->token]->isComputed = true;
    return;
}

FollowEntry *ComputeFollowTable(HEAD_NODE *grammar)
{
    Traverse_DT();
    FollowTable = (FollowEntry *)malloc(sizeof(FollowEntry) * GRAMMAR_RULES);
    for (int i = 0; i < GRAMMAR_RULES; i++)
    {
        FollowTable[i] = (FollowEntry)malloc(sizeof(struct FollowTableEntry));
        FollowTable[i]->FollowSet = NULL;
        FollowTable[i]->isComputed = false;
        FollowTable[i]->size_followset = 0;
        FollowTable[i]->type = grammar[i]->token;
    }
    for (int i = 0; i < GRAMMAR_RULES; i++)
    {
        ComputeFollow(grammar[i]);
    }
    return FollowTable;
}

int main()
{
    FILE *fp = fopen("1.txt", "r");
    GrammarReader(fp);
    FirstEntry *FirstTable = ComputeFirstTable(grammar);
    for (int i = 0; i < GRAMMAR_RULES; i++)
    {
        if(FirstTable[i]->size_firstset == 0){
            printf("?\n");
            continue;
        }
        printf("%d) First of %s: ", (i + 1), getStringFromToken(grammar[i]->token));
        for (int j = 0; j < FirstTable[i]->size_firstset; j++)
        {
            if (!strcmp(getStringFromToken(FirstTable[i]->FirstSet[j]), "Unrecognized Token"))
            {
                printf("Case Blocked\n");
                break;
            }
            printf("%s ", getStringFromToken(FirstTable[i]->FirstSet[j]));
        }
        printf("\n");
    }
    FollowEntry *FollowTable = ComputeFollowTable(grammar);
    for (int i = 0; i < GRAMMAR_RULES; i++)
    {
        printf("%d) Follow of %s: ", (i + 1), getStringFromToken(grammar[i]->token));
        if(FollowTable[i]->size_followset == 0){
            printf("%s\n", getStringFromToken(FollowTable[i]->FollowSet[0]));
            continue;
        }
        for (int j = 0; j < FollowTable[i]->size_followset; j++)
        {
            if (!strcmp(getStringFromToken(FollowTable[i]->FollowSet[j]), "Unrecognized Token"))
            {
                printf("Case Blocked\n");
                break;
            }
            printf("%s ", getStringFromToken(FollowTable[i]->FollowSet[j]));
        }
        printf("\n");
    }
}

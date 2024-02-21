#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

typedef enum
{
    TK_ASSIGNOP,
    TK_COMMENT,
    TK_FIELDID,
    TK_ID,
    TK_NUM,
    TK_RNUM,
    TK_FUNID,
    TK_RUID,
    TK_WITH,
    TK_PARAMETERS,
    TK_END,
    TK_WHILE,
    TK_UNION,
    TK_ENDUNION,
    TK_DEFINETYPE,
    TK_AS,
    TK_TYPE,
    TK_MAIN,
    TK_GLOBAL,
    TK_PARAMETER,
    TK_LIST,
    TK_SQL,
    TK_SQR,
    TK_INPUT,
    TK_OUTPUT,
    TK_INT,
    TK_REAL,
    TK_COMMA,
    TK_SEM,
    TK_COLON,
    TK_DOT,
    TK_ENDWHILE,
    TK_OP,
    TK_CL,
    TK_IF,
    TK_THEN,
    TK_ENDIF,
    TK_READ,
    TK_WRITE,
    TK_RETURN,
    TK_PLUS,
    TK_MINUS,
    TK_MUL,
    TK_DIV,
    TK_CALL,
    TK_RECORD,
    TK_ENDRECORD,
    TK_ELSE,
    TK_AND,
    TK_OR,
    TK_NOT,
    TK_LT,
    TK_LE,
    TK_EQ,
    TK_GT,
    TK_GE,
    TK_NE,
    TK_ERROR,
    TK_DELIM
} TokenType;

typedef struct
{
    TokenType type;
    char *lexeme;
    int line;
} TokenInfo;

struct buffer
{
    char buffer1[1024];
    char buffer2[1024];
};

const char *getTokenTypeName(TokenType type)
{
    switch (type)
    {
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
    case TK_ERROR:
        return "TK_ERROR";
    case TK_DELIM:
        return "TK_DELIM";
    default:
        return "Unknown Token";
    }
}

char *current_buffer, *next_buffer;
int curr, forw, lineno = 0;
FILE *fp;

FILE *getStream(FILE *fp, int space_to_fill)
{
    for (int i = 0; i < space_to_fill; i++)
    {
        *(next_buffer + i) = current_buffer[curr++];
    }

    size_t char_read = fread(next_buffer + space_to_fill, 1, 1024 - space_to_fill, fp);
    if (char_read == -1)
    {
        printf("Error opening file.");
    }
    char *temp;
    temp = current_buffer;
    current_buffer = next_buffer;
    next_buffer = temp;
    curr = 0;
    forw = space_to_fill;

    return fp;
}

void removeComments(char *testcaseFile, char *cleanFile)
{
    FILE *inputFile = fopen(testcaseFile, "r");
    FILE *outputFile = fopen(cleanFile, "w");

    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Error opening files.\n");
        return;
    }

    char *line = NULL;
    size_t bufferSize = 0;
    size_t charactersRead;

    while ((charactersRead = getline(&line, &bufferSize, inputFile)) != -1)
    {
        char *commentPos = strchr(line, '%');
        if (commentPos != NULL)
        {
            *commentPos = '\n';
            *(commentPos + 1) = '\0';
        }
        fprintf(outputFile, "%s", line);
    }

    free(line);
    fclose(inputFile);
    fclose(outputFile);
}

TokenInfo getNextToken()
{
    curr = forw;
    TokenInfo CurrToken;
    if (current_buffer[curr] == '@')
    {
        forw++;
        checklimits();
        if (current_buffer[forw] == '@')
        {
            forw++;
            checklimits();
            if (current_buffer[forw] == '@')
            {
                forw++;
                CurrToken.lexeme = (char *)malloc(strlen("@@@") + 1);
                strcpy(CurrToken.lexeme, "@@@");
                CurrToken.line = lineno;
                CurrToken.type = TK_OR;
                return CurrToken;
            }
            else
            {
                CurrToken.lexeme = (char *)malloc(strlen("@@") + 1);
                strcpy(CurrToken.lexeme, "@@");
                CurrToken.line = lineno;
                CurrToken.type = TK_ERROR;
                return CurrToken;
            }
        }
        else
        {
            CurrToken.lexeme = (char *)malloc(strlen("@") + 1);
            strcpy(CurrToken.lexeme, "@");
            CurrToken.line = lineno;
            CurrToken.type = TK_ERROR;
            return CurrToken;
        }
    }

    if (current_buffer[curr] == "&")
    {
        forw++;
        checklimits();
        if (current_buffer[forw] == "&")
        {
            forw++;
            checklimits();
            if (current_buffer[forw] == "&")
            {
                forw++;
                CurrToken.lexeme = (char *)malloc(strlen("&&&") + 1);
                strcpy(CurrToken.lexeme, "&&&");
                CurrToken.line = lineno;
                CurrToken.type = TK_AND;
                return CurrToken;
            }
            else
            {
                CurrToken.lexeme = (char *)malloc(strlen("&&") + 1);
                strcpy(CurrToken.lexeme, "&&");
                CurrToken.line = lineno;
                CurrToken.type = TK_ERROR;
                return CurrToken;
            }
        }
        else
        {
            CurrToken.lexeme = (char *)malloc(strlen("&") + 1);
            strcpy(CurrToken.lexeme, "&");
            CurrToken.line = lineno;
            CurrToken.type = TK_ERROR;
            return CurrToken;
        }
    }

    if (current_buffer[curr] == "*")
    {
        forw++;
        CurrToken.lexeme = (char *)malloc(strlen("*") + 1);
        strcpy(CurrToken.lexeme, "*");
        CurrToken.line = lineno;
        CurrToken.type = TK_MUL;
        return CurrToken;
    }

    if (current_buffer[forw] == "/")
    {
        forw++;
        CurrToken.lexeme = (char *)malloc(strlen("/") + 1);
        strcpy(CurrToken.lexeme, "/");
        CurrToken.line = lineno;
        CurrToken.type = TK_DIV;
        return CurrToken;
    }

    if (current_buffer[curr] == "~")
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("~") + 1);
        strcpy(CurrToken.lexeme, "~");
        CurrToken.line = lineno;
        CurrToken.type = TK_NOT;
        return CurrToken;
    }

    if (current_buffer[curr] == "-")
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("-") + 1);
        strcpy(CurrToken.lexeme, "-");
        CurrToken.line = lineno;
        CurrToken.type = TK_MINUS;
        return CurrToken;
    }

    if (current_buffer[curr] == "+")
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("+") + 1);
        strcpy(CurrToken.lexeme, "+");
        CurrToken.line = lineno;
        CurrToken.type = TK_PLUS;
        return CurrToken;
    }

    if (current_buffer[curr] == ")")
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen(")") + 1);
        strcpy(CurrToken.lexeme, ")");
        CurrToken.line = lineno;
        CurrToken.type = TK_CL;
        return CurrToken;
    }

    if (current_buffer[curr] == "(")
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("(") + 1);
        strcpy(CurrToken.lexeme, "(");
        CurrToken.line = lineno;
        CurrToken.type = TK_OP;
        return CurrToken;
    }

    if (current_buffer[curr] == ".")
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen(".") + 1);
        strcpy(CurrToken.lexeme, ".");
        CurrToken.line = lineno;
        CurrToken.type = TK_DOT;
        return CurrToken;
    }

    if (current_buffer[curr] == ":")
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen(":") + 1);
        strcpy(CurrToken.lexeme, ":");
        CurrToken.line = lineno;
        CurrToken.type = TK_COLON;
        return CurrToken;
    }

    if (current_buffer[curr] == ";")
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen(";") + 1);
        strcpy(CurrToken.lexeme, ";");
        CurrToken.line = lineno;
        CurrToken.type = TK_SEM;
        return CurrToken;
    }

    if (current_buffer[curr] == ",")
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen(",") + 1);
        strcpy(CurrToken.lexeme, ",");
        CurrToken.line = lineno;
        CurrToken.type = TK_COMMA;
        return CurrToken;
    }

    if (current_buffer[curr] == "]")
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("]") + 1);
        strcpy(CurrToken.lexeme, "]");
        CurrToken.line = lineno;
        CurrToken.type = TK_SQR;
        return CurrToken;
    }

    if (current_buffer[curr] == "[")
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("[") + 1);
        strcpy(CurrToken.lexeme, "[");
        CurrToken.line = lineno;
        CurrToken.type = TK_SQL;
        return CurrToken;
    }

    if (current_buffer[curr] == "%")
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("%") + 1);
        strcpy(CurrToken.lexeme, "%");
        CurrToken.line = lineno;
        CurrToken.type = TK_COMMENT;
        return CurrToken;
    }

    if (current_buffer[forw] == '=')
    {
        forw++;
        checklimits();
        if (current_buffer[forw] == '=')
        {
            forw++;
            CurrToken.lexeme = (char *)malloc(strlen("==") + 1);
            strcpy(CurrToken.lexeme, "==");
            CurrToken.line = lineno;
            CurrToken.type = TK_EQ;
            return CurrToken;
        }
        else
        {
            CurrToken.lexeme = (char *)malloc(strlen("=") + 1);
            strcpy(CurrToken.lexeme, "=");
            CurrToken.line = lineno;
            CurrToken.type = TK_ERROR;
            return CurrToken;
        }
    }

    if (current_buffer[forw] == '!')
    {
        forw++;
        checklimits();
        if (current_buffer[forw] == '=')
        {
            forw++;
            CurrToken.lexeme = (char *)malloc(strlen("!=") + 1);
            strcpy(CurrToken.lexeme, "!=");
            CurrToken.line = lineno;
            CurrToken.type = TK_NE;
            return CurrToken;
        }
        else
        {
            CurrToken.lexeme = (char *)malloc(strlen("!") + 1);
            strcpy(CurrToken.lexeme, "!");
            CurrToken.line = lineno;
            CurrToken.type = TK_ERROR;
            return CurrToken;
        }
    }
}

void checklimits()
{
    if (forw > 1023)
    {
        fp = getStream(fp, 1024 - curr);
    }
}

int main()
{

    TokenInfo printToken;
    while (current_buffer[curr] != EOF)
    {
        printToken = getNextToken();
        if (printToken.type == TK_ERROR)
        {
        }
        else
            printf("Line no. %d Lexeme %s Token %s\n", printToken.line, printToken.lexeme, getTokenTypeName(printToken.type));
    }
    return 0;
}
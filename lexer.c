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
    TK_ERROR_PATTERN,
    TK_ERROR_SYMBOL,
    TK_ERROR_ASSIGNOP,
    TK_ERROR_SIZE20,
    TK_ERROR_SIZE30,
    TK_DELIM
} TokenType;

typedef struct
{
    TokenType type;
    char *lexeme;
    int line;
} TokenInfo;

// struct buffer
// {
// char buffer1[1024];
// char buffer2[1024];
// } buffer;

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
    case TK_ERROR_SYMBOL:
        return "TK_ERROR_SYMBOL";
    case TK_ERROR_PATTERN:
        return "TK_ERROR_PATTERN";
    case TK_ERROR_ASSIGNOP:
        return "TK_ERROR_ASSIGNOP";
    case TK_ERROR_SIZE20:
        return "TK_ERROR_SIZE20";
    case TK_ERROR_SIZE30:
        return "TK_ERROR_SIZE30";
    case TK_DELIM:
        return "TK_DELIM";
    default:
        return "Unknown Token";
    }
}

// Linked List node
struct node
{

    // key is string
    char *key;
    // value is also string
    TokenType token;
    struct node *next;
};

// like constructor
void setNode(struct node *node, char *key, TokenType token)
{
    node->key = key;
    node->token = token;
    node->next = NULL;
    return;
};

struct hashMap
{

    // Current number of elements in hashMap
    // and capacity of hashMap
    int numOfElements, capacity;

    // hold base address array of linked list
    struct node **arr;
};

void initializeHashMap(struct hashMap *mp)
{

    // Default capacity in this case
    mp->capacity = 100;
    mp->numOfElements = 0;

    // array of size = 1
    mp->arr = (struct node **)malloc(sizeof(struct node *) * mp->capacity);
    return;
}

int hashFunction(struct hashMap *mp, char *key)
{
    int bucketIndex;
    int sum = 0, factor = 31;
    for (int i = 0; i < strlen(key); i++)
    {

        // sum = sum + (ascii value of
        // char * (primeNumber ^ x))...
        // where x = 1, 2, 3....n
        sum = ((sum % mp->capacity) + (((int)key[i]) * factor) % mp->capacity) % mp->capacity;

        // factor = factor * prime
        // number....(prime
        // number) ^ x
        factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
    }

    bucketIndex = sum;
    return bucketIndex;
}

void insert(struct hashMap *mp, char *key, TokenType token)
{

    // Getting bucket index for the given
    // key - value pair
    int bucketIndex = hashFunction(mp, key);
    struct node *newNode = (struct node *)malloc(

        // Creating a new node
        sizeof(struct node));

    // Setting value of node
    setNode(newNode, key, token);

    // Bucket index is empty....no collision
    if (mp->arr[bucketIndex] == NULL)
    {
        mp->arr[bucketIndex] = newNode;
    }

    // Collision
    else
    {

        // Adding newNode at the head of
        // linked list which is present
        // at bucket index....insertion at
        // head in linked list
        newNode->next = mp->arr[bucketIndex];
        mp->arr[bucketIndex] = newNode;
    }
    return;
}

void delete(struct hashMap *mp, char *key)
{

    // Getting bucket index for the
    // given key
    int bucketIndex = hashFunction(mp, key);

    struct node *prevNode = NULL;

    // Points to the head of
    // linked list present at
    // bucket index
    struct node *currNode = mp->arr[bucketIndex];

    while (currNode != NULL)
    {

        // Key is matched at delete this
        // node from linked list
        if (strcmp(key, currNode->key) == 0)
        {

            // Head node
            // deletion
            if (currNode == mp->arr[bucketIndex])
            {
                mp->arr[bucketIndex] = currNode->next;
            }

            // Last node or middle node
            else
            {
                prevNode->next = currNode->next;
            }
            free(currNode);
            break;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
    return;
}

TokenType search(struct hashMap *mp, char *key)
{

    // Getting the bucket index
    // for the given key
    int bucketIndex = hashFunction(mp, key);
    // Head of the linked list
    // present at bucket index

    struct node *bucketHead = mp->arr[bucketIndex];

    while (bucketHead != NULL)
    {
        // Key is found in the hashMap
        if (strcmp(bucketHead->key, key) == 0)
        {
            return bucketHead->token;
        }
        bucketHead = bucketHead->next;
    }

    // If no key found in the hashMap
    // equal to the given key
    char *errorMssg = (char *)malloc(sizeof(char) * 25);
    return TK_ERROR_PATTERN;
}

void insertKeyWords(struct hashMap *mp)
{
    insert(mp, "with", TK_WITH);
    insert(mp, "parameters", TK_PARAMETERS);
    insert(mp, "end", TK_END);
    insert(mp, "while", TK_WHILE);
    insert(mp, "union", TK_UNION);
    insert(mp, "endunion", TK_ENDUNION);
    insert(mp, "definetype", TK_DEFINETYPE);
    insert(mp, "as", TK_AS);
    insert(mp, "type", TK_TYPE);
    insert(mp, "global", TK_GLOBAL);
    insert(mp, "parameter", TK_PARAMETER);
    insert(mp, "list", TK_LIST);
    insert(mp, "input", TK_INPUT);
    insert(mp, "output", TK_OUTPUT);
    insert(mp, "int", TK_INT);
    insert(mp, "real", TK_REAL);
    insert(mp, "endwhile", TK_ENDWHILE);
    insert(mp, "if", TK_IF);
    insert(mp, "then", TK_THEN);
    insert(mp, "endif", TK_ENDIF);
    insert(mp, "read", TK_READ);
    insert(mp, "write", TK_WRITE);
    insert(mp, "return", TK_RETURN);
    insert(mp, "call", TK_CALL);
    insert(mp, "record", TK_RECORD);
    insert(mp, "endrecord", TK_ENDRECORD);
    insert(mp, "else", TK_ELSE);
}

char *current_buffer, *next_buffer;
int curr, forw, lineno;
FILE *fp;
struct hashMap *mp;
size_t char_read;

FILE *getStream(FILE *fp, int space_to_fill)
{
    free(next_buffer);
    next_buffer = (char *)malloc(sizeof(char) * 1024);
    for (int i = 0; i < space_to_fill; i++)
    {
        *(next_buffer + i) = current_buffer[curr++];
    }

    char_read = fread(next_buffer + space_to_fill, 1, 1024 - space_to_fill, fp);
    if (char_read == -1)
    {
        printf("Error opening file.");
        return fp;
    }
    char_read += space_to_fill;
    if(char_read < 1024)
    {
        char *temp = (char*) malloc(char_read*sizeof(char));
        memcpy(temp,next_buffer,char_read);
        // printf("%s",temp);
        free(next_buffer);
        next_buffer = current_buffer;
        current_buffer = temp;
        // printf("%s",current_buffer);
        return fp; 
    }
    char *temp;
    temp = current_buffer;
    current_buffer = next_buffer;
    next_buffer = temp;
    curr = 0;
    forw = space_to_fill;

    return fp;
}

void checklimits()
{
    // printf("The value of forw is: %d\n", forw);
    if (forw > 1023)
    {
        fp = getStream(fp, 1024 - curr);
    }
    return;
}

TokenInfo getNextToken()
{
    curr = forw;
    checklimits();
    TokenInfo CurrToken;
    if (current_buffer[curr] == ' ' || current_buffer[curr] == '\t')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen(" ") + 1);
        strcpy(CurrToken.lexeme, " ");
        CurrToken.line = lineno;
        CurrToken.type = TK_DELIM;
        return CurrToken;
    }
    if (current_buffer[curr] == '\n')
    {
        lineno++;
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen(" ") + 1);
        strcpy(CurrToken.lexeme, " ");
        CurrToken.line = lineno;
        CurrToken.type = TK_DELIM;
        return CurrToken;
    }
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
                checklimits();
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
                CurrToken.type = TK_ERROR_PATTERN;
                return CurrToken;
            }
        }
        else
        {
            CurrToken.lexeme = (char *)malloc(strlen("@") + 1);
            strcpy(CurrToken.lexeme, "@");
            CurrToken.line = lineno;
            CurrToken.type = TK_ERROR_SYMBOL;
            return CurrToken;
        }
    }

    if (current_buffer[curr] == '&')
    {
        forw++;
        checklimits();
        if (current_buffer[forw] == '&')
        {
            forw++;
            checklimits();
            if (current_buffer[forw] == '&')
            {
                forw++;
                checklimits();
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
                CurrToken.type = TK_ERROR_PATTERN;
                return CurrToken;
            }
        }
        else
        {
            CurrToken.lexeme = (char *)malloc(strlen("&") + 1);
            strcpy(CurrToken.lexeme, "&");
            CurrToken.line = lineno;
            CurrToken.type = TK_ERROR_SYMBOL;
            return CurrToken;
        }
    }

    if (current_buffer[curr] == '*')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("*") + 1);
        strcpy(CurrToken.lexeme, "*");
        CurrToken.line = lineno;
        CurrToken.type = TK_MUL;
        return CurrToken;
    }

    if (current_buffer[curr] == '/')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("/") + 1);
        strcpy(CurrToken.lexeme, "/");
        CurrToken.line = lineno;
        CurrToken.type = TK_DIV;
        return CurrToken;
    }

    if (current_buffer[curr] == '~')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("~") + 1);
        strcpy(CurrToken.lexeme, "~");
        CurrToken.line = lineno;
        CurrToken.type = TK_NOT;
        return CurrToken;
    }

    if (current_buffer[curr] == '-')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("-") + 1);
        strcpy(CurrToken.lexeme, "-");
        CurrToken.line = lineno;
        CurrToken.type = TK_MINUS;
        return CurrToken;
    }

    if (current_buffer[curr] == '+')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("+") + 1);
        strcpy(CurrToken.lexeme, "+");
        CurrToken.line = lineno;
        CurrToken.type = TK_PLUS;
        return CurrToken;
    }

    if (current_buffer[curr] == ')')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen(")") + 1);
        strcpy(CurrToken.lexeme, ")");
        CurrToken.line = lineno;
        CurrToken.type = TK_CL;
        return CurrToken;
    }

    if (current_buffer[curr] == '(')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("(") + 1);
        strcpy(CurrToken.lexeme, "(");
        CurrToken.line = lineno;
        CurrToken.type = TK_OP;
        return CurrToken;
    }

    if (current_buffer[curr] == '.')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen(".") + 1);
        strcpy(CurrToken.lexeme, ".");
        CurrToken.line = lineno;
        CurrToken.type = TK_DOT;
        return CurrToken;
    }

    if (current_buffer[curr] == ':')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen(":") + 1);
        strcpy(CurrToken.lexeme, ":");
        CurrToken.line = lineno;

        CurrToken.type = TK_COLON;
        return CurrToken;
    }

    if (current_buffer[curr] == ';')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen(";") + 1);
        strcpy(CurrToken.lexeme, ";");
        CurrToken.line = lineno;
        CurrToken.type = TK_SEM;
        return CurrToken;
    }

    if (current_buffer[curr] == ',')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen(",") + 1);
        strcpy(CurrToken.lexeme, ",");
        CurrToken.line = lineno;
        CurrToken.type = TK_COMMA;
        return CurrToken;
    }

    if (current_buffer[curr] == ']')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("]") + 1);
        strcpy(CurrToken.lexeme, "]");
        CurrToken.line = lineno;
        CurrToken.type = TK_SQR;
        return CurrToken;
    }

    if (current_buffer[curr] == '[')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("[") + 1);
        strcpy(CurrToken.lexeme, "[");
        CurrToken.line = lineno;
        CurrToken.type = TK_SQL;
        return CurrToken;
    }
    if (current_buffer[curr] == '%')
    {
        forw++;
        checklimits();
        CurrToken.lexeme = (char *)malloc(strlen("%") + 1);
        strcpy(CurrToken.lexeme, "%");

        CurrToken.line = lineno;
        CurrToken.type = TK_COMMENT;
        while (current_buffer[forw] != '\n')
        {
            if (current_buffer[forw] == '\0')
            {
                break;
            }
            forw++;
            checklimits();
        }
        return CurrToken;
    }

    if (current_buffer[forw] == '=')
    {
        forw++;
        checklimits();
        if (current_buffer[forw] == '=')
        {
            forw++;
            checklimits();
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
            CurrToken.type = TK_ERROR_SYMBOL;
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
            checklimits();
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
            CurrToken.type = TK_ERROR_SYMBOL;
            return CurrToken;
        }
    }

    if (current_buffer[curr] == '>')
    {
        forw++;
        checklimits();
        if (current_buffer[forw] == '=')
        {
            forw++;
            checklimits();
            CurrToken.lexeme = (char *)malloc(strlen(">=") + 1);
            strcpy(CurrToken.lexeme, ">=");
            CurrToken.line = lineno;
            CurrToken.type = TK_GE;
            return CurrToken;
        }
        else
        {
            CurrToken.lexeme = (char *)malloc(strlen(">") + 1);
            strcpy(CurrToken.lexeme, ">");
            CurrToken.line = lineno;
            CurrToken.type = TK_GT;
            return CurrToken;
        }
    }

    if (current_buffer[curr] == '<')
    {
        forw++;
        checklimits();
        if (current_buffer[forw] == '=')
        {
            forw++;
            checklimits();
            CurrToken.lexeme = (char *)malloc(strlen("<=") + 1);
            strcpy(CurrToken.lexeme, "<=");
            CurrToken.line = lineno;
            CurrToken.type = TK_LE;
            return CurrToken;
        }
        else if (current_buffer[forw] == '-')
        {
            forw++;
            checklimits();
            if (current_buffer[forw] == '-')
            {
                forw++;
                checklimits();
                if (current_buffer[forw] == '-')
                {
                    forw++;
                    checklimits();
                    CurrToken.lexeme = (char *)malloc(strlen("<---") + 1);
                    strcpy(CurrToken.lexeme, "<---");
                    CurrToken.line = lineno;
                    CurrToken.type = TK_ASSIGNOP;
                    return CurrToken;
                }
                else
                {
                    CurrToken.lexeme = (char *)malloc(strlen("<--") + 1);
                    strcpy(CurrToken.lexeme, "<--");
                    CurrToken.line = lineno;
                    CurrToken.type = TK_ERROR_ASSIGNOP;
                    return CurrToken;
                }
            }
            else
            {
                forw--;
                CurrToken.lexeme = (char *)malloc(strlen("<") + 1);
                strcpy(CurrToken.lexeme, "<");
                CurrToken.line = lineno;
                CurrToken.type = TK_LT;
                return CurrToken;
            }
        }
        else
        {
            CurrToken.lexeme = (char *)malloc(strlen("<") + 1);
            strcpy(CurrToken.lexeme, "<");
            CurrToken.line = lineno;
            CurrToken.type = TK_LT;
            return CurrToken;
        }
    }

    if (current_buffer[curr] == '#')
    {
        forw++;
        checklimits();
        int counter = 0;
        if ((current_buffer[forw] >= 'a') && (current_buffer[forw] <= 'z'))
        {
            counter++;
            forw++;
            checklimits();
            while ((current_buffer[forw] >= 'a') && (current_buffer[forw] <= 'z'))
            {
                counter++;
                forw++;
                checklimits();
            }
            if (counter <= 20)
            {
                CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                CurrToken.line = lineno;
                CurrToken.type = TK_RUID;
                return CurrToken;
            }
            else
            {
                CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                CurrToken.line = lineno;
                CurrToken.type = TK_ERROR_SIZE20;
                return CurrToken;
            }
        }
        else
        {
            CurrToken.lexeme = (char *)malloc(strlen("#") + 1);
            strcpy(CurrToken.lexeme, "#");
            CurrToken.line = lineno;
            CurrToken.type = TK_ERROR_SYMBOL;
            return CurrToken;
        }
    }

    if (current_buffer[curr] == '_')
    {
        forw++;
        checklimits();
        int counter = 0;
        if (((current_buffer[forw] >= 'a') && (current_buffer[forw] <= 'z')) || ((current_buffer[forw] >= 'A') && (current_buffer[forw] <= 'Z')))
        {
            counter++;
            forw++;
            checklimits();
            while (((current_buffer[forw] >= 'a') && (current_buffer[forw] <= 'z')) || ((current_buffer[forw] >= 'A') && (current_buffer[forw] <= 'Z')))
            {
                counter++;
                forw++;
                checklimits();
            }
            while ((current_buffer[forw] >= '0') && (current_buffer[forw] <= '9'))
            {
                counter++;
                forw++;
                checklimits();
            }
            if (counter <= 30)
            {
                CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                CurrToken.line = lineno;
                if (strcmp(CurrToken.lexeme, "_main") == 0)
                {
                    CurrToken.type = TK_MAIN;
                    return CurrToken;
                }
                CurrToken.type = TK_FUNID;
                return CurrToken;
            }
            else
            {
                CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                CurrToken.line = lineno;
                CurrToken.type = TK_ERROR_SIZE30;
                return CurrToken;
            }
        }
        else
        {
            CurrToken.lexeme = (char *)malloc(strlen("_") + 1);
            strcpy(CurrToken.lexeme, "_");
            CurrToken.line = lineno;
            CurrToken.type = TK_ERROR_SYMBOL;
            return CurrToken;
        }
    }

    if ((current_buffer[curr] >= 'a') && (current_buffer[curr] <= 'z'))
    {
        int counter = 0;
        if ((current_buffer[curr] >= 'b') && (current_buffer[curr] <= 'd'))
        {
            forw++;
            counter++;
            checklimits();
            if ((current_buffer[forw] >= 'a') && (current_buffer[forw] <= 'z'))
            {
                counter++;
                forw++;
                checklimits();
                while ((current_buffer[forw] >= 'a') && (current_buffer[forw] <= 'z'))
                {
                    counter++;
                    forw++;
                    checklimits();
                }
                if (counter <= 20)
                {
                    CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                    strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);

                    CurrToken.line = lineno;
                    TokenType type = search(mp, CurrToken.lexeme);
                    if (type == TK_ERROR_PATTERN)
                        CurrToken.type = TK_FIELDID;
                    else
                    {
                        CurrToken.type = type;
                    }
                    return CurrToken;
                }
                else
                {
                    CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                    strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                    CurrToken.line = lineno;
                    CurrToken.type = TK_ERROR_SIZE20;
                    return CurrToken;
                }
            }
            else if ((current_buffer[forw] >= '2') && (current_buffer[forw] <= '7'))
            {
                counter++;
                forw++;
                checklimits();
                while ((current_buffer[forw] >= 'b') && (current_buffer[forw] <= 'd'))
                {
                    counter++;
                    forw++;
                    checklimits();
                }
                while ((current_buffer[forw] >= '2') && (current_buffer[forw] <= '7'))
                {
                    counter++;
                    forw++;
                    checklimits();
                }
                if (counter <= 20)
                {
                    CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                    strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                    CurrToken.line = lineno;
                    CurrToken.type = TK_ID;
                    return CurrToken;
                }
                else
                {
                    CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                    strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                    CurrToken.line = lineno;
                    CurrToken.type = TK_ERROR_SIZE20;
                    return CurrToken;
                }
            }
            else
            {
                CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                CurrToken.line = lineno;
                TokenType type = search(mp, CurrToken.lexeme);
                if (type == TK_ERROR_PATTERN)
                    CurrToken.type = TK_FIELDID;
                else
                {
                    CurrToken.type = type;
                }
                return CurrToken;
            }
        }
        else
        {
            counter++;
            forw++;
            checklimits();
            while ((current_buffer[forw] >= 'a') && (current_buffer[forw] <= 'z'))
            {
                counter++;
                forw++;
                checklimits();
            }
            if (counter <= 20)
            {
                CurrToken.lexeme = (char *)malloc(forw - curr + 2);
                strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                CurrToken.line = lineno;
                CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                if (CurrToken.lexeme != NULL)
                {
                    strncpy(CurrToken.lexeme, current_buffer + curr, forw - curr);
                    CurrToken.lexeme[forw - curr] = '\0'; // Ensure null-termination
                }
                TokenType type = search(mp, CurrToken.lexeme);
                if (type == TK_ERROR_PATTERN)
                    CurrToken.type = TK_FIELDID;
                else
                {
                    CurrToken.type = type;
                }
                return CurrToken;
            }
            else
            {
                CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                CurrToken.line = lineno;
                CurrToken.type = TK_ERROR_SIZE20;
                return CurrToken;
            }
        }
    }

    if ((current_buffer[curr] >= '0') && (current_buffer[curr] <= '9'))
    {
        forw++;
        checklimits();
        while ((current_buffer[forw] >= '0') && (current_buffer[forw] <= '9'))
        {
            forw++;
            checklimits();
        }
        if (current_buffer[forw] == '.')
        {
            forw++;
            checklimits();
            if ((current_buffer[forw] >= '0') && (current_buffer[forw] <= '9'))
            {
                forw++;
                checklimits();
                if ((current_buffer[forw] >= '0') && (current_buffer[forw] <= '9'))
                {
                    forw++;
                    checklimits();
                    if (current_buffer[forw] == 'E' || current_buffer[forw] == 'e')
                    {
                        forw++;
                        checklimits();
                        if (current_buffer[forw] == '+' || current_buffer[forw] == '-')
                        {
                            forw++;
                            checklimits();
                        }
                        if ((current_buffer[forw] >= '0') && (current_buffer[forw] <= '9'))
                        {
                            forw++;
                            checklimits();
                            if ((current_buffer[forw] >= '0') && (current_buffer[forw] <= '9'))
                            {
                                forw++;
                                checklimits();
                                CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                                strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                                CurrToken.line = lineno;
                                CurrToken.type = TK_RNUM;
                                return CurrToken;
                            }
                            else
                            {
                                CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                                strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                                CurrToken.line = lineno;
                                CurrToken.type = TK_ERROR_PATTERN;
                                return CurrToken;
                            }
                        }
                        else
                        {
                            CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                            strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                            CurrToken.line = lineno;
                            CurrToken.type = TK_ERROR_PATTERN;
                            return CurrToken;
                        }
                    }
                    else
                    {
                        CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                        strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                        CurrToken.line = lineno;
                        CurrToken.type = TK_RNUM;
                        return CurrToken;
                    }
                }
                else
                {
                    CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                    strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                    CurrToken.line = lineno;
                    CurrToken.type = TK_ERROR_PATTERN;
                    return CurrToken;
                }
            }
            else
            {
                forw--;
                CurrToken.lexeme = (char *)malloc(forw - curr + 1);
                strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
                CurrToken.line = lineno;
                CurrToken.type = TK_NUM;
                return CurrToken;
            }
        }
        else
        {
            CurrToken.lexeme = (char *)malloc(forw - curr + 1);
            strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
            CurrToken.line = lineno;
            CurrToken.type = TK_NUM;
            return CurrToken;
        }
    }
    forw++;
    checklimits();
    CurrToken.type = TK_ERROR_SYMBOL;
    CurrToken.lexeme = (char *)malloc(forw - curr + 1);
    strncpy(CurrToken.lexeme, current_buffer + (curr), forw - curr);
    CurrToken.line = lineno;
    return CurrToken;
}

int main()
{
    fp = fopen("test-cases/t9.txt", "r");

    current_buffer = (char *)malloc(sizeof(char) * 1024);
    next_buffer = (char *)malloc(sizeof(char) * 1024);

    fp = getStream(fp, 0);
    if (fp == NULL)
        printf("Error in opening the file\n");
    mp = (struct hashMap *)malloc(sizeof(struct hashMap));
    initializeHashMap(mp);
    insertKeyWords(mp);
    lineno = 1;
    // printf("The length of the current buffer is : %lu\n", strlen(current_buffer));
    TokenInfo printToken;
    while (feof(fp) == 0)
    {
        printToken = getNextToken();
        if (printToken.type == TK_ERROR_SYMBOL)
        {
            printf("Line no. %d Error: Unknown Symbol <%s>\n", printToken.line, printToken.lexeme);
        }
        else if (printToken.type == TK_DELIM)
            continue;
        else if (printToken.type == TK_ERROR_PATTERN)
            printf("Line no. %d Error: Unknown Pattern <%s>\n", printToken.line, printToken.lexeme);
        else if (printToken.type == TK_ERROR_ASSIGNOP)
            printf("Line no. %d Error: Wrong assignment operator '<--' found, expected '<---'\n", printToken.line);
        else if (printToken.type == TK_ERROR_SIZE20)
            printf("Line no. %d Error: Variable Identifier is longer than the prescribed length of 20\n", printToken.line);
        else if (printToken.type == TK_ERROR_SIZE30)
            printf("Line no. %d Error: Function/Record Identifier is longer than the prescribed length of 30\n", printToken.line);
        else
        {
            printf("Line no. %d Lexeme %s Token %s\n", printToken.line, printToken.lexeme, getTokenTypeName(printToken.type));
        }
    }
    // printf("The forw and char_read is : %d %lu\n", forw, char_read);
    forw=curr=0;
    while((forw<char_read))
    {
        printToken = getNextToken();
        if (printToken.type == TK_ERROR_SYMBOL)
        {
            printf("Line no. %d Error: Unknown Symbol <%s>\n", printToken.line, printToken.lexeme);
        }
        else if (printToken.type == TK_DELIM)
            continue;
        else if (printToken.type == TK_ERROR_PATTERN)
            printf("Line no. %d Error: Unknown Pattern <%s>\n", printToken.line, printToken.lexeme);
        else if (printToken.type == TK_ERROR_ASSIGNOP)
            printf("Line no. %d Error: Wrong assignment operator '<--' found, expected '<---'\n", printToken.line);
        else if (printToken.type == TK_ERROR_SIZE20)
            printf("Line no. %d Error: Variable Identifier is longer than the prescribed length of 20\n", printToken.line);
        else if (printToken.type == TK_ERROR_SIZE30)
            printf("Line no. %d Error: Function/Record Identifier is longer than the prescribed length of 30\n", printToken.line);
        else
        {
            printf("Line no. %d Lexeme %s Token %s\n", printToken.line, printToken.lexeme, getTokenTypeName(printToken.type));
        }
    }
    return 0;
}
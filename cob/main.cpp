#include <stdio.h>
#include <locale.h>
#include <string.h>
#include "sqlite3.h"

static int 
Callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for(int i = 0; i < argc; i++) 
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
   
    return 0;
}

void
PrintUsage()
{
    printf("Usage: \n");
    printf("* To get a word explanation: cob MyWord\n");
    printf("* To add/update a word explanation: cob MyWord \"My Explanation\" \n\n");
}

int main(int argc, char *argv[])
{
    // NOTE(Oskar): Allow special characters such as åäö
    setlocale(LC_ALL, "");
    
    sqlite3 *db;
    char *zErrMsg = 0;
    char *aErrMsg = 0;
    int rc;
    rc = sqlite3_open("cob.db", &db);
    char QueryBuffer[1024];
    
    if (rc) 
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } 
    else 
    {
        // TODO(Oskar): Only in verbose mode.
        //fprintf(stderr, "Opened database successfully\n");
    }

    char *sql = "CREATE TABLE WORDS("  \
      "ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
      "WORD           TEXT    NOT NULL UNIQUE," \
      "EXPLANATION    TEXT    NOT NULL);";

    rc = sqlite3_exec(db, sql, Callback, 0, &zErrMsg);
    if (rc != SQLITE_OK ) { } //NOTE(Oskar): Table already exists. 
    else { } // NOTE(Oskar): Table created


    if (argc == 2)
    {
        // NOTE(Oskar): Show word
        sprintf(QueryBuffer, "SELECT WORD,EXPLANATION FROM WORDS WHERE WORD LIKE '%s';", argv[1]);
        
        sqlite3_stmt *stmt;
        int SelectResult = sqlite3_prepare_v2(db, QueryBuffer, -1, &stmt, NULL);
        int step = sqlite3_step(stmt);
        if(step == SQLITE_DONE)
        {
            printf("No saved explanations for word.\n");
        }
        else
        {
		    int num_cols = sqlite3_column_count(stmt);
            for (int i = 0; i < num_cols; i++)
            {
                switch (sqlite3_column_type(stmt, i))
                {
                case (SQLITE3_TEXT):
                    printf("%s = %s\n", sqlite3_column_name(stmt, i), sqlite3_column_text(stmt, i));
                    break;
                default:
                    break;
                }
            }
        }
        sqlite3_finalize(stmt);
    }
    else if (argc == 3)
    {
        sprintf(QueryBuffer, "INSERT INTO WORDS (WORD, EXPLANATION) VALUES ('%s', '%s'); ", argv[1], argv[2]);
        int InsertResult = sqlite3_exec(db, QueryBuffer, Callback, 0, &zErrMsg);
        if (InsertResult != SQLITE_OK)
        {
            if (InsertResult == SQLITE_CONSTRAINT)
            {
                char Answer[100];
                printf("Word already exists.\n");
                printf("Do you want to update the explanation?(Y/N) ");

                scanf("%s", Answer);
                if (strcmp(Answer, "Y") == 0 || strcmp(Answer, "Yes") == 0 ||
                    strcmp(Answer, "y") == 0 || strcmp(Answer, "yes") == 0)
                {
                    sprintf(QueryBuffer, "UPDATE WORDS SET EXPLANATION = '%s' WHERE WORD LIKE '%s';", argv[2], argv[1]);

                    int UpdateResult = sqlite3_exec(db, QueryBuffer, Callback, 0, &aErrMsg);
                    if (UpdateResult != SQLITE_OK)
                    {
                        fprintf(stderr, "SQL error: %s\n", aErrMsg);
                    }
                    else
                    {
                        printf("Explanation successfully updated: \n");
                        printf("WORD = %s\nEXPLANATION =  %s\n", argv[1], argv[2]);
                    }
                }
            }
            else
            {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
            }
        } 
        else 
        { 
            // NOTE(Oskar): Saved successfully.
            printf("Saving the following words: \n");
            printf("WORD = %s\nEXPLANATION =  %s\n", argv[1], argv[2]);
        }

        sqlite3_free(zErrMsg);
    }
    else
    {
        PrintUsage();
    }

    sqlite3_close(db);

    return 0;
}
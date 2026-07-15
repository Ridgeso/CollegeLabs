#include <stdlib.h>
#include <libpq-fe.h>

// Zawiera mackra takie jak: dbase, user, pass | analogicznie jak na laboratirach nr 9
#include "test.h"


void insert(PGconn* conn, const char* table, const char* values)
{
    printf("------------------------------\n");
    printf("INSERING\n");

    char command[512];
    int len = sprintf(command, "INSERT INTO %s valuse(%s);", table, values);

    PGresult* result = PQexec(conn, command);

    printf("status is : %s\n", PQresStatus(PQresultStatus(result)));
    printf("#rows affected: %s\n", PQcmdTuples(result));
    printf("result message: %s\n", PQresultErrorMessage(result));

    if (PQresultStatus(result) == PGRES_TUPLES_OK)
    {
        int n = 0, r = 0;
        int nrows   = PQntuples(result);
        int nfields = PQnfields(result);
        printf("number of rows returned = %d\n", nrows);
        printf("number of fields returned = %d\n", nfields);
        for(r = 0; r < nrows; r++)
        {
            for(n = 0; n < nfields; n++)
                printf(" %s = %s", PQfname(result, n), PQgetvalue(result,r,n));
            
            printf("\n");
        }
    }

    PQclear(result);
    printf("------------------------------\n");
}

void executeSQL(PGconn* conn, char* command){
    printf("------------------------------\n");
    printf("%s\n", command);

    PGresult* result = PQexec(conn, command);

    printf("status is : %s\n", PQresStatus(PQresultStatus(result)));
    printf("#rows affected: %s\n", PQcmdTuples(result));
    printf("result message: %s\n", PQresultErrorMessage(result));

    if (PQresultStatus(result) == PGRES_TUPLES_OK)
    {
        int n = 0, r = 0;
        int nrows   = PQntuples(result);
        int nfields = PQnfields(result);
        printf("number of rows returned = %d\n", nrows);
        printf("number of fields returned = %d\n", nfields);
        for(r = 0; r < nrows; r++)
        {
            for(n = 0; n < nfields; n++)
                printf(" %s = %s", PQfname(result, n), PQgetvalue(result,r,n));
            
            printf("\n");
        }
    }

    PQclear(result);
}
 
int main()
{
    PGconn *conn;
    const char *connection_str = "host=localhost port=5432 dbname=" dbase " user=" user " password=" pass;

    
    conn = PQconnectdb(connection_str);
    
    if (PQstatus(conn) == CONNECTION_BAD)
    {
        fprintf(stderr, "Connection to %s failed, %s", connection_str, PQerrorMessage(conn));
    }
    else
    {
        printf("=== Connected OK ===\n");
        // executeSQL(conn, "CREATE SCHEMA lab10;");
        insert(conn, "lab10.person", "11, 'Radek', 'Dadacki'");
        //executeSQL(conn, "DROP TABLE lab10.person");
        // executeSQL(conn, "CREATE TABLE lab10.person (id INTEGER PRIMARY KEY, fname VARCHAR, lname VARCHAR);");
        // executeSQL(conn, "INSERT INTO lab10.person values(10, 'Adam', 'Dadacki')");
        // executeSQL(conn, "INSERT INTO lab10.person values(29, 'Bogdan', 'Zawadzki')");
        // executeSQL(conn, "INSERT INTO lab10.person values(31, 'Anna', 'Abacka')");
        // executeSQL(conn, "INSERT INTO lab10.person values(66, 'Krystyna', 'Babacka')");
        // executeSQL(conn, "SELECT * FROM lab10.person");
        // executeSQL(conn, "UPDATE lab10.person SET fname = 'Zbigniew' WHERE id = 29");
        // executeSQL(conn, "DELETE FROM lab10.person WHERE id = 29");
        // executeSQL(conn, "SELECT * FROM lab10.person");
    }
  
  PQfinish(conn);
  return EXIT_SUCCESS;
}

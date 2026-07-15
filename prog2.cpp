#include <stdlib.h>
#include <libpq-fe.h>
#include "test.h"
 
void doSQL(PGconn *conn, char *command){
  PGresult *result;
  printf("------------------------------\n");
  printf("%s\n", command);
  result = PQexec(conn, command);
  printf("status is : %s\n", PQresStatus(PQresultStatus(result)));
  printf("#rows affected: %s\n", PQcmdTuples(result));
  printf("result message: %s\n", PQresultErrorMessage(result));
  switch(PQresultStatus(result)) {
    case PGRES_TUPLES_OK:{
      int n = 0, r = 0;
      int nrows   = PQntuples(result);
      int nfields = PQnfields(result);
      printf("number of rows returned = %d\n", nrows);
      printf("number of fields returned = %d\n", nfields);
      for(r = 0; r < nrows; r++) {
        for(n = 0; n < nfields; n++)
           printf(" %s = %s", PQfname(result, n),PQgetvalue(result,r,n));
        printf("\n");
      }
    }/*end case*/
  }/* end switch */
  PQclear(result);
}
 
int main(){
  PGresult *result;
  PGconn *conn;
  const char *connection_str = "host=localhost port=5432 dbname=" dbase " user=" user " password=" pass;
  conn = PQconnectdb(connection_str);
  if (PQstatus(conn) == CONNECTION_BAD) {
     fprintf(stderr, "Connection to %s failed, %s", connection_str, PQerrorMessage(conn));
  } else {
     printf("Connected OK\n");
     //doSQL(conn, "DROP TABLE lab10.person");
     doSQL(conn, "CREATE TABLE lab10.person (id INTEGER PRIMARY KEY, fname VARCHAR, lname VARCHAR);");
     doSQL(conn, "INSERT INTO lab10.person values(10, 'Adam', 'Dadacki')");
     doSQL(conn, "INSERT INTO lab10.person values(29, 'Bogdan', 'Zawadzki')");
     doSQL(conn, "INSERT INTO lab10.person values(31, 'Anna', 'Abacka')");
     doSQL(conn, "INSERT INTO lab10.person values(66, 'Krystyna', 'Babacka')");
     doSQL(conn, "SELECT * FROM lab10.person");
     doSQL(conn, "UPDATE lab10.person SET fname = 'Zbigniew' WHERE id = 29");
     doSQL(conn, "DELETE FROM lab10.person WHERE id = 29");
     doSQL(conn, "SELECT * FROM lab10.person");
  }
  // else
  // printf("connection failed: %s\n", PQerrorMessage(conn));
  PQfinish(conn);
  return EXIT_SUCCESS;
 
}

#include "server.h"

static int callback(void *data, int argc, char **argv, char **col) {
   (void)col;
   if (argc == 0) {
      return 0;
   }
   vector_t **list = (vector_t**)data;
   for (int i = 0; i < argc && data != NULL; i++) {
      //printf("%s = %s\n", col[i], argv[i] ? argv[i] : "NULL");
      vector_push_back(*(&list), argv[i] ? strdup(argv[i]) : strdup("NULL"));
   }
   return 0;
}

static void create_db() {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc = 0;
   char *sql = NULL;

   // открыть базу данных
   rc = sqlite3_open("test.sqlite", &db);
   
   if (rc != SQLITE_OK) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
      exit(EXIT_FAILURE);
   }

   // создать SQL запрос
   sql = mx_strrejoin(sql, "PRAGMA encoding = \"UTF-8\";");
   sql = mx_strrejoin(sql, "CREATE TABLE `user` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT , `token` VARCHAR(64) NOT NULL, `username` VARCHAR(32) NOT NULL, `user_icon` INTEGER(4) NOT NULL, `chat_id` INTEGER(4) NOT NULL);");
   //sql = mx_strrejoin(sql, "CREATE TABLE `chat` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT , `title` VARCHAR(256) DEFAULT NULL, `subscribe` VARCHAR(1024) DEFAULT NULL, `active_game` INTEGER(4) DEFAULT `0`, `type` INTEGER(4) NOT NULL);");
   sql = mx_strrejoin(sql, "CREATE TABLE `message` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `type` INTEGER(4) NOT NULL, `chat_id` INTEGER(4) NOT NULL, `username` VARCHAR(32) NOT NULL, `user_icon` INTEGER(4) NOT NULL, `text` VARCHAR(1024) NOT NULL, `for_user` VARCHAR(32), `datetime` INTEGER(8) NOT NULL);");
   //sql = mx_strrejoin(sql, "CREATE TABLE `game` ( 'id' INTEGER PRIMARY KEY AUTOINCREMENT, `name` VARCHAR(255) NOT NULL);");
   //sql = mx_strrejoin(sql, "CREATE TABLE `chat_relation` ( 'id' INTEGER PRIMARY KEY AUTOINCREMENT, 'user_id' INTEGER NOT NULL, 'chat_id' INTEGER NOT NULL, `is_admin` BOOLEAN NOT NULL);");

   // передать запрос в базу данных
   rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
   
   if (rc != SQLITE_OK){
      fprintf(stderr, "Failed to select data\n");
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      sqlite3_close(db);
      exit(EXIT_FAILURE);
   }
   sqlite3_close(db);
}

void *query_db(char *query, int type) {
   struct stat buf;
   if (stat("test.sqlite", &buf) != 0) {
      create_db();
   }
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc = 0;
   vector_t *bases = NULL;
   int increment = 0;
   rc = sqlite3_open("test.sqlite", &db);
   if (type == 1) {
      rc = sqlite3_exec(db, query, callback, &bases, &zErrMsg);
      sqlite3_close(db);
      return bases;
   }
   if (type == 2) {
      rc = sqlite3_exec(db, query, 0, 0, &zErrMsg);
      increment = sqlite3_last_insert_rowid(db);
      sqlite3_close(db);
      int *a = &increment;
      return a;
   }
   return NULL;
}

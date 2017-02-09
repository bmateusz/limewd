#include "auth.h"

struct Auth *construct_auth()
{
  struct Auth *auth = malloc(sizeof(struct Auth));
  auth->user[0] = '\0';
  auth->roles = 0;
  return auth;
}

int auth_iterator(void *cls,
                  enum MHD_ValueKind kind UNUSED,
                  const char *key,
                  const char *filename UNUSED,
                  const char *content_type UNUSED,
                  const char *transfer_encoding UNUSED,
                  const char *data, uint64_t off, size_t size)
{
  struct Auth *auth = cls;
  if (auth == NULL)
  {
    printf("iterator cls null\n");
    return MHD_NO;
  }

  if (off && !size)
  {
    printf("ignore last iteration\n");
    return MHD_YES;
  }

  printf("key <%s> data <%s> off %ld size %ld\n", key, data, off, size);

  if (strcmp(key, "user") == 0)
  {
    strcpy(auth->user, data);
  }

  if (strcmp(key, "password") == 0)
  {
    auth_user(auth, data);
  }

  return MHD_YES;
}

int auth_user(struct Auth *auth,
              const char *password)
{
  printf("compare user pwd: %s/%s\n", auth->user, password);
  auth->roles = 1;
  return 1;
}

int init_auth()
{
  const char *dbpath = "db/auth.db";
  const char *create_table =
  "CREATE TABLE user(id INTEGER PRIMARY KEY ASC AUTOINCREMENT,"
                    "name TEXT UNIQUE,"
                    "password TEXT);";

  int ret = 0;
  sqlite3 *db = NULL;
  sqlite3_stmt *stmt = NULL;

  ret = sqlite3_open_v2(dbpath, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
  // ret = sqlite3_open(dbpath, &db);
  printf("open %d\n", ret);
  ret = sqlite3_prepare_v2(db, create_table, -1, &stmt, NULL);
  printf("prepare %d\n", ret);
  ret = sqlite3_step(stmt);
  printf("step %d\n", ret);

  sqlite3_finalize(stmt);
  sqlite3_close(db);

  return 0;
}

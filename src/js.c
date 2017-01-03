#include "js.h"

/* For brevity assumes a maximum file length of 16kB. */
static void push_file_as_string(duk_context *ctx, const char *filename) {
  FILE *file;
  size_t len;
  char buf[16384];

  file = fopen(filename, "rb");
  if (file) {
    len = fread((void *) buf, 1, sizeof(buf), file);
    fclose(file);
    duk_push_lstring(ctx, (const char *) buf, (duk_size_t) len);
  } else {
    duk_push_undefined(ctx);
  }
}

static duk_ret_t native_print(duk_context *ctx) {
  duk_push_string(ctx, " ");
  duk_insert(ctx, 0);
  duk_join(ctx, duk_get_top(ctx) - 1);
  printf("%s\n", duk_to_string(ctx, -1));
  return 0;
}

int answer_js(struct MHD_Connection *connection,
              const char *url)
{
  int ret = MHD_NO;
  duk_context *ctx = duk_create_heap_default();

  if (!ctx) {
    printf("Failed to create a Duktape heap.\n");
    return MHD_NO;
  }

  duk_push_global_object(ctx);
  duk_push_c_function(ctx, native_print, DUK_VARARGS);
  duk_put_prop_string(ctx, -2, "print");
  duk_push_string(ctx, url);
  duk_put_prop_string(ctx, -2, "url");

  push_file_as_string(ctx, "js/process.js");
  if (duk_peval(ctx) != 0) {
    printf("Error: %s\n", duk_safe_to_string(ctx, -1));
  }

  ret = answer_copy(connection,
                    duk_safe_to_string(ctx, -1));

  duk_pop(ctx);

  /*
  if (duk_pcall(ctx, 1) != 0) {
    printf("Error: %s\n", duk_safe_to_string(ctx, -1));
  } else {
    printf("%s\n", duk_safe_to_string(ctx, -1));
  }
  duk_pop(ctx);  */

  duk_push_context_dump(ctx);
  printf("%s\n", duk_to_string(ctx, -1));
  duk_pop(ctx);

  duk_destroy_heap(ctx);

  return ret;
}

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "jv.h"

static void test_stream_slurp(const char* input, int flags) {
  jv_parser* p = jv_parser_new(flags);
  jv_parser_set_buf(p, input, strlen(input), 1);
  
  jv value = jv_parser_next(p);
  while (jv_is_valid(value)) {
    jv_free(value);
    value = jv_parser_next(p);
  }
  jv_free(value);
  jv_parser_free(p);
}

int LLVMFuzzerTestOneInput(uint8_t *data, size_t size) {
  // Create null-terminated string
  char *null_terminated = (char *)malloc(size + 1);
  memcpy(null_terminated, (char *)data, size);
  null_terminated[size] = '\0';

  // Test normal streaming
  jv res = jv_parse_custom_flags(null_terminated, JV_PARSE_STREAMING);
  jv_free(res);

  // Test streaming + slurping with terminated input
  test_stream_slurp("[1]\n", JV_PARSE_STREAMING);
  
  // Test streaming + slurping with unterminated input
  test_stream_slurp("[1]", JV_PARSE_STREAMING);

  // Free the null-terminated string
  free(null_terminated);

  return 0;
}

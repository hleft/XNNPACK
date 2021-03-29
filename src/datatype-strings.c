// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <math.h>
#include <stddef.h>
#include <stdint.h>

#include <xnnpack.h>
#include <xnnpack/common.h>
#include <xnnpack/log.h>


// This function is defined inline when logging is disabled
#if XNN_LOG_LEVEL > 0
const char* xnn_datatype_to_string(enum xnn_datatype type) {
  switch (type) {
    case xnn_datatype_invalid:
      return "Invalid";
    case xnn_datatype_fp32:
      return "FP32";
    case xnn_datatype_fp16:
      return "FP16";
  }
  XNN_UNREACHABLE;
  return NULL;
}
#endif  // XNN_LOG_LEVEL > 0

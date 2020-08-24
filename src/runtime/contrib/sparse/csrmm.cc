#include <dmlc/logging.h>
#include <tvm/runtime/data_type.h>
#include <tvm/runtime/registry.h>

extern "C" {
#include "csrmm.h"
}

namespace tvm {
namespace contrib {

using namespace runtime;

struct csrmmOp {

  void operator()(int* colptr, int* rowidx, float* values, int N, int K, int C, float* l_a, float* l_c) {
    // typedef float TDatatype;
    csrmm(colptr, rowidx, values, N, K, C, l_a);

  }

};



TVM_REGISTER_GLOBAL("tvm.contrib.sparse.csrmm").set_body([](TVMArgs args, TVMRetValue* ret) {
  void* colptr = args[0];
  void* rowidx = args[1];
  void* values = args[2];
  int N = args[3];
  int K = args[4];
  int C = args[5];
  void* l_a = args[6];
  void* l_c = args[7];

  csrmmOp()(static_cast<int*>(colptr), static_cast<int*>(rowidx), static_cast<float*>(values), N, K, C, static_cast<float*>(l_a), static_cast<float*>(l_c));
});

}
}

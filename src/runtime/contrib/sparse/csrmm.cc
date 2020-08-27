#include <dmlc/logging.h>
#include <tvm/runtime/data_type.h>
#include <tvm/runtime/registry.h>
#include <dlfcn.h>

extern "C" {
#include "csrmm.h"
}

namespace tvm {
namespace contrib {

using namespace runtime;

struct csrmmOp {

  void operator()(int* colptr, int* rowidx, float* values, int N, int K, int C, float* l_a, float* l_c) {
    // typedef float TDatatype;
    // const char *filename = "/home/ubuntu/blockSparse/csrmm-libxsmm-onekernel/csrmm.so";
    void* handle = dlopen("/home/ubuntu/blockSparse/csrmm-libxsmm-onekernel/csrmm.so", RTLD_LAZY);
    char* error;
    if (!handle) {
            fputs (dlerror(), stderr);
            exit(1);
    }

    void (*csrmm_func)(int*, int*, float*, int, int, int, float*, float*);
    // *(void**) (&csrmm_func) = dlsym(handle, "jiacsrmm");
    *(void**) (&csrmm_func) = dlsym(handle, "_Z8jiacsrmmPiS_PfiiiS0_S0_");
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
    }


    // (*csrmm_func)(colptr, rowidx, values, N, K, C, l_a, l_c);
    csrmm_func(colptr, rowidx, values, N, K, C, l_a, l_c);

    dlclose(handle);

  }

};



TVM_REGISTER_GLOBAL("tvm.contrib.sparse.csrmm").set_body([](TVMArgs args, TVMRetValue* ret) {
  void* colptr = args[0];
  void* rowidx = args[1];
  void* values = args[2];
  void* l_a = args[3];
  void* l_c = args[4];
  int N = args[5];
  int K = args[6];
  int C = args[7];

  csrmmOp()(static_cast<int*>(colptr), static_cast<int*>(rowidx), static_cast<float*>(values), N, K, C, static_cast<float*>(l_a), static_cast<float*>(l_c));
});

}
}

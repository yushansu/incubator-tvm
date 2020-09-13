#include <dmlc/logging.h>
#include <tvm/runtime/data_type.h>
#include <tvm/runtime/registry.h>
#include <dlfcn.h>

namespace tvm {
namespace contrib {

using namespace runtime;

struct csrmmOp {

  void operator()(int* colptr, int* rowidx, float* values, int N, int K, int C, float* l_a, float* l_c) {
    void* handle = dlopen("/home/ubuntu/blockSparse/csrmm-libxsmm-onekernel/csrmm.so", RTLD_LAZY);
    char* error;
    if (!handle) {
            fputs (dlerror(), stderr);
            exit(1);
    }

    void (*csrmm_func)(int*, int*, float*, int, int, int, float*, float*);
    // *(void**) (&csrmm_func) = dlsym(handle, "_Z8jiacsrmmPiS_PfiiiS0_S0_");
    *(void**) (&csrmm_func) = dlsym(handle, "csrmm");
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
    }

    csrmm_func(colptr, rowidx, values, N, K, C, l_a, l_c);
    dlclose(handle);
  }

};



TVM_REGISTER_GLOBAL("tvm.contrib.sparse.csrmm").set_body([](TVMArgs args, TVMRetValue* ret) {
  DLTensor* colptr = args[0];
  DLTensor* rowidx = args[1];
  DLTensor* values = args[2];
  DLTensor* l_a = args[3];
  DLTensor* l_c = args[4];
  int N = args[5];
  int K = args[6];
  int C = args[7];

  csrmmOp()(static_cast<int*>(colptr->data), static_cast<int*>(rowidx->data), static_cast<float*>(values->data), N, K, C, static_cast<float*>(l_a->data), static_cast<float*>(l_c->data));
});

}
}

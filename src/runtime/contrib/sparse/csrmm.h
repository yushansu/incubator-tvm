#pragma once

#include <tvm/runtime/data_type.h>
#include <tvm/runtime/registry.h>

namespace tvm {
namespace contrib {

using namespace runtime;

float* csrmm(int* colptr, int* rowidx, float* values, int N, int K, int C, float* l_a);

}
}

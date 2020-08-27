# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

if(USE_SPARSE)
  message(STATUS "Build with contrib.sparse")
  file(GLOB SPARSE_CONTRIB_SRC src/runtime/contrib/sparse/csrmm.cc)
  list(APPEND RUNTIME_SRCS ${SPARSE_CONTRIB_SRC})
  include_directories(/home/ubuntu/libxsmm/include)

  #find_library(SPARSEMM_LIB1 libxsmm.a /home/ubuntu/libxsmm/lib/)
  #find_library(SPARSEMM_LIB2 libxsmmnoblas.a /home/ubuntu/libxsmm/lib/)
  #find_library(SPARSEMM_LIB3 libxsmmext.a /home/ubuntu/libxsmm/lib/)

  list(APPEND TVM_RUNTIME_LINKER_LIBS /home/ubuntu/libxsmm/lib/libxsmm.a)
  list(APPEND TVM_RUNTIME_LINKER_LIBS /home/ubuntu/libxsmm/lib/libxsmmnoblas.a)
  list(APPEND TVM_RUNTIME_LINKER_LIBS /home/ubuntu/libxsmm/lib/libxsmmext.a)

  #file(GLOB SPARSE_CONTRIB_SRC /home/ubuntu/blockSparse/csrmm-libxsmm-onekernel/csrmm.so)
  #list(APPEND RUNTIME_SRCS ${SPARSE_CONTRIB_SRC})
  #list(APPEND TVM_RUNTIME_LINKER_LIBS /home/ubuntu/blockSparse/csrmm-libxsmm-onekernel/csrmm.so)

  #find_library(EXTERN_LIBRARY_CSRMM NAMES csrmm.so HINTS /home/ubuntu/blockSparse/csrmm-libxsmm-onekernel/)
  #list(APPEND TVM_RUNTIME_LINKER_LIBS ${EXTERN_LIBRARY_CSRMM})

endif(USE_SPARSE)

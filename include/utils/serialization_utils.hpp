#pragma once

#include <array>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>

#include "mpi.h"

// ------------------ Macro-Based Serialization ------------------

// Push a variable into a byte array
#define PUSH(variable)                                            \
  *((__typeof__(variable) *)(arrayRank + nArrayRank)) = variable; \
  nArrayRank += sizeof(variable)

// Pop a variable from a byte array
#define POP(variable)                                             \
  variable = *((__typeof__(variable) *)(arrayRank + nArrayRank)); \
  nArrayRank += sizeof(variable)

// Push into custom array
#define PUSH_INTO(variable, array, length)                \
  *((__typeof__(variable) *)(array + length)) = variable; \
  length += sizeof(variable)

// Pop from custom array
#define POP_FROM(variable, array, length)                 \
  variable = *((__typeof__(variable) *)(array + length)); \
  length += sizeof(variable)

// Push into mpiContext::toRank[iRank]
#define PUSH_TO(variable, iRank)                                         \
  {                                                                      \
    __typeof__(variable) var = variable;                                 \
    int nBytes = sizeof(var);                                            \
    for (int nChr = 0; nChr < nBytes; ++nChr)                            \
      mpiContext.toRank[iRank].push_back(((unsigned char *)&var)[nChr]);\
  }

// ------------------ String Serialization ------------------

inline void serialize_string(const std::string &str, unsigned char *arrayRank, int &nArrayRank) {
  int len = str.size();
  PUSH(len);
  std::memcpy(arrayRank + nArrayRank, str.data(), len);
  nArrayRank += len;
}

inline void deserialize_string(std::string &str, unsigned char *arrayRank, int &nArrayRank) {
  int len;
  POP(len);
  str.assign(reinterpret_cast<char *>(arrayRank + nArrayRank), len);
  nArrayRank += len;
}

inline void serialize_vector_strings(const std::vector<std::string> &vec, unsigned char *arrayRank, int &nArrayRank) {
  PUSH(static_cast<int>(vec.size()));
  for (const auto &str : vec) {
    serialize_string(str, arrayRank, nArrayRank);
  }
}

inline void deserialize_vector_strings(std::vector<std::string> &vec, unsigned char *arrayRank, int &nArrayRank) {
  int size;
  POP(size);
  vec.resize(size);
  for (int i = 0; i < size; ++i) {
    deserialize_string(vec[i], arrayRank, nArrayRank);
  }
}

// ------------------ Primitive Vector ------------------

template <typename T>
void serialize_primitive_vector(const std::vector<T> &vec, unsigned char *arrayRank, int &nArrayRank) {
  PUSH(static_cast<int>(vec.size()));
  for (const T &val : vec) {
    PUSH(val);
  }
}

template <typename T>
void deserialize_primitive_vector(std::vector<T> &vec, unsigned char *arrayRank, int &nArrayRank) {
  int size;
  POP(size);
  vec.resize(size);
  for (int i = 0; i < size; ++i) {
    POP(vec[i]);
  }
}

// ------------------ Primitive Matrix ------------------

template <typename T>
void serialize_primitive_matrix(const std::vector<std::vector<T>> &matrix, unsigned char *arrayRank, int &nArrayRank) {
  PUSH(static_cast<int>(matrix.size()));
  for (const auto &row : matrix) {
    serialize_primitive_vector(row, arrayRank, nArrayRank);
  }
}

template <typename T>
void deserialize_primitive_matrix(std::vector<std::vector<T>> &matrix, unsigned char *arrayRank, int &nArrayRank) {
  int rows;
  POP(rows);
  matrix.resize(rows);
  for (int i = 0; i < rows; ++i) {
    deserialize_primitive_vector(matrix[i], arrayRank, nArrayRank);
  }
}

// ------------------ Abstract Vector ------------------

template <typename T>
void serialize_abstract_vector(const std::vector<T> &vec, unsigned char *arrayRank, int &nArrayRank) {
  PUSH(static_cast<int>(vec.size()));
  for (const auto &elem : vec) {
    elem.serialize(arrayRank, nArrayRank);
  }
}

template <typename T>
void deserialize_abstract_vector(std::vector<T> &vec, unsigned char *arrayRank, int &nArrayRank) {
  int size;
  POP(size);
  vec.resize(size);
  for (auto &elem : vec) {
    elem.deserialize(arrayRank, nArrayRank);
  }
}

// ------------------ Abstract Matrix ------------------

template <typename T>
void serialize_abstract_matrix(const std::vector<std::vector<T>> &matrix, unsigned char *arrayRank, int &nArrayRank) {
  PUSH(static_cast<int>(matrix.size()));
  for (const auto &row : matrix) {
    serialize_abstract_vector(row, arrayRank, nArrayRank);
  }
}

template <typename T>
void deserialize_abstract_matrix(std::vector<std::vector<T>> &matrix, unsigned char *arrayRank, int &nArrayRank) {
  int rows;
  POP(rows);
  matrix.resize(rows);
  for (int i = 0; i < rows; ++i) {
    deserialize_abstract_vector(matrix[i], arrayRank, nArrayRank);
  }
}

// ------------------ Array<Vector> Serialization ------------------

template <typename T, std::size_t S>
void serialize_vector_array(const std::vector<std::array<T, S>> &vec, unsigned char *arrayRank, int &nArrayRank) {
  PUSH(static_cast<int>(vec.size()));
  for (const auto &arr : vec) {
    for (const auto &val : arr) {
      PUSH(val);
    }
  }
}

template <typename T, std::size_t S>
void deserialize_vector_array(std::vector<std::array<T, S>> &vec, unsigned char *arrayRank, int &nArrayRank) {
  int size;
  POP(size);
  vec.resize(size);
  for (auto &arr : vec) {
    for (auto &val : arr) {
      POP(val);
    }
  }
}
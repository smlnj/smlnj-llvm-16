/// \file codegen.hpp
///
/// \copyright 2023 The Fellowship of SML/NJ (https://smlnj.org)
/// All rights reserved.
///
/// \brief Interface to the code generator library (for testing purposes).
///
/// \author John Reppy
///

#ifndef _CODEGEN_HPP_
#define _CODEGEN_HPP_

#include <string>

enum class output { PrintAsm, AsmFile, ObjFile, Memory, LLVMAsmFile };

// set the target architecture.  This call returns `true` when there
// is an error and `false` otherwise.
//
bool setTarget (std::string const &target);

void codegen (std::string const & src, bool emitLLVM, bool dumpBits, output out);

#endif // !_CODEGEN_HPP_

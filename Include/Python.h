// Entry point of the Python C API.
// C extensions should only #include <Python.h>, and not include directly
// the other Python header files included by <Python.h>.

#ifndef Py_PYTHON_H
#define Py_PYTHON_H

// Since this is a "meta-include" file, "#ifdef __cplusplus / extern "C" {"
// is not needed.


// Include Python header files
#include "patchlevel.h"
#include "pyconfig.h"
#include "pymacconfig.h"


// Include standard header files
#include <assert.h>               // assert()
#include <inttypes.h>             // uintptr_t
#include <limits.h>               // INT_MAX
#include <math.h>                 // HUGE_VAL
#include <stdarg.h>               // va_list
#include <wchar.h>                // wchar_t
#ifdef HAVE_SYS_TYPES_H
#  include <sys/types.h>          // ssize_t
#endif

// <errno.h>, <stdio.h>, <stdlib.h> and <string.h> headers are no longer used
// by Python, but kept for the backward compatibility of existing third party C
// extensions. They are not included by limited C API version 3.11 and newer.
//
// The <ctype.h> and <unistd.h> headers are not included by limited C API
// version 3.13 and newer.
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 < 0x030b0000
#  include <errno.h>              // errno
#  include <stdio.h>              // FILE*
#  include <stdlib.h>             // getenv()
#  include <string.h>             // memcpy()
#endif
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 < 0x030d0000
#  include <ctype.h>              // tolower()
#  ifndef MS_WINDOWS
#    include <unistd.h>           // close()
#  endif
#endif

// gh-111506: The free-threaded build is not compatible with the limited API
// or the stable ABI.
#if defined(Py_LIMITED_API) && defined(Py_GIL_DISABLED)
#  error "The limited API is not currently supported in the free-threaded build"
#endif

#if defined(Py_GIL_DISABLED) && defined(_MSC_VER)
#  include <intrin.h>             // __readgsqword()
#endif

#if defined(Py_GIL_DISABLED) && defined(__MINGW32__)
#  include <intrin.h>             // __readgsqword()
#endif

// Include Python header files
#include "pyport.h"
#include "pymacro.h"
#include "pymath.h"
#include "pymem.h"
#include "pytypedefs.h"
#include "pybuffer.h"
#include "pystats.h"
#include "pyatomic.h"
#include "lock.h"
#include "object.h"
#include "objimpl.h"
#include "typeslots.h"
#include "pyhash.h"
#include "cpython/pydebug.h"
#include "bytearrayobject.h"
#include "bytesobject.h"
#include "unicodeobject.h"
#include "pyerrors.h"
#include "longobject.h"
#include "cpython/longintrepr.h"
#include "boolobject.h"
#include "floatobject.h"
#include "complexobject.h"
#include "rangeobject.h"
#include "memoryobject.h"
#include "tupleobject.h"
#include "listobject.h"
#include "dictobject.h"
#include "cpython/odictobject.h"
#include "enumobject.h"
#include "setobject.h"
#include "methodobject.h"
#include "moduleobject.h"
#include "monitoring.h"
#include "cpython/funcobject.h"
#include "cpython/classobject.h"
#include "fileobject.h"
#include "pycapsule.h"
#include "cpython/code.h"
#include "pyframe.h"
#include "traceback.h"
#include "sliceobject.h"
#include "cpython/cellobject.h"
#include "iterobject.h"
#include "cpython/initconfig.h"
#include "pystate.h"
#include "cpython/genobject.h"
#include "descrobject.h"
#include "genericaliasobject.h"
#include "warnings.h"
#include "weakrefobject.h"
#include "structseq.h"
#include "cpython/picklebufobject.h"
#include "cpython/pytime.h"
#include "codecs.h"
#include "pythread.h"
#include "cpython/context.h"
#include "modsupport.h"
#include "compile.h"
#include "pythonrun.h"
#include "pylifecycle.h"
#include "ceval.h"
#include "sysmodule.h"
#include "osmodule.h"
#include "intrcheck.h"
#include "import.h"
#include "abstract.h"
#include "bltinmodule.h"
#include "critical_section.h"
#include "cpython/pyctype.h"
#include "pystrtod.h"
#include "pystrcmp.h"
#include "fileutils.h"
#include "cpython/pyfpe.h"
#include "cpython/tracemalloc.h"

#define ENABLE_INSTR    1
#define ENABLE_IBPB     0

#define INSTR_DIV                           0 << 8
#define INSTR_SUB                           1 << 8
#define INSTR_EQ                            2 << 8
#define INSTR_EQ_SPEC                       3 << 8
#define INSTR_POW_BASE_SHORT                4 << 8
#define INSTR_POW_COND_SHORT                5 << 8
#define INSTR_POW_ZERO                      6 << 8
#define INSTR_POW_WINDOW					7 << 8
#define INSTR_POW_WINDOW_REST		        8 << 8
#define INSTR_POW_TRAILING					9 << 8
#define INSTR_POW_TRAILING_REST				10 << 8

#if ENABLE_INSTR
PyAPI_DATA(void) *python_opcode_targets[256];
PyAPI_DATA(binaryfunc) python_opcode_binary_op_targets[26];
PyAPI_DATA(void) *python_language_feature_targets[7];

inline __attribute__((always_inline)) uint64_t python_rdtscp(void) {
	uint64_t low, high;
	__asm__ volatile("rdtscp" : "=a"(low), "=d"(high) : : "rbx", "rcx");
	return ((high << 32) | low);
}

PyAPI_DATA(uint64_t) python_opcode_log[1<<16][3];
PyAPI_DATA(uint16_t) python_opcode_log_ctr;
#endif

#endif /* !Py_PYTHON_H */

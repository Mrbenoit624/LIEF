/* Copyright 2017 - 2023 R. Thomas
 * Copyright 2017 - 2023 Quarkslab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <string>
#include <sstream>
#include <nanobind/stl/string.h>
#include <nanobind/stl/map.h>

#include "ELF/pyELF.hpp"

#include "LIEF/ELF/NoteDetails/core/CoreAuxv.hpp"
#include "LIEF/ELF/EnumToString.hpp"

#include "enums_wrapper.hpp"

#define PY_ENUM(x) LIEF::ELF::to_string(x), x

namespace LIEF::ELF::py {

template<>
void create<CoreAuxv>(nb::module_& m) {

  nb::class_<CoreAuxv, NoteDetails> cls(m, "CoreAuxv");
  LIEF::enum_<AUX_TYPE>(cls, "TYPES")
    .value(PY_ENUM(AUX_TYPE::AT_NULL))
    .value(PY_ENUM(AUX_TYPE::AT_IGNORE))
    .value(PY_ENUM(AUX_TYPE::AT_EXECFD))
    .value(PY_ENUM(AUX_TYPE::AT_PHDR))
    .value(PY_ENUM(AUX_TYPE::AT_PHENT))
    .value(PY_ENUM(AUX_TYPE::AT_PHNUM))
    .value(PY_ENUM(AUX_TYPE::AT_PAGESZ))
    .value(PY_ENUM(AUX_TYPE::AT_BASE))
    .value(PY_ENUM(AUX_TYPE::AT_FLAGS))
    .value(PY_ENUM(AUX_TYPE::AT_ENTRY))
    .value(PY_ENUM(AUX_TYPE::AT_NOTELF))
    .value(PY_ENUM(AUX_TYPE::AT_UID))
    .value(PY_ENUM(AUX_TYPE::AT_EUID))
    .value(PY_ENUM(AUX_TYPE::AT_GID))
    .value(PY_ENUM(AUX_TYPE::AT_EGID))
    .value(PY_ENUM(AUX_TYPE::AT_CLKTCK))
    .value(PY_ENUM(AUX_TYPE::AT_PLATFORM))
    .value(PY_ENUM(AUX_TYPE::AT_HWCAP))
    .value(PY_ENUM(AUX_TYPE::AT_HWCAP2))
    .value(PY_ENUM(AUX_TYPE::AT_FPUCW))
    .value(PY_ENUM(AUX_TYPE::AT_DCACHEBSIZE))
    .value(PY_ENUM(AUX_TYPE::AT_ICACHEBSIZE))
    .value(PY_ENUM(AUX_TYPE::AT_UCACHEBSIZE))
    .value(PY_ENUM(AUX_TYPE::AT_IGNOREPPC))
    .value(PY_ENUM(AUX_TYPE::AT_SECURE))
    .value(PY_ENUM(AUX_TYPE::AT_BASE_PLATFORM))
    .value(PY_ENUM(AUX_TYPE::AT_RANDOM))
    .value(PY_ENUM(AUX_TYPE::AT_EXECFN))
    .value(PY_ENUM(AUX_TYPE::AT_SYSINFO))
    .value(PY_ENUM(AUX_TYPE::AT_SYSINFO_EHDR))
    .value(PY_ENUM(AUX_TYPE::AT_L1I_CACHESHAPE))
    .value(PY_ENUM(AUX_TYPE::AT_L1D_CACHESHAPE));

  cls
    .def_prop_rw("values",
        nb::overload_cast<>(&CoreAuxv::values, nb::const_),
        nb::overload_cast<const CoreAuxv::val_context_t&>(&CoreAuxv::values),
        "Current values as a dictionary for which keys are AUXV types"_doc)

    .def("get",
        [] (const CoreAuxv& status, AUX_TYPE atype) -> nb::object {
          bool error;
          const uint64_t val = status.get(atype, &error);
          if (error) {
            return nb::none();
          }
          return nb::int_(val);
        },
        "Return the type value"_doc,
        "type"_a)

    .def("set",
        &CoreAuxv::set,
        "Set type value"_doc,
        "type"_a, "value"_a)

    .def("has",
        &CoreAuxv::has,
        "Check if a value is associated with the given type"_doc,
        "type"_a)

    .def("__getitem__",
        &CoreAuxv::operator[],
        nb::rv_policy::copy)

    .def("__setitem__",
        [] (CoreAuxv& status, AUX_TYPE atype, uint64_t val) {
          status.set(atype, val);
        })

    .def("__contains__", &CoreAuxv::has)

    LIEF_DEFAULT_STR(CoreAuxv);
}
}

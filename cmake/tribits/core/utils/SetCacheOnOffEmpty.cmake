# @HEADER
# ************************************************************************
#
#            TriBITS: Tribal Build, Integrate, and Test System
#                    Copyright 2013 Sandia Corporation
#
# Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
# the U.S. Government retains certain rights in this software.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
# 1. Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
#
# 3. Neither the name of the Corporation nor the names of the
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# ************************************************************************
# @HEADER


#
# @FUNCTION: set_cache_on_off_empty()
#
# Usage::
#
#   set_cache_on_off_empty(<varName> <initialVal> "<docString>" [FORCE])
#
# Sets a special string cache variable with possible values "", "ON", or
# "OFF".  This results in a nice drop-down box in the CMake cache manipulation
# GUIs.
#
function(set_cache_on_off_empty VAR INITIAL_VALUE DOCSTR)
  set(FORCE_ARG)
  foreach(ARG ${ARGN})
    if (ARG STREQUAL FORCE)
      set(FORCE_ARG FORCE)
    else()
      message(FATAL_ERROR "set_cache_on_off_empty(...): Error, last arg '${ARG}' is"
        "invalid!  Must be 'FORCE' or nothing." )
    endif()
  endforeach()
  set( ${VAR} "${INITIAL_VALUE}" CACHE STRING "${DOCSTR}" ${FORCE_ARG})
  set_property(CACHE ${VAR} PROPERTY STRINGS "" "ON" "OFF")
endfunction()

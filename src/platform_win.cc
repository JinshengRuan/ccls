// Copyright 2017-2018 ccls Authors
// SPDX-License-Identifier: Apache-2.0

#if defined(_WIN32)
#include "platform.hh"

#include "utils.hh"

#include <Windows.h>
#include <direct.h>
#include <fcntl.h>
#include <io.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <algorithm>
#include <string>
#include <thread>

std::string NormalizePath(const std::string &path) {
  DWORD retval = 0;
  TCHAR buffer[MAX_PATH] = TEXT("");
  TCHAR **lpp_part = {NULL};

  std::string result;
  retval = GetFullPathName(path.c_str(), MAX_PATH, buffer, lpp_part);
  // fail, return original
  if (retval == 0)
    result = path;
  else
    result = buffer;

  std::replace(result.begin(), result.end(), '\\', '/');
  // Normalize drive letter.
  if (result.size() > 1 && result[0] >= 'a' && result[0] <= 'z' &&
      result[1] == ':')
    result[0] = toupper(result[0]);
  return result;
}

void FreeUnusedMemory() {}

// TODO Wait for debugger to attach
void TraceMe() {}

std::string GetExternalCommandOutput(const std::vector<std::string> &command,
                                     std::string_view input) {
  return "";
}

void SpawnThread(void *(*fn)(void *), void *arg) {
  std::thread(fn, arg).detach();
}

#endif

// ----------------------------------------------------------------------------
// SOSpin Library
// Copyright (C) 2015,2023 SOSpin Project
//
//   Authors:
//
//     Nuno Cardoso (nuno.cardoso@tecnico.ulisboa.pt)
//     David Emmanuel-Costa (david.costa@tecnico.ulisboa.pt)
//     Nuno Gonçalves (nunogon@deec.uc.pt)
//     Catarina Simoes (csimoes@ulg.ac.be)
//
// ----------------------------------------------------------------------------
// This file is part of SOSpin Library.
//
// SOSpin Library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or any
// later version.
//
// SOSpin Library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SOSpin Library.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

//       son.cpp created on 27/02/2015
//
//      This file is an integrant part of the SOSpin Library.
//
//      Revision 1.1 28/02/2015 23:19:29 david
//      License updated
//      Revision 1.2 12/09/2023 16:53:51 david

/*!
  \file
  \brief Main Sospin header file. Includes C++ macros, to simplify expression writing, B operator, Verbosity level and memory usage.
*/

#include <sospin/son.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace sospin {

static int GroupDim = 10;  // default value
static Verbosity verbose_flag = SUMMARIZE;

void setDim(int n) {
  GroupDim = n;
  cout << "Setting group dimension to " << GroupDim << endl;
}

int getDim() {
  return GroupDim;
}

bool GroupEven() {
  bool a = false;
  if (GroupDim % 2 == 0) a = true;
  return a;
}

void CleanGlobalDecl() {
  form.clear();
  tabids.clear();
}

void setVerbosity(Verbosity verb) {
  verbose_flag = verb;
}

Verbosity getVerbosity() {
  return verbose_flag;
}

/*!\brief Operator B, "charge conjugation" matrix for SO(2N) spinor representations

  \param startid the algebraic indexes are written as startid_? (optional, default startid="i")

  \f{eqnarray*}{

    B = \Pi_{\mu=odd}\Gamma_\mu = \frac{(-i)^N}{N!} \varepsilon_{i_1,...,i_N} \Pi_{k=1}^N \left(b_{i_k}-b^\dagger_{i_k}\right)

  \f}

*/
Braket Bop(string startid) {
  Braket b0, b1;
  b0 = bb(startid + "1");
  b0 -= bbt(startid + "1");
  string constpart0 = "*e_(" + startid + "1";
  string constpart;
  if ((getDim() / 2) % 2 == 0)
    constpart = "1/";
  else
    constpart = "i_/";
  int factorn = 1;
  for (int i = 2; i <= getDim() / 2; i++) {
    string idx = startid + ToString<int>(i);
    b1 = bb(idx);
    b1 -= bbt(idx);
    b0 = b0 * b1;
    constpart0 += ",";
    constpart0 += idx;
    factorn *= i;
  }
  constpart += ToString<int>(factorn) + constpart0 + ")";
  if ((getDim() / 2) % 4 == 0 || (getDim() / 2) % 4 == 3)
    b0 = b0 * constpart;
  else
    b0 = -b0 * constpart;
  return b0;
}

/*!\brief Operator B, charge conjugation matrix for SO(2N) spinor representations

  \f{eqnarray*}{

    B = \Pi_{\mu=odd}\Gamma_\mu = (-i)^N \Pi_{k=1}^N \left(b_k-b^\dagger_k\right)

  \f}

*/

Braket BopIdnum() {
  Braket b0, b1;
  b0 = bb(1);
  b0 -= bbt(1);
  for (int i = 2; i <= getDim() / 2; i++) {
    b1 = bb(i);
    b1 -= bbt(i);
    b0 = b0 * b1;
  }
  string constpart;
  if ((getDim() / 2) % 2 == 0)
    constpart = "1";
  else
    constpart = "i_";
  if ((getDim() / 2) % 4 == 0 || (getDim() / 2) % 4 == 3)
    b0 = b0 * constpart;
  else
    b0 = -b0 * constpart;
  return b0;
}

ostream& operator<<(ostream& out, const Verbosity& a) {
  switch (a) {
    case SILENT:
      out << "SILENT";
      break;
    case SUMMARIZE:
      out << "SUMMARIZE";
      break;
    case VERBOSE:
      out << "VERBOSE";
      break;
    case DEBUG_VERBOSE:
      out << "DEBUG_VERBOSE";
      break;
    default:
      out << "Not defined";
      break;
  }
  return out;
}

}  // namespace sospin

#include <unistd.h>

#include <fstream>
#include <ios>
#include <iostream>
#include <string>

namespace sospin {

// FROM: http://nadeausoftware.com/articles/2012/07/c_c_tip_how_get_process_resident_set_size_physical_memory_use

/*
 * Author:  David Robert Nadeau
 * Site:    http://NadeauSoftware.com/
 * License: Creative Commons Attribution 3.0 Unported License
 *          http://creativecommons.org/licenses/by/3.0/deed.en_US
 */

#if defined(_WIN32)
#include <psapi.h>
#include <windows.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/resource.h>
#include <unistd.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <mach/mach.h>

#elif (defined(_AIX) || defined(__TOS__AIX__)) || (defined(__sun__) || defined(__sun) || defined(sun) && (defined(__SVR4) || defined(__svr4__)))
#include <fcntl.h>
#include <procfs.h>

#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
#include <stdio.h>

#endif

#else
#error "Cannot define getPeakRSS( ) or getCurrentRSS( ) for an unknown OS."
#endif

/**
 * Returns the peak (maximum so far) resident set size (physical
 * memory use) measured in bytes, or zero if the value cannot be
 * determined on this OS.
 */
size_t getPeakRSS() {
#if defined(_WIN32)
  /* Windows -------------------------------------------------- */
  PROCESS_MEMORY_COUNTERS info;
  GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
  return (size_t)info.PeakWorkingSetSize;

#elif (defined(_AIX) || defined(__TOS__AIX__)) || (defined(__sun__) || defined(__sun) || defined(sun) && (defined(__SVR4) || defined(__svr4__)))
  /* AIX and Solaris ------------------------------------------ */
  struct psinfo psinfo;
  int fd = -1;
  if ((fd = open("/proc/self/psinfo", O_RDONLY)) == -1)
    return (size_t)0L; /* Can't open? */
  if (read(fd, &psinfo, sizeof(psinfo)) != sizeof(psinfo)) {
    close(fd);
    return (size_t)0L; /* Can't read? */
  }
  close(fd);
  return (size_t)(psinfo.pr_rssize * 1024L);

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
  /* BSD, Linux, and OSX -------------------------------------- */
  struct rusage rusage;
  getrusage(RUSAGE_SELF, &rusage);
#if defined(__APPLE__) && defined(__MACH__)
  return (size_t)rusage.ru_maxrss;
#else
  return (size_t)(rusage.ru_maxrss * 1024L);
#endif

#else
  /* Unknown OS ----------------------------------------------- */
  return (size_t)0L; /* Unsupported. */
#endif
}

/**
 * Returns the current resident set size (physical memory use) measured
 * in bytes, or zero if the value cannot be determined on this OS.
 */
size_t getCurrentRSS() {
#if defined(_WIN32)
  /* Windows -------------------------------------------------- */
  PROCESS_MEMORY_COUNTERS info;
  GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
  return (size_t)info.WorkingSetSize;

#elif defined(__APPLE__) && defined(__MACH__)
  /* OSX ------------------------------------------------------ */
  struct mach_task_basic_info info;
  mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
  if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO,
                (task_info_t)&info, &infoCount) != KERN_SUCCESS)
    return (size_t)0L; /* Can't access? */
  return (size_t)info.resident_size;

#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
  /* Linux ---------------------------------------------------- */
  long rss = 0L;
  FILE* fp = NULL;
  if ((fp = fopen("/proc/self/statm", "r")) == NULL)
    return (size_t)0L; /* Can't open? */
  if (fscanf(fp, "%*s%ld", &rss) != 1) {
    fclose(fp);
    return (size_t)0L; /* Can't read? */
  }
  fclose(fp);
  return (size_t)rss * (size_t)sysconf(_SC_PAGESIZE);

#else
  /* AIX, BSD, Solaris, and Unknown OS ------------------------ */
  return (size_t)0L; /* Unsupported. */
#endif
}

/**
 * Prints memory stats (current and peak resident set size) in MB.
 */
void print_process_mem_usage() {
  cout << "===============================================================" << endl;
  cout << "RSS: " << getCurrentRSS() / (1024. * 1024.) << " (MB); RSS_Peak: " << getPeakRSS() / (1024. * 1024.) << " (MB)" << endl;
  cout << "===============================================================" << endl;
}

}  // namespace sospin

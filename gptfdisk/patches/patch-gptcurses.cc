$NetBSD$

Use inttypes.h for printing 64 bit numbers compatibly
ncurses/ instead of ncursesw/ in NetBSD10

--- gptcurses.cc.orig	2024-02-19 19:55:41.000000000 -0500
+++ gptcurses.cc	2025-01-23 19:18:47.298098980 -0500
@@ -23,13 +23,14 @@
 #include <iostream>
 #include <string>
 #include <sstream>
-#if defined (__APPLE__) || (__FreeBSD__)
+#if defined (__APPLE__) || (__FreeBSD__) || (__NetBSD__)
 #include <ncurses.h>
 #else
 #include <ncursesw/ncurses.h>
 #endif
 #include "gptcurses.h"
 #include "support.h"
+#include <inttypes.h>
 
 using namespace std;
 
@@ -333,13 +334,13 @@
    printw("Partition GUID code: %s (%s)\n", partitions[partNum].GetType().AsString().c_str(),
           partitions[partNum].GetTypeName().c_str());
    printw("Partition unique GUID: %s\n", partitions[partNum].GetUniqueGUID().AsString().c_str());
-   printw("First sector: %llu (at %s)\n", (long long unsigned int) partitions[partNum].GetFirstLBA(),
+   printw("First sector: %" PRIu64" (at %s)\n", (uint64_t) partitions[partNum].GetFirstLBA(),
           BytesToIeee(partitions[partNum].GetFirstLBA(), blockSize).c_str());
-   printw("Last sector: %llu (at %s)\n", (long long unsigned int) partitions[partNum].GetLastLBA(),
+   printw("Last sector: %" PRIu64" (at %s)\n", (uint64_t) partitions[partNum].GetLastLBA(),
           BytesToIeee(partitions[partNum].GetLastLBA(), blockSize).c_str());
    size = partitions[partNum].GetLastLBA() - partitions[partNum].GetFirstLBA() + 1;
-   printw("Partition size: %llu sectors (%s)\n", (long long unsigned int) size, BytesToIeee(size, blockSize).c_str());
-   printw("Attribute flags: %016llx\n", (long long unsigned int) partitions[partNum].GetAttributes().GetAttributes());
+   printw("Partition size: %" PRIu64 " sectors (%s)\n", (uint64_t) size, BytesToIeee(size, blockSize).c_str());
+   printw("Attribute flags: %016" PRIX64 "\n", (uint64_t) partitions[partNum].GetAttributes().GetAttributes());
    #ifdef USE_UTF16
    partitions[partNum].GetDescription().extract(0, NAME_SIZE , temp, NAME_SIZE );
    printw("Partition name: '%s'\n", temp);
@@ -447,8 +448,8 @@
       clrtoeol();
       newFirstLBA = currentSpace->firstLBA;
       Align(&newFirstLBA);
-      printw("First sector (%llu-%llu, default = %llu): ", (long long unsigned int) newFirstLBA,
-             (long long unsigned int) currentSpace->lastLBA, (long long unsigned int) newFirstLBA);
+      printw("First sector (%" PRIu64 "-%" PRIu64 ", default = %" PRIu64 "): ", (uint64_t) newFirstLBA,
+             (uint64_t) currentSpace->lastLBA, (uint64_t) newFirstLBA);
       echo();
       getnstr(inLine, 79);
       noecho();
@@ -462,7 +463,7 @@
    while ((newLastLBA > currentSpace->lastLBA) || (newLastLBA < newFirstLBA)) {
       move(LINES - 3, 0);
       clrtoeol();
-      printw("Size in sectors or {KMGTP} (default = %llu): ", (long long unsigned int) size);
+      printw("Size in sectors or {KMGTP} (default = %" PRIu64 "): ", (uint64_t) size);
       echo();
       getnstr(inLine, 79);
       noecho();

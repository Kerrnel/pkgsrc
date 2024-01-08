$NetBSD$

Change to netbsd compiler friendliness lld -> lu, llx -> lux

--- gptcurses.cc.orig	2022-04-14 23:17:12.000000000 +0000
+++ gptcurses.cc
@@ -333,13 +333,13 @@ void GPTDataCurses::ShowInfo(int partNum
    printw("Partition GUID code: %s (%s)\n", partitions[partNum].GetType().AsString().c_str(),
           partitions[partNum].GetTypeName().c_str());
    printw("Partition unique GUID: %s\n", partitions[partNum].GetUniqueGUID().AsString().c_str());
-   printw("First sector: %lld (at %s)\n", partitions[partNum].GetFirstLBA(),
+   printw("First sector: %lu (at %s)\n", partitions[partNum].GetFirstLBA(),
           BytesToIeee(partitions[partNum].GetFirstLBA(), blockSize).c_str());
-   printw("Last sector: %lld (at %s)\n", partitions[partNum].GetLastLBA(),
+   printw("Last sector: %lu (at %s)\n", partitions[partNum].GetLastLBA(),
           BytesToIeee(partitions[partNum].GetLastLBA(), blockSize).c_str());
    size = partitions[partNum].GetLastLBA() - partitions[partNum].GetFirstLBA() + 1;
-   printw("Partition size: %lld sectors (%s)\n", size, BytesToIeee(size, blockSize).c_str());
-   printw("Attribute flags: %016llx\n", partitions[partNum].GetAttributes().GetAttributes());
+   printw("Partition size: %lu sectors (%s)\n", size, BytesToIeee(size, blockSize).c_str());
+   printw("Attribute flags: %016lux\n", partitions[partNum].GetAttributes().GetAttributes());
    #ifdef USE_UTF16
    partitions[partNum].GetDescription().extract(0, NAME_SIZE , temp, NAME_SIZE );
    printw("Partition name: '%s'\n", temp);
@@ -447,7 +447,7 @@ void GPTDataCurses::MakeNewPart(void) {
       clrtoeol();
       newFirstLBA = currentSpace->firstLBA;
       Align(&newFirstLBA);
-      printw("First sector (%lld-%lld, default = %lld): ", newFirstLBA, currentSpace->lastLBA, newFirstLBA);
+      printw("First sector (%lu-%lu, default = %lu): ", newFirstLBA, currentSpace->lastLBA, newFirstLBA);
       echo();
       getnstr(inLine, 79);
       noecho();
@@ -461,7 +461,7 @@ void GPTDataCurses::MakeNewPart(void) {
    while ((newLastLBA > currentSpace->lastLBA) || (newLastLBA < newFirstLBA)) {
       move(LINES - 3, 0);
       clrtoeol();
-      printw("Size in sectors or {KMGTP} (default = %lld): ", size);
+      printw("Size in sectors or {KMGTP} (default = %lu): ", size);
       echo();
       getnstr(inLine, 79);
       noecho();

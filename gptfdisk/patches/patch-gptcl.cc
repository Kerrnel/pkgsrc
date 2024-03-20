$NetBSD$

(Unused numOptions removed)

Make device string to LoadPartitions mutable to let it
 auto-convert to the character version of a block device

--- gptcl.cc.orig	2024-02-19 19:55:41.000000000 -0500
+++ gptcl.cc	2024-03-20 01:22:30.041041528 -0400
@@ -65,7 +65,7 @@
 // 8 = disk replication operation (-R) failed
 int GPTDataCL::DoOptions(int argc, char* argv[]) {
    GPTData secondDevice;
-   int opt, numOptions = 0, saveData = 0, neverSaveData = 0;
+   int opt, saveData = 0, neverSaveData = 0;
    int partNum = 0, newPartNum = -1, saveNonGPT = 1, retval = 0, pretend = 0;
    int byteSwapPartNum = 0;
    uint64_t low, high, startSector, endSector, sSize, mainTableLBA, secondTableLBA;
@@ -153,7 +153,6 @@
          default:
             break;
       } // switch
-      numOptions++;
    } // while
 
    // Assume first non-option argument is the device filename....
@@ -164,7 +163,8 @@
       poptResetContext(poptCon);
       JustLooking(); // reset as necessary
       BeQuiet(); // Tell called functions to be less verbose & interactive
-      if (LoadPartitions((string) device)) {
+      string devstr = device;
+      if (LoadPartitions(devstr)) {
          if ((WhichWasUsed() == use_mbr) || (WhichWasUsed() == use_bsd))
             saveNonGPT = 0; // flag so we don't overwrite unless directed to do so
          sSize = GetBlockSize();

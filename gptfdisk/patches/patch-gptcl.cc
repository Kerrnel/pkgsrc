$NetBSD$

Maybe a no-op in progress to mutable device path

--- gptcl.cc.orig	2022-04-14 23:17:12.000000000 +0000
+++ gptcl.cc
@@ -161,7 +161,8 @@ int GPTDataCL::DoOptions(int argc, char*
    if (device != NULL) {
       JustLooking(); // reset as necessary
       BeQuiet(); // Tell called functions to be less verbose & interactive
-      if (LoadPartitions((string) device)) {
+      string devstr = device;
+      if (LoadPartitions(devstr)) {
          if ((WhichWasUsed() == use_mbr) || (WhichWasUsed() == use_bsd))
             saveNonGPT = 0; // flag so we don't overwrite unless directed to do so
          sSize = GetBlockSize();

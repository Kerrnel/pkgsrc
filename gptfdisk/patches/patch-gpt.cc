$NetBSD$

Switch from chosen block to raw (character) device automagically for the user on NetBSD

--- gpt.cc.orig	2024-02-19 19:55:41.000000000 -0500
+++ gpt.cc	2024-03-20 01:07:47.883983159 -0400
@@ -836,11 +836,25 @@
 } // GPTData::PartitionScan()
 
 // Read GPT data from a disk.
-int GPTData::LoadPartitions(const string & deviceFilename) {
+int GPTData::LoadPartitions(string & deviceFilename) {
    BSDData bsdDisklabel;
    int err, allOK = 1;
    MBRValidity mbrState;
 
+#ifdef		__NetBSD__	// Always use character device if given block
+   // Convert /dev/wd0 to /dev/rwd0
+   size_t start_pos = deviceFilename.find("/dev/");
+   if (start_pos == 0)
+   {
+      start_pos = deviceFilename.find("/dev/r");
+      if (start_pos == std::string::npos)
+      {
+         deviceFilename.replace(0, 5, string("/dev/r"));
+         cout << "Using character device at " << deviceFilename.c_str() << "\n";
+      }
+   }
+#endif	//	__NetBSD__
+
    if (!justLooking) {
       if (myDisk.OpenForRead(deviceFilename)) {
          err = myDisk.OpenForWrite(deviceFilename);

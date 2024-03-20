$NetBSD$

Moved Add NetBSD to list of non-64-ending stat function OSes
(I think FreeBSD/OpenBSD as well ... but they have maintainers)

--- diskio-unix.cc.orig	2024-03-20 02:29:15.444855783 -0400
+++ diskio-unix.cc	2024-03-20 02:31:28.663900580 -0400
@@ -37,7 +37,7 @@
 
 using namespace std;
 
-#if defined(__APPLE__) || defined(__linux__)
+#if defined(__APPLE__) || defined(__linux__) || defined(__NetBSD__)
 #define off64_t off_t
 #define stat64 stat
 #define fstat64 fstat
@@ -261,7 +261,7 @@
 // (Note that for most OSes, the default of 0 is returned because I've not yet
 // looked into how to test for success in the underlying system calls...)
 int DiskIO::DiskSync(void) {
-   int i, retval = 0, platformFound = 0;
+   int retval = 0, platformFound = 0;
 
    // If disk isn't open, try to open it....
    if (!isOpen) {
@@ -277,15 +277,15 @@
                * it definitely will get things on disk though:
                * http://topiks.org/mac-os-x/0321278542/ch12lev1sec8.html */
 #ifdef __sun__
-      i = ioctl(fd, DKIOCFLUSHWRITECACHE);
+      int i = ioctl(fd, DKIOCFLUSHWRITECACHE);
 #else
-      i = ioctl(fd, DKIOCSYNCHRONIZECACHE);
+      int i = ioctl(fd, DKIOCSYNCHRONIZECACHE);
 #endif
       platformFound++;
 #endif
 #if defined (__FreeBSD__) || defined (__FreeBSD_kernel__)
       sleep(2);
-      i = ioctl(fd, DIOCGFLUSH);
+      int i = ioctl(fd, DIOCGFLUSH);
       cout << "Warning: The kernel may continue to use old or deleted partitions.\n"
            << "You should reboot or remove the drive.\n";
       platformFound++;
@@ -293,7 +293,7 @@
 #ifdef __linux__
       sleep(1); // Theoretically unnecessary, but ioctl() fails sometimes if omitted....
       fsync(fd);
-      i = ioctl(fd, BLKRRPART);
+      int i = ioctl(fd, BLKRRPART);
       if (i) {
          cout << "Warning: The kernel is still using the old partition table.\n"
               << "The new table will be used at the next reboot or after you\n"

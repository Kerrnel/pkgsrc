$NetBSD$

Moved Add NetBSD to list of non-64-ending stat function OSes

Auto change /dev/wd0 -> /dev/rwd0 since /dev/wd0 always returns ERRNO 16 on open

(I think FreeBSD/OpenBSD as well ... but they have maintainers)

--- diskio-unix.cc.orig	2024-02-19 19:55:41.000000000 -0500
+++ diskio-unix.cc	2025-01-23 19:56:28.136385316 -0500
@@ -37,7 +37,7 @@
 
 using namespace std;
 
-#if defined(__APPLE__) || defined(__linux__)
+#if defined(__APPLE__) || defined(__linux__) || defined(__NetBSD__)
 #define off64_t off_t
 #define stat64 stat
 #define fstat64 fstat
@@ -85,7 +85,7 @@
          if (fstat64(fd, &st) == 0) {
             if (S_ISDIR(st.st_mode))
                cerr << "The specified path is a directory!\n";
-#if !(defined(__FreeBSD__) || defined(__FreeBSD_kernel__)) \
+#if !(defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__)) \
                        && !defined(__APPLE__)
             else if (S_ISCHR(st.st_mode))
                cerr << "The specified path is a character device!\n";
@@ -174,7 +174,7 @@
       if (err == 0)
           blockSize = minfo.dki_lbsize;
 #endif
-#if defined (__FreeBSD__) || defined (__FreeBSD_kernel__)
+#if defined (__FreeBSD__) || defined (__FreeBSD_kernel__) || defined(__NetBSD__)
       err = ioctl(fd, DIOCGSECTORSIZE, &blockSize);
 #endif
 #ifdef __linux__
@@ -283,11 +283,11 @@
 #endif
       platformFound++;
 #endif
-#if defined (__FreeBSD__) || defined (__FreeBSD_kernel__)
+#if defined (__FreeBSD__) || defined (__FreeBSD_kernel__) || defined (__NetBSD__)
       sleep(2);
-      i = ioctl(fd, DIOCGFLUSH);
+      i = ioctl(fd, DIOCCACHESYNC);
       cout << "Warning: The kernel may continue to use old or deleted partitions.\n"
-           << "You should reboot or remove the drive.\n";
+           << "You should reboot or remove the drive. (" << i << ")\n";
       platformFound++;
 #endif
 #ifdef __linux__
@@ -460,7 +460,7 @@
           sectors = minfo.dki_capacity;
       platformFound++;
 #endif
-#if defined (__FreeBSD__) || defined (__FreeBSD_kernel__)
+#if defined (__FreeBSD__) || defined (__FreeBSD_kernel__) || defined(__NetBSD__)
       *err = ioctl(fd, DIOCGMEDIASIZE, &bytes);
       long long b = GetBlockSize();
       sectors = bytes / b;

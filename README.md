Compile:
=======
		$ make
		[dep] src/main.cc ...
		[dep] src/DL.cc ...
		[dep] src/utils.cc ...
		[dep] src/debugutils.cc ...
		[cc] src/utils.cc ...
		[cc] src/debugutils.cc ...
		[cc] src/main.cc ...
		[cc] src/DL.cc ...
		mkdir: created directory ‘bin’
		Linking ...
		done.

Algorithm:
=========
首先將數獨問題轉化爲exact cover問題(http://en.wikipedia.org/wiki/Exact_cover)
然後利用Donald E. Knuth提出的Algorithm X求解(http://en.wikipedia.org/wiki/Knuth's_Algorithm_X)
	求解思路爲,對於當前已選擇的行,刪除行中所有1所在的列,及這些列中的1所在的行,再進行遞歸搜索.
	搜索失敗則回溯,選擇另外的行.
Algorithm X的實現利用了Knuth提出的Dancing Links算法(http://en.wikipedia.org/wiki/Dancing_Links).
	實現原理大致爲,將所有“1”利用雙向十字鏈表相連,快速的維護刪除及還原的操作,以保證遞歸回溯時的效率.


Efficiency:
=========
test 目錄中包含91個網上找到的比較難的測試數據.
通過`make test`命令調用腳本進行測試,均可以瞬間出解.
$ make test
real    0m0.002s
user    0m0.000s
sys     0m0.000s

real    0m0.002s
user    0m0.000s
sys     0m0.000s

real    0m0.002s
user    0m0.000s
sys     0m0.000s
....


Memory:
======

$ cat /proc/$(pgrep main)/status |grep 'VmHWM'
VmHWM:      1380 kB
程序大約佔用1~2M物理內存.

用valgrind檢查,無內存泄漏
$ valgrind --leak-check=full --track-origins=yes --show-reachable=yes bin/main test1.txt /tmp/out                                                                                                                                           1
==1054== Memcheck, a memory error detector
==1054== Copyright (C) 2002-2012, and GNU GPL'd, by Julian Seward et al.
==1054== Using Valgrind-3.8.1 and LibVEX; rerun with -h for copyright info
==1054== Command: bin/main test1.txt /tmp/out
==1054==
==1054==
==1054== HEAP SUMMARY:
==1054==     in use at exit: 0 bytes in 0 blocks
==1054==   total heap usage: 974 allocs, 974 frees, 6,345,900 bytes allocated
==1054==
==1054== All heap blocks were freed -- no leaks are possible
==1054==
==1054== For counts of detected and suppressed errors, rerun with: -v
==1054== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)

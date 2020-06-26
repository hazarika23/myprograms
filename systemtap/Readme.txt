1. Following packages need to be install
	- systemtap
	- systemtap-client
	- systemtap-devel
	- systemtap-runtime

2. Systemtap setup testing can be done using the following command.

[root@localhost systemtap]# stap -v -e 'probe vfs.read {printf("read performed\n"); exit()}'

Pass 1: parsed user script and 483 library scripts using 356160virt/130128res/9132shr/120592data kb, in 560usr/90sys/1014real ms.
Pass 2: analyzed script: 2 probes, 1 function, 5 embeds, 0 globals using 596708virt/369348res/8132shr/361140data kb, in 5790usr/2740sys/33314real ms.
Pass 3: translated to C into "/tmp/stapidXEaV/stap_fe1402fe2b7cfe9352ec7299b8c1966c_2807_src.c" using 596708virt/369752res/8536shr/361140data kb, in 30usr/10sys/167real ms.
Pass 4: compiled C into "stap_fe1402fe2b7cfe9352ec7299b8c1966c_2807.ko" in 22090usr/3460sys/31740real ms.
Pass 5: starting run.
read performed
Pass 5: run completed in 20usr/60sys/708real ms.
[root@localhost systemtap]# 

3. Find the kernel function with their file name and line number.  
[root@localhost systemtap]# stap -l 'kernel.function("*")' | sort | grep inode | head
kernel.function("__address_space_init_once@fs/inode.c:368")
kernel.function("address_space_init_once@fs/inode.c:377")
kernel.function("alloc_anon_inode@fs/libfs.c:1218")
kernel.function("alloc_inode@fs/inode.c:226")
kernel.function("anon_inodefs_dname@fs/anon_inodes.c:33")
kernel.function("anon_inodefs_init_fs_context@fs/anon_inodes.c:43")
kernel.function("anon_inode_getfd@fs/anon_inodes.c:125")
kernel.function("anon_inode_getfile@fs/anon_inodes.c:74")
kernel.function("atime_needs_update@fs/inode.c:1707")
kernel.function("audit_copy_inode@kernel/auditsc.c:1920")
[root@localhost systemtap]# 

4. For one function
[root@localhost systemtap]# stap -L 'kernel.function("vfs_read")'
kernel.function("vfs_read@fs/read_write.c:446")
[root@localhost systemtap]# 

5.
stap -p2 -e 'probe kernel.function("*") {}' | sort | uniq


6.
// Generating Instrumentation for Other Computers

step 1: stap -r kernel_version script -m module_name
	- kernel_version refers to the version of the target kernel 
	- script refers to the script to be converted into the instrumentation module
	- module_name is the desired name of the instrumentation module
step2:
	- Once the instrumentation module is compiled, copy it to the target system and then load it using.
	$staprun module_name.ko
e.g: 	$stap -r 2.6.18-92.1.10.el5 -e 'probe vfs.read {exit()}' -m simple
     	$staprun simple.ko



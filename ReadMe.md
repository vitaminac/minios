# Mini Operating System From Zero

## WSL Dev Environment Setup

    sudo apt update
    sudo apt install build-essential nasm gcc g++ gdb qemu qemu-system-x86

## Debug

Run **make debug** and then you can use any gdb command.

### gdb commands

#### break

* **b main**: puts a breakpoint at the symbol main
* **b f:N**: puts a breakpoint at the line N of file **f**

#### continue

* **c**: continues running the program until the next breakpoint or error

#### info break

* **info break**: list breakpoints

#### del

* **del N**: remove break point **N**

#### step

* **s**: runs the next line of the program

#### next

* **n**: Like **s**, but it does not step into functions

#### print

* **p var**: print the current value of the variable **var**.

#### finish

* **finish**: Runs until the current function is finished

#### list

* **list**: print more lines

#### quit

* **q**: quits gdb

### VNC

You can access the remote desktop with VNC viewer connecting to "localhost:5900".

## Tutorial

- [x] [Writing a Simple Operating System from Scratch](http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
- [x] [os-tutorial](https://github.com/cfenollosa/os-tutorial)
- [ ] [Kmalloc Internals: Exploring Linux Kernel Memory Allocation](http://www.jikos.cz/jikos/Kmalloc_Internals.html)
- [ ] [JamesM's kernel development tutorials](http://www.jamesmolloy.co.uk/tutorial_html/index.html)
- [ ] [The little book about OS development](https://littleosbook.github.io/)
- [ ] [Operating Systems: From 0 to 1](https://tuhdo.github.io/os01/)
- [ ] [30 day Make OS](https://github.com/yourtion/30dayMakeOS)
- [ ] [Writing an OS in Rust](https://os.phil-opp.com/)
- [ ] [Write an OS running on a CPU that complies with RISC V in Rust (CPU experiment sideshow)](https://gist.github.com/cb372/5f6bf16ca0682541260ae52fc11ea3bb)
- [ ] [Shichao's Notes](https://notes.shichao.io)
- [ ] [How to write a simple operating system](http://mikeos.sourceforge.net/write-your-own-os.html)
- [ ] [Operating Systems Study Guide](http://faculty.salina.k-state.edu/tim/ossg)
- [ ] [Operating Systems Course Notes Main Page](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/)

## Course

- [ ] [Harvard CS 61: Systems Programming and Machine Organization - WeensyOS](https://cs61.seas.harvard.edu/site/2019/)
- [ ] [Harvard CS 161: Operating Systems - Chickadee OS](https://read.seas.harvard.edu/cs161/2020/)
- [ ] [MIT 6.S081 2020: Operating System Engineering - xv6-riscv](https://pdos.csail.mit.edu/6.828/2020/)
- [ ] [MIT 6.S081 2018: Operating System Engineering - xv6-x86](https://pdos.csail.mit.edu/6.828/2018/)
- [ ] [Stanford CS 140: Operating Systems - PintOS](http://web.stanford.edu/~ouster/cgi-bin/cs140-spring20/index.php)
- [ ] [THU Operating Systems - rCore OS](http://os.cs.tsinghua.edu.cn/oscourse/OS2020spring)
- [ ] [Udacity: GT Introduction to Operating Systems](https://www.udacity.com/course/introduction-to-operating-systems--ud923)
- [ ] [Udacity: GT Refresher - Advanced OS](https://www.udacity.com/course/gt-refresher-advanced-os--ud098)
- [ ] [Udacity: GT Advanced Operating Systems](https://www.udacity.com/course/advanced-operating-systems--ud189)
- [ ] [Udacity: GT Embedded Systems](https://www.udacity.com/course/embedded-systems--ud169)
- [ ] [UIC CS385: Operating Systems](https://cs385.class.uic.edu/)
- [ ] [操作系统原理(Operating Systems)](https://www.coursera.org/learn/os-pku)
- [ ] [Carnegie Mellon 15-410: Operating System Design and Implementation](https://www.cs.cmu.edu/~410/)
- [ ] [CS401: Operating Systems](https://learn.saylor.org/course/CS401)
- [ ] [ILLINOIS URBANA-CHAMPAIGN ECE 391: Computer Systems Engineering](https://courses.grainger.illinois.edu/ece391)
- [ ] [UPM: Sistemas Operativos Avanzados](http://laurel.datsi.fi.upm.es/docencia/asignaturas/soa)
- [ ] [UPM: Sistemas Empotrados y Ubicuos](http://www.datsi.fi.upm.es/docencia/SEUM/)

## Book

- [ ] [Computer Systems: A Programmer's Perspective](https://csapp.cs.cmu.edu/)
- [ ] [Operating Systems: Three Easy Pieces](http://pages.cs.wisc.edu/~remzi/OSTEP/)
- [ ] [Operating Systems: Principles and Practice](http://ospp.cs.washington.edu/)
- [ ] Operating Systems: Internals and Design Principles
- [ ] Operating System Concepts
- [ ] The Design of the UNIX Operating System
- [ ] Understanding The Linux Kernel
- [ ] Linux Kernel Development
- [ ] The Essentials of Computer Organization and Architecture
- [ ] Windows Internals
- [ ] Operating Systems: Design and Implementation
- [ ] Modern Operating Systems
- [ ] Distributed Systems: Principles and Paradigms
- [ ] The C Programming Language
- [ ] [Linux Device Drivers](https://lwn.net/Kernel/LDD3/)
- [ ] 一个64位操作系统的设计与实现

## Source Code

* [Linux 0.01](https://mirrors.edge.kernel.org/pub/linux/kernel/Historic/)
* [elfboot](https://github.com/croemheld/elfboot)
* [Busybox](https://git.busybox.net/busybox/)
* [MS DOS](https://github.com/microsoft/MS-DOS)
* [Biscuit research OS](https://github.com/mit-pdos/biscuit)
* [WSL2](https://github.com/microsoft/WSL2-Linux-Kernel)
* [Boot OS](https://github.com/nanochess/bootOS)
* [IncludeOS](https://github.com/includeos/IncludeOS)
* [BareMetal-OS-legacy](https://github.com/ReturnInfinity/BareMetal-OS-legacy)
* [darwin-xnu](https://github.com/apple/darwin-xnu)
* [Windows Research Kernel WRK v1.2](http://gate.upm.ro/os/LABs/Windows_OS_Internals_Curriculum_Resource_Kit-ACADEMIC/WindowsResearchKernel-WRK/)
* [Reactos](https://github.com/reactos/reactos)
* [FreeBSD](https://github.com/freebsd/freebsd)
* [OpenBSD](https://www.openbsd.org/)
* [Minix 3](http://gerrit.minix3.org)
* [OpenHarmony](https://gitee.com/openharmony)
* [TencentOS-tiny](https://github.com/Tencent/TencentOS-tiny)
* [RT-Thread](https://github.com/RT-Thread/rt-thread)
* [Grub2](https://www.gnu.org/software/grub/grub-download.html)
* [µC/OS-III](https://github.com/SiliconLabs/uC-OS3)
* [FreeRTOS](https://github.com/FreeRTOS/FreeRTOS)
* [LiteOS](https://gitee.com/LiteOS)
* [AliOS](https://github.com/alibaba/AliOS-Things)
* [ROS](https://github.com/ros/ros)
* [ROS2](https://github.com/ros2/ros2)
* [OpenRC](https://github.com/OpenRC/openrc)
* [Hurlex II](https://github.com/hurley25/Hurlex-II)
* [TedkOS](https://github.com/TakefiveInteractive/TedkOS)
* [Syslinux](https://git.kernel.org/pub/scm/boot/syslinux/syslinux.git)
* [x86 Bare Metal Examples](https://github.com/cirosantilli/x86-bare-metal-examples)
* [OpenWrt](https://github.com/openwrt/openwrt)
* [DD-WRT](https://svn.dd-wrt.com//)
* [pfSense](https://github.com/pfsense/pfsense)
* [eCos](http://mirrors.kernel.org/sources.redhat.com/ecos/)
* [U-Boot](https://github.com/u-boot/u-boot)

### [Linux](https://elixir.bootlin.com/linux/latest/source)

* [irq_vectors.h](https://github.com/torvalds/linux/blob/master/arch/x86/include/asm/irq_vectors.h)
* [idt.c](https://github.com/torvalds/linux/blob/master/arch/x86/kernel/idt.c)
* [syscall_32.tbl](https://github.com/torvalds/linux/blob/master/arch/x86/entry/syscalls/syscall_32.tbl)
* [syscalls.h](https://github.com/torvalds/linux/blob/master/include/linux/syscalls.h)
* [fork.c](https://github.com/torvalds/linux/blob/master/kernel/fork.c)
* [copy.S](https://github.com/torvalds/linux/blob/master/arch/x86/boot/copy.S)
* [sched.h](https://github.com/torvalds/linux/blob/master/include/linux/sched.h)
* [mem.c](https://github.com/torvalds/linux/blob/master/drivers/char/mem.c)

### Emulator

* [QEMU](https://www.qemu.org/)
* [Bochs](http://bochs.sourceforge.net/)
* [Unicorn Engine](https://github.com/unicorn-engine/unicorn)
* [VirtualBox](https://www.virtualbox.org/)
* [VMware Workstation Player](https://www.vmware.com/products/workstation-player.html)

## Reference

* [OS Dev](https://wiki.osdev.org)
* [Linux Kernel Teaching](https://linux-kernel-labs.github.io/refs/heads/master/index.html)
* [The Linux Kernel documentation](https://www.kernel.org/doc/html/latest/)
* [The Linux Documentation Project](https://www.tldp.org)
* [The GNU C Library](https://www.gnu.org/software/libc/manual/html_node)
* [Intel® 64 and IA-32 Architectures Software Developer’s Manuals](https://software.intel.com/en-us/articles/intel-sdm)
* [Operating System Design](https://en.wikibooks.org/wiki/Operating_System_Design)

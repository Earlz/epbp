**EPBP**

**See the EPBP official website for more information: http://epbp.earlz.biz.tm**

EPBP is a portable bytecode project. It is designed to resemble an actual machine from the bytecode/assembler point of view. It is designed in this way so that _real_ programming languages can be ported to compile to this bytecode format.

**Emulated Machine Info:**

The strangest _feature_ of the emulated machine is that there are no true registers. There is a registers _mechanism_ however. This is implemented by register banks. Register banks make it so an area of memory can be mapped so that this area of memory can be addressed by using only 1 byte.

For getting "outside" the emulation, there is a method of external callings of system functions. This is called "xcall". This must be used for things such as printing to screen, or drawing graphics, or other external functions.

**This Implementation:**

EPBP is encouraged to be implemented by people other than me. I only wish to make a decent, but basic implementation demonstrating all of the opcodes and how xcall-able libraries can work.

**This Is The Concept Version:**

This is only the concept version. This is done to prove the concept and to make it easy for current developers to develop on the EPBP platform. This version is 32bit and the FPU functions are elementary at best. The expected eventual version will be 64bit and the FPU functions will be very elegant including all the functions expected of an FPU.

**Interested?**

At this point, the code is no where near a working demo. If you find this project interesting though, please feel free to contact me at "earlz?at?earlz.biz.tm" by email for any questions. I am looking for some help with this project. You don't just have to add code, I am looking for someone just to bounce ideas off of that has some experience with bytecode. Of course, I am always looking for programmers, documenters, and testers to help me with the project.
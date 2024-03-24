#include "boot.h"

#define SECTSIZE 512

void bootMain(void) {
	//TODO   
   	void (*entry)(void) = (void (*)(void)) 0x8c00;
    // 读取一个扇区到指定内存位置
  	readSect((void *)entry,1);
    
    // 跳转执行加载的代码
	entry();  // 调用该地址处的函数 填入0x8c00处的程序 就是app

}


void waitDisk(void) { // waiting for disk
	while((inByte(0x1F7) & 0xC0) != 0x40);
}

void readSect(void *dst, int offset) { // reading a sector of disk
	int i;
	waitDisk();
	outByte(0x1F2, 1);//扇区1
	outByte(0x1F3, offset);
	outByte(0x1F4, offset >> 8);
	outByte(0x1F5, offset >> 16);
	outByte(0x1F6, (offset >> 24) | 0xE0);
	outByte(0x1F7, 0x20);

	waitDisk();
	for (i = 0; i < SECTSIZE / 4; i ++) {
		((int *)dst)[i] = inLong(0x1F0);
	}
}

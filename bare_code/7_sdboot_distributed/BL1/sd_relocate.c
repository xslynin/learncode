typedef unsigned int bool;
typedef bool(*pCopySDMMC2Mem)(int, unsigned int, unsigned short, unsigned int*,bool);
typedef void(*pBL2_Function)(void);

#define SD_START_BLOCK 45
#define SD_BLOCK_CNT   32
#define DDR_START_ADDR 0x23E00000

void b2_copy_init(void){
	//读取sd卡的扇区到ddr中
	pCopySDMMC2Mem p1 = (pCopySDMMC2Mem)(*(unsigned int *)0xD0037F98);
	p1(2, SD_START_BLOCK, SD_BLOCK_CNT, (unsigned int *)DDR_START_ADDR, 0);

	//跳转到ddr中的bl2执行代码
	pBL2_Function p2 = (pBL2_Function)DDR_START_ADDR;
	p2();
}
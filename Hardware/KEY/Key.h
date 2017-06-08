
#include "LPC11xx.h"
#include "GPIO.h"
#include "timer.h"

//¼üÖµ¶¨Òå

#define READ_KEY1() do{ return LPC_GPIO3 -> DATA & (1<<1);}while(0);
#define READ_KEY2() do{ return LPC_GPIO3 -> DATA & (1<<0);}while(0);


#define GPIO_READ_3(x) (!(LPC_GPIO3->DATA &(1<<##x)))?T16B0_delay_ms(20),(!(LPC_GPIO3->DATA &(1<<##x)))?1:0:0


extern void Key_init(void);
extern void Key_scanf(void);
extern uint16_t Get_Key(void);
extern int Press;

void New_Key_Init(void);
int New_Key_Get(void);





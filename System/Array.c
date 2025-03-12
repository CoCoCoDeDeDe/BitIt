#include "stm32f10x.h"                  // Device header

int Array_char_isEqual(char *a, char *b) {
	if(sizeof(a) != sizeof(b)) {
		return 0;
	} else {
		for(uint8_t i = 0 ; i < sizeof(a) ; i ++ ) {
			if(a[i] != b[i]) {
				return 0;
			} else {
				//nothing
			}
		}	//遍历完，发现每个元素都相同
		return 1;
	}
}


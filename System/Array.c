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

//取数组前n个元素平均数()
float MyArray_GetAverage_uint16_t(uint8_t n, uint16_t *arr) {
	uint32_t sum = 0;
	for(int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum / (float)n;	//错点：转n为float，否则结果为整数
}

//数组尾部加入新元素并舍去第一个元素()
void MyArray_TailAdd_uint16_t(uint16_t *arr, uint16_t ele, uint8_t n) {
	for(int i = 0; i < n - 1; i ++) {
		arr[i] = arr[i + 1];
	}
	arr[n - 1] = ele;	//错点：arr最后一位是arr[n - 1]
}









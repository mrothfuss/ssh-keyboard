#include <linux/input.h>

extern void btn_on(int);
extern void btn_off(int);

void send_ascii(char val) {
	int lshift = 0;
	int key = 0;

	switch(val) {
		// 1234 Row
		case '1': key = KEY_1; break;
		case '2': key = KEY_2; break;
		case '3': key = KEY_3; break;
		case '4': key = KEY_4; break;
		case '5': key = KEY_5; break;
		case '6': key = KEY_6; break;
		case '7': key = KEY_7; break;
		case '8': key = KEY_8; break;
		case '9': key = KEY_9; break;
		case '0': key = KEY_0; break;
					 // Shift 1234 Row
		case '!': key = KEY_1; lshift = 1; break;
		case '@': key = KEY_2; lshift = 1; break;
		case '#': key = KEY_3; lshift = 1; break;
		case '$': key = KEY_4; lshift = 1; break;
		case '%': key = KEY_5; lshift = 1; break;
		case '^': key = KEY_6; lshift = 1; break;
		case '&': key = KEY_7; lshift = 1; break;
		case '*': key = KEY_8; lshift = 1; break;
		case '(': key = KEY_9; lshift = 1; break;
		case ')': key = KEY_0; lshift = 1; break;
					 // QWER row
		case 'q': key = KEY_Q; break;
		case 'w': key = KEY_W; break;
		case 'e': key = KEY_E; break;
		case 'r': key = KEY_R; break;
		case 't': key = KEY_T; break;
		case 'y': key = KEY_Y; break;
		case 'u': key = KEY_U; break;
		case 'i': key = KEY_I; break;
		case 'o': key = KEY_O; break;
		case 'p': key = KEY_P; break;
					 // Shift QWER row
		case 'Q': key = KEY_Q; lshift = 1; break;
		case 'W': key = KEY_W; lshift = 1; break;
		case 'E': key = KEY_E; lshift = 1; break;
		case 'R': key = KEY_R; lshift = 1; break;
		case 'T': key = KEY_T; lshift = 1; break;
		case 'Y': key = KEY_Y; lshift = 1; break;
		case 'U': key = KEY_U; lshift = 1; break;
		case 'I': key = KEY_I; lshift = 1; break;
		case 'O': key = KEY_O; lshift = 1; break;
		case 'P': key = KEY_P; lshift = 1; break;
					 // ASDF row
		case 'a': key = KEY_A; break;
		case 's': key = KEY_S; break;
		case 'd': key = KEY_D; break;
		case 'f': key = KEY_F; break;
		case 'g': key = KEY_G; break;
		case 'h': key = KEY_H; break;
		case 'j': key = KEY_J; break;
		case 'k': key = KEY_K; break;
		case 'l': key = KEY_L; break;
					 // Shift ASDF row
		case 'A': key = KEY_A; lshift = 1; break;
		case 'S': key = KEY_S; lshift = 1; break;
		case 'D': key = KEY_D; lshift = 1; break;
		case 'F': key = KEY_F; lshift = 1; break;
		case 'G': key = KEY_G; lshift = 1; break;
		case 'H': key = KEY_H; lshift = 1; break;
		case 'J': key = KEY_J; lshift = 1; break;
		case 'K': key = KEY_K; lshift = 1; break;
		case 'L': key = KEY_L; lshift = 1; break;
					 // ZXCV row
		case 'z': key = KEY_Z; break;
		case 'x': key = KEY_X; break;
		case 'c': key = KEY_C; break;
		case 'v': key = KEY_V; break;
		case 'b': key = KEY_B; break;
		case 'n': key = KEY_N; break;
		case 'm': key = KEY_M; break;
					 // Shift ZXCV row
		case 'Z': key = KEY_Z; lshift = 1; break;
		case 'X': key = KEY_X; lshift = 1; break;
		case 'C': key = KEY_C; lshift = 1; break;
		case 'V': key = KEY_V; lshift = 1; break;
		case 'B': key = KEY_B; lshift = 1; break;
		case 'N': key = KEY_N; lshift = 1; break;
		case 'M': key = KEY_M; lshift = 1; break;
	}

	if(lshift) {
		btn_on(KEY_LEFTSHIFT);
	}

	if(key) {
		btn_on(key);
		btn_off(key);
	}

	if(lshift) {
		btn_off(KEY_LEFTSHIFT);
	}
}

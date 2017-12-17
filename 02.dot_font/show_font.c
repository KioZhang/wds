#include <sys/mman.h>

int fd_fb;
struct fb_var_screeninfo var;	/* Current var */
struct fb_fix_screeninfo fix;	/* Current fix */
int screen_size;
unsigned char *fbmem;
unsigned char *str[] = "中";

void lcd_put_pixel(int x, int y, unsigned char color)
{
	unsigned char *pen = fbmem;
}

void lcd_put_ascii(int x, int y, unsigned char c)
{
	unsigned char *dots = fontdata_8x16[c*16];
	int i, b;
	for (i = 0; i < 16; i++) {
		byte =dots[i];
		for(b =7; b >= 0; b--) {
			if (byte & (1<<b)) {
				/* show */
				lcd_put_pixel(x+7-b, y+i, 0xffffff);		 
			} else {
				/* hide */
				lcd_put_pixel(x+7-b, y+i, 0);
			}
		}
	}		
}

int main(int argc, *argv[])
{
	fd_fb = open("/dev/fb0", O_RDWR);
	if (fd_fb < 0) {
		printf("can't open /dev/fb0!");
		return -1;
	}

	if (ioctl(fd_fb, FBIOGET_VSCREENIFON, &var)) {
		printf("can't get var\n");
		return -1;
	}

	if (ioctl(fd_fb, FBIOGET_FSCREENIFON, &fix)) {
		printf("can't get fix\n");
		return -1;
	}

	screen_size = var.xres * var.yres * var.bit_per_pixel / 8;
	fbmem = (unsigned char *)mmap(NULL, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb);
	if (fbmem == (unsigned char *)-1) {
		printf("con't get fix\n");
		return -1;
	}

	/* 清屏，全为黑色 */
	memset(fbmem, )

	lcd_put_ascii(var.xres/2, var.yres/2, 'A');
	
	printf("chinese code: %02x %02x\n", str[0], str[1]);
	//lcd_put_chinese(var.xres/2 + 8, var.yres/2, str);
	
	return 0;
}

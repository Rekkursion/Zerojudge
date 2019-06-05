#pragma warning (disable:4996)

#include <stdio.h>
#include <math.h>
#define MAX_SIZE 256

typedef struct pnode {
	int r, g, b;
}Pixel;

typedef struct inode {
	int w, h;
	Pixel pixels[MAX_SIZE][MAX_SIZE];
}Image;

void processGradients(Image, Image*);
int main() {
	Image orig, processed;

	scanf("%d %d", &orig.w, &orig.h);
	for (int k = 0; k < orig.h; ++k) {
		for (int j = 0; j < orig.w; ++j)
			scanf("%d %d %d", &orig.pixels[k][j].r, &orig.pixels[k][j].g, &orig.pixels[k][j].b);
	}

	processGradients(orig, &processed);

	printf("%d %d\n", processed.w, processed.h);
	for (int k = 0; k < processed.h; ++k) {
		for (int j = 0; j < processed.w; ++j)
			printf("%d %d %d ", processed.pixels[k][j].r, processed.pixels[k][j].g, processed.pixels[k][j].b);
		putchar('\n');
	}

	return 0;
}

void processGradients(Image src, Image* dst) {
	dst->h = src.h;
	dst->w = src.w;

	for (int k = 0; k < src.h; ++k) {
		for (int j = 0; j < src.w; ++j) {
			int delta_x_r = src.pixels[k][j + 1 < src.w ? j + 1 : j].r - src.pixels[k][j].r;
			int delta_y_r = src.pixels[k + 1 < src.h ? k + 1 : k][j].r - src.pixels[k][j].r;

			int delta_x_g = src.pixels[k][j + 1 < src.w ? j + 1 : j].g - src.pixels[k][j].g;
			int delta_y_g = src.pixels[k + 1 < src.h ? k + 1 : k][j].g - src.pixels[k][j].g;

			int delta_x_b = src.pixels[k][j + 1 < src.w ? j + 1 : j].b - src.pixels[k][j].b;
			int delta_y_b = src.pixels[k + 1 < src.h ? k + 1 : k][j].b - src.pixels[k][j].b;

			int new_r = (int)((((double)abs(delta_x_r) + (double)abs(delta_y_r)) * 0.5) + 0.5);
			int new_g = (int)((((double)abs(delta_x_g) + (double)abs(delta_y_g)) * 0.5) + 0.5);
			int new_b = (int)((((double)abs(delta_x_b) + (double)abs(delta_y_b)) * 0.5) + 0.5);

			dst->pixels[k][j].r = new_r;
			dst->pixels[k][j].g = new_g;
			dst->pixels[k][j].b = new_b;
		}
	}

	return;
}

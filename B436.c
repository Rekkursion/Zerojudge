#pragma warning (disable:4996)

#include <stdio.h>
#include <math.h>
#define MAX_SIZE 256
const int sobelOperator_x[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
const int sobelOperator_y[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

typedef struct pnode {
	int r, g, b;
}Pixel;

typedef struct inode {
	int w, h;
	Pixel pixels[MAX_SIZE][MAX_SIZE];
}Image;

void processGradients(Image, Image*);
int sobel(Image*, int, int, int, int);
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

void processGradients(Image src, Image * dst) {
	dst->h = src.h;
	dst->w = src.w;

	for (int k = 0; k < src.h; ++k) {
		for (int j = 0; j < src.w; ++j) {
			int delta_x_r = sobel(&src, k, j, 0, 0);
			int delta_y_r = sobel(&src, k, j, 0, 1);

			int delta_x_g = sobel(&src, k, j, 1, 0);
			int delta_y_g = sobel(&src, k, j, 1, 1);

			int delta_x_b = sobel(&src, k, j, 2, 0);
			int delta_y_b = sobel(&src, k, j, 2, 1);

			int new_r = (int)((((double)abs(delta_x_r) + (double)abs(delta_y_r)) / 8.0) + 0.5);
			int new_g = (int)((((double)abs(delta_x_g) + (double)abs(delta_y_g)) / 8.0) + 0.5);
			int new_b = (int)((((double)abs(delta_x_b) + (double)abs(delta_y_b)) / 8.0) + 0.5);

			dst->pixels[k][j].r = new_r;
			dst->pixels[k][j].g = new_g;
			dst->pixels[k][j].b = new_b;
		}
	}

	return;
}

int sobel(Image* img, int row, int col, int rgb, int xy) {
	int ret = 0;

	for (int k = row - 1; k <= row + 1; ++k) {
		for (int j = col - 1; j <= col + 1; ++j) {
			int rIdx = k, cIdx = j;

			if (k < 0 && j < 0)
				rIdx = cIdx = 0;
			else if (k < 0 && j >= img->w)
				rIdx = 0, cIdx = img->w - 1;
			else if (k >= img->h && j < 0)
				rIdx = img->h - 1, cIdx = 0;
			else if (k >= img->h && j >= img->w)
				rIdx = img->h - 1, cIdx = img->w - 1;
			else if (k < 0)
				rIdx = 0;
			else if (j < 0)
				cIdx = 0;
			else if (k >= img->h)
				rIdx = img->h - 1;
			else if (j >= img->w)
				cIdx = img->w - 1;

			if (xy == 0) {
				if (rgb == 0)
					ret += img->pixels[rIdx][cIdx].r * sobelOperator_x[k - row + 1][j - col + 1];
				else if (rgb == 1)
					ret += img->pixels[rIdx][cIdx].g * sobelOperator_x[k - row + 1][j - col + 1];
				else
					ret += img->pixels[rIdx][cIdx].b * sobelOperator_x[k - row + 1][j - col + 1];
			} else {
				if (rgb == 0)
					ret += img->pixels[rIdx][cIdx].r * sobelOperator_y[k - row + 1][j - col + 1];
				else if (rgb == 1)
					ret += img->pixels[rIdx][cIdx].g * sobelOperator_y[k - row + 1][j - col + 1];
				else
					ret += img->pixels[rIdx][cIdx].b * sobelOperator_y[k - row + 1][j - col + 1];
			}
		}
	}

	return ret;
}

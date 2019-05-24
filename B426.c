#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 256
#define range_restrict(x) ((x) < 0 ? 0 : ((x) > 255 ? 255 : (x)))

typedef struct pixel_node {
	int r, g, b;
}Pixel;

typedef struct picture_node {
	Pixel pixels[MAX_SIZE + 1][MAX_SIZE + 1];
	int width;
	int height;
}Picture;
Picture fore, back;

inline void getPicture(Picture*);
inline void alphaCompositing(Picture*, Picture*, Picture*, const int* const, const int* const, const double* const);
int main() {
	double opacity;
	int x, y;
	Picture* res = (Picture*)malloc(sizeof(Picture));

	scanf("%d %d %lf", &x, &y, &opacity);
	getPicture(&fore);
	getPicture(&back);

	alphaCompositing(res, &fore, &back, &x, &y, &opacity);

	printf("%d %d\n", res->width, res->height);
	for (int h = 0; h < res->height; ++h) {
		for (int w = 0; w < res->width; ++w)
			printf("%d %d %d ", res->pixels[h][w].r, res->pixels[h][w].g, res->pixels[h][w].b);
		putchar('\n');
	}

	return 0;
}

void getPicture(Picture* pic) {
	scanf("%d %d", &pic->width, &pic->height);

	for (int h = 0; h < pic->height; ++h) {
		for (int w = 0; w < pic->width; ++w)
			scanf("%d %d %d", &pic->pixels[h][w].r, &pic->pixels[h][w].g, &pic->pixels[h][w].b);
	}

	return;
}

void alphaCompositing(Picture* dst, Picture* fore, Picture* back, const int* const X, const int* const Y, const double* const OPACITY) {
	dst->height = back->height;
	dst->width = back->width;
	for (int h = 0; h < back->height; ++h) {
		for (int w = 0; w < back->width; ++w)
			dst->pixels[h][w].r = back->pixels[h][w].r,
			dst->pixels[h][w].g = back->pixels[h][w].g,
			dst->pixels[h][w].b = back->pixels[h][w].b;
	}

	int startH = *Y;
	int startW = *X;
	int endH = startH + fore->height;
	int endW = startW + fore->width;

	for (int h = startH; h < endH; ++h) {
		for (int w = startW; w < endW; ++w) {
			if (h < 0 || w < 0 || h >= dst->height || w >= dst->width)
				continue;

			double mixed_r = (double)fore->pixels[h - *Y][w - *X].r * (*OPACITY) + \
				(double)back->pixels[h][w].r * (1.0 - (*OPACITY));
			double mixed_g = (double)fore->pixels[h - *Y][w - *X].g * (*OPACITY) + \
				(double)back->pixels[h][w].g * (1.0 - (*OPACITY));
			double mixed_b = (double)fore->pixels[h - *Y][w - *X].b * (*OPACITY) + \
				(double)back->pixels[h][w].b * (1.0 - (*OPACITY));

			int rounded_r = range_restrict((int)(mixed_r + 0.5));
			int rounded_g = range_restrict((int)(mixed_g + 0.5));
			int rounded_b = range_restrict((int)(mixed_b + 0.5));

			dst->pixels[h][w].r = rounded_r;
			dst->pixels[h][w].g = rounded_g;
			dst->pixels[h][w].b = rounded_b;
		}
	}

	return;
}

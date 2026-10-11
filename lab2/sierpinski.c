#include <stdio.h>
#include <stdlib.h>

int nb_columns() { return 129; }

int nb_lines() { return 65; }

void grid_init(char grid[], char pixel) {
  for (int i = 0; i < nb_lines(); i++)
    for (int j = 0; j < nb_columns(); j++)
      grid[i * nb_columns() + j] = pixel;
}

void grid_display(char grid[]) {
  for (int i = 0; i < nb_lines(); i++) {
    for (int j = 0; j < nb_columns(); j++)
      printf("%c", grid[i * nb_columns() + j]);
    printf("\n");
  }
}

void plot_point(char grid[], int x, int y, char pixel) {
  if (x < 0 || y < 0 || x >= nb_columns() || y >= nb_lines())
    exit(EXIT_FAILURE);
  grid[(nb_lines() - y - 1) * nb_columns() + x] = pixel;
}

void plot_vline(char grid[], int x, float fy0, float fy1, char pixel) {
  int y0 = fy0 + 0.5f;
  if (fy0 == y0 - 0.5f)
    y0 -= 1;
  int y1 = fy1 + 0.5f;
  for (int y = y0; y <= y1; y++)
    plot_point(grid, x, y, pixel);
}

int sort_get_index(float tab[], int top, float val) {
  int i = 0;
  while (i < top && tab[i] < val)
    i++;
  // printf("insert %f at %d\n", val, i);
  return i;
}

void sort_insert_at(float tab[], int i, int top, float val) {
  for (int j = top; j > i; j--)
    tab[j] = tab[j - 1];
  tab[i] = val;
}

void sort_insert(float tab[], int top, float val) {
  sort_insert_at(tab, sort_get_index(tab, top, val), top, val);
}

struct point {
  float x, y;
};

void plot_poly_sweep(char grid[], struct point p[], int n, int x, char pixel) {
  float vlines[n * 4];
  int top = 0;
  // printf("sweep %d:", x);
  int j = n - 1;
  for (int i = 0; i < n; i++) {
    if (p[i].x == x) {
      if (p[j].x == x) {
        if (p[i].y < p[j].y)
          plot_vline(grid, x, p[i].y, p[j].y, pixel);
        else
          plot_vline(grid, x, p[j].y, p[i].y, pixel);
      } else
        plot_vline(grid, x, p[i].y, p[i].y, pixel);
    }

    if ((p[i].x <= x && x < p[j].x) || (p[j].x <= x && x < p[i].x)) {
      if (p[j].x != p[i].x) {
        float intersect_y =
            p[i].y + (x - p[i].x) * (p[j].y - p[i].y) / (p[j].x - p[i].x);
        sort_insert(vlines, top, intersect_y);
        top++;
      }
    }
    j = i;
  }
  /*for (int i = 0; i < top; i++) {
        printf("  %f", vlines[i]);
  }
  printf("\n");*/
  for (int k = 0; k < top; k += 2)
    if (k + 1 < top)
      plot_vline(grid, x, vlines[k], vlines[k + 1], pixel);
}

void plot_poly(char grid[], struct point p[], int n, char pixel) {
  for (int x = 0; x < nb_columns(); x++) {
    plot_poly_sweep(grid, p, n, x, pixel);
  }
}

void plot_triangle(char grid[], struct point p1, struct point p2,
                   struct point p3, char pixel) {
  struct point p[3] = {p1, p2, p3};
  plot_poly(grid, p, 3, pixel);
}

struct point line_middle(struct point p1, struct point p2) {
  return (struct point){(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
}

void sierpinski(char grid[], struct point p1, struct point p2, struct point p3,
                int n, char pixel) {
  if (n == 1)
    plot_triangle(grid, p1, p2, p3, pixel);
  else {
    struct point midpoint_12 = line_middle(p1, p2);
    struct point midpoint_23 = line_middle(p2, p3);
    struct point midpoint_31 = line_middle(p3, p1);
    sierpinski(grid, p1, midpoint_12, midpoint_31, n - 1, pixel);
    sierpinski(grid, midpoint_12, p2, midpoint_23, n - 1, pixel);
    sierpinski(grid, midpoint_31, midpoint_23, p3, n - 1, pixel);
  }
}

int main(void) {
  char grid[nb_lines() * nb_columns()];
  grid_init(grid, ' ');
  struct point p1 = {0, 0};
  struct point p2 = {64, 64};
  struct point p3 = {128, 0};
  sierpinski(grid, p1, p2, p3, 6, '*');
  grid_display(grid);
  return 0;
}

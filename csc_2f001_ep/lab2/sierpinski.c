#include <stdio.h>
#include <stdlib.h>
int nb_columns() { return 32; }

int nb_lines() { return 16; }

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

int sort_get_index(float tab[], int top, float val) {
  int i = 0;
  while (i < top && tab[i] < val)
    i++;
  printf("insert %f at %d\n", val, i);
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

int main(void) {
  float tab[5] = {1.0f, 3.0f, 5.0f, 7.0f, 0.0f};
  char grid[nb_lines() * nb_columns()];
  sort_insert(tab, 4, 3.5f);

  for (int i = 0; i < 5; i++) {
    printf("%f ", tab[i]);
  }
  printf("\n");

  grid_init(grid, '*');
  plot_point(grid, 3, 1, ' ');
  grid_display(grid);
  return 0;
}

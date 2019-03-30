/*
geo.c -- 
Written on torsdag, 31 augusti 2017.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define Square(x) ((x)*(x))

struct point {
  int x;
  int y;
};
typedef struct point point_t;

struct rectangle {
  point_t ul;
  point_t lr;
};

typedef struct rectangle rectangle_t;

struct circle {
  point_t center;
  int radius;
};

typedef struct circle circle_t;

void print_rect(rectangle_t *rect);
point_t make_point(int x, int y);
void print_point(point_t *p);
void translate(point_t *p1, point_t *p2);
rectangle_t make_rect();
bool intersects_rect(rectangle_t *a, rectangle_t *b);
rectangle_t intersection_rect(rectangle_t *a, rectangle_t *b);
circle_t make_circle(int x, int y, int r);
void print_circle(circle_t *c);
double area_circle(circle_t *c);

int main(int argc, char *argv[]) {
  circle_t c = make_circle(3, 3, 1);
  print_circle(&c);
  double area = area_circle(&c);
  printf("Arean av cirkeln är: %f\n", area);
  return 0;
}

void translate(point_t *p1, point_t *p2) {
  p1->x += p2->x;
  p1->y += p2->y;
}

void print_point(point_t *p) {
  printf("point(%d, %d)", p->x, p->y);
}

point_t make_point(int x, int y) {
  point_t p = {.x = x, .y = y };
  return p;
}

void print_rect(rectangle_t *rect) {
  printf("rectangle(upper_left = ");
  print_point(&rect->ul);
  printf(", lower_right = ");
  print_point(&rect->lr);
  printf(")\n");
}

rectangle_t make_rect(int x1, int y1, int x2, int y2) {
  rectangle_t r = { .ul = make_point(x1, y1), .lr = make_point(x2, y2) };
  return r;
}

int area_rect(rectangle_t *rect) {
  point_t p1 = rect->ul;
  point_t p2 = rect->lr;
  int x1 = p1.x;
  int y1 = p1.y;
  int x2 = p2.x;
  int y2 = p2.y;
  return (x2 - x1)*(y2 - y1);
}

bool intersects_rect(rectangle_t *a, rectangle_t *b) {
  point_t a_upper = a->ul;
  point_t a_lower = a->lr;
  point_t b_upper = b->ul;
  point_t b_lower = b->lr;
  int a_lowest_x  = a_upper.x;
  int a_highest_x = a_lower.x;
  int a_lowest_y  = a_lower.y;
  int a_highest_y = a_upper.y;
  int b_lowest_x  = b_upper.x;
  int b_highest_x = b_lower.x;
  int b_lowest_y  = b_lower.y;
  int b_highest_y = b_upper.y;

  return !(a_highest_x < b_lowest_x || b_highest_x < a_lowest_x || a_highest_y < b_lowest_y || b_highest_y < a_lowest_y);
}

rectangle_t intersection_rect(rectangle_t *a, rectangle_t *b) {
  rectangle_t inner_rect;
  
    point_t a_upper = a->ul;
    point_t a_lower = a->lr;
    point_t b_upper = b->ul;
    point_t b_lower = b->lr;
    int a_lowest_x  = a_upper.x;
    int a_highest_x = a_lower.x;
    int a_lowest_y  = a_lower.y;
    int a_highest_y = a_upper.y;
    int b_lowest_x  = b_upper.x;
    int b_highest_x = b_lower.x;
    int b_lowest_y  = b_lower.y;
    int b_highest_y = b_upper.y;
    
    if (a_highest_x <= b_highest_x) {
      if (a_highest_y >= b_highest_y) {
        inner_rect = make_rect(b_lowest_x, b_highest_y, a_highest_x, a_lowest_y);
      }
      else {
	inner_rect = make_rect(b_lowest_x, a_highest_y, a_highest_x, b_lowest_y);
      }
    }
    else {
      if (b_highest_y>=a_highest_y) {
	inner_rect = make_rect(a_lowest_x, a_highest_y, b_highest_x, b_lowest_y);
    }
      else {
        inner_rect = make_rect(a_lowest_x, b_highest_y, b_highest_x, a_lowest_y);
      }
    }
  return inner_rect;
}

circle_t make_circle(int x, int y, int r) {
  circle_t c = { .center = make_point(x, y), .radius = r };
  return c;
}

void print_circle(circle_t *c) {
  point_t center_point = c->center;
  int rad = c->radius;
  printf("circle(center=");
  print_point(&center_point);
  printf(", radius=%d)\n", rad);
}

double area_circle(circle_t *c) {
  int r = c->radius;
  return M_PI * Square((double) r);
}



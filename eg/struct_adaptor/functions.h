typedef struct _s1 {
  int a;
  int b;
  int c;
  int d;
} struct1;

typedef struct _s2 {
  int a;
  int b;
  int c;
  int d;
} struct2;

int f1_sf(struct1 *s) {
  if(s) {
    // s->a = 1;
    //return s->a - s->b;
    return 3*(s->a) + 5*(s->b);
    //return s->a - s->b - s->c;
    //return s->a - s->b + s->c - s->d;
    //return 3*(s->a) + 5*(s->b) + 7*(s->c);
    //return 3*(s->a) + 5*(s->b) + 7*(s->c) + 11*(s->d);
    //return s->b;
  }
  return 0;
}

int f2_sf(struct2 *s) {
  if(s) {
    // s->b = 1;
    //return s->b - s->a;
    return 3*(s->b) + 5*(s->a);
    //return 3*(s->c) + 5*(s->b) + 7*(s->a);
    //return s->c - s->b - s->a;
    //return s->d - s->c + s->b - s->a;
    //return 3*(s->d) + 5*(s->c) + 7*(s->b) + 11*(s->a);
    //return s->a;
  }
  return 0;
}

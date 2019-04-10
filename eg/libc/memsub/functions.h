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

//f1(c = 1, input[0] = 1) = 0
//f2(c = 0, input[0] = 0) =
// arg adapter is (0,1) (0,1) (0,0) (0,3)
#define ARR_LEN 1
int f1_sf(struct1 *s, int len) {
  //s->a = 1;
  // s->b = 2;
  //s->c = 3;
  //s->d = 4;
    //return s->a; // - s->b;
    //return 3*(s->a) + 5*(s->b);
    //return s->a - s->b - s->c;
    //return s->a - s->b + s->c - s->d;
    //return 3*(s->a) + 5*(s->b) + 7*(s->c);
    return 3*(s->a) + 5*(s->b) + 7*(s->c) + 11*(s->d);
    //return s->b;
    /*int i = 0;
    int x, y, a, b;
    unsigned char *input="0000";
    unsigned char *output;
    unsigned int *m = &(s->c);
    for (i = 0; i < len; i++) {
      x = ( x + 1 ) & (ARR_LEN - 1);
      a = s->a;
      y = ( y + a ) & (ARR_LEN - 1);
      b = s->b;
      s->a = (unsigned char) b;
      s->b = (unsigned char) a;
      
      // output[i] = (unsigned char)
      //  ( input[i] ^ m[ ( a + b ) & (ARR_LEN - 1) ] );
      // output[i] = input[i] + 3*(s->a) + 5*(s->b) + 7*(s->c) + 11*(s->d);
      output[i] = input[i] ^ (s->c);
      break;
    }
    s->a=a;
    s->b=b;
    //return 0;
    return output[0];*/
}

int f2_sf(int len, struct2 *s) {
  // s->a = 1;
  // s->b = 2;
  // s->c = 3;
  // s->d = 4;
  // return s->a; // - s->b;
    //return 3*(s->a) + 5*(s->b);
    //return s->a - s->b - s->c;
    //return s->a - s->b + s->c - s->d;
    //return 3*(s->a) + 5*(s->b) + 7*(s->c);
    return 3*(s->a) + 5*(s->b) + 7*(s->c) + 11*(s->d);
    //return s->b;
    /*int i = 0;
    int x, y, a, b;
    unsigned char *input="0000";
    unsigned char *output;
    unsigned int *m = &(s->c);
    for (i = 0; i < len; i++) {
      x = ( x + 1 ) & (ARR_LEN - 1);
      a = s->a;
      y = ( y + a ) & (ARR_LEN - 1);
      b = s->b;
      s->a = (unsigned char) b;
      s->b = (unsigned char) a;
      
      // output[i] = (unsigned char)
      //  ( input[i] ^ m[ ( a + b ) & (ARR_LEN - 1) ] );
      // output[i] = input[i] + 3*(s->a) + 5*(s->b) + 7*(s->c) + 11*(s->d);
      output[i] = input[i] ^ (s->c);
      break;
    }
    s->a=a;
    s->b=b;
    //return 0;
    return output[0]; */
}

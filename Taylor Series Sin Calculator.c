#include <stdio.h>
#include <assert.h>
#define __USE_MISC
#include <math.h>


#define TO_RADIANS (M_PI/180) // converts degrees to radians
#define TO_DEGREES (180/M_PI) // converts radians to degrees
#define N (360)

float TABLE[N] = {0.0f};


// uses the first 4 terms taylor series of sin(0) to estimate sin at degree
// NOTE: degree is treated in radians
float estimate_sin(float degree);

// returns absolute value, no longer in math.h in c99
float absValue(float value);


// creates and fills in the TABLE
// index at point = degree
void init() 
{

  for(int i = 0;i < N;i++) 
  {
    float degree = (float) i;
    degree *= TO_RADIANS;
    TABLE[i] = estimate_sin(degree);
    assert( absValue(TABLE[i]) <= 1.1f); // we expect our values to be from about -1 to 1
  }

}

// calulates the factorial of a number
int factorial(int factor)
{
  if(factor == 0)
  {
    return 1;
  }

  if(factor < 0)
  {
    return 0 - factorial(-factor);
  }

  int total = factor;

  assert(factor > 0); // factor should be above 0 at this point

  // set base case to 2 because any 
  // number times 1 is still the same
  while(factor > 2)
  {
    factor--;
    total *= factor;
  }

  return total;
}


float absValue(float value)
{
  if(value < 0.0f)
  {
    return -value;
  }
  return value;
}


// NOTE: degree is treated in radians
float estimate_sin(float degree)
{
  float cos = 1.0f; // represents cos value of the trig circle

  if(degree >= M_PI/2 && degree < 3*M_PI/2) // between 90 and 270
  {
    degree -= M_PI; // sub from 180 to offset
    cos = -cos; // inverse because we are on the left side of trig circle
  }

  else if(degree >= 3*M_PI/2) // greater than or equal to 270
  {
    degree -= M_PI*2; // sub from 360 to offset
    // cos stays the same because we are on the right side
  }
 
  float calc = (cos * degree)
            - (cos * pow(degree, 3)) / factorial(3)
            + (cos * pow(degree, 5)) / factorial(5)
            - (cos * pow(degree, 7)) / factorial(7);
  return calc;
}



// interpolates a value for input_angle
// NOTE: input_angle is treated in degrees, NOT radians
float sin_(float input_angle)
{
  // if input_angle is out of bounds[0,359], return 0
  if(input_angle <= 0.0 || input_angle >= N) 
  {
    return 0.0;
  }

  // this variable clips the floating point off
  int clip = (int) input_angle; 
  
  // if input_angle already represents an index, return that value
  if(clip == input_angle)
  {
    return TABLE[clip];
  }

  float indexBefore = (float) clip;
  float indexAfter = indexBefore + 1;
  float beforeValue = TABLE[(int)indexBefore];
  float afterValue = TABLE[(int)indexAfter];

  
  float value = (beforeValue * (indexAfter - input_angle) + afterValue * (input_angle - indexBefore));
  value /= (indexAfter - indexBefore);

  return value;
}


// prints and compares the estimated and true values of degree
// NOTE: degree is is in degreees not radians
void compareValues(float degree)
{
  float estimate = sin_(degree);
  float trueValue = sin(degree * TO_RADIANS);
  float error = trueValue - estimate;

  printf("%f %f %f %f\n\n", degree, estimate, trueValue, error);
}




/* MAIN FUNCTION

 depending on arguments it will read from a
 file or input from the user */
int main(int argc, char* argv[]) 
{
  init();

  if(argc >= 2) // if file to read
  {
    FILE *read = fopen(argv[1], "r");

    if(!read) // failed to read
    {
      printf("Failed to open file %p.", argv[1]);
    }

    else
    {
      float input;

      while(!feof(read) && input != -1.0f)
      {
        fscanf(read, "%f", &input);

        if(absValue(input + 1.0f) > 0.0000001) // check that input is not -1
        {
          compareValues(input);
        }
        
      }

      fclose(read);
    }
    
  }

  else // read from terminal
  {
    float input;   

    do
    {
      scanf("%f", &input); 

      if(absValue(input + 1.0f) > 0.0000001) // check that input is not -1
      {
        compareValues(input);
      }

    } while(input != -1.0f);
    
  }

}

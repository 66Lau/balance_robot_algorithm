//
// File: main.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include Files
#include "main.h"
#include "MPC_Prediction.h"
#include "MPC_Prediction_terminate.h"
#include "rt_nonfinite.h"

// Function Declarations
static void argInit_10x10_real_T(double result[100]);

static void argInit_10x4_real_T(double result[40]);

static void argInit_4x1_real_T(double result[4]);

static double argInit_real_T();

// Function Definitions
//
// Arguments    : double result[100]
// Return Type  : void
//
static void argInit_10x10_real_T(double result[100])
{
  // Loop over the array to initialize each element.
  for (int i{0}; i < 100; i++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[i] = argInit_real_T();
  }
}

//
// Arguments    : double result[40]
// Return Type  : void
//
static void argInit_10x4_real_T(double result[40])
{
  // Loop over the array to initialize each element.
  for (int i{0}; i < 40; i++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[i] = argInit_real_T();
  }
}

//
// Arguments    : double result[4]
// Return Type  : void
//
static void argInit_4x1_real_T(double result[4])
{
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < 4; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
  }
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int, char **)
{
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  main_MPC_Prediction();
  // Terminate the application.
  // You do not need to do this more than one time.
  MPC_Prediction_terminate();
  return 0;
}

//
// Arguments    : void
// Return Type  : void
//
void main_MPC_Prediction()
{
  double dv2[100];
  double dv1[40];
  double u_k_data[10];
  double dv[4];
  double N_tmp;
  int u_k_size;
  // Initialize function 'MPC_Prediction' input arguments.
  // Initialize function input argument 'x_k'.
  // Initialize function input argument 'E'.
  // Initialize function input argument 'H'.
  N_tmp = argInit_real_T();
  // Call the entry-point 'MPC_Prediction'.
  argInit_4x1_real_T(dv);
  argInit_10x4_real_T(dv1);
  argInit_10x10_real_T(dv2);
  MPC_Prediction(dv, dv1, dv2, N_tmp, N_tmp, u_k_data, *(int(*)[1]) & u_k_size);
}

//
// File trailer for main.cpp
//
// [EOF]
//

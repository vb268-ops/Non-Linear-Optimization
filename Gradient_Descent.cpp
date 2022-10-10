#include <iostream>
#include <string>
#include <math.h>
#define order 3

using namespace std;

int** analytical_derivative(int** entry)
{
/*
This function return the analytical derivative of expression.
nx2 matrix, 1: Order & 2: Coefficient.
*/

    // Declaring "derivative" array using pointers
    int** derivative = new int*[order-1];
    for(int i=0; i<order-1; i++)
        derivative[i] = new int[2];

    // Differentiating
    for (int i=1; i<=order-1; i++)
    {
        derivative[i-1][0] = entry[i][0]-1; derivative[i-1][1] = entry[i][1]*entry[i][0];
    }

    return derivative;
}

float numerical_derivative(int** derivative, float parameter)
{
/*
This function return the numerical derivative using the analytical one.
*/

    // Calculating Gradient by plugging value of parameter into analytical solution.
    float gradient = 0;
    for (int i=0; i<order-1; i++)
    {
        gradient = gradient + (pow(parameter, derivative[i][0])*derivative[i][1]);
    }

    return gradient;
}

int main()
{
    // Accepting terms with order and coefficients
    // 1: Order & 2: Coefficient, of each row
    int** entries = new int*[order];
    for (int i=0; i<order; i++)
        entries[i] = new int[2];

    // Entering values for Order and Coefficient
    for (int i=0; i<order; i++)
    {
        entries[i][0] = i;
        string degree = to_string(i);
        cout<<"Enter coefficient for degree "<<degree<<" ";
        cin>>entries[i][1];
    }

    // Extracting analytical differential
    int** analytical_deriv;
    analytical_deriv = analytical_derivative(entries);

    // Gradient Descent using numerical derivative
    float numerical_deriv; 
    float updated_parameter; float parameter = -5; 
    int flag=0;
    float learning_rate = 0.01;
    int number_of_steps_to_convergence = 0;

    float gradient_threshold = -0.1; 

    while (flag==0)
    {
        updated_parameter = parameter - (learning_rate*numerical_derivative(analytical_deriv, parameter));
        parameter = updated_parameter;

        number_of_steps_to_convergence = number_of_steps_to_convergence + 1;

        if (abs(numerical_derivative(analytical_deriv, parameter)) < abs(gradient_threshold))
            flag = 1;
    }
    
    numerical_deriv = numerical_derivative(analytical_deriv, parameter);

    // Quantitative data from Gradient Descent
    cout<<"Number of Steps to Convergence: "<<number_of_steps_to_convergence<<"\n";
    cout<<"Final Value of Parameter: "<<parameter<<" ";

    return 0;
}
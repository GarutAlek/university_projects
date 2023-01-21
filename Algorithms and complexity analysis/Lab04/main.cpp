#include <iostream>
#include <random>

using namespace std;

//config
float k1, k2, k3, k4;     // k of reference funcion
float sk1, sk2, sk3, sk4; // start k1 ..
const float D = 0.1;
const int N = 100;
const int MAX_GEN = 50;
const float MIN_DEVIATION = 0.5;

bool mode = true;
// true for direct sign    (integral)
// false for indirect sign (dist)

// in our program it will be constants
const int x0 = -100;
const int x1 = 100;
const float dx = 0.5;

// reference function y(x) = k1x^3 + k2x^2 + k3x + k4
int max_degree = 3;
float reference_integral;

// we will get function like k0*x^(md - 0) + k1*x^(md - 1) + k2*x^(md - 2) + ... + kmd*x^0, where md is max_degree
float func_val(float* params, float x) {
	float res = 0;
	for (int i = 0; i <= max_degree; i++) {
		res += params[i] * pow(x, max_degree - i);
	}
	return res;
}

float integral(float* params) {
	float res = 0;
	for (float i = x0 + dx; i < x1; i += dx) {
		res += dx * (func_val(params, i - dx) + func_val(params, i)) / 2;
		// mean value on interval
	}
	return res;
}

float dist(float* params) {
	float res = 0;
	for (float i = x0 + dx; i < x1; i += dx) {
		res += abs(func_val(params, i) - func_val(new float[] {k1, k2, k3, k4}, i));
		// difference between values of our function and reference function
	}
	return res;
}

float sign(float* params) {
	if (mode)
		return dist(params);
	return abs(reference_integral - integral(params));
}

class Function {
public:

	float* params;
	float sign_value;

	Function(float* params) {
		this->params = new float[4];
		for (int i = 0; i <= max_degree; i++) {
			this->params[i] = params[i];
		}
		this->sign_value = sign(this->params);
	}

	void new_params() {
		for (int i = 0; i <= max_degree; i++) {
			this->params[i] += (rand() % 201 - 100) / 100.0 * D;
		}
		this->sign_value = sign(this->params);
	}

	void output() {
		cout << "params of our funcion: " << endl;
		for (int i = 0; i <= max_degree; i++) {
			cout << this->params[i] << " ";
		}
		cout << endl << "sign value: " << this->sign_value << endl;
	}
};

Function generation(Function parent) {
	Function best = parent;
	for (int i = 0; i < N; i++) {
		Function temp(parent.params);
		temp.new_params();
		if (temp.sign_value < best.sign_value)
			best = temp;
	}
	return best;
}

int main() {
	k1 = 1;
	k2 = 5;
	k3 = 2;
	k4 = 6;

	reference_integral = integral(new float[] {k1, k2, k3, k4});

	sk1 = 0.3;
	sk2 = 1.5;
	sk3 = 9;
	sk4 = 1;

	if (mode)
		cout << "Direct sign!" << endl;
	else
		cout << "Indirect sign!" << endl;

	Function start_function(new float[] {sk1, sk2, sk3, sk4});
	cout << "Start function: " << endl;
	start_function.output();
	cout << endl;

	int gen = 0;
	float delta = 100;
	float first_value, second_value;

	while (gen < MAX_GEN and delta > MIN_DEVIATION) {
		first_value = start_function.sign_value;
		Function new_func = generation(start_function);
		cout << "New function: " << endl;
		new_func.output();
		start_function = new_func;
		second_value = start_function.sign_value;
		delta = ((first_value - second_value) / first_value) * 100;
		cout << "delta: " << delta << " %" << endl << endl;
		gen++;
	}
}
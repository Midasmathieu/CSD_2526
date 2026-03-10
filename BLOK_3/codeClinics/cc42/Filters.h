//
// Created by Dean on 27/02/2024.
//
#include <iostream>
#include "math.h"
#pragma once

class Filter {
public:
  Filter() {
    std::cout << 'Filter constructor' << std::endl;

  }
  virtual float process(float input) = 0;
};


//                   IIRFilter
//   X[n] ---->(+)----------------> Y[n]
//              |                   |
//             (a)<--[ 1 sample ]---


// class FIRLowpass : public Filter {
// public:
//   float process(float input) override {
//     output = (input + a * x1)*2;
//     x1 = input;
//     return output;
//   }
//
// void setCoefficient(float coefficient){
//   a = coefficient;
// }
//
// private:
//   float a = {0.0f};
//   float x1 = {0.0f};
//   float output = {0.0f};
// };
//
// class IIRFilter : public Filter {
//     public:
//     float process(float input) override {
//         // Y[n] = X[n] + aY[n-1]
//         feedback = input + (a * feedback);
//         return feedback;
//     }
//
//     void setCoefficient(float coefficient) {
//         // Do not exceed 1, for the safety of all our ears
//         a = coefficient;
//     }
//
// private:
//     float feedback { 0.0 };
//     float a { 0.0 }; // Coefficient "a" is mostly used for feedback lines
//
// };
//
//
//
//
//
//
//
// //                    OneZero
// //   X[n] ----------------------->(+)--> Y[n]
// //              |                  |
// //             (b)-->[ 1 sample ]-->
// //
// class FIRFilter : public Filter {
//     public:
//     float process(float input) override {
//         // Y[n] = X[n] - bX[n-1]
//         auto output = input - (b * x1);
//
//         x1 = input; // Recaching Delay
//         return output;
//     }
//
//     void setCoefficient(float coefficient) {
//         b = coefficient;
//     }
//
// private:
//     float x1 {0.0 }; // x1 for a single sample delay
//     float b { 0.0 };  // Coefficient "b" is usually used for feed forward lines
//
// };
//
//
// //                   OnePole
// //   X[n] --(b)->(+)--->[ 1 sample ] ---> Y[n]
// //                |                   |
// //               (a)<-----------------
//
// class OnePole : public Filter {
//   public:
//   float process(float input) override {
//       // Y[n] = bX[n] + aY[n-1]
//       // You make this one:
//       feedback = b*input + a*feedback;
//       return feedback;
//   }
//
//   void setCoefficient(float coefficient) {
//       a = coefficient;
//       b = 1.0f - a;
//       std::cout << "test" << std::endl;
//   }
//
// private:
//     float feedback { 0.0 };
//     float a { 0.0 };
//     float b { 0.0 };
// };
//
//
// //                   4_Pole / Simple Cascade
// //   X[n]--->[OnePole][OnePole][OnePole][OnePole]--->Y[n]
// //
// class SimpleLadder :  public Filter {
//   public:
//       OnePole firstPole;
//       OnePole secondPole;
//       OnePole thirdPole;
//       OnePole fourthPole;
//     float process(float input) override {
//       A = firstPole.process(input);
//       B = secondPole.process(A);
//       C = thirdPole.process(B);
//       D = fourthPole.process(C);
//       return D;
//     }
//
//     void setCoefficient(float coefficient) {
//         a = coefficient;
//         // b = 1.0f - a;
//         firstPole.setCoefficient(coefficient);
//         secondPole.setCoefficient(coefficient);
//         thirdPole.setCoefficient(coefficient);
//         fourthPole.setCoefficient(coefficient);
//     }
//
// private:
//     float A = { 0.0 };
//     float B = { 0.0 };
//     float C = { 0.0 };
//     float D = { 0.0 };
//
//     float b = { 0.0 };
//     float a = { 0.0 };
// };
//
//
// //                   4 Sample
// //   X[n] --(b)->(+)--->[ 4 sample ] ---> Y[n]
// //                |                   |
// //               (a)<----------------
//
//
// class FourSample :  public Filter {
// public:
//   float process(float input) override {
//     tickSample(input);
//     // Y[n] = X[n] + aY[n-4]
//     float output = input + getDelayedSample();
//     return output;
//     }
//
//
//
//   void setCoefficient(float coefficient) {
//     a = coefficient;
//     b = 1.0;
//   }
//
//   void tickSample(float input){
//     P = O;
//     O = N;
//     N = M;
//     M = L;
//     L = K;
//     K = J;
//     J = I;
//     I = H;
//     H = G;
//     G = F;
//     F = E;
//     E = D;
//     D = C;
//     C = B;
//     B = A;
//     A = input;
//     std::cout << P << std::endl;
//   }
//
//   float getDelayedSample(){
//     return P;
//   }
//
//
// private:
//   float a { 0.0 };
//   float b { 0.0 };
//   float A { 0.0 };
//   float B { 0.0 };
//   float C { 0.0 };
//   float D { 0.0 };
//   float E { 0.0 };
//   float F { 0.0 };
//   float G { 0.0 };
//   float H { 0.0 };
//   float I { 0.0 };
//   float J { 0.0 };
//   float K { 0.0 };
//   float L { 0.0 };
//   float M { 0.0 };
//   float N { 0.0 };
//   float O { 0.0 };
//   float P { 0.0 };
// };



//                   Halve Biquad
//   X[n] --(b)->(+)--------------------> Y[n]
//                |                  |
//               (a1)<----------[ 1 sample ]
//                |                  |
//               (a2)<----------[ 1 sample ]


class HalfBiquad :  public Filter {
  public:
  float process(float input) override {
    // y[n] = bX[n] - a1Y[n-1] - a2Y[n-2]

    float output = input * b1 + sample1 * a1 + sample2 * a2;
    // std::cout << a2 << std::endl;
    sample2 = sample1;
    sample1 = output;
    // std::cout << sample1 << ", " << sample2 << std::endl;
    return output;
  }

  void setB1Coefficient(float coefficient){
      b1 = coefficient;
      // std::cout << b1 << std::endl;
  }

  void setA1Coefficient(float coefficient) {
      a1 = coefficient;
      // std::cout << a1 << std::endl;

  }

  void setA2Coefficient(float coefficient) {
      a2 = coefficient;
      // std::cout << a2 << std::endl;

  }


private:
  float b1  = { 0.0 };
  float a1 = { 0.0 };
  float a2 = { 0.0 };
  float sample1 = { 0.0 };
  float sample2 = { 0.0 };
};





class ActualBiquad : public Filter {
  public:
  float process(float input) override {
    // y[n] = bX[n] - a1Y[n-1] - a2Y[n-2]

    float output = input * b0 - sample1 * a1 - sample2 * a2 + sample4 * b1 + sample3 * b2;
    // std::cout << a2 << std::endl;
    sample2 = sample1;
    sample1 = output;
    sample4 = sample3;
    sample3 = input;
    // std::cout << sample1 << ", " << sample2 << std::endl;

    std::cout << input << " , " << output << std::endl;
    return output;
  }

  void setB0Coefficient(float coefficient){
      b0 = coefficient;
      // std::cout << b1 << std::endl;
  }

  void setB1Coefficient(float coefficient){
      b1 = coefficient;
      // std::cout << b1 << std::endl;
  }

  void setB2Coefficient(float coefficient){
      b2 = coefficient;
      // std::cout << b1 << std::endl;
  }

  void setA0Coefficient(float coefficient) {
      a0 = coefficient;
      // std::cout << a1 << std::endl;
  }

  void setA1Coefficient(float coefficient) {
      a1 = coefficient;
      // std::cout << a1 << std::endl;
  }

  void setA2Coefficient(float coefficient) {
      a2 = coefficient;
      // std::cout << a2 << std::endl;
  }


private:
  float b0  = { 0.0 };
  float b1  = { 0.0 };
  float b2  = { 0.0 };
  float a0 = { 0.0 };
  float a1 = { 0.0 };
  float a2 = { 0.0 };
  float sample1 = { 0.0 };
  float sample2 = { 0.0 };
  float sample3 = { 0.0 };
  float sample4 = { 0.0 };
};











class Biquad :  public Filter {
public:
  float process(float input) override {
    // y[n] = b0X[n] + b1X[n-1] + b2X[n-2] - a1Y[n-1] - a2Y[n-2]
    float output = input * b0 + sample1;
    sample1 = sample2 + input * b1 - output * a1;
    sample2 = input * b2 - output * a2;
    // std::cout << input << " , " << output << std::endl;
    return output;
  }

  // TODO: implement calculation in efficient manner
  //
  // float calculateW0(frequency, samplerate) {
  //   w0 = 2*M_PI*(f0/Fs);
  //   return w0;
  // }
  //
  // float calculateCosW0(w0) {
  //   cosW0 = cos(w0);
  //   return cosW0;
  // }
  //
  // float calculateSin0(w0) {
  //   sinW0 = sin(w0);
  //   return sinW0;
  // }
  //
  // float calculateAlfa(){
  //   alfa = sinW0/(2*q);
  //   return alfa;
  // }
  //
  // float calculateCoefficients(alfa, cosW0) {
  //   b1 = 1-cosW0;
  //   b0 = b2 = b1/2.0;
  //   a0 = 1+alfa;
  //   a1 = -2*cosW0;
  //   a2 = 1-alfa;
  // }

  void calculateCoefficients() {
    float w0 = 2.0f*M_PI*/static_cast<float>(sampleRate);
    float cosW0 = cos(w0);
    float sinW0 = sin(w0);
    // std::cout << w0 << ", " << sinW0 << std::endl;
    float alfa = sinW0/(2.0f*1.0f);
    float b1 = 1.0f-cosW0;
    float b0 = b1/2.0f;
    float b2 = b0;
    float a0 = 1.0f+alfa;
    float a1 = -2.0f*cosW0;
    float a2 = 1.0f-alfa;
    // std::cout << "check deze: " << a1 << ", " << a2 << ", " << b0 << ", " << b1 << ", " << b2 << std::endl;
  }

  void setA1Coefficient(float coefficient) {
    a1 = coefficient;
  }
  void setA2Coefficient(float coefficient) {
    a2 = coefficient; // chill
  }

  void setB0Coefficient(float coefficient) {
    b0 = coefficient;
  }

  void setB1Coefficient(float coefficient) {
    b1 = coefficient;
  }

  void setB2Coefficient(float coefficient) {
    b2 = coefficient;
  }

private:
  float a1 = { 0.9f };
  float a2 = { 0.94f };
  float b0 = { 0.5f };
  float b1 = { 0.4f };
  float b2 = { 0.4f };
  float sample1 = { 0.0f };
  float sample2 = { 0.0f };

  // float z1 = { 0.0 };
  // float z2 = { 0.0 };
  // float a0 = { 0.0 };
  // float f0 = { 150.0 };
  // float Fs = { 44100 };
  // float w0 = { 0.0 };
  // float w = { 0.0 };
  // float q = { 0.9 }; //ik snap deze nog niet
  // float cosW0 = { 0.0 };
  // float sinW0 = { 0.0 };
  // float alfa = { 0.0 };
};

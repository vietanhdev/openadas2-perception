#ifndef KALMAN_FILTER_H_
#define KALMAN_FILTER_H_

#include <cstdint>
#include <string>
#include <vector>

#include "simple_matrix.h"


class KalmanFilter {
public:
    KalmanFilter()
        : sigma_true(1.0), sigma_observe(1.0)
    {}


    ~KalmanFilter() {}

    void Initialize(
        const SimpleMatrix& _F,
        const SimpleMatrix& _Q,
        const SimpleMatrix& _H,
        const SimpleMatrix& _R,
        const SimpleMatrix& _X,
        const SimpleMatrix& _P
    )
    {
        F = _F;
        Q = _Q;
        H = _H;
        R = _R;
        X = _X;
        P = _P;
    }

    void Predict()
    {
        X = F * X;
        P = F * P * F.Transpose() + Q;
    }

    void Update(const SimpleMatrix& Z)
    {
        SimpleMatrix S = (H * P) * H.Transpose() + R;
        SimpleMatrix K = P * H.Transpose() * S.Inverse();
        SimpleMatrix e = Z - H * X;
        X = X + K * e;
        P = (SimpleMatrix::IdentityMatrix(K.rows) - (K * H)) * P;
    }


public:
    double sigma_true;
    double sigma_observe;

    /*** X(t) = F * X(t-1) + w(t) ***/
    /* Matrix to calculate X(t) from X(t-1) */
    SimpleMatrix F;
    /* w(t), = noise, follows Q */
    SimpleMatrix Q;

    /*** Z(t) = H * X(t) + v(t) ***/
    /* Matrix to calculate Z(observed value) from X(internal status) */
    SimpleMatrix H;
    /* v(t), = noise, follows R */
    SimpleMatrix R;

    /*** Internal status ***/
    SimpleMatrix X;
    SimpleMatrix P;

};


#endif


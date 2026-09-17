/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#include "kalman_filter.h"
#include <iostream>
#include <stdexcept>

namespace active_safety {
namespace math {

KalmanFilter::KalmanFilter(int state_dim, int measure_dim, int control_dim)
    : state_dim_(state_dim),
      measure_dim_(measure_dim),
      control_dim_(control_dim) {
    if ((state_dim <= 0)  ||  (measure_dim <= 0)  ||  (control_dim < 0)) {
        throw std::invalid_argument("Dimensions must be positive");
    }

    // 初始化矩阵大小
    F_ = Eigen::MatrixXd::Identity(state_dim, state_dim);
    H_ = Eigen::MatrixXd::Zero(measure_dim, state_dim);
    Q_ = Eigen::MatrixXd::Identity(state_dim, state_dim);
    R_ = Eigen::MatrixXd::Identity(measure_dim, measure_dim);

    if (control_dim > 0) {
        B_ = Eigen::MatrixXd::Zero(state_dim, control_dim);
    }

    // 初始状态和协方差
    x_ = Eigen::VectorXd::Zero(state_dim);
    P_ = Eigen::MatrixXd::Identity(state_dim, state_dim);
}

void KalmanFilter::init(const Eigen::MatrixXd& F,
                        const Eigen::MatrixXd& B,
                        const Eigen::MatrixXd& H,
                        const Eigen::MatrixXd& Q,
                        const Eigen::MatrixXd& R) {
    // 检查矩阵维度
    if (F.rows() != state_dim_ || F.cols() != state_dim_ ||
        H.rows() != measure_dim_ || H.cols() != state_dim_ ||
        Q.rows() != state_dim_ || Q.cols() != state_dim_ ||
        R.rows() != measure_dim_ || R.cols() != measure_dim_) {
        throw std::invalid_argument("Matrix dimensions mismatch");
    }

    if (control_dim_ > 0 &&
        (B.rows() != state_dim_ || B.cols() != control_dim_)) {
        throw std::invalid_argument("Control matrix dimensions mismatch");
    }

    F_ = F;
    B_ = B;
    H_ = H;
    Q_ = Q;
    R_ = R;
}

const Eigen::VectorXd& KalmanFilter::predict(const Eigen::VectorXd& control) {
    if ((control_dim_ > 0)  &&  (control.size() != control_dim_)) {
        throw std::invalid_argument("Control vector dimension mismatch");
    }

    // 状态预测: x = F*x + B*u
    x_ = F_ * x_;
    if (control_dim_ > 0) {
        x_ += B_ * control;
    }

    // 协方差预测: P = F*P*F' + Q
    P_ = F_ * P_ * F_.transpose() + Q_;

    return x_;
}

const Eigen::VectorXd& KalmanFilter::update(
    const Eigen::VectorXd& measurement) {
    if (measurement.size() != measure_dim_) {
        throw std::invalid_argument("Measurement dimension mismatch");
    }

    // 计算卡尔曼增益: K = P*H'*(H*P*H' + R)^-1
    Eigen::MatrixXd K =
        P_ * H_.transpose() * (H_ * P_ * H_.transpose() + R_).inverse();

    // 状态更新: x = x + K*(z - H*x)
    x_ = x_ + K * (measurement - H_ * x_);

    // 协方差更新: P = (I - K*H)*P
    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(state_dim_, state_dim_);
    P_ = (I - K * H_) * P_;

    return x_;
}

void KalmanFilter::setProcessNoiseCov(const Eigen::MatrixXd& Q) {
    if ((Q.rows() != state_dim_)  ||  (Q.cols() != state_dim_)) {
        throw std::invalid_argument("Q matrix dimension mismatch");
    }
    Q_ = Q;
}

void KalmanFilter::setMeasurementNoiseCov(const Eigen::MatrixXd& R) {
    if ((R.rows() != measure_dim_)  ||  (R.cols() != measure_dim_)) {
        throw std::invalid_argument("R matrix dimension mismatch");
    }
    R_ = R;
}

void KalmanFilter::setStateTransitionMatrix(const Eigen::MatrixXd& F) {
    if ((F.rows() != state_dim_)  ||  (F.cols() != state_dim_)) {
        throw std::invalid_argument("F matrix dimension mismatch");
    }
    F_ = F;
}

void KalmanFilter::reset(const Eigen::VectorXd& x0, const Eigen::MatrixXd& P0) {
    if (x0.size() != state_dim_ || P0.rows() != state_dim_ ||
        P0.cols() != state_dim_) {
        throw std::invalid_argument("Initial state dimensions mismatch");
    }

    x_ = x0;
    P_ = P0;
}
}  // namespace math
}  // namespace active_safety
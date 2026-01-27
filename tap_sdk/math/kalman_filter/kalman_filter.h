/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>
#include <Eigen/Dense>

namespace active_safety {
namespace math {

/*
 * 多维自适应卡尔曼滤波器实现,支持任意维度的状态空间
 */
class KalmanFilter {
 public:
    /**
     * @brief 构造函数
     * @param state_dim 状态维度
     * @param measure_dim 观测维度
     * @param control_dim 控制输入维度(可选，默认为0)
     */
    KalmanFilter(int state_dim, int measure_dim, int control_dim = 0);

    /**
     * @brief 初始化滤波器参数
     * @param F 状态转移矩阵(state_dim x state_dim)
     * @param B 控制输入矩阵(state_dim x control_dim)
     * @param H 观测矩阵(measure_dim x state_dim)
     * @param Q 过程噪声协方差矩阵(state_dim x state_dim)
     * @param R 观测噪声协方差矩阵(measure_dim x measure_dim)
     */
    void init(const Eigen::MatrixXd& F,
              const Eigen::MatrixXd& B,
              const Eigen::MatrixXd& H,
              const Eigen::MatrixXd& Q,
              const Eigen::MatrixXd& R);

    /**
     * @brief 执行卡尔曼滤波预测步骤
     * @param control 控制输入向量(可选)
     * @return 预测后的状态估计
     */
    const Eigen::VectorXd& predict(
        const Eigen::VectorXd& control = Eigen::VectorXd());

    /**
     * @brief 执行卡尔曼滤波更新步骤
     * @param measurement 观测向量
     * @return 更新后的状态估计
     */
    const Eigen::VectorXd& update(const Eigen::VectorXd& measurement);

    /**
     * @brief 获取当前状态估计
     */
    const Eigen::VectorXd& getState() const { return x_; }

    /**
     * @brief 获取当前误差协方差矩阵
     */
    const Eigen::MatrixXd& getCovariance() const { return P_; }

    /**
     * @brief 重置滤波器状态
     * @param x0 初始状态向量
     * @param P0 初始协方差矩阵
     */
    void reset(const Eigen::VectorXd& x0, const Eigen::MatrixXd& P0);

    /**
     * @brief 设置过程噪声协方差
     * @param Q 过程噪声协方差值
     */
    void setProcessNoiseCov(const Eigen::MatrixXd& Q);

    /**
     * @brief 设置测量噪声协方差
     * @param R 测量噪声协方差值
     */
    void setMeasurementNoiseCov(const Eigen::MatrixXd& R);

    /**
     * @brief 设置转换矩阵
     * @param F 转化矩阵
     */
    void setStateTransitionMatrix(const Eigen::MatrixXd& F);

 private:
    int state_dim_;    // 状态维度
    int measure_dim_;  // 观测维度
    int control_dim_;  // 控制输入维度

    // 系统模型参数
    Eigen::MatrixXd F_;  // 状态转移矩阵
    Eigen::MatrixXd B_;  // 控制输入矩阵
    Eigen::MatrixXd H_;  // 观测矩阵
    Eigen::MatrixXd Q_;  // 过程噪声协方差
    Eigen::MatrixXd R_;  // 观测噪声协方差

    // 滤波器状态
    Eigen::VectorXd x_;  // 状态估计
    Eigen::MatrixXd P_;  // 误差协方差矩阵
};
}  // namespace math
}  // namespace active_safety
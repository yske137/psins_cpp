//PSINS unit test
//Author:zqlee@whu.edu.cn
//DATE  :2017/04/11

#include "IMU_LIB/psins.h"
#include "gtest/gtest.h"

TEST(PSINSTEST, _initial)
{
  Eigen::Quaterniond qnb0(0.999995764425447, -7.249573916614352e-05, 7.273541927842237e-05, -0.002908708492192);
  Eigen::Vector3d vn0(0.085969838743798, 0.084805706657056, 0.102424996171661);
  Eigen::Vector3d pos0(0.597706189526688, 1.900832183803790, 3.843311239067717e+02);
  IMU_LIB::PSINS psinsfortest(qnb0, vn0, pos0);

  EXPECT_DOUBLE_EQ(0.999983068248932, psinsfortest.Cnb_(0, 0)) << "Cnb(0,0)";
  EXPECT_DOUBLE_EQ(0.0058173817982646887, psinsfortest.Cnb_(0, 1)) << "Cnb(0,1)";
  EXPECT_DOUBLE_EQ(1.458919603485834e-04, psinsfortest.Cnb_(0, 2)) << "Cnb(0,2)";
  EXPECT_DOUBLE_EQ(0.99998306831855055, psinsfortest.Cnb_(1, 1)) << "Cnb(1,1)";
  EXPECT_DOUBLE_EQ(1.445677319465944e-04, psinsfortest.Cnb_(1, 2)) << "Cnb(1,2)";
  EXPECT_DOUBLE_EQ(0.999999978907853, psinsfortest.Cnb_(2, 2)) << "Cnb(2,2)";
  EXPECT_DOUBLE_EQ(-1.454139964735476e-04, psinsfortest.Cnb_(2, 1)) << "Cnb(2,1)";
  EXPECT_DOUBLE_EQ(-1.450484844599421e-04,psinsfortest.Cnb_(2, 0)) << "Cnb(2,0)";
  EXPECT_DOUBLE_EQ(-0.0058174028902966256,psinsfortest.Cnb_(1, 0)) << "Cnb(1,0)";
  EXPECT_DOUBLE_EQ(-1.454139969860164e-04, psinsfortest.att_(0)) << "att(0)";
  EXPECT_DOUBLE_EQ(1.450484865020980e-04, psinsfortest.att_(1)) << "att(1)";
  EXPECT_DOUBLE_EQ(-0.0058174146721759242, psinsfortest.att_(2)) << "att(2)";
}

TEST(PSINISTEST, _update)
{
  Eigen::Vector3d wm1(-0.099134701513277898, 0.14730578886832138, 0.02722713633111154),
    wm2(-0.099134701513277898, 0.14032447186034408, 0.029321531433504733),
    wm3(-0.098436569812480182, 0.12775810124598494, 0.037699111843077518),
    wm4(-0.10262536001726656, 0.11588986233242347, 0.045378560551852569);
  Eigen::Vector3d vm1(8.1476917083333333, -0.37592158333333331, -2.4026292499999999),
    vm2(8.033280791666666, -0.40861041666666664, -2.4026292499999999),
    vm3(7.8861810416666662, -0.42495483333333334, -2.4353180833333332),
    vm4(7.8289755833333325, -0.37592158333333331, -2.4680069166666665);
  std::vector<Eigen::Vector3d> wm, vm;
  wm.push_back(wm1);
  wm.push_back(wm2);
  wm.push_back(wm3);
  wm.push_back(wm4);
  vm.push_back(vm1);
  vm.push_back(vm2);
  vm.push_back(vm3);
  vm.push_back(vm4);

  Eigen::Quaterniond qnb0(0.999995764425447, -7.249573916614352e-05, 7.273541927842237e-05, -0.002908708492192);
  Eigen::Vector3d vn0(0.085969838743798, 0.084805706657056, 0.102424996171661);
  Eigen::Vector3d pos0(0.597706189526688, 1.900832183803790, 3.843311239067717e+02);
  IMU_LIB::PSINS psinsfortest(qnb0, vn0, pos0);

  psinsfortest.Update(wm, vm, 4, 0.01);

  EXPECT_DOUBLE_EQ(0.852119771562837, psinsfortest.Cnb_(0, 0)) << "Cnb(0,0)";
  EXPECT_DOUBLE_EQ(-0.231977999063132, psinsfortest.Cnb_(0, 1)) << "Cnb(0,1)";
  EXPECT_DOUBLE_EQ(0.469124826525270, psinsfortest.Cnb_(0, 2)) << "Cnb(0,2)";
  EXPECT_DOUBLE_EQ(0.916925123594336, psinsfortest.Cnb_(1, 1)) << "Cnb(1,1)";
  EXPECT_DOUBLE_EQ(0.39788678587132753, psinsfortest.Cnb_(1, 2)) << "Cnb(1,2)";
  EXPECT_DOUBLE_EQ(0.788421208978183, psinsfortest.Cnb_(2, 2)) << "Cnb(2,2)";
  EXPECT_DOUBLE_EQ(-0.324706830344201, psinsfortest.Cnb_(2, 1)) << "Cnb(2,1)";
  EXPECT_DOUBLE_EQ(-0.522453319982946, psinsfortest.Cnb_(2, 0)) << "Cnb(2,0)";
  EXPECT_DOUBLE_EQ(0.030568339020900767, psinsfortest.Cnb_(1, 0)) << "Cnb(1,0)";
  
  EXPECT_DOUBLE_EQ(0.999983068248932, psinsfortest.Cnb0_(0, 0)) << "Cnb0(0,0)";
  EXPECT_DOUBLE_EQ(0.0058173817982646887, psinsfortest.Cnb0_(0, 1)) << "Cnb0(0,1)";
  EXPECT_DOUBLE_EQ(1.458919603485834e-04, psinsfortest.Cnb0_(0, 2)) << "Cnb0(0,2)";
  EXPECT_DOUBLE_EQ(0.99998306831855055, psinsfortest.Cnb0_(1, 1)) << "Cnb0(1,1)";
  EXPECT_DOUBLE_EQ(1.445677319465944e-04, psinsfortest.Cnb0_(1, 2)) << "Cnb0(1,2)";
  EXPECT_DOUBLE_EQ(0.999999978907853, psinsfortest.Cnb0_(2, 2)) << "Cnb0(2,2)";
  EXPECT_DOUBLE_EQ(-1.454139964735476e-04, psinsfortest.Cnb0_(2, 1)) << "Cnb0(2,1)";
  EXPECT_DOUBLE_EQ(-1.450484844599421e-04, psinsfortest.Cnb0_(2, 0)) << "Cnb0(2,0)";
  EXPECT_DOUBLE_EQ(-0.0058174028902966256, psinsfortest.Cnb0_(1, 0)) << "Cnb0(1,0)";

  EXPECT_DOUBLE_EQ(-0.33070174638114969, psinsfortest.att_(0)) << "att(0)";
  EXPECT_DOUBLE_EQ(0.585221970081742, psinsfortest.att_(1)) << "att(1)";
  EXPECT_DOUBLE_EQ(0.24779603476581344, psinsfortest.att_(2)) << "att(2)";
  
  EXPECT_DOUBLE_EQ(0.943062312911421, psinsfortest.qnb_.coeffs()(3));
  EXPECT_DOUBLE_EQ(-0.19155510890492974, psinsfortest.qnb_.coeffs()(0));
  EXPECT_DOUBLE_EQ(0.26286124812023742, psinsfortest.qnb_.coeffs()(1));
  EXPECT_DOUBLE_EQ(0.06959941418756839, psinsfortest.qnb_.coeffs()(2));
  
  EXPECT_DOUBLE_EQ(29.310124312027245, psinsfortest.vn_(0));
  EXPECT_DOUBLE_EQ(-1.6947637618592977, psinsfortest.vn_(1));
  EXPECT_DOUBLE_EQ(-18.606709546860724, psinsfortest.vn_(2));
  
  EXPECT_DOUBLE_EQ(0.597706184460760, psinsfortest.pos_(0));
  EXPECT_DOUBLE_EQ(1.900832295189213, psinsfortest.pos_(1));
  EXPECT_DOUBLE_EQ(3.839610382157579e+02, psinsfortest.pos_(2));

  EXPECT_DOUBLE_EQ(-9.800071435377495, psinsfortest.wib_(0));
  EXPECT_DOUBLE_EQ(13.366966264430491, psinsfortest.wib_(1));
  EXPECT_DOUBLE_EQ(3.687895092070441, psinsfortest.wib_(2));

  EXPECT_DOUBLE_EQ(-9.800062817103760, psinsfortest.wnb_(0));
  EXPECT_DOUBLE_EQ(13.366914744248200, psinsfortest.wnb_(1));
  EXPECT_DOUBLE_EQ(3.687844187587751, psinsfortest.wnb_(2));

  EXPECT_DOUBLE_EQ(7.306033515459526e+02, psinsfortest.fn_(0));
  EXPECT_DOUBLE_EQ(-44.488630019067877, psinsfortest.fn_(1));
  EXPECT_DOUBLE_EQ(-4.579337657807483e+02, psinsfortest.fn_(2));

  EXPECT_DOUBLE_EQ(7.309162120354432e+02, psinsfortest.fb_(0));
  EXPECT_DOUBLE_EQ(-40.171088133719310, psinsfortest.fb_(1));
  EXPECT_DOUBLE_EQ(-4.578335985870871e+02, psinsfortest.fb_(2));
}

TEST(PSINISTEST, _AlignCoarse)
{
  Eigen::Vector3d wmm(-0.099134701513277898, 0.14032447186034408, 0.029321531433504733),
    vmm(-0.098436569812480182, 0.12775810124598494, 0.037699111843077518);
  Eigen::Quaterniond qnb0(0.999995764425447, -7.249573916614352e-05, 7.273541927842237e-05, -0.002908708492192);
  Eigen::Vector3d vn0(0.085969838743798, 0.084805706657056, 0.102424996171661);
  Eigen::Vector3d pos0(0.597706189526688, 1.900832183803790, 3.843311239067717e+02);
  IMU_LIB::PSINS psinsfortest(qnb0, vn0, pos0);
  Eigen::Matrix3d align_ = psinsfortest.AlignCoarse(wmm, vmm, 0.5);
  EXPECT_DOUBLE_EQ(0.060946941345988596, align_(0, 0));
  EXPECT_DOUBLE_EQ(0.033590075628186902, align_(0, 1));
  EXPECT_DOUBLE_EQ(0.045306201663447926, align_(0, 2));
  EXPECT_DOUBLE_EQ(-0.32344235607774685, align_(1, 0));
  EXPECT_DOUBLE_EQ(0.49601913698754968, align_(1, 1));
  EXPECT_DOUBLE_EQ(0.067352853874327143, align_(1, 2));
  EXPECT_DOUBLE_EQ(-0.59431804875540417, align_(2, 0));
  EXPECT_DOUBLE_EQ(0.77134895689531202, align_(2, 1));
  EXPECT_DOUBLE_EQ(0.22761116760845268, align_(2, 2));
}
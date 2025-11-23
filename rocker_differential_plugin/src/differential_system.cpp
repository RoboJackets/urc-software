// Copyright 2023 Fictionlab sp. z o.o.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifdef USE_IGNITION

#include <ignition/gazebo/System.hh>
#include <ignition/gazebo/Model.hh>
#include <ignition/gazebo/components.hh>
#include <ignition/plugin/Register.hh>

namespace gazebo = ignition::gazebo;

#define GZ_ADD_PLUGIN IGNITION_ADD_PLUGIN

#else

#define SUPPRESS_IGNITION_HEADER_DEPRECATION
#include <gz/sim/System.hh>
#include <gz/sim/Model.hh>
#include <gz/sim/components.hh>
#include <gz/plugin/Register.hh>

namespace gazebo = gz::sim;

#endif

namespace leo_gz
{

class DifferentialSystem
  : public gazebo::System,
    public gazebo::ISystemConfigure,
    public gazebo::ISystemPreUpdate
{
  // Model entity
  gazebo::Model model_{gazebo::kNullEntity};

  // Force multiplier constant
  double force_constant_{};

  // Joint entities
  gazebo::Entity joint_a_{gazebo::kNullEntity};   // left rocker joint
  gazebo::Entity joint_b_{gazebo::kNullEntity};   // right rocker joint
  gazebo::Entity joint_bar_{gazebo::kNullEntity}; // bar (base<->bar) joint

  // Whether the system has been properly configured
  bool configured_{false};

public:
  void Configure(
      const gazebo::Entity &entity,
      const std::shared_ptr<const sdf::Element> &sdf,
      gazebo::EntityComponentManager &ecm,
      gazebo::EventManager & /*eventMgr*/) override
  {
    model_ = gazebo::Model(entity);

    if (!model_.Valid(ecm))
    {
      ignerr << "DifferentialSystem plugin should be attached to a model entity."
             << std::endl;
      return;
    }

    if (!sdf->HasElement("jointA"))
    {
      ignerr << "No jointA element present. DifferentialSystem could not be loaded." << std::endl;
      return;
    }
    auto joint_a_name_ = sdf->Get<std::string>("jointA");

    if (!sdf->HasElement("jointB"))
    {
      ignerr << "No jointB element present. DifferentialSystem could not be loaded." << std::endl;
      return;
    }
    auto joint_b_name_ = sdf->Get<std::string>("jointB");

    if (!sdf->HasElement("barJoint"))
    {
      ignerr << "No barJoint element present. DifferentialSystem could not be loaded." << std::endl;
      return;
    }
    auto joint_bar_name_ = sdf->Get<std::string>("barJoint");

    if (!sdf->HasElement("forceConstant"))
    {
      ignerr << "No forceConstant element present. DifferentialSystem could not be loaded." << std::endl;
      return;
    }
    force_constant_ = sdf->Get<double>("forceConstant");

    // Resolve joints
    joint_a_ = model_.JointByName(ecm, joint_a_name_);
    if (joint_a_ == gazebo::kNullEntity)
    {
      ignerr << "Failed to find joint named '" << joint_a_name_ << "'" << std::endl;
      return;
    }

    joint_b_ = model_.JointByName(ecm, joint_b_name_);
    if (joint_b_ == gazebo::kNullEntity)
    {
      ignerr << "Failed to find joint named '" << joint_b_name_ << "'" << std::endl;
      return;
    }

    joint_bar_ = model_.JointByName(ecm, joint_bar_name_);
    if (joint_bar_ == gazebo::kNullEntity)
    {
      ignerr << "Failed to find joint named '" << joint_bar_name_ << "'" << std::endl;
      return;
    }

    // Ensure components
    if (!ecm.EntityHasComponentType(joint_a_, gazebo::components::JointPosition().TypeId()))
    {
      ecm.CreateComponent(joint_a_, gazebo::components::JointPosition());
    }
    if (!ecm.EntityHasComponentType(joint_b_, gazebo::components::JointPosition().TypeId()))
    {
      ecm.CreateComponent(joint_b_, gazebo::components::JointPosition());
    }
    if (!ecm.EntityHasComponentType(joint_bar_, gazebo::components::JointPosition().TypeId()))
    {
      ecm.CreateComponent(joint_bar_, gazebo::components::JointPosition());
    }

    if (!ecm.EntityHasComponentType(joint_a_, gazebo::components::JointForceCmd().TypeId()))
    {
      ecm.CreateComponent(joint_a_, gazebo::components::JointForceCmd({0}));
    }
    if (!ecm.EntityHasComponentType(joint_b_, gazebo::components::JointForceCmd().TypeId()))
    {
      ecm.CreateComponent(joint_b_, gazebo::components::JointForceCmd({0}));
    }
    if (!ecm.EntityHasComponentType(joint_bar_, gazebo::components::JointForceCmd().TypeId()))
    {
      ecm.CreateComponent(joint_bar_, gazebo::components::JointForceCmd({0}));
    }

    configured_ = true;

    std::cerr << "DifferentialSystem: Configure called!" << std::endl;
    std::cerr << "Joint A: " << joint_a_name_ << ", Joint B: " << joint_b_name_
              << ", Bar Joint: " << joint_bar_name_ << std::endl;
    std::cerr << "Force constant: " << force_constant_ << std::endl;
  }

  void PreUpdate(
      const gazebo::UpdateInfo &info,
      gazebo::EntityComponentManager &ecm) override
  {
    if (!configured_ || info.paused)
      return;

    auto pos_a = ecm.Component<gazebo::components::JointPosition>(joint_a_)->Data()[0];
    auto pos_b = ecm.Component<gazebo::components::JointPosition>(joint_b_)->Data()[0];
    auto pos_bar = ecm.Component<gazebo::components::JointPosition>(joint_bar_)->Data()[0];

    // Enforce differential kinematics: if both rockers move up equally,
    // base/bar should not roll. That implies:
    //   pos_bar = 0.5 * (pos_a - pos_b)
    double error_avg = pos_bar - 0.5 * (pos_a - pos_b);

    // Distribute torques along gradient of cost 0.5*error_avg^2
    double tau_bar = -force_constant_ * error_avg;
    double tau_a =  0.5 * force_constant_ * error_avg;  // +k * 0.5 * E
    double tau_b = -0.5 * force_constant_ * error_avg;  // -k * 0.5 * E

    ecm.SetComponentData<gazebo::components::JointForceCmd>(joint_a_, {tau_a});
    ecm.SetComponentData<gazebo::components::JointForceCmd>(joint_b_, {tau_b});
    ecm.SetComponentData<gazebo::components::JointForceCmd>(joint_bar_, {tau_bar});
  }
};

} // namespace leo_gz

GZ_ADD_PLUGIN(
    leo_gz::DifferentialSystem,
    gazebo::System,
    leo_gz::DifferentialSystem::ISystemConfigure,
    leo_gz::DifferentialSystem::ISystemPreUpdate)

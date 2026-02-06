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
#include <ignition/gazebo/Link.hh>
#include <ignition/gazebo/components.hh>
#include <ignition/plugin/Register.hh>
#include <ignition/math/Quaternion.hh>
#include <ignition/math/Vector3.hh>

namespace gazebo = ignition::gazebo;
namespace math = ignition::math;

#define GZ_ADD_PLUGIN IGNITION_ADD_PLUGIN

#else

#define SUPPRESS_IGNITION_HEADER_DEPRECATION
#include <gz/sim/System.hh>
#include <gz/sim/Model.hh>
#include <gz/sim/Link.hh>
#include <gz/sim/components.hh>
#include <gz/plugin/Register.hh>
#include <gz/math/Quaternion.hh>
#include <gz/math/Vector3.hh>

namespace gazebo = gz::sim;
namespace math = gz::math;

#endif

namespace leo_gz
{

class AverageRockerPosition
  : public gazebo::System,
  public gazebo::ISystemConfigure,
  public gazebo::ISystemUpdate
{
  gazebo::Model model_{gazebo::kNullEntity};
  gazebo::Entity rocker_left_joint_, rocker_right_joint_, base_link_;
  bool configured_{false};

public:
  void Configure(
    const gazebo::Entity & entity,
    const std::shared_ptr<const sdf::Element> & sdf,
    gazebo::EntityComponentManager & ecm,
    gazebo::EventManager & /*eventMgr*/) override
  {
    model_ = gazebo::Model(entity);

    if (!model_.Valid(ecm)) {
      ignerr << "AverageRockerPosition plugin should be attached to a model entity." << std::endl;
      return;
    }

    if (!sdf->HasElement("rocker_left_joint")) {
      ignerr << "No rocker_left_joint element present." << std::endl;
      return;
    }
    auto left_joint_name = sdf->Get<std::string>("rocker_left_joint");

    if (!sdf->HasElement("rocker_right_joint")) {
      ignerr << "No rocker_right_joint element present." << std::endl;
      return;
    }
    auto right_joint_name = sdf->Get<std::string>("rocker_right_joint");

    if (!sdf->HasElement("base_link")) {
      ignerr << "No base_link element present." << std::endl;
      return;
    }
    auto base_link_name = sdf->Get<std::string>("base_link");

    rocker_left_joint_ = model_.JointByName(ecm, left_joint_name);
    if (rocker_left_joint_ == gazebo::kNullEntity) {
      ignerr << "Failed to find joint named '" << left_joint_name << "'" << std::endl;
      return;
    }

    rocker_right_joint_ = model_.JointByName(ecm, right_joint_name);
    if (rocker_right_joint_ == gazebo::kNullEntity) {
      ignerr << "Failed to find joint named '" << right_joint_name << "'" << std::endl;
      return;
    }

    base_link_ = model_.LinkByName(ecm, base_link_name);
    if (base_link_ == gazebo::kNullEntity) {
      ignerr << "Failed to find link named '" << base_link_name << "'" << std::endl;
      return;
    }

    // Ensure position components exist
    if (!ecm.EntityHasComponentType(rocker_left_joint_, gazebo::components::JointPosition().TypeId())) {
      ecm.CreateComponent(rocker_left_joint_, gazebo::components::JointPosition());
    }
    if (!ecm.EntityHasComponentType(rocker_right_joint_, gazebo::components::JointPosition().TypeId())) {
      ecm.CreateComponent(rocker_right_joint_, gazebo::components::JointPosition());
    }

    configured_ = true;
    ignmsg << "AverageRockerPosition plugin configured successfully." << std::endl;
  }

  void Update(
    const gazebo::UpdateInfo & info,
    gazebo::EntityComponentManager & ecm) override
  {
    if (!configured_ || info.paused) {return;}

    // Get joint positions (angles in radians)
    auto left_pos = ecm.Component<gazebo::components::JointPosition>(rocker_left_joint_);
    auto right_pos = ecm.Component<gazebo::components::JointPosition>(rocker_right_joint_);

    if (!left_pos || !right_pos) {return;}

    double left_angle = left_pos->Data()[0];
    double right_angle = right_pos->Data()[0];

    // Average angle (this will pitch the base_link to level position)
    double avg_angle = (left_angle + right_angle) / 2.0;

    // Get current base_link pose
    auto pose = ecm.Component<gazebo::components::Pose>(base_link_);
    if (!pose) {return;}

    math::Pose3d current_pose = pose->Data();

    // Create a rotation around Y-axis by the average angle
    // This represents the average pitch of the two rockers
    math::Quaterniond rotation(math::Vector3d(0, 1, 0), -avg_angle);

    // Update only the orientation, keep position the same
    math::Pose3d new_pose = current_pose;
    new_pose.Rot() = rotation;

    ecm.SetComponentData<gazebo::components::Pose>(base_link_, new_pose);
  }
};

}  // namespace leo_gz

GZ_ADD_PLUGIN(
  leo_gz::AverageRockerPosition,
  gazebo::System,
  leo_gz::AverageRockerPosition::ISystemConfigure,
  leo_gz::AverageRockerPosition::ISystemUpdate)

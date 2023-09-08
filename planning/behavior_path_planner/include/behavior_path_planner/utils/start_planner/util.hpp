// Copyright 2021 Tier IV, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef BEHAVIOR_PATH_PLANNER__UTILS__START_PLANNER__UTIL_HPP_
#define BEHAVIOR_PATH_PLANNER__UTILS__START_PLANNER__UTIL_HPP_

#include "behavior_path_planner/data_manager.hpp"
#include "behavior_path_planner/utils/path_safety_checker/path_safety_checker_parameters.hpp"
#include "behavior_path_planner/utils/path_safety_checker/safety_check.hpp"
#include "behavior_path_planner/utils/start_planner/pull_out_path.hpp"

#include <route_handler/route_handler.hpp>

#include <autoware_auto_perception_msgs/msg/predicted_objects.hpp>
#include <autoware_auto_perception_msgs/msg/predicted_path.hpp>
#include <autoware_auto_planning_msgs/msg/path_with_lane_id.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/twist.hpp>

#include <lanelet2_core/primitives/Primitive.h>

#include <memory>
#include <utility>
#include <vector>

namespace behavior_path_planner::start_planner_utils
{
using autoware_auto_perception_msgs::msg::PredictedObjects;
using autoware_auto_perception_msgs::msg::PredictedPath;
using autoware_auto_planning_msgs::msg::PathWithLaneId;
using behavior_path_planner::utils::path_safety_checker::EgoPredictedPathParams;
using geometry_msgs::msg::Pose;
using geometry_msgs::msg::Twist;
using route_handler::RouteHandler;

PathWithLaneId combineReferencePath(const PathWithLaneId path1, const PathWithLaneId path2);
PathWithLaneId getBackwardPath(
  const RouteHandler & route_handler, const lanelet::ConstLanelets & target_lanes,
  const Pose & current_pose, const Pose & backed_pose, const double velocity);
lanelet::ConstLanelets getPullOutLanes(
  const std::shared_ptr<const PlannerData> & planner_data, const double backward_length);
Pose getBackedPose(
  const Pose & current_pose, const double & yaw_shoulder_lane, const double & back_distance);
/**
 * @brief calculate end arc length to generate reference path considering the goal position
 * @return a pair of s_end and terminal_is_goal
 */
std::pair<double, bool> calcEndArcLength(
  const double s_start, const double forward_path_length, const lanelet::ConstLanelets & road_lanes,
  const Pose & goal_pose);
}  // namespace behavior_path_planner::start_planner_utils

#endif  // BEHAVIOR_PATH_PLANNER__UTILS__START_PLANNER__UTIL_HPP_
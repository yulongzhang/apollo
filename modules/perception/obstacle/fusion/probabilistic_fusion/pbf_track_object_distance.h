/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef MODULES_PERCEPTION_OBSTACLE_FUSION_PROBABILISTIC_FUSION_PBF_TRACK_OBJECT_DISTANCE_H_ // NOLINT
#define MODULES_PERCEPTION_OBSTACLE_FUSION_PROBABILISTIC_FUSION_PBF_TRACK_OBJECT_DISTANCE_H_ // NOLINT

#include "modules/common/macro.h"
#include "modules/perception/obstacle/base/types.h"
#include "modules/perception/obstacle/fusion/probabilistic_fusion/pbf_sensor_object.h"
#include "modules/perception/obstacle/fusion/probabilistic_fusion/pbf_track.h"

namespace apollo {
namespace perception {

struct TrackObjectDistanceOptions {
  Eigen::Vector3d *ref_point = nullptr;
};
class PbfTrackObjectDistance {
 public:
  PbfTrackObjectDistance();
  virtual ~PbfTrackObjectDistance();

  float Compute(const PbfTrackPtr &fused_track,
                const PbfSensorObjectPtr &sensor_object,
                const TrackObjectDistanceOptions &options);

 protected:
  float ComputeVelodyne64Velodyne64(const PbfSensorObjectPtr &fused_object,
                                    const PbfSensorObjectPtr &sensor_object,
                                    const Eigen::Vector3d &ref_pos,
                                    int range = 3);
  float ComputeVelodyne64Radar(const PbfSensorObjectPtr &fused_object,
                               const PbfSensorObjectPtr &sensor_object,
                               const Eigen::Vector3d &ref_pos, int range = 3);
  float ComputeRadarRadar(const PbfSensorObjectPtr &fused_object,
                          const PbfSensorObjectPtr &sensor_object,
                          const Eigen::Vector3d &ref_pos, int range = 3);

  float ComputeDistance3D(const PbfSensorObjectPtr &fused_object,
                          const PbfSensorObjectPtr &sensor_object,
                          const Eigen::Vector3d &ref_pos, int range);
  float ComputeEuclideanDistance(const Eigen::Vector3d &des,
                                 const Eigen::Vector3d &src);
  bool ComputePolygonCenter(const PolygonDType &polygon,
                            Eigen::Vector3d *center);
  bool ComputePolygonCenter(const PolygonDType &polygon,
                            const Eigen::Vector3d &ref_pos, int range,
                            Eigen::Vector3d *center);

 private:
  DISALLOW_COPY_AND_ASSIGN(PbfTrackObjectDistance);
};
}  // namespace perception
}  // namespace apollo

#endif  // MODULES_PERCEPTION_OBSTACLE_FUSION_PROBABILISTIC_FUSION_PBF_TRACK_OBJECT_DISTANCE_H_ // NOLINT
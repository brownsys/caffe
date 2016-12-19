#include <glog/logging.h>

#include <grpc++/grpc++.h>
#include "caffe/proto/deepos_app.grpc.pb.h"

namespace deepos_app {

  void output_accuracy(float accuracy);
  void output_iteration(int iteration);

}


#include <glog/logging.h>

#include <grpc++/grpc++.h>
#include "caffe/proto/deepos.grpc.pb.h"

namespace deepos {

  void output_accuracy(float accuracy);
  void output_iteration(int iteration);

}


#include "caffe/deepos.hpp"

using grpc::ClientContext;
using grpc::Status;

namespace deepos {

void output_accuracy(float accuracy) {
  LOG(INFO) << "** current accuracy: " << accuracy;

  auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
  auto stub = Greeter::NewStub(channel);

  ClientContext context;
  HelloRequest request;
  request.set_name("hello");
  request.set_number(accuracy);
  HelloReply reply;
  Status status = stub->SayHello(&context, request, &reply);
  if (status.ok()) {
    LOG(INFO) << "** RPC SUCCESSFUL!";
  } else {
    LOG(INFO) << "** RPC FAILED :(";
  }
}

void output_iteration(int iteration) {
  LOG(INFO) << "** we're on interation: " << iteration;
  auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
  auto stub = Greeter::NewStub(channel);

  ClientContext context;
  HelloRequest request;
  request.set_name("hello");
  request.set_number(iteration);
  HelloReply reply;
  Status status = stub->SayHello(&context, request, &reply);
  if (status.ok()) {
    LOG(INFO) << "** RPC SUCCESSFUL!";
  } else {
    LOG(INFO) << "** RPC FAILED :(";
  }
}

} // namespace deepos


#include "caffe/deepos_app.hpp"
#include <string>

using grpc::ClientContext;
using grpc::Status;

static const int DEEPOS_NODE_AGENT_PORT = 50022;
static const std::string DEEPOS_ADDRESS = "localhost:" + std::to_string(DEEPOS_NODE_AGENT_PORT);

namespace deepos_app {

void output_accuracy(float accuracy) {
  auto stub = ApplicationStats::NewStub(grpc::CreateChannel(DEEPOS_ADDRESS, grpc::InsecureChannelCredentials()));
  ClientContext context;
  AppStat request;
  request.set_stat_name("accuracy");
  request.set_stat(accuracy);
  AppStatReply reply;
  Status status = stub->SendAppStat(&context, request, &reply);
  if (status.ok()) {
    LOG(INFO) << "** RPC SUCCESSFUL!";
  } else {
    LOG(INFO) << "** RPC FAILED :(";
  }
}

void output_iteration(int iteration) {
  //auto stub = ApplicationStats::NewStub(grpc::CreateChannel(DEEPOS_ADDRESS, grpc::InsecureChannelCredentials()));
  //ClientContext context;
  //AppStat request;
  //request.set_stat_name("iteration");
  //request.set_stat(iteration);
  //AppStatReply reply;
  //Status status = stub->SendAppStat(&context, request, &reply);
  //if (status.ok()) {
  //  LOG(INFO) << "** RPC SUCCESSFUL!";
  //} else {
  //  LOG(INFO) << "** RPC FAILED :(";
  //}
}

void job_complete() {
  auto stub = ApplicationStats::NewStub(grpc::CreateChannel(DEEPOS_ADDRESS, grpc::InsecureChannelCredentials()));
  ClientContext context;
  AppStat request;
  request.set_stat_name("job_complete");
  AppStatReply reply;
  Status status = stub->SendAppStat(&context, request, &reply);
  if (status.ok()) {
    LOG(INFO) << "** RPC SUCCESSFUL!";
  } else {
    LOG(INFO) << "** RPC FAILED :(";
  }
}

} // namespace deepos


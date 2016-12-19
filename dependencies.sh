#!/bin/bash

# fail script on any errors
set -e 

if [ "Linux" != `uname` ]; then
  echo "Only currently support linux systems"
  exit 1
fi

sudo apt-get update

# General dependencies
sudo apt-get -y install libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev
sudo apt-get -y install --no-install-recommends libboost-all-dev
sudo apt-get -y install libatlas-base-dev python-dev

release=`lsb_release -r | awk '{print $2}'`
if [ "14.04" == "$release" ]; then
  sudo apt-get -y install libgflags-dev libgoogle-glog-dev liblmdb-dev
elif [ "16.04" != "$release" ]; then
  echo "Only support Ubuntu 14.04 and 16.04"
  exit 1
fi

# gRPC (C++)
if [ `command -v grpc_cpp_plugin` ]; then
  echo "gRPC C++ already installed";
else
  sudo apt-get -y install build-essential autoconf libtool
  git clone https://github.com/grpc/grpc 
  cd grpc
  git checkout v1.0.0
  git submodule update --init
  make
  sudo make install
  cd -
fi

# Install protobuf-3
pbuf_version=`protoc --version | awk '{print $2}'`
if [ "3.0.0" != "$pbuf_version" ]; then
  sudo apt-get -y remove libprotobuf-dev protobuf-compiler
  git clone -b v3.0.0-patch git@github.com:brownsys/protobuf.git
  cd protobuf
  sudo apt-get -y install autoconf automake libtool curl make g++ unzip
  ./autogen.sh
  ./configure
  make
  make check
  sudo make install
  sudo ldconfig 
  cd -
fi

# gRPC (Python)
sudo python -m pip install --upgrade pip
sudo python -m pip install grpcio
sudo python -m pip install grpcio-tools

# DeepOS-enabled Caffe
git clone -b deepos git@github.com:brownsys/caffe.git
cd caffe
cp Makefile.config.example Makefile.config
sed -i "s/# CPU_ONLY := 1/CPU_ONLY := 1/" Makefile.config
make all
./data/mnist/get_mnist.sh
./examples/mnist/create_mnist.sh
cd -


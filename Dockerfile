FROM ubuntu:18.04

RUN useradd xaya

RUN apt-get update && apt-get upgrade -y
#RUN apt-get install software-properties-common -y
RUN apt-get install -y \
  autotools-dev \
  automake \
  bsdmainutils \
  build-essential \
  git \
  libboost-chrono-dev \
  libboost-filesystem-dev \
  libboost-program-options-dev \
  libboost-system-dev \
  libboost-test-dev \
  libboost-thread-dev \
  libevent-dev \
  libminiupnpc-dev \
  libprotobuf-dev \
  libqrencode-dev \
  libqt5gui5 \
  libqt5core5a \
  libqt5dbus5 \
  libssl-dev \
  libtool \
  libzmq3-dev \
  pkg-config \
  protobuf-compiler \
  python3 \
  qttools5-dev \
  qttools5-dev-tools \
  software-properties-common

RUN add-apt-repository ppa:bitcoin/bitcoin 
RUN apt-get update

RUN apt-get install libdb4.8-dev libdb4.8++-dev -y

WORKDIR /usr/src
COPY . .

RUN git checkout 1.0

RUN ./autogen.sh && ./configure && make -j4 && make install

USER xaya

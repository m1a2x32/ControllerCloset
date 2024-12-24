FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

# setup all the dependencies for F' and the TM4C
RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    cmake \
    ffmpeg \
    libsm6 \
    libxext6 \
    libtool \
    pkg-config \
    libusb-1.0-0-dev \
    lm4flash \
    automake \
    libncurses-dev \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    gdb-multiarch \
    graphviz \
    stlink-tools \
    openocd

# if using GDB on the host instead of the container
EXPOSE 50000
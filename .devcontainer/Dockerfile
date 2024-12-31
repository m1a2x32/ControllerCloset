FROM debian

ENV TZ=America/New_York \
    DEBIAN_FRONTEND=noninteractive

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
    stlink-tools \
    openocd \
    usbip \
    usbutils \
    hwdata && \
    rm -rf /var/lib/apt/lists/*

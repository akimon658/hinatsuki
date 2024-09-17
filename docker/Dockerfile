# syntax=docker/dockerfile:1
FROM ubuntu:24.04

RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y \
    build-essential \
    clang \
    dosfstools \
    gnupg \
    lld \
    llvm \
    lsb-release \
    nasm \
    qemu-utils \
    software-properties-common \
    sudo \
    uuid-dev \
    wget

CMD ["/bin/bash"]

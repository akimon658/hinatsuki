# syntax=docker/dockerfile:1
FROM ubuntu:24.04

RUN rm -f /etc/apt/apt.conf.d/docker-clean; echo 'Binary::apt::APT::Keep-Downloaded-Packages "true";' > /etc/apt/apt.conf.d/keep-cache
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get install --no-install-recommends -y \
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

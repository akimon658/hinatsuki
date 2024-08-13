FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    dosfstools \
    gnupg \
    lsb-release \
    qemu-utils \
    software-properties-common \
    sudo \
    wget

RUN wget https://apt.llvm.org/llvm.sh
RUN chmod +x llvm.sh
RUN ./llvm.sh

CMD ["/bin/bash"]

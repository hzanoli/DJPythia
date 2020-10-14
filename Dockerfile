# Base image: all runtime dependencies
FROM ubuntu:20.04 as base

ARG PYTHIA_VERSION=8303
ARG NCORES=4
ARG TZ=Europe/Amsterdam
ARG ROOT_IMAGE=http://root.cern/download/root_v6.22.02.Linux-ubuntu20-x86_64-gcc9.3.tar.gz

# Set timezone
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# ROOT dependencies
RUN apt-get update  \
    && apt-get install -y --no-install-recommends \
    binutils \
    ca-certificates \
    cmake \
    dpkg-dev \
    g++ \
    gcc \
    libssl-dev \
    libx11-dev \
    libxext-dev \
    libxft-dev \
    libxpm-dev \
    python \
    wget \
    && apt-get clean


# Dependencies from DJPythia
RUN apt-get update  \
    && apt-get install -y --no-install-recommends \
    libboost-program-options-dev \
    && apt-get clean

# Installs PYTHIA8
ENV PYTHIA_IMAGE http://home.thep.lu.se/~torbjorn/pythia8/pythia${PYTHIA_VERSION}.tgz
ENV PYTHIA_DIRNAME pythia${PYTHIA_VERSION}
WORKDIR /pythia
RUN wget -O pythia8.tgz $PYTHIA_IMAGE && \
    tar -xzf pythia8.tgz && \
    rm pythia8.tgz &&\
    mv $PYTHIA_DIRNAME pythia8

RUN cd pythia8 && \
    ./configure --enable-optdebug && \
    make -j${NCORES} && \
    rm -rf pythia8/tmp

WORKDIR /root-cern
# Installs root
RUN wget -q -O root6.tag.gz $ROOT_IMAGE && tar -xzf root6.tag.gz && rm root6.tag.gz
RUN echo "source /root-cern/root/bin/thisroot.sh ">>/root/.bashrc
RUN echo /root-cern/root/lib >> /etc/ld.so.conf \
 && ldconfig

ENV ROOT_DIR /root-cern/root/cmake
ENV ROOTSYS root-cern/root/root
ENV PATH $ROOTSYS/bin:$PATH
ENV PYTHONPATH $ROOTSYS/lib:$PYTHONPATH
ENV CLING_STANDARD_PCH none

ENV PYTHIA8_ROOT_DIR /pythia/pythia8/
RUN echo "export PYTHIA8_ROOT_DIR=/pythia/pythia8/">>/root/.bashrc

FROM base as dev

RUN apt-get update  \
    && apt-get install -y \
    build-essential \
    clang \
    cmake \
    g++ \
    gcc \
    gdb \
    linux-base \
    linux-tools-common \
    linux-tools-generic \
    rsync \
    ssh \
    tar \
    valgrind \
    wget \
    && apt-get clean

RUN ( \
    echo 'PermitRootLogin yes'; \
    echo 'PasswordAuthentication yes'; \
    echo 'Subsystem sftp /usr/lib/openssh/sftp-server'; \
    ) > /etc/ssh/sshd_config_clion \
  && mkdir /run/sshd

RUN echo 'root:password' | chpasswd

CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config_clion"]

FROM base as prod


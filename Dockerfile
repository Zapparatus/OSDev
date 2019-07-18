# Start from ubuntu
FROM ubuntu:latest

# Update package lists
RUN apt-get update

# Install the cross-chain compiler
RUN cd /root && \
    apt-get install wget xz-utils -y && \
    wget http://newos.org/toolchains/i686-elf-4.9.1-Linux-x86_64.tar.xz && \
    tar xf i686-elf-4.9.1-Linux-x86_64.tar.xz

# Install the utilities to make and run
RUN apt-get install make qemu -y

# Install the utilities to create a cd
RUN apt-get install grub-pc-bin xorriso -y

# Clone the repository
RUN apt-get install git -y

ENTRYPOINT [ "/bin/bash", "-c", "cd /root && git clone https://github.com/Zapparatus/OSDev" ]